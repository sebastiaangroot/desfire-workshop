#!/bin/bash


if [ ! -f './proxmark3-4.18589.tar.gz' ]; then
  echo '[!] only run this script from its own directory'
  exit 1
fi

echo '[!] This script assumes Debian / Ubuntu. Read https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/md/Installation_Instructions/Linux-Installation-Instructions.md if your setup differs'
echo "[!] press RETURN to start"
read

echo '[*] installing dependencies'
sudo apt install --no-install-recommends git ca-certificates build-essential pkg-config libreadline-dev gcc-arm-none-eabi libnewlib-dev qtbase5-dev libbz2-dev liblz4-dev libbluetooth-dev libpython3-dev libssl-dev libgd-dev

echo '[*] extracting proxmark3'
tar xf ./proxmark3-4.18589.tar.gz
cd proxmark3-4.18589

echo '[*] preparing build'
sed -e 's/^PLATFORM=PM3RDV4$/PLATFORM=PM3GENERIC/' Makefile.platform.sample > Makefile.platform

echo '[*] building...'
make clean && make -j

echo '[+] done. You can run "cd proxmark3-4.18589; sudo ./pm3" to open the proxmark3 client (or "./pm3 -o" for offline mode)'
