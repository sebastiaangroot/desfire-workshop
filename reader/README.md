# Reader

## Basic setup

The reader software uses libfreefare to implement the DESFire protocol. This project has a couple of dependencies:

- [libnfc](https://github.com/nfc-tools/libnfc)
- git
- Autotools (autoconf, automake, libtool)
- OpenSSL development package

On Debian-based systems, try:

```
apt-get install autoconf automake git libnfc libtool libssl-dev pkg-config
```

Then, to build:
```
git clone https://github.com/nfc-tools/libfreefare.git

cd libfreefare
autoreconf -vis
./configure
make
cd ..

make
```

Presenting a card to the reader and executing `./ctf_simple.sh` will print out which challenges were passed.

## Adding lights & button

Using a raspberry pi, set up the wiring as follows using 3.3V and 330 Ohm resistors for the LEDs:

- GPIO 21: button in
- GPIO 4: LED challenge 1
- GPIO 5: LED challenge 2
- GPIO 6: LED challenge 3

Configure `button_listener.py` to run continuously in the background, for example using `button_listener.service`:

```
sed -i -e 's/path_to/new_path_here/g' ./button_listener.service
cp button_listener.service /etc/systemd/system/
sudo systemctl enable --now button_listener.service
```

## Misc: configuring OMNIKEY readers for lower speeds

Proxmark3 can only sniff traffic at 106Kbps. OMNIKEY readers will try to negotiate a faster read speed, causing only the traffic up to the PPS message to show up in traces. If you want to create your own challenges and need to create traces, you will need to configure your readers to cap out at 106Kbps.

### HID OMNIKEY 5022

On Windows:
- Install latest HID OMNIKEY CCID drivers
- Install OMNIKEY WorkBench
- Connect OMNIKEY 5022
- Open "Card Protocols" tab in WorkBench for the 5022 reader
- Configure 106 Rx / Tx baud rates only for ISO14443A protocols

### HID OMNIKEY 5427 CK

This OMNIKEY will create a faux network interface allowing you to configure the device via a web UI.
- Connect OMNIKEY 5427
- Navigate to web UI (default: http://192.168.63.99)
- Open "Contactless Config" tab
- Open "ISO14443A Config" tab
- Set "Maximum Tx Baud Rate" and "Maximum Rx Baud Rate" to 106k
