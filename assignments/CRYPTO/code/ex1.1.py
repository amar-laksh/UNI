#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : ex1.1.py
# Author            : Amar Lakshya <amar.lakshya@xaviers.edu.in>
# Date              : 07.10.2019
# Last Modified Date: 07.10.2019
# Last Modified By  : Amar Lakshya <amar.lakshya@xaviers.edu.in>

from math import ceil


def encode(msg, key):
    cipher = ""
    for rails in range(0, key):
        for char in range(rails, len(msg), key):
            cipher += msg[char]
    return cipher


def decode(cipher, key):
    msg = ""
    count = ceil(len(cipher)/key)
    for rails in range(0, count):
        for c in range(rails, len(cipher), count):
            msg += cipher[c]
    return msg


def crack_cipher(cipher):
    for key in range(1, len(cipher)):
        print(decode(cipher, key))


cipher = "AVUEVLETSEISBNACBOOLEOBTILBDLCOBOOE"

crack_cipher(cipher)
