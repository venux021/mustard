#!/usr/bin/env python
# -*- encoding: utf-8 -*-
import os
import subprocess
import sys

if len(sys.argv) < 3:
    print 'usage: python mustard.py <CMD> <MODULE>'
    print '\t\t CMD - crun | run'
    exit()

cmd = sys.argv[1]
module = sys.argv[2]

cmd_supports = set(['crun', 'run'])
if cmd not in cmd_supports:
    print 'unknown CMD: ' + cmd
    exit()

if cmd == 'crun':
    command = 'g++ -o {0}.out {1}.cpp'.format(module, module)
    code = os.system(command)
    if code != 0:
        exit()

# cmd == 'run'
input_file_path = module + '.input'
lines = []
with open(input_file_path) as fin:
    lines = fin.readlines()
lines.append('\n')

exe_file = './' + module + '.out'
inputs = []
for i in xrange(0, len(lines)):
    if len(lines[i].strip()) == 0:
        if len(inputs) == 0:
            continue
        p = subprocess.Popen(exe_file, stdin=subprocess.PIPE)
        for line in inputs:
            p.stdin.write(line)
        p.stdin.close()
        p.wait()
        inputs = []
    else:
         inputs.append(lines[i])

