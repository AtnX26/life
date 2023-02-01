import collections
import sys

buffer = collections.deque()

try:
    line = input('>>>> ')
except EOFError:
    print()
    sys.exit(0)

buffer.append(line)

while True:
    #line = sys.stdin.readline()
    try:
        line = input('... ')
        buffer.append(line)
    except EOFError:
        print(f'\nSending {buffer} to interpreter.py')
        break
