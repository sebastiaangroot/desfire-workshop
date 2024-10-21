# Challenge 2: Encrypted comms

Having learned from their mistakes, the security team made sure the secret access file is now marked to use an encrypted channel for file transfer. The trace below was sniffed between a working card and the reader, but the file contents look encrypted. You spot an employee in the lobby with an access card within antenna distance.

Hint: The file content is in the format: `flag{.*}`, but to beat the challenge you must get the reader to light up the middle LED with your own card.

## Files

- `chal2.trace`
- Physical Chal2 DESFire card

## Commands

```
# analysis - step 1
trace load -f ../challenges/2-encrypted-comms/chal2.trace
hf mfdes list

# analysis - step 2
hf mfdes lsapp
hf mfdes lsfiles --aid <app-id>
hf mfdes read --aid <app-id> --fid <file-id> --no-auth

# programming
hf mfdes createapp --aid <app-id>
hf mfdes createfile --aid <app-id> --fid <file-id>
hf mfdes write --aid <app-id> --fid <file-id> -d <hex-encoded file contents>
```
