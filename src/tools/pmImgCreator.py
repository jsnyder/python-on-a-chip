#!/usr/bin/env python
"""
PyMite Image Creator
====================

Converts Python source files to a PyMite code image library.
Performs code filtering to ensure it will run in PyMite.
Formats the image as a C header file containing a byte array
or a raw binary file.

16- and 32-bit values are in LITTLE ENDIAN order.
This matches both Python and the AVR compiler's access to EEPROM.

The order of the images in the file is undetermined.
PyMite scans the images and makes a dict of available code objects.

If the Python source contains a native code declaration
and '--native-file=filename" is specified, the native code
is formatted as C functions and an array of functions and output
to the given filename.

Log
---

==========      ==============================================================
Date            Action
==========      ==============================================================
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


__author__ = "Dean Hall"
__copyright__ = "Copyright 2002 Dean Hall.  All rights reserved."
__version__ = (0, 0, 7)
__date__  = "2006/08/10"
__usage__ = """USAGE:
    pmImgCreator.py [-b|h] [OPTIONS] -o imgfilename infile0.py [infileN.py ...]

    -b                      Generates a raw binary file of the image
    -h                      Generates a C header file of the image (default)

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

# remove documentation string from const pool
REMOVE_DOC_STR = 1

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
NATIVE_TABLE_NAME = "nat_fxn_table"

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
    "END_FINALLY",
#    "BUILD_CLASS", "STORE_NAME",
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
    "CONTINUE_LOOP",
#    "SETUP_LOOP",
    "SETUP_EXCEPT",
    "SETUP_FINALLY",
#    "LOAD_FAST", "STORE_FAST",
    "DELETE_FAST",
#    "SET_LINENO",
    "RAISE_VARARGS",
#    "CALL_FUNCTION", "MAKE_FUNCTION",
    "BUILD_SLICE", "MAKE_CLOSURE", "LOAD_CLOSURE",
    "LOAD_DEREF", "STORE_DEREF",
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

    def __init__(self, ui=False,):

        self.formatFromExt = {".h": self.format_img_as_h,
                              ".bin": self.format_img_as_bin,
                              ".s19": self.format_img_as_s19,
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


    def set_input(self, outfn=None, imgtype=".h", infiles=None):
        self.outfn = outfn
        self.imgtype = imgtype
        self.infiles = infiles

    def set_options(self, memspace=None, nativeFilename=None):
        if not memspace:
            memspace = "ram"
        self.memspace = memspace
        self.nativeFilename = nativeFilename

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

        # init native table
        self.nativetable = []

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
        if nativecode:
            objtype = OBJ_TYPE_NIM

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
        # XXX it's most likely a docstring.
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

                # replace code with native table index
                code = self._U16_to_str(len(self.nativetable))

                # native function name is
                # "nat_<modname>_<pyfuncname>".
                # append (nat func name, nat code) to table
                self.nativetable.append((NATIVE_FUNC_PREFIX +
                                         mn + "_" + co.co_name,
                                        nativecode))

            ## Consts filter
            # if want to remove __doc__ string
            # XXX this assumes a string in the 0th const
            # is always __doc__.
            elif REMOVE_DOC_STR:
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


    def format_img_as_h(self,):
        """format_img_as_h() --> string

        Format image bytes to a C header format string.
        The C header file defines a byte array in RAM
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
        if self.memspace.lower() == "flash":
            fileBuff.append("#if not defined(__AVR__)\n"
                            "#error Defining image memspace for "
                            "non-AVR-devices is not supported!\n"
                            "#endif\n"
                           )
            fileBuff.append("/* Place the image into FLASH */\n"
                            "unsigned char __attribute__((progmem))\n"
                            "lib_img[] =\n"
                           )
        else:
            fileBuff.append("/* Place the image into RAM */\n"
                            "unsigned char\n"
                            "lib_img[] =\n"
                           )

        fileBuff.append("{\n");

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


    def format_img_as_s19(self, img):
        """format_img_as_s19(img) --> string

        Format image bytes to Motorola S-Record format string.
        The resulting string is suitable to write to a file.
        """
        pass


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
                        " * PyMite native function file\n"
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
                        % (time.ctime(time.time()), self.nativeFilename)
                       )

        # module-level native sections (for #include headers)
        for (funcname, funcstr) in self.nativetable:
            if funcname[-1:] == "?":
                fileBuff.append("/* From: %s */%s\n"
                                % (funcname[len(NATIVE_FUNC_PREFIX):-2],
                                   funcstr)
                               )

        # for each entry create fxn
        for (funcname, funcstr) in self.nativetable:
            if funcname[-1:] != "?":
                fileBuff.append("static PyReturn_t\n"
                                "%s(pPyFrame_t pframe, signed char numargs)\n"
                                "{\n"
                                "%s\n"
                                "}\n\n" % (funcname, funcstr))

        # create fxn table
        fileBuff.append("/* native function lookup table */\n"
                        "PyReturn_t (* %s[])(pPyFrame_t, signed char) =\n"
                        "{\n" % (NATIVE_TABLE_NAME))
        for (funcname, funcstr) in self.nativetable:
            if funcname[-1:] != "?":
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
                                   "bhso:",
                                   ["memspace=", "native-file="])
    except:
        print __usage__
        sys.exit(2)

    # Parse opts for the image type to write
    imgtype = ".h"
    outfn = None
    memspace = None
    nativeFilename = None
    for opt in opts:
        if opt[0] == "-b":
            imgtype = ".bin"
        elif opt[0] == "-h":
            imgtype = ".h"
        elif opt[0] == "--memspace":
            # Error if memspace switch given without arg
            if not opt[1] or (opt[1].lower() not in ["ram", "flash"]):
                print "Only one of these memspace types allowed: ram, flash"
                print __usage__
                sys.exit(2)
            memspace = opt[1]
        elif opt[0] == "--native-file":
            # Error if switch given without arg
            if not opt[1]:
                print "Specify a filename like this: --native-file=libnative.c"
                print __usage__
                sys.exit(2)
            nativeFilename = opt[1]
        elif opt[0] == "-o":
            # Error if out filename switch given without arg
            if not opt[1]:
                print __usage__
                sys.exit(2)
            outfn = opt[1]

    # Error if no image type was given
    if not imgtype:
        print __usage__
        sys.exit(2)

    # Error if no input filenames are given
    if len(args) == 0:
        print __usage__
        sys.exit(2)

    return outfn, imgtype, args, memspace, nativeFilename


def main():
    fn, imgtype, infiles, memspace, nativeFilename = parse_cmdline()
    pic = PmImgCreator()
    pic.set_input(outfn=fn,
                  imgtype=imgtype,
                  infiles=infiles
                 )
    pic.set_options(memspace=memspace,
                    nativeFilename=nativeFilename
                   )
    pic.convert_files()
    pic.write_image_file()
    pic.write_native_file()


if __name__ == "__main__":
    main()
