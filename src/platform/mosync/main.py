# This file is Copyright 2010 Oscar Lindberg.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.

import sys
import list
from ma import *


# Print statements end up in the log
print "MoPync - bringing the Guido goodness to the world of MoSync"

LOGO_HANDLE = 1
logo_width, logo_height = maGetImageSize(LOGO_HANDLE)

screen_width, screen_height = maGetScrSize()
background_color = 0x330055

# Create some random rectangles
rectangles = []
for _ in xrange(10):
    list.append(rectangles, [rand() % screen_width, rand() % screen_height,
                             rand() % 40 + 20, rand() % 40 + 20,
                             (rand() % 0x40) * 0x10002 + 0x883388,
                             rand() % 7 - 3, rand() % 7 - 3])


# Clear screen
maSetColor(background_color)
maFillRect(0, 0, screen_width, screen_height)

keep_going = True
while keep_going:
    sys.gc()
    # Wait for an event, or 20 ms
    maWait(1)

    # Handle all events from the event queue
    for event in maGetEvents():
        print event.__str__()
        if (event.type == EVENT_TYPE_CLOSE or
            event.type == EVENT_TYPE_KEY_PRESSED and event.key == MAK_FIRE):
            keep_going = False

    # Erase rectangles
    maSetColor(background_color)
    for rectangle in rectangles:
        x, y, w, h, c, xv, yv = rectangle
        maFillRect(x-w, y-h, w, h)

    # Erase logo
    maFillRect(screen_width-logo_width >> 1,
               screen_height-logo_height >> 1,
               logo_width, logo_height)

    # Update rectange position
    for rectangle in rectangles:
        x, y, w, h, c, xv, yv = rectangle
        rectangle[0] += xv + screen_width + w
        rectangle[0] %= screen_width + w
        rectangle[1] += yv + screen_height + h
        rectangle[1] %= screen_height + h

    # Draw pymite logo in center of screen
    maDrawImage(LOGO_HANDLE,
                screen_width-logo_width >> 1,
                screen_height-logo_height >> 1)

    # Draw rectangles
    for rectangle in rectangles:
        x, y, w, h, c, xv, yv = rectangle
        maSetColor(c)
        maFillRect(x-w, y-h, w, h)

    maUpdateScreen()

