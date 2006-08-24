#!/usr/bin/python
"""
#
# Dean Hall
#
# dismantle.py
#
# Dismantle a .py file by compiling it
# into a code object and recursively dismantling
# and disassembling the code object.
#
"""


#### CONSTS ####
STRINGTOOLONG = 32


#### MODULES ####
import dis, sys, types, py_compile, time


#### FXNS ####

def dummy():
    a = 6
    b = ((4,5,6))


def dismantle(fn):
    """
    Dismantle the .py file, fn.
    Returns the root code object.
    """

    #create a code object
    f = open(fn)
    source = f.read()
    f.close()
    code = compile(source, fn, "exec")

    #compile the .py file
    py_compile.compile(fn)
    #open the .pyc file
    f = open(fn + 'c','rb')
    pyc = f.read()
    f.close()

    #check for magic number
    magic = int((ord(pyc[0])      ) | (ord(pyc[1]) <<  8) |
                (ord(pyc[2]) << 16) | (ord(pyc[3]) << 24))
    #different magic numbers for different versions of python
    #if magic not in [0x0a0dc687,]:
    #    raise IOError("Did not find .pyc magic number.")

    #grab the next 4 bytes (don't know what they do)
    ignore = int((ord(pyc[4])      ) | (ord(pyc[5]) <<  8) |
                 (ord(pyc[6]) << 16) | (ord(pyc[7]) << 24))

    #print header
    print "BEGIN DISMANTLE"
    print "date:           \t", time.ctime(time.time())
    print "src file:       \t", fn
    print "src file size:  \t", len(source), "bytes"
    print "pyc file size:  \t", len(pyc), "bytes"
    print
    print "magic:          \t0x%08x" % magic
    print "ignore:         \t0x%08x" % ignore
    print

    #recurse into the code object
    rdismantle(code)

    print "END DISMANTLE"
    return code


def rdismantle(co, parent = None):
    """
    Dismantle the code object, co.
    Prints the co_* field values and
    the co_code disassembly for each code object
    in the file and recurses into any code objects
    in the constant pool.
    """

    #create full name
    if parent:
        fullname = parent + "." + co.co_name
    else:
        fullname = co.co_name

    #print object fields and values
    print "fullname:       \t", fullname
    print " co_name:       \t", co.co_name
    print " co_filename:   \t", co.co_filename
    print " co_firstlineno:\t", co.co_firstlineno
    print " co_flags:      \t0x%04x"  % co.co_flags
    print " co_stacksize:  \t", co.co_stacksize
    print " co_lnotab:     \t", repr(co.co_lnotab[:8]), "..."
    print " co_argcount:   \t", co.co_argcount
    print " co_nlocals:    \t", co.co_nlocals

    #print vital compound components
    tabspacing = "\t\t"

    print " co_varnames:"
    i = 0
    for item in co.co_varnames:
        print tabspacing, i, ":\t", item
        i += 1

    print " co_names:       "
    i = 0
    for item in co.co_names:
        print tabspacing, i, ":\t", item
        i += 1

    print " co_consts:      "
    i = 0
    for item in co.co_consts:
        if type(item) == types.StringType and \
           len(item) > STRINGTOOLONG:
                print tabspacing, i, ":\t", repr(item[:STRINGTOOLONG]), "..."
        else:
            print tabspacing, i, ":\t", repr(item)
        i += 1

    #print disassembly
    print " co_code:"
    dis.dis(co)
    print "\n"

    #dismantle code objects in constant pool
    for obj in co.co_consts:
        if type(obj) == types.CodeType:
            rdismantle(obj, fullname)
    return


#### MAIN ####

def main():
    """
    Perform a dismantling of the source file, fn.
    """
    if len(sys.argv) == 2:
        return dismantle(sys.argv[1])
    else:
        return dismantle("c:\\dwh\\tech\\cis\\py\\dismantle.py")


if __name__ == "__main__":
        main()

