#!/bin/env python
import pipes
import sys
import os

warriors = len(sys.argv) - 1
asm_files = [sys.argv[i + 1] for i in range(warriors)]
cor_files = [i + ".cor" for i in asm_files]

for i in asm_files:
    os.system("./asm " + i)

os.system("./corewar " + " ".join(cor_files) + " | ./script.py")
