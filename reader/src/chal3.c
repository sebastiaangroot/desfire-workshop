/*-
 * Copyright (C) 2010, Romain Tartiere.
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * 
 * $Id$
 */

#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <nfc/nfc.h>

#include <freefare.h>

int
main(int argc, char *argv[])
{
    int error = EXIT_SUCCESS;
    nfc_device *device = NULL;
    FreefareTag *tags = NULL;

    if (argc > 1)
	errx (EXIT_FAILURE, "usage: %s", argv[0]);

    nfc_connstring devices[8];
    size_t device_count;
    
    nfc_context *context;
    nfc_init (&context);
    if (context == NULL)
	errx(EXIT_FAILURE, "Unable to init libnfc (malloc)");

    device_count = nfc_list_devices (context, devices, 8);
    if (device_count <= 0)
	errx (EXIT_FAILURE, "No NFC device found.");

    for (size_t d = 0; d < device_count; d++) {
        device = nfc_open (context, devices[d]);
        if (!device) {
            warnx ("nfc_open() failed.");
            error = EXIT_FAILURE;
            continue;
        }

	tags = freefare_get_tags (device);
	if (!tags) {
	    nfc_close (device);
	    errx (EXIT_FAILURE, "Error listing tags.");
	}

	for (int i = 0; (!error) && tags[i]; i++) {
	    if (MIFARE_DESFIRE != freefare_get_tag_type (tags[i]))
		continue;

	    int res;
	    char *tag_uid = freefare_get_tag_uid (tags[i]);

	    res = mifare_desfire_connect (tags[i]);
	    if (res < 0) {
		warnx ("Can't connect to Mifare DESFire target.");
		error = 1;
		break;
	    }

      printf("[+] Connected to tag with uid: %s\n", tag_uid);

      // select aid
      MifareDESFireAID aid;
      aid = mifare_desfire_aid_new(0x100002);
      res = mifare_desfire_select_application(tags[i], aid);
      if (res < 0)
        errx(EXIT_FAILURE, "Application selection failed on aid 0x100002");
      free(aid);
      printf("[+] Connected to aid 0x100002\n");

      // authenticate with key
      MifareDESFireKey key_app;
      //uint8_t key_data_app[16] = { 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
      uint8_t key_data_app[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
      int key_iter;
      char *pos = tag_uid;
      if (strlen(tag_uid) != 14) {
        errx(EXIT_FAILURE, "Tag is not 7 bytes long\n");
      }
      for (key_iter = 0; key_iter < 7; key_iter++) {
        sscanf(pos, "%2hhx", &key_data_app[9+key_iter]);
        pos += 2;
      }
      printf("key: ");
      for (key_iter = 0; key_iter < 16; key_iter++) {
        printf("%02x", key_data_app[key_iter]);
      }
      printf("\n");

      key_app = mifare_desfire_aes_key_new_with_version(key_data_app, 0);
      res = mifare_desfire_authenticate(tags[i], 1, key_app);
      if (res < 0)
        errx(EXIT_FAILURE, "Error authenticating to card");
      printf("[+] Authenticated\n");

      struct mifare_desfire_file_settings settings;
      mifare_desfire_get_file_settings(tags[i], 0x01, &settings);
      printf("cs: %d\n", settings.communication_settings);

      uint8_t data[49];
      int j;
      for (j = 0; j < 1; j++) {
        res = mifare_desfire_read_data(tags[i], 0x01, 0, 48, data);
        if (res < 0)
          errx(EXIT_FAILURE, "Error reading data");
        data[48] = '\x00';
	if (strncmp(&data[24], "flag{d3crypt_fr0m_tr4c3}", 24) != 0)
	  errx(EXIT_FAILURE, "Wrong flag");
        printf("[+] read successful (3): ");

        printf("%s\n", &data[24]);
      }
      // desfire communication here

	    free (tag_uid);

	    mifare_desfire_disconnect (tags[i]);
	}

	freefare_free_tags (tags);
	nfc_close (device);
    }
    nfc_exit (context);
    exit (error);
} /* main() */

