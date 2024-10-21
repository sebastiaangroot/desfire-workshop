#!/bin/bash

PIN_CHAL1=4
PIN_CHAL2=5
PIN_CHAL3=6

export LD_LIBRARY_PATH=libfreefare/libfreefare/.libs/
RES=$(./bin/chal1; ./bin/chal2; ./bin/chal3)

echo ""
echo "[=========== Results ===========]"
echo ""

PIN_ARGS=""
if echo $RES | grep "successful (1)" > /dev/null; then
  echo "[+] challenge 1: success"
	PIN_ARGS="$PIN_CHAL1"
else
  echo '[!] challenge 1: fail'
fi

if echo $RES | grep "successful (2)" > /dev/null; then
  echo "[+] challenge 2: success"
	PIN_ARGS="$PIN_ARGS $PIN_CHAL2"
else
  echo '[!] challenge 2: fail'
fi

if echo $RES | grep "successful (3)" > /dev/null; then
  echo "[+] challenge 3: success"
	PIN_ARGS="$PIN_ARGS $PIN_CHAL3"
else
  echo '[!] challenge 3: fail'
fi

if [ -z $(echo "$PIN_ARGS" | tr -d " ") ]; then
	echo "All challenges failed"
	exit
fi

python ./flash.py $PIN_ARGS

