#!/bin/bash

echo "[+] cloning libfreefare"
git clone https://github.com/nfc-tools/libfreefare.git

echo "[+] building libfreefare"
cd libfreefare
autoreconf -vis
./configure
make
cd ..

echo "[+] compiling challenges"
make
