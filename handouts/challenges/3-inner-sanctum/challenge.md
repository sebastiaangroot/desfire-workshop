# Challenge 3: Inner sanctum

You have managed to gain access to the building, but the server room is still off-limits! Turns out the admin of this room created a separate application with stricter settings for access. They even managed to hand-roll different encryption keys for each unique card. Good luck getting into this one!

At least you have managed to capture two valid traces from one working card and the reader.

Hint: The file content is in the format: `[\x00]*flag{.*}`, but to beat the challenge you must get the reader to light up the bottom LED with your own card.

## Files

- `chal3-1.trace`
- `chal3-2.trace`

## Commands

```
# programming
hf mfdes createapp --aid <app-id> --dstalgo <app cipher>
hf mfdes changekey --newalgo <app cipher> --newkeyno <key number> --newkey <hex-encoded key>
hf mfdes createfile --aid <app-id> --fid <file-id>
hf mfdes write --aid <app-id> --fid <file-id> -d <hex-encoded file contents>
```

## Hints

1. This challenge is very error-prone. There are two trace files just to allow you to more easily identify which parts of the messages you should extract. Which parts of the messages are different? How many bytes would you expect the encrypted RndA / RndB / file contents be?

2. Use the prepended null bytes in the file to your advantage! In order to cleanly decrypt the full plaintext, you would need to keep the IV state fully correct when you start decrypting the file contents. Since the file contents are prepended with known bytes, you can afford the first AES-CBC block to be mangled during decryption.

3. The chosen key scheme is the following: `(9*\x00 bytes) .. (7-byte UID)`

4. The python3 script skeleton `decrypt.py` can be used to recreate the session key and decrypt the file from the trace (requires the `pycryptodome` package)

