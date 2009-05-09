# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
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

#
# System Test 232
# Fix pmImgCreator so two classes can have same method name
# An error during C compiling indicates a regression
#


class A():
    def __init__(self,):
        """__NATIVE__
        NATIVE_SET_TOS(PM_NONE);
        return PM_RET_OK;
        """
        pass


class B():
    def __init__(self,):
        """__NATIVE__
        NATIVE_SET_TOS(PM_NONE);
        return PM_RET_OK;
        """
        pass
