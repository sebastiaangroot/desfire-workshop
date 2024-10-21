# Getting familiar with DESFire

## Getting Started

If you have not done so already, prepare the proxmark3 client:

```bash
tar xf proxmark3-4.18589.tar.gz
cd proxmark3-4.18589/
sed -e 's/^PLATFORM=PM3RDV4$/PLATFORM=PM3GENERIC/' Makefile.platform.sample > Makefile.platform
make clean && make -j
```

Connect the Proxmark3 over USB and check if you can communicate with it:

```bash
./pm3
[usb] pm3 --> hw status
[#] Memory
[#]   BigBuf_size............. 41684
[#]   Available memory........ 39376
[#] Tracing
[#]   tracing ................ 1
[..]
```

Check if you can read your blank DESFire card:

```
[usb] pm3 --> hf mfdes info

[=] ---------------------------------- Tag Information ----------------------------------
[+]               UID: 04 92 17 62 0E 15 90
[+]      Batch number: 20 52 07 30 30
[+]   Production date: week 02 / 2023
[+]      Product type: MIFARE DESFire native IC (physical card)
[..]
```

## Challenges

Each challenge contains a `challenge.md` with all the context you need. All challenges are accompanied with trace files you can load into proxmark in the following way:

```
./pm3 -o
[offline] pm3 --> trace load -f ../challenges/1-top-of-the-line-security/chal1.trace
[offline] pm3 --> hf mfdes list
[..]
      Start |        End | Src | Data (! denotes parity error) | CRC | Annotation
------------+------------+-----+-------------------------------+-----+--------------------
          0 |       1056 | Rdr |26                             |     | REQA
       2228 |       4596 | Tag |44  03                         |     |
      13088 |      15552 | Rdr |93  20                         |     | ANTICOLL
[..]
```

Your goal for each challenge is to program your blank DESFire card to trick the reader into letting you through by making the LED corresponding to the challenge light up.
