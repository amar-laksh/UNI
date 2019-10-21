#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : ex1.2.py
# Author            : Amar Lakshya <amar.lakshya@xaviers.edu.in>
# Date              : 07.10.2019
# Last Modified Date: 07.10.2019
# Last Modified By  : Amar Lakshya <amar.lakshya@xaviers.edu.in>
ROUNDS = 2


def key_function(K, i):
    return (K + 75 * i) % 256


def F(Ki, Pi):
    return (127 * (Ki + Pi)) % 256


def encrypt(msg, key):
    Li = msg[0]
    Ri = msg[1]
    temp = 0
    for i in range(0, ROUNDS):
        Ki = key_function(key, i)
        temp = Li ^ F(Ki, Ri)
        Li = Ri
        Ri = temp
    return [Ri, Li]


def decrypt(cipher, key):
    Li = cipher[1]
    Ri = cipher[0]
    temp = 0
    for i in range(ROUNDS, 0, -1):
        Ki = key_function(key, (i - 1))
        temp = Ri ^ F(Ki, Li)
        Ri = Li
        Li = temp
    return [Li, Ri]


print(encrypt([86, 83], 89))
