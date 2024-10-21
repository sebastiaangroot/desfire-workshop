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
      aid = mifare_desfire_aid_new(0x100000);
      res = mifare_desfire_select_application(tags[i], aid);
      if (res < 0)
        errx(EXIT_FAILURE, "Application selection failed on aid 0x100000");
      free(aid);
      printf("[+] Connected to aid 0x100000\n");

      uint8_t data[21];
      int j;
      for (j = 0; j < 1; j++) {
        res = mifare_desfire_read_data(tags[i], 0x01, 0, 20, data);
        data[20] = '\x00';
        if (res < 0)
          errx(EXIT_FAILURE, "Error reading data");
	if (strncmp(data, "flag{pla1n_m1s7ak3s}", 20) != 0)
	  errx(EXIT_FAILURE, "Wrong flag");
        printf("[+] read successful (1): ");
        //for (j = 0; j < 4; j++)
        //  printf("%02x", data[j]);
        printf("%s\n", (char*)data);
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

