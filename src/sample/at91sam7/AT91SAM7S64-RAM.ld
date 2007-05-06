/*---------------------------------------------------------------------------*/
/*-         ATMEL Microcontroller Software Support  -  ROUSSET  -            */
/*---------------------------------------------------------------------------*/
/* The software is delivered "AS IS" without warranty or condition of any    */
/* kind, either express, implied or statutory. This includes without	     */
/* limitation any warranty or condition with respect to merchantability or   */
/* fitness for any particular purpose, or against the infringements of	     */
/* intellectual property rights of others.				     */
/*---------------------------------------------------------------------------*/
/*- File source          : GCC_RAM.ld                                        */
/*- Object               : Linker Script File for RAM Workspace              */
/*- Compilation flag     : None                                              */
/*-                                                                          */
/*- 1.0 11/Mar/05 JPP    : Creation S256                                     */
/*---------------------------------------------------------------------------*/


/*
//*** <<< Use Configuration Wizard in Context Menu >>> *** 
*/


/*
// <h> Memory Configuration
//   <h> Code (Read Only)
//     <o>  Start <0x0-0xFFFFFFFF>
//     <o1> Size  <0x0-0xFFFFFFFF>
//   </h>
//   <h> Data (Read/Write)
//     <o2> Start <0x0-0xFFFFFFFF>
//     <o3> Size  <0x0-0xFFFFFFFF>
//   </h>
//   <h> Top of Stack (Read/Write)
//     <o4> STACK <0x0-0xFFFFFFFF>
//   </h>
// </h>
*/

/* Memory Definitions */

MEMORY
{
  CODE (rx) : ORIGIN = 0x00000000, LENGTH = 0x00003000
  DATA (rw) : ORIGIN = 0x00003000, LENGTH = 0x00001000
  STACK (rw) : ORIGIN = 0x00004000,LENGTH = 0x00000000
}


/* Section Definitions */

SECTIONS
{
  /* first section is .text which is used for code */
  . = 0x0000000;
  .text : { *Cstartup.o (.text) }>CODE =0
  .text :
  {
    *(.text)                   /* remaining code */

    *(.glue_7t) *(.glue_7)

  } >CODE =0

  . = ALIGN(4);

  /* .rodata section which is used for read-only data (constants) */

  .rodata :
  {
    *(.rodata)
  } >CODE

  . = ALIGN(4);

  _etext = . ;
  PROVIDE (etext = .);

  /* .data section which is used for initialized data */

  .data : AT (_etext)
  {
    _data = . ;
    *(.data)
    SORT(CONSTRUCTORS)
  } >DATA
  . = ALIGN(4);

  _edata = . ;
   PROVIDE (edata = .);

  /* .bss section which is used for uninitialized data */

  .bss :
  {
    __bss_start = . ;
    __bss_start__ = . ;
    *(.bss)
    *(COMMON)
  } 
  . = ALIGN(4);
  __bss_end__ = . ;
  __bss_end__ = . ;
  _end = .;
  PROVIDE (end = .);


   .int_data :  
   { 
   *(.internal_ram_top) 
   }> STACK 

  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }

}
