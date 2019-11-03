#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : ex1.4.py
# Author            : Amar Lakshya <amar.lakshya@xaviers.edu.in>
# Date              : 09.10.2019
# Last Modified Date: 09.10.2019
# Last Modified By  : Amar Lakshya <amar.lakshya@xaviers.edu.in>
import sys
sys.path.insert(1, 'Python-AES')
from AES import *

plaintext = "00000000000000000000000000000000"
key = "ffffffffffffffffffffffffffffffff"
key = process_key(key, 4)
Nr = 1
expanded_key = KeyExpansion(key, 4, 4, Nr)


block = process_key(plaintext)

#  Printing out subkeys
print("key:\t {0}".format(str_block_line(expanded_key)))
c = 0
for i in range(0, (32 * Nr) + 1, 32):
    print("k{}:\t{}".format(c, str_block_line(expanded_key)[i:i+32]))
    c += 1
print("PLAINTEXT:\t {0}".format(plaintext))


block = Cipher(block, expanded_key, 4, 4, Nr)
print("ENCRYPTED:\t {0}".format(str_block_line(block)))

block = InvCipher(block, expanded_key, 4, 4, Nr)
print("DECRYPTED:\t {0}".format(str_block_line(block)))
