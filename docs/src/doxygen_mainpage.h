/** 
\mainpage API documentation
Copyright 2010 Dean Hall

Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.2
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover
Texts.  A copy of the license is in the file 
<a href="../../../LICENSE">LICENSE</a>.

See the <a href="../index.html">index</a> for user/developer 
documentation. The following items describe the implementation
of Python-on-a-chip (abbreviated p14p).

The p14p impelementation consists of several essential components
which combine to form a <a href="../PyMiteFeatures.html">working 
subset</a> of the Python language:
- The \ref virtualMachine "virtual machine", which executes the 
  bytecode which composes a Python program.
- A set of \ref standardLibraries "standard libraries", which
  implement essential features of the langauge.
- A \ref ports "port", which enables the virtual machine to execute 
  on a specific microprocessor.
- \ref tools "Supporting tools" used to produce bytecode and
  interact with a working p14p implementation.

\section virtualMachine Virtual Machine

\section standardLibraries Standard Libraries
 
\section ports Ports
Several ports, listed below, enable use of p14p on specific 
microprocessors. All ports reside in the <code>src/platform</code>
<a href="dirs.html">directory</a>.
- The <a href="../../../src/platform/avr/README">AVR</a> port provides
  read/write access to PORTA only.
- The \ref PIC24_dsPIC33_port "PIC24 and dsPIC33 processor" port provides
  digital I/O, Analog input, and PWM outputs.

\section tools Tools

*/