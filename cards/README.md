# Workshop Card Info

## Overview

The workshop uses three card types:

- Blank cards for participants
- Master card programmed to pass all challenges (legitimately)
- Challenge 2 card programmed to pass challenge 2 (legitimately)

## Challenge 1

### Card Prep

```
# create app
hf mfdes createapp --aid 100000 --dstalgo AES --no-auth

# create file with weak access permissions
hf mfdes createfile --aid 100000 --fid 01 --rrights free --wrights key1 --rwrights key1 --chrights key1 --size 000014 --no-auth
hf mfdes lsfiles --aid 100000 --no-auth

# set key1 for aid 100000
hf mfdes changekey --aid 100000 --newkeyno 1 --newalgo AES --newkey 00000000000000000000000000000001 -t AES -n 0 -k 00000000000000000000000000000000

# write file data
hf mfdes write --aid 100000 --fid 01 -t AES -k 00000000000000000000000000000001 -n 1 -d 666c61677b706c61316e5f6d317337616b33737d

# test
hf mfdes read --aid 100000 --fid 01 --no-auth
```

### Solution

```
echo "66  6c  61  67  7b  70  6c  61  31  6e  5f  6d  31  73  37  61 6b  33  73  7d " | tr -d " " | xxd -r -p
flag{pla1n_m1s7ak3s}
```

## Challenge 2

### Card Prep

```
# create app
hf mfdes createapp --aid 100001 --dstalgo DES --no-auth

# create file with weak access permissions
hf mfdes createfile --aid 100001 --fid 01 --amode encrypt --rrights free --wrights key1 --rwrights key1 --chrights key1 --size 00001e --no-auth

# set key1 for aid 100001
hf mfdes changekey --aid 100001 --newkeyno 1 --newalgo DES --newkey 0000000000000001 -n 0 -k 0000000000000000

# write file data
hf mfdes write --aid 100001 --fid 01 -k 0000000000000001 -n 1 -t DES -d 666c61677b347537685f346c6f6e335f69355f6e30375f336e6f7539687d

# test
hf mfdes read --aid 100001 --fid 01 -k 0000000000000001 -n 1 -t DES
```

### Solution

```
echo "66 6C 61 67 7B 34 75 37 68 5F 34 6C 6F 6E 33 5F 69 35 5F 6E 30 37 5F 33 6E 6F 75 39 68 7D" | tr -d " " | xxd -r -p
flag{4u7h_4lon3_i5_n07_3nou9h}
```

## Challenge 3

### Card Prep

```
# create app
hf mfdes createapp --aid 100002 --dstalgo AES --no-auth

# create file
hf mfdes createfile --aid 100002 --fid 01 --amode encrypt --rrights key1 --wrights key1 --rwrights key1 --chrights key1 --size 000030 --no-auth

# set key 1 for aid 100002 (change key to 0's followed by YOUR card's 7-byte UID)
hf mfdes changekey --aid 100002 --newalgo AES --newkeyno 1 --newkey 000000000000000000'7-byte-uid' -t AES -n 0 -k 00000000000000000000000000000000

# write file data
hf mfdes write --aid 100002 -n 1 -t AES -k 000000000000000000'7-byte-uid' -d 000000000000000000000000000000000000000000000000666c61677b643363727970745f6672306d5f74723463337d

# test
hf mfdes read --aid 100002 -n 1 -t AES -k 000000000000000000'7-byte-uid'
```

### Solution

```
\x00*24 .. flag{d3crypt_fr0m_tr4c3}
```
