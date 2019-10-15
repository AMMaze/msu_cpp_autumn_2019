import subprocess as sp
import sys

class ColorPrint:

    @staticmethod
    def print_fail(message, end = '\n'):
        sys.stdout.write('\x1b[1;31m' + message.strip() + '\x1b[0m' + end)

    @staticmethod
    def print_pass(message, end = '\n'):
        sys.stdout.write('\x1b[1;32m' + message.strip() + '\x1b[0m' + end)


def assert_string(inputd, expected):
    output = sp.getoutput("./calc \"" + inputd + '"')
    if (output != expected):
        ColorPrint.print_fail(inputd + ' != ' + expected, ': ')
        print('got "' + output + '"')
    else:
        ColorPrint.print_pass(inputd + ' == ' + expected)

assert_string('1+1', '2')
assert_string('1+1*2', '3')
assert_string('1*2+1', '3')
assert_string('1+1*-2', '-1')
assert_string('1', '1')
assert_string('-1', '-1')
assert_string('1+1 * 2-3', '0')
assert_string('1+f', 'Invalid character: \'f\'')
assert_string('1+', 'Invalid syntax: not enough operands')
assert_string('1 +1', '2')
assert_string('1+ 1', '2')
assert_string('1 + 1', '2')
assert_string('1+-1', '0')
assert_string('1+ -1', '0')
assert_string('1+- 1', '0')
assert_string('+', 'Invalid syntax: not enough operands')
assert_string('+1', 'Invalid syntax: not enough operands')
assert_string('1+*2', 'Invalid syntax: not enough operands')
assert_string('1 2', 'Invalid syntax')
