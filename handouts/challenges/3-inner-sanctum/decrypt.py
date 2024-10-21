#!/usr/bin/env python3

import binascii
from Crypto.Cipher import AES # from pycryptodome

# Message & key material
msg1 = binascii.unhexlify('<16-byte hexstring for msg1>')
msg2 = binascii.unhexlify('<32-byte hexstring for msg2>')
key =  9 * b'\x00' + binascii.unhexlify('<7-byte uid hexstring>')
iv  = 16 * b'\x00'
ciphertext = binascii.unhexlify('<48-byte file ciphertext hexstring>')

print(f'AES input:\nmsg1: {binascii.hexlify(msg1)}\nmsg2: {binascii.hexlify(msg2)}\nkey: {binascii.hexlify(key)}\niv: {binascii.hexlify(iv)}')

# Recover RndB from msg1
cipher = AES.new(key, AES.MODE_CBC, iv=iv)
RndB = cipher.decrypt(msg1)

# Recover RndA from msg2
tmp = cipher.decrypt(msg2)
RndA = tmp[:16]

# Construct session key
sesskey = RndA[:4] + RndB[:4] + RndA[12:] + RndB[12:]

print(f'RndA: {binascii.hexlify(RndA)}\nRndB: {binascii.hexlify(RndB)}')
print(f'SessKey: {binascii.hexlify(sesskey)}')

# Decrypt encrypted file contents
cipher = AES.new(sesskey, AES.MODE_CBC, iv=iv)
plaintext = cipher.decrypt(ciphertext)
print(f'Ciphertext: {binascii.hexlify(ciphertext)}\nPlaintext: {plaintext}')



