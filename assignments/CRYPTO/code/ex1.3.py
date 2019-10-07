#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# File              : ex1.3.py
# Author            : Amar Lakshya <amar.lakshya@xaviers.edu.in>
# Date              : 07.10.2019
# Last Modified Date: 07.10.2019
# Last Modified By  : Amar Lakshya <amar.lakshya@xaviers.edu.in>

import sys
sys.path.insert(1, 'des')
from des import DesKey
key = DesKey(b"00000000", rounds=1)
print(key.encrypt(b"00000000").hex())
