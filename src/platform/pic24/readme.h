/** 
\page PIC24_dsPIC33_port The PIC24 and dsPIC33 port
 
\author Bryan A. Jones

\section purpose Purpose

This is a sample project that demonstrates the use of PyMite on the
<a href="http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=2629&param=en533465">PIC24
and dsPIC33 family</a> of microcontrollers.  Any PIC with at least 128 KiB of
program memory and 4 KiB of RAM can run PyMite.


\section details Details

This sample project demonstrates a simple use case of 
python-on-a-chip (p14p) on a microcontroller.  The file 
\ref src/platform/pic24/main.c "main.c" is used to initialize p14p
and indicate the name of the module it should run.  In this case, it
will run the module \ref src/platform/pic24/main.py "main.py".

In the module \ref src/platform/pic24/main.py "main.py", we see that 
the program prints a "Hello world" message, defines and runs an 
initialization function and then executes ipm.

Additional sample code in sample_lib.py illustrates use of the
\ref src/platform/pic24/pic24_dspic33.py "PIC24/dsPIC33" library.
The program \ref src/platform/pic24/robot.py "robot.py" 
gives code to operate a simple robot.


\section building Building the Project

First, install <a href="http://www.cygwin.com">Cygwin</a>, manually
selecting installation of make. To build documentation,
install <a href="http://docutils.sourceforge.net">docutils</a> and
<a href="http://www.doxygen.org">Doxygen</a>. 

Open the p14p.mcp project file with the 
<a href="http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1406&dDocName=en019469&part=SW007002">Microchip
MPLAB IDE</a> then build the project. However, you must have the path to 
Cygwin's make.exe in your Windows path for this to work.

Alternatively, you can compile from the command line.
Start with a clean PyMite tree.  Edit 
<a href="../../../src/platform/pic24/Makefile">src/platform/pic24/Makefile</a>
near line 14 to set the part number of your PIC. Then, execute the following
at the command prompt, which will build the PyMite VM archive as well as the 
sample application.

@verbatim
    $ cd src/platform/pic24
    $ make
@endverbatim


\section flashing Flashing the Binary

The steps above result in the binary file that need to go on the PIC.
Use a PICKit2/3 to program your PIC.

*/

/* Old info
The Makefile is configured for use with the 
<a href="http://www.reesemicro.com/Home/pic24-software-library-collection/pic24-bully-bootloader">Bully
Bootloader</a>. 
*/