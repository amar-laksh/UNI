#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : ex1.3.py
# Author            : Amar Lakshya <amar.lakshya@xaviers.edu.in>
# Date              : 07.10.2019
# Last Modified Date: 07.10.2019
# Last Modified By  : Amar Lakshya <amar.lakshya@xaviers.edu.in>

import sys
sys.path.insert(1, 'pydes')
from pydes import des


def h2b(byte_string):
    return bytes.fromhex(byte_string)


key = h2b("0000000000000000")
msg = h2b("0000000000000000")

d = des(rounds=1)
cipher = d.encrypt(key, msg)

cipher = ' '.join(format(ord(x), 'b') for x in cipher)

print("The ciphertext after 1 round: %s" % cipher)
