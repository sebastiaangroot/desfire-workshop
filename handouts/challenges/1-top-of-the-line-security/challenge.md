# Challenge 1: Top of the line security

The security team bought these new fancy DESFire cards and quickly implemented a secret access code on the cards. The readers are programmed to read the secret access code from the cards and only allow access when the returned value is correct. The trace below was sniffed between a working card and the reader.

Hint: The file content is in the format: `flag{.*}`, but to beat the challenge you must get the reader to light up the top LED with your own card.

## Files

- `chal1.trace`

## Commands

```
# analysis
trace load -f ../challenges/1-top-of-the-line-security/chal1.trace
hf mfdes list

# programming
hf mfdes createapp --aid <app-id>
hf mfdes createfile --aid <app-id> --fid <file-id>
hf mfdes write --aid <app-id> --fid <file-id> -d <hex-encoded file contents>
```
