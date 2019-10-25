#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : ex1.4.py
# Author            : Amar Lakshya <amar.lakshya@xaviers.edu.in>
# Date              : 09.10.2019
# Last Modified Date: 09.10.2019
# Last Modified By  : Amar Lakshya <amar.lakshya@xaviers.edu.in>
import sys
sys.path.insert(1, 'pydes')
from pydes import des


def h2b(byte_string):
    return bytes.fromhex(byte_string)


key = h2b("0000000000000000")
x = h2b("0000000000000000")
y = h2b("0008000000000000")


for i in range(1, 17):
    print("ROUND %i:" % i)

    d = des(rounds=i)
    cipher_x = d.encrypt(key, x)
    cipher_y = d.encrypt(key, y)

    cipher_x = int.from_bytes(bytes(cipher_x, "UTF-8"), "little")
    cipher_y = int.from_bytes(bytes(cipher_y, "UTF-8"), "little")

    # XOR operation can be used to get the number of different bits
    diff_x_y = ((cipher_x) ^ (cipher_y))

    print(hex(cipher_x))
    print(hex(cipher_y))
    print("NUMBER OF BITS DIFFERENT: %s" % bin(diff_x_y).count('1'))
