#!/bin/bash

export LD_LIBRARY_PATH=libfreefare/libfreefare/.libs/
RES=$(./bin/chal1; ./bin/chal2; ./bin/chal3)

echo ""
echo "[=========== Results ===========]"
echo ""

if echo $RES | grep "successful (1)" > /dev/null; then
  echo "[+] challenge 1: success"
else
  echo '[!] challenge 1: fail'
fi

if echo $RES | grep "successful (2)" > /dev/null; then
  echo "[+] challenge 2: success"
else
  echo '[!] challenge 2: fail'
fi

if echo $RES | grep "successful (3)" > /dev/null; then
  echo "[+] challenge 3: success"
else
  echo '[!] challenge 3: fail'
fi

