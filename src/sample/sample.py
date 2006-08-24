#
# sample.py
#
# This is a sample application that calls native functions.
#

import mmb


def main():
    # init the library
    mmb.init()

    # beep four times
    for i in range(4):
        mmb.beep(440, 500)
        mmb.sleepms(500)

    # print a message on the lcd
    mmb.lcdPrintStr("hell, oh, world!")


main()
