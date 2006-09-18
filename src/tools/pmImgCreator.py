#!/usr/bin/env python

# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2002 Dean Hall
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

"""
PyMite Image Creator
====================

Converts Python source files to a PyMite code image library.
Performs code filtering to ensure it will run in PyMite.
Formats the image as a raw binary file or a C file
containing a byte array.

16- and 32-bit values are in LITTLE ENDIAN order.
This matches both Python and the AVR compiler's access to EEPROM.

The order of the images in the output is undetermined.

If the Python source contains a native code declaration
and '--native-file=filename" is specified, the native code
is formatted as C functions and an array of functions and output
to the given filename.  When native functions are present, the user
should specify where the native functions should be placed-- in the
standard library or the user library--using the argument -s or -u,
respectively.

Log
---

==========      ==============================================================
Date            Action
==========      ==============================================================
2006/09/15      #28: Module with __NATIVE__ at root doesn't load
2006/09/12      #2: Separate stdlib from user app
2006/09/06      #24: Remove consts[0] == docstring assumption
2006/09/01      #11: Make src/tests/ build module images as C files, not
                header files
2006/08/25      #6: Have pmImgCreator append a null terminator to image list
2006/08/15      Added option for storing image to RAM or FLASH
2006/08/14      Smooth command line use
2006/08/10      Make command line interface work
2002/12/15      Native images reduced to four bytes!
2002/09/04      Rename from co_conv.py to pmImgCreator.py
                Refactor to use new UI.
2002/09/03      Refactor:
                    create init_globals.
                    add named consts.
2002/06/04      Remove nameoff and codeoff from code img.
2002/05/26      Add command line interface.
2002/05/25      Remove consts len and names len from code img.
2002/04/27      Add tuple as a type to encode into img.
2002/04/25      Recode to match pPyCo_t
2001/10/12      Recode to match py_code_obj and py_static_obj.
                Rename all functions *ToStr() or strTo*().
2001/10/10      Recode to match py_code_obj and py_obj_desc.
2001/10/07      First go.
==========      ==============================================================
"""


__usage__ = """USAGE:
    pmImgCreator.py [-b|c] [-s|u] [OPTIONS] -o imgfilename file0.py [files...]

    -b      Generates a raw binary file of the image
    -c      Generates a C file of the image (default)

    -s      Place native functions in the PyMite standard library (default)
    -u      Place native functions in the user library

    OPTIONS:
    --native-file=filename  If specified, pmImgCreator will write a C source
                            file with native functions from the python files.
    --memspace=ram|flash    Sets the memory space in which the image will be
                            placed (default is "ram")
    """


import exceptions, string, sys, types, dis, os, time, getopt, struct


################################################################
# CONSTANTS
################################################################

# Exit error codes (from /usr/include/sysexits.h)
EX_USAGE = 64

# remove documentation string from const pool
REMOVE_DOC_STR = 0

# XXX remap bcode values to make parsing easier
REMAP_BCODE_VALS = 0

# Py obj descriptor type constants
# Must match PyType_e in py.h
OBJ_TYPE_NON = 0x00     # None
OBJ_TYPE_INT = 0x01     # Signed integer
OBJ_TYPE_FLT = 0x02     # Floating point 32b
OBJ_TYPE_STR = 0x03     # String
OBJ_TYPE_TUP = 0x04     # Tuple (static sequence)
OBJ_TYPE_COB = 0x05     # Code obj
OBJ_TYPE_MOD = 0x06     # Module obj
OBJ_TYPE_CLO = 0x07     # Class obj
OBJ_TYPE_FXN = 0x08     # Funtion obj
OBJ_TYPE_CLI = 0x09     # Class instance
OBJ_TYPE_CIM = 0x0A     # Code image
OBJ_TYPE_NIM = 0x0B     # Native func img
OBJ_TYPE_NOB = 0x0C     # Native func obj
# All types after this never appear in an image

# Number of bytes from top of code img to start of consts
CO_IMG_FIXEDPART_SIZE = 6

# Number of bytes in a native image (constant)
NATIVE_IMG_SIZE = 4

# Maximum number of objs in a tuple
MAX_TUPLE_LEN = 127

# Maximum number of chars in a string (XXX bytes vs UTF-8 chars?)
MAX_STRING_LEN = 127

# Maximum number of chars in a code img
MAX_IMG_LEN = 32767

# String used to ID a native method
NATIVE_INDICATOR = "__NATIVE__"
NATIVE_INDICATOR_LENGTH = len(NATIVE_INDICATOR)

# String name of function table variable
NATIVE_TABLE_NAME = {"std": "std_nat_fxn_table",
                     "usr": "usr_nat_fxn_table"
                    }

# String name to prefix all native functions
NATIVE_FUNC_PREFIX = "nat_"

# maximum number of locals a native func can have
NATIVE_NUM_LOCALS = 8

# PyMite's unimplemented bytecodes (from Python 2.0)
# the commented-out bytecodes are implemented
UNIMPLEMENTED_BCODES = (
#    "STOP_CODE", "POP_TOP", "ROT_TWO", "ROT_THREE",
#    "DUP_TOP", "ROT_FOUR", "UNARY_POSITIVE",
#    "UNARY_NEGATIVE", "UNARY_NOT",
    "UNARY_CONVERT",
#    "UNARY_INVERT",
    "BINARY_POWER",
#    "BINARY_MULTIPLY", "BINARY_DIVIDE", "BINARY_MODULO",
#    "BINARY_ADD", "BINARY_SUBTRACT",
#    "BINARY_SUBSCR",
#    "SLICE+0",
    "SLICE+1", "SLICE+2", "SLICE+3", "STORE_SLICE+0",
    "STORE_SLICE+1", "STORE_SLICE+2", "STORE_SLICE+3",
#    "DELETE_SLICE+0", "DELETE_SLICE+1", "DELETE_SLICE+2",
    "DELETE_SLICE+3",
#    "INPLACE_ADD", "INPLACE_SUBTRACT",
#    "INPLACE_MULTIPLY", "INPLACE_DIVIDE", "INPLACE_MODULO",
#    "STORE_SUBSCR",
    "DELETE_SUBSCR",
#    "BINARY_LSHIFT",
#    "BINARY_RSHIFT", "BINARY_AND", "BINARY_XOR", "BINARY_OR",
    "INPLACE_POWER",
#    "PRINT_EXPR", "PRINT_ITEM", "PRINT_NEWLINE",
#    "PRINT_ITEM_TO", "PRINT_NEWLINE_TO",
#    "INPLACE_LSHIFT", "INPLACE_RSHIFT",
#    "INPLACE_AND", "INPLACE_XOR", "INPLACE_OR",
#    "BREAK_LOOP", "LOAD_LOCALS", "RETURN_VALUE",
    "IMPORT_STAR", "EXEC_STMT",
#    "POP_BLOCK",
    "END_FINALLY", "BUILD_CLASS",
#    "STORE_NAME",
    "DELETE_NAME",
#    "UNPACK_SEQUENCE", "STORE_ATTR",
    "DELETE_ATTR",
#    "STORE_GLOBAL",
    "DELETE_GLOBAL",
#    "DUP_TOPX",
#    "LOAD_CONST", "LOAD_NAME", "BUILD_TUPLE", "BUILD_LIST",
#    "BUILD_MAP", "LOAD_ATTR", "COMPARE_OP", "IMPORT_NAME",
    "IMPORT_FROM",
#    "JUMP_FORWARD", "JUMP_IF_FALSE", "JUMP_IF_TRUE",
#    "JUMP_ABSOLUTE", "FOR_LOOP", "LOAD_GLOBAL",
## The following bytecode is not present in Python 2.0
##    "CONTINUE_LOOP",
#    "SETUP_LOOP",
    "SETUP_EXCEPT",
    "SETUP_FINALLY",
#    "LOAD_FAST", "STORE_FAST",
    "DELETE_FAST",
#    "SET_LINENO", "RAISE_VARARGS", "CALL_FUNCTION", "MAKE_FUNCTION",
    "BUILD_SLICE",
## The following bytecodes are not present in Python 2.0
##    "MAKE_CLOSURE", "LOAD_CLOSURE", "LOAD_DEREF", "STORE_DEREF",
    "CALL_FUNCTION_VAR", "CALL_FUNCTION_KW",
    "CALL_FUNCTION_VAR_KW", "EXTENDED_ARG"
    )


################################################################
# GLOBALS
################################################################


################################################################
# CLASS
################################################################

class PmImgCreator:

    def __init__(self,):

        self.formatFromExt = {".c": self.format_img_as_c,
                              ".bin": self.format_img_as_bin,
                             }

        # bcode to mnemonic conversion (sparse list of strings)
        bcodes = dis.opname[:]

        # remove invalid bcodes
        for i in range(len(bcodes)):
            if bcodes[i][0] == '<':
                bcodes[i] = None

        # remove unimplmented bcodes
        for bcname in UNIMPLEMENTED_BCODES:
            # in case bcname was misspelled
            try:
                i = bcodes.index(bcname)
            except Exception, e:
                print bcname
                raise e
            bcodes[i] = None

#        # bcode remap table
#        if REMAP_BCODE_VALS:
#           bcode_remap = range(256)
#            # the following bcodes are remapped
#            # NONE YET
#            self.bcode_remap = bcode_remap

        # set class variables
        self.bcodes = bcodes

        # function renames
        self._U8_to_str = chr
        self._str_to_U8 = ord


    def set_options(self,
                    outfn,
                    imgtype,
                    imgtarget,
                    memspace,
                    nativeFilename,
                    infiles,
                   ):
        self.outfn = outfn
        self.imgtype = imgtype
        self.imgtarget = imgtarget
        self.memspace = memspace
        self.nativeFilename = nativeFilename
        self.infiles = infiles

################################################################
# CONVERSION FUNCTIONS
################################################################

    def convert_files(self,):
        """Attempts to convert all source files.
        Creates a dict whose keys are the filenames
        and values are the code object string.
        """
        # init image dict
        imgs = {"imgs": [], "fns": []}

        # init module table and native table
        self.nativemods = []
        self.nativetable = []

        # if creating usr lib, create placeholder in 0th index
        if self.imgtarget == "usr":
            self.nativetable.append((NATIVE_FUNC_PREFIX + "placeholder_func",
                                    "\n/*\n"
                                    " * Use placeholder because an index \n"
                                    " * value of zero denotes the stdlib.\n"
                                    " * This function should not be called.\n"
                                    " */\n"
                                    "return PY_RET_EX_SYS;\n"
                                   ))

        # for each src file, convert and format
        for fn in self.infiles:

            # try to compile and convert the file
            co = compile(open(fn).read(), fn, 'exec')
            imgs["fns"].append(fn)
            imgs["imgs"].append(self.co_to_str(co))

        # Append null terminator to list of images
        imgs["fns"].append("null-terminator")
        imgs["imgs"].append("\x00")

        self.imgDict = imgs
        return


    def _str_to_U16(self, s):
        """Convert two bytes from a sequence to a 16-bit word.

        The bytes are expected in little endian order.
        LSB first.
        """

        return self._str_to_U8(s[0]) | (self._str_to_U8(s[1]) << 8)


    def _U16_to_str(self, w):
        """Convert the 16-bit word, w, to a string of two bytes.

        The 2 byte string is in little endian order.
        DOES NOT INSERT TYPE BYTE.
        """

        return self._U8_to_str(w & 0xff) + \
               self._U8_to_str((w >> 8) & 0xff)


    def _seq_to_str(self, seq):
        """Convert a Python sequence to a PyMite image.

        The sequence is converted to a tuple of objects.
        This handles both co_consts and co_names.
        This is recursive to handle tuples in the const pool.
        Return string shows type in the leading byte.
        """

        # OPT
        _U8_to_str = self._U8_to_str

        # ensure tuple fits within limits
        assert len(seq) <= MAX_TUPLE_LEN

        # image string init with tuple marker and num elements
        imgstr = _U8_to_str(OBJ_TYPE_TUP) + \
                 _U8_to_str(len(seq))

        # iterate through the sequence of objects
        for i in range(len(seq)):
            obj = seq[i]
            objtype = type(obj)

            # if its a string
            if objtype == types.StringType:
                # ensure string is not too long
                assert len(obj) <= MAX_STRING_LEN
                # marker, string length, string itself
                imgstr += _U8_to_str(OBJ_TYPE_STR) + \
                          _U8_to_str(len(obj)) + obj

            # if its an integer
            elif objtype == types.IntType:
                # marker, int (little endian)
                imgstr += _U8_to_str(OBJ_TYPE_INT) + \
                          _U8_to_str(obj & 0xff) + \
                          _U8_to_str((obj >>  8) & 0xff) + \
                          _U8_to_str((obj >> 16) & 0xff) + \
                          _U8_to_str((obj >> 24) & 0xff)

            #if its a float
            elif objtype == types.FloatType:
                # marker, float (little endian)
                imgstr += _U8_to_str(OBJ_TYPE_FLT)
                # get bits of a float
                imgstr += struct.pack('f', obj)

            #if its a code object
            elif objtype == types.CodeType:
                #determine if it's native or regular
                if ((obj.co_consts[0] != None) and
                    (obj.co_consts[0][0:NATIVE_INDICATOR_LENGTH] ==
                    NATIVE_INDICATOR)):
                    imgstr += self.no_to_str(obj)
                else:
                    imgstr += self.co_to_str(obj)

            #if its a tuple
            elif objtype == types.TupleType:
                imgstr += self._seq_to_str(obj)

            #if its None
            elif objtype == types.NoneType:
                # marker, none (0)
                imgstr += _U8_to_str(OBJ_TYPE_NON)

            #other type?
            else:
                raise exceptions.NotImplementedError(
                          "Unhandled type %s." % objtype)
        return imgstr


    def co_to_str(self, co):
        """Convert a Python code object to a PyMite image.

        The code image is relocatable and goes in the device's
        memory. Return string shows type in the leading byte.
        """

        # filter code object elements
        consts, names, code, nativecode = self._filter_co(co)

        # list of strings to build image

        # set image type byte
        objtype = OBJ_TYPE_CIM

        # skip co_type and size
        # co_argcount
        imgstr = self._U8_to_str(co.co_argcount)
        # co_stacksize
        imgstr += self._U8_to_str(co.co_stacksize)
        # co_nlocals
        imgstr += self._U8_to_str(co.co_nlocals)

        # variable length objects
        # co_names
        s = self._seq_to_str(names)
        lennames = len(s)
        imgstr += s
        # co_consts
        s = self._seq_to_str(consts)
        lenconsts = len(s)
        imgstr += s

        # add code (or native index) to image
        imgstr += code

        # size = fixed part + len(names) + len(consts) + len(code)
        size = CO_IMG_FIXEDPART_SIZE + lennames + lenconsts + \
               len(code)
        # insert fixed length objects (skipped earlier)
        imgstr = self._U8_to_str(objtype) + \
                 self._U16_to_str(size) + \
                 imgstr

        # ensure string length fits within S16 type
        assert len(imgstr) <= MAX_IMG_LEN

        return imgstr


    def no_to_str(self, co):
        """Convert a native code object to a PyMite image.

        The native image is relocatable and goes in the device's
        memory. Return string shows type in the leading byte.
        """

        # filter code object elements
        consts, names, code, nativecode = self._filter_co(co)

        # list of strings to build image

        # set image type byte
        objtype = OBJ_TYPE_NIM

        # Create native image string
        # (type, argcount, funcindex)
        imgstr = (self._U8_to_str(OBJ_TYPE_NIM) +
                  self._U8_to_str(co.co_argcount) +
                  code)

        # ensure string length fits within S16 type
        assert len(imgstr) <= MAX_IMG_LEN

        return imgstr


################################################################
# FILTER FUNCTION
################################################################

    def _filter_co(self, co):
        """Run the Python code obj, co, through various filters.

        Ensure it is compliant with PyMite restrictions.

        Consts filter:
            Ensure num consts is less than 256.
            Replace __doc__ with None if present.

        Native code filter:
            If this function has a native indicator,
            extract the native code from the doc string
            and clear the doc string.
            Ensure num args is less or equal to
            NATIVE_NUM_LOCALS.

        Names/varnames filter:
            Ensure num names is less than 256.
            If co_name is root "?":
                1.  append path-less co_filename to co_names.
                2.  change "?" to trimmed module name
                    and append to co_names.
            otherwise just append the co_name.

        Bcode filter:
            Raise NotImplementedError for an invalid bcode.

        If all is well, return the filtered consts list,
        names list, code string and native code.
        """

        ## General filter
        # ensure values fit within S8 type size
        assert len(co.co_consts) < 128
        assert len(co.co_names) < 128
        assert co.co_argcount < 128
        assert co.co_stacksize < 128
        assert co.co_nlocals < 128

        # make consts a list so a single element can be modified
        consts = list(co.co_consts)
        # get trimmed src file name and module name
        fn = os.path.basename(co.co_filename)
        mn = os.path.splitext(fn)[0]
        # init native code
        nativecode = None

        ## Bcode filter
        # bcode string
        s = co.co_code
        # filtered code string
        code = ""
        # iterate through the string
        lno = 0
        i = 0
        len_s = len(s)
        while i < len_s:

            #get char
            c = ord(s[i])

            #ensure no illegal bytecodes are present
            if self.bcodes[c] == None:
                raise NotImplementedError(
                        "Illegal bytecode (%d/%s/%s) "
                        "comes at offset %d in file %s." %
                        (c, hex(c), dis.opname[c],
                         i, co.co_filename))

            #if simple bcode, copy one byte
            if c < dis.HAVE_ARGUMENT:
                code += s[i]
                i += 1

            #else copy three bytes
            else:
                code += s[i:i+3]
                i += 3

        # if the first const is a String,
        if (type(consts[0]) == types.StringType):

            ## Native code filter
            # if this CO is intended to be a native func.
            if (consts[0][:NATIVE_INDICATOR_LENGTH] ==
                NATIVE_INDICATOR):

                # ensure num args is less or equal
                # to NATIVE_NUM_LOCALS
                assert co.co_nlocals <= NATIVE_NUM_LOCALS

                # extract native code and clear doc string
                nativecode = consts[0][NATIVE_INDICATOR_LENGTH:]
                consts[0] = None

                # If this co is a module
                # Issue #28: Module root, "?", must keep its bytecode
                if co.co_name == "?":
                    self.nativemods.append((co.co_filename, nativecode))

                # Else this co is a function;
                # replace code with native table index
                else:
                    # stdlib code gets a positive index
                    if self.imgtarget == "std":
                        code = self._U16_to_str(len(self.nativetable))
                    # usr code gets a negative index
                    else:
                        code = self._U16_to_str(-len(self.nativetable))

                    # native function name is
                    # "nat_<modname>_<pyfuncname>".
                    # append (nat func name, nat code) to table
                    self.nativetable.append((NATIVE_FUNC_PREFIX +
                                             mn + "_" + co.co_name,
                                            nativecode))

            ## Consts filter
            # if want to remove __doc__ string
            # WARNING: this heuristic is not always accurate
            elif REMOVE_DOC_STR and co.co_names[0] == "__doc__":
                consts[0] = None

        ## Names filter
        names = list(co.co_names)
        # if co_name is "?" change it to module name
        if co.co_name == '?':
            # append trimmed filename and module name
            names.append(fn) # XXX remove, not needed
            # append module name (filename without extension)
            names.append(mn)
        # else use unmodified co_name
        else:
            names.append(co.co_name)


        return consts, names, code, nativecode


################################################################
# IMAGE WRITING FUNCTIONS
################################################################

    def write_image_file(self,):
        """Writes an image file
        """
        fmtfxn = self.formatFromExt[self.imgtype]
        f = open(self.outfn, 'w')
        f.write(fmtfxn())
        f.close()

    def write_native_file(self,):
        """Writes native functions if filename was given
        """
        if not self.nativeFilename:
            return
        f = open(self.nativeFilename, 'w')
        f.write(self.format_native_table())
        f.close()


    def format_img_as_bin(self,):
        """format_img_as_bin() --> string

        Write image bytes to raw binary string.
        The resulting string is suitable to write to a file.
        """

        # no reformatting necessary, join all object images
        return string.join(self.imgDict["imgs"], "")


    def format_img_as_c(self,):
        """format_img_as_c() --> string

        Format image bytes to a string that is a C byte array.
        The C byte array can be located in RAM
        or program memory.  The byte array is named lib_img.
        """

        # list of filenames
        fns = self.imgDict["fns"]
        imgs = self.imgDict["imgs"]

        # create intro
        fileBuff = []
        fileBuff.append("/**\n"
                        " * PyMite library image file.\n"
                        " *\n"
                        " * Automatically created from:\n"
                        " * \t%s\n"
                        " * by pmImgCreator.py on\n"
                        " * %s.\n"
                        " * \n"
                        " * Byte count: %d\n"
                        " * \n"
                        " * Selected memspace type: %s\n"
                        " * \n"
                        " * DO NOT EDIT THIS FILE.\n"
                        " * ANY CHANGES WILL BE LOST.\n"
                        " */\n\n"
                        % (string.join(fns, "\n *\t"),
                           time.ctime(time.time()),
                           len(string.join(imgs, "")),
                           self.memspace.upper()
                          )
                       )
        fileBuff.append("/* Place the image into %s */\n"
                        "unsigned char\n"
                        % self.memspace.upper()
                       )

        if self.memspace.lower() == "flash":
            fileBuff.append("#if defined(__AVR__)\n"
                            "__attribute__((progmem))\n"
                            "#endif\n"
                           )

        fileBuff.append("%slib_img[] =\n"
                        "{\n"
                        % (self.imgtarget)
                       )

        # for each src file, convert and format
        i = 0
        for fn in fns:

            # get img string for this file
            img = imgs[i]
            i += 1

            # print all bytes
            fileBuff.append("\n\n/* %s */" % fn)
            j = 0
            while j < len(img):
                if (j % 8) == 0:
                    fileBuff.append("\n    ")
                fileBuff.append("0x%02X, " % ord(img[j]))
                j += 1

        # finish off array
        fileBuff.append("\n};\n")

        return string.join(fileBuff, "")


    def format_native_table(self,):
        """format_native_table() --> string

        Format native table to a C file containing
        native functions and a function table.
        """
        # create intro
        fileBuff = []
        fileBuff.append("#undef __FILE_ID__\n"
                        "#define __FILE_ID__ 0x0A\n"
                        "/**\n"
                        " * PyMite %s native function file\n"
                        " *\n"
                        " * automatically created by pmImgCreator.py\n"
                        " * on %s\n"
                        " *\n"
                        " * DO NOT EDIT THIS FILE.\n"
                        " * ANY CHANGES WILL BE LOST.\n"
                        " *\n"
                        " * @file    %s\n"
                        " */\n\n"
                        "#define __IN_LIBNATIVE_C__\n"
                        "#include \"py.h\"\n\n"
                        % (self.imgtarget,
                           time.ctime(time.time()),
                           self.nativeFilename
                          )
                       )

        # module-level native sections (for #include headers)
        for (modname, modstr) in self.nativemods:
            fileBuff.append("/* From: %s */%s\n" % (modname, modstr))

        # for each entry create fxn
        for (funcname, funcstr) in self.nativetable:
            fileBuff.append("static PyReturn_t\n"
                            "%s(pPyFrame_t pframe, signed char numargs)\n"
                            "{\n"
                            "%s\n"
                            "}\n\n" % (funcname, funcstr))

        # create fxn table
        fileBuff.append("/* native function lookup table */\n"
                        "PyReturn_t (* %s[])(pPyFrame_t, signed char) =\n"
                        "{\n" % (NATIVE_TABLE_NAME[self.imgtarget]))

        # put all native funcs in the table
        for (funcname, funcstr) in self.nativetable:
            fileBuff.append("    %s,\n" % funcname)
        fileBuff.append("};\n")

        return string.join(fileBuff, "")


################################################################
# MAIN
################################################################

def parse_cmdline():
    """Parses the command line for options.
    """
    try:
        opts, args = getopt.getopt(sys.argv[1:],
                                   "bcsuo:",
                                   ["memspace=", "native-file="])
    except:
        print __usage__
        sys.exit(EX_USAGE)

    # Parse opts for the image type to write
    imgtype = ".c"
    imgtarget = "std"
    memspace = "ram"
    outfn = None
    nativeFilename = None
    for opt in opts:
        if opt[0] == "-b":
            imgtype = ".bin"
        elif opt[0] == "-c":
            imgtype = ".c"
        elif opt[0] == "-s":
            imgtarget = "std"
        elif opt[0] == "-u":
            imgtarget = "usr"
        elif opt[0] == "--memspace":
            # Error if memspace switch given without arg
            if not opt[1] or (opt[1].lower() not in ["ram", "flash"]):
                print "Only one of these memspace types allowed: ram, flash"
                print __usage__
                sys.exit(EX_USAGE)
            memspace = opt[1]
        elif opt[0] == "--native-file":
            # Error if switch given without arg
            if not opt[1]:
                print "Specify a filename like this: --native-file=libnative.c"
                print __usage__
                sys.exit(EX_USAGE)
            nativeFilename = opt[1]
        elif opt[0] == "-o":
            # Error if out filename switch given without arg
            if not opt[1]:
                print __usage__
                sys.exit(EX_USAGE)
            outfn = opt[1]

    # Error if no image type was given
    if not imgtype:
        print __usage__
        sys.exit(EX_USAGE)

    # Error if no input filenames are given
    if len(args) == 0:
        print __usage__
        sys.exit(EX_USAGE)

    return outfn, imgtype, imgtarget, memspace, nativeFilename, args


def main():
    pic = PmImgCreator()
    outfn, imgtyp, imgtarget, memspace, natfn, fns = parse_cmdline()
    pic.set_options(outfn, imgtyp, imgtarget, memspace, natfn, fns)
    pic.convert_files()
    pic.write_image_file()
    pic.write_native_file()


if __name__ == "__main__":
    main()
