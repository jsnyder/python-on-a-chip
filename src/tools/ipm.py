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
==================
Interactive PyMite
==================

An interactive command line that runs on a host computer that is connected
to a target device that is running PyMite.  The host computer compiles the
interactive statement and converts it to a form that PyMite can handle,
sends that over the connection where the target device loads and interprets it.
The target device then packages any result, sends it to the host computer
and the host computer prints the result.

Log
---

==========      ================================================================
Date            Action
==========      ================================================================
2006/12/21      Initial creation
"""


import cmd, dis, getopt, os, subprocess, sys
import pmImgCreator


__usage__ = """USAGE:
    ipm.py -d

    -d      Specifies the desktop connection; uses pipes to send/receive bytes
            to/from the target, which is the vm also running on the desktop.
            ipm will spawn the process and run the vm.
    """

PMVM_EXE = "../sample/ipm-desktop/main.out"
IPM_PROMPT = "ipm> "
COMPILE_FN = "<ipm>"
COMPILE_MODE = "single"
HELP_MESSAGE = "This is the interactive PyMite command line.\n" \
               "Just type the code that you want the target device to run.\n" \
               "Type another return if you see no prompt to exit multiline mode.\n" \
               "Type Ctrl+C to interrupt and Ctrl+D to quit.\n"
REPLY_TERMINATOR = '\x04'


class Connection(object):
    def open(self,): raise NotImplementedError
    def read(self,): raise NotImplementedError
    def write(self, msg): raise NotImplementedError


class PipeConnection(Connection):
    """Provides ipm-host to target connection over stdio pipes on the desktop.
    This connection should work on any POSIX-compliant OS.
    The ipm-device must be spawned as a subprocess
    (the executable created when PyMite was built with TARGET=DESKTOP).
    """
    def __init__(self, target=PMVM_EXE):
        self.open(target)


    def open(self, target):
        self.child = subprocess.Popen(target,
                                      bufsize=-1,
                                      stdin=subprocess.PIPE,
                                      stdout=subprocess.PIPE,
                                      stderr=subprocess.PIPE,
                                      )


    def read(self,):
        # If the child process is not alive, read in everything from the buffer.
        # It will usually be an exception message from the target
        # TODO

        # Collect all characters up to and including the ipm reply terminator
        chars = []
        c = 'z'
        while c != REPLY_TERMINATOR:
            c = self.child.stdout.read(1)
            if c == '':
                print "DEBUG: child returncode = %s\n" % hex(self.child.poll())
                break
            chars.append(c)
        msg = "".join(chars)
        return msg


    def write(self, msg):
        self.child.stdin.write(msg)
        self.child.stdin.flush()


class Interactive(cmd.Cmd):
    """The interactive command line parser accepts typed input line-by-line.
    If a statement requires multiple lines to complete,  the input
    is collected until two sequential end-of-line characters are received.
    """
    ipmcommands = ("?", "help", "load",)


    def __init__(self, conn):
        cmd.Cmd.__init__(self,)
        self.prompt = IPM_PROMPT
        self.conn = conn


    def do_help(self, *args):
        """Prints the help message.
        """
        self.stdout.write(HELP_MESSAGE)


    def do_load(self, *args):
        """Loads a module from the host to the target device.
        """

        # Ensure the filename arg names a python source file
        fn = args[0]
        if not fn.endswith(".py"):
            self.stdout.write('Error using "load <module>": '
                              'module must be a ".py" source file.\n')
            return

        print "TODO: Loading module %s" % (args[0])
        # TODO: load module, compile to image, send to target


    def do_input(self, line):
        """Compiles the input and creates a code image from "line",
        sends the code image to the target over the connection,
        prints the return stream.
        """

        codeobj = compile(line, COMPILE_FN, COMPILE_MODE)

        # DEBUG: Uncomment the next line to print the statement's bytecodes
        #dis.disco(codeobj)

        # Convert to a code image
        pic = pmImgCreator.PmImgCreator()
        try:
            codeimg = pic.co_to_str(codeobj)

        # Print any conversion errors
        except Exception, e:
            self.stdout.write("%s:%s\n" % (e.__class__.__name__, e))

        # Otherwise send the image and print the reply
        else:

            # DEBUG: Uncomment the next line to print the size of the code image
            # print "DEBUG: len(codeimg) = ", len(codeimg)
            # DEBUG: Uncomment the next line to print the code image
            # print "DEBUG: codeimg = ", repr(codeimg)

            try:
                self.conn.write(codeimg)
            except Exception, e:
                self.stdout.write("Connection write error, type Ctrl+D to quit.\n")

            rv = self.conn.read()
            if rv == '':
                self.stdout.write("Connection read error, type Ctrl+D to quit.\n")
            else:
                self.stdout.write(rv)


    def onecmd(self, line):
        """Gathers one interactive line of input (gets more lines as needed).
        """

        # Ignore empty line, continue interactive prompt
        if not line:
            return

        # Handle ctrl+D (End Of File) input, stop interactive prompt
        if line == "EOF":
            # Send invalid image to disconnect the target
            self.conn.write("\0")
            # The connection will close automatically

            # Do this so OS prompt is on a new line
            self.stdout.write("\n")

            # Quit the run loop
            self.stop = True
            return True

        # Handle ipm-specific commands
        if line.split()[0] in Interactive.ipmcommands:
            cmd.Cmd.onecmd(self, line)
            return

        # Gather input from the interactive line
        codeobj = None
        while not codeobj:

            # Try to compile the given line
            try:
                codeobj = compile(line, COMPILE_FN, COMPILE_MODE)

            # Get more input if syntax error reports unexpected end of file
            except SyntaxError, se:

                # Print any other syntax error
                if not se.msg.startswith("unexpected EOF while parsing"):
                    self.stdout.write("%s:%s\n" % (se.__class__.__name__, se))
                    return

                # Restore the newline chopped by cmd.py:140
                line += "\n"

                # Get more input if needed
                while not line.endswith("\n\n"):
                    line += self.stdin.readline()

            # Print any other exception
            except Exception, e:
                self.stdout.write("%s:%s\n" % (e.__class__.__name__, e))
                return

        # Process the input
        self.do_input(line)


    def run(self,):
        """Runs the command loop and handles keyboard interrupts (ctrl+C).
        The command loop is what calls self.onecmd().
        """

        print HELP_MESSAGE,

        self.stop = False
        while not self.stop:
            try:
                self.stop = self.cmdloop()
            except KeyboardInterrupt, ki:
                print "\n", ki.__class__.__name__
                # TODO: check connection?


def parse_cmdline():
    """Parses the command line for options.
    """

    try:
        opts, args = getopt.getopt(sys.argv[1:], "d", [])
    except Exception, e:
        raise e
        print __usage__
        sys.exit(os.EX_USAGE)

    if not opts:
        print __usage__
        sys.exit(os.EX_USAGE)

    for opt in opts:
        if opt[0] == "-d":
            conn = PipeConnection()

    return (conn,)


def main():
    (conn,) = parse_cmdline()
    i = Interactive(conn)
    i.run()


if __name__ == "__main__":
    main()
