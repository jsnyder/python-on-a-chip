# Hey Emacs, this is a -*- makefile -*-
# PyMite Configuration
PLATFORM := $(notdir $(CURDIR))
PM_LIB_ROOT = pmvm_$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
PM_USR_SOURCES = main.py econotag.py
PMIMGCREATOR := ../../tools/pmImgCreator.py
PMGENPMFEATURES := ../../tools/pmGenPmFeatures.py
IPM := true

# Serial device used to connect to Econotag
PM_SER_DEV = /dev/tty.usbserial-000030FDB

# Toolchain prefix (i.e arm-elf -> arm-elf-gcc.exe)
TCHAIN = arm-none-eabi-

USE_THUMB_MODE = YES
#USE_THUMB_MODE = NO

# MCU name and submodel
MCU = arm7tdmi-s

# Target file name (without extension).
TARGET = main

# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files
SRC = $(TARGET).c plat.c $(TARGET)_nat.c $(TARGET)_img.c syscalls.c

# List C source files here which must be compiled in ARM-Mode.
# use file-extension c for "c-only"-files
SRCARM =

# List C++ source files here.
# use file-extension cpp for C++-files (use extension .cpp)
CPPSRC =

# List C++ source files here which must be compiled in ARM-Mode.
# use file-extension cpp for C++-files (use extension .cpp)
#CPPSRCARM = $(TARGET).cpp
CPPSRCARM =

# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC =

# List Assembler source files here which must be assembled in ARM-Mode..
ASRCARM =

# Linker Script
LINKERSCRIPT= mc1322x.lds

#STARTOBJ = libmc1322x/src/start.o
STARTOBJ = libmc1322x/src/start-romvars.o

## Output format. (can be ihex or binary or both)
## (binary i.e. for openocd and SAM-BA, hex i.e. for lpc21isp and uVision)
#FORMAT = ihex
FORMAT = binary

# Optimization level, can be [0, 1, 2, 3, s].
# 0 = turn off optimization. s = optimize for size.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s
#OPT = 0

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
#DEBUG = stabs
DEBUG_FMT = dwarf-2

# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS = . ../../vm obj_redbee-econotag_board \
    libmc1322x/lib/include libmc1322x/src libmc1322x/board

# List any extra directories to look for library files here.
#     Each directory must be seperated by a space.
#EXTRA_LIBDIRS = ../arm7_efsl_0_2_4
EXTRA_LIBDIRS = . ../../vm libmc1322x/lib libmc1322x/src


# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

# Place -D or -U options for C here
CDEFS =
# PyMite CDEFS
ifeq ($(DEBUG),true)
	CDEFS += -g -g$(DEBUG_FMT) -D__DEBUG__=1
endif

# Place -I options here
CINCS = -I$(abspath .)

# Place -D or -U options for ASM here
ADEFS =

# Compiler flags.

ifeq ($(USE_THUMB_MODE),YES)
THUMB    = -mthumb
THUMB_IW = -mthumb-interwork
#-msoft-float
else
THUMB    =
THUMB_IW =
endif

#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)
PMCFLAGS = $(CDEFS) $(CINCS)
PMCFLAGS += -g
PMCFLAGS += -O$(OPT)
PMCFLAGS += -Wcast-align
PMCFLAGS += -Wall -Wimplicit
PMCFLAGS += -Wpointer-arith -Wswitch
PMCFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
PMCFLAGS += -Wa,-adhlns=$(subst $(suffix $<),.lst,$<)
PMCFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

# flags only for C
CONLYFLAGS += -Wnested-externs
CONLYFLAGS += $(CSTANDARD)

ifneq ($(AT91LIBNOWARN),yes)
#AT91-lib warnings with:
PMCFLAGS += -Wcast-qual
CONLYFLAGS += -Wmissing-prototypes
CONLYFLAGS += -Wstrict-prototypes
CONLYFLAGS += -Wmissing-declarations
endif

# flags only for C++ (arm-elf-g++)
# CPPFLAGS = -fno-rtti -fno-exceptions
CPPFLAGS =

# Assembler flags.
#  -Wa,...:    tell GCC to pass this to the assembler.
#  -ahlns:     create listing
#  -g$(DEBUG): have the assembler create line number information
ASFLAGS = $(ADEFS) -Wa,-adhlns=$(<:.S=.lst),--g$(DEBUG_FMT)


#Additional libraries.

# Extra libraries
#    Each library-name must be seperated by a space.
#    To add libxyz.a, libabc.a and libefsl.a:
#    EXTRA_LIBS = xyz abc efsl
#EXTRA_LIBS = efsl
EXTRA_LIBS = $(PM_LIB_ROOT) mc1322x src

#Support for newlibc-lpc (file: libnewlibc-lpc.a)
#NEWLIBLPC = -lnewlib-lpc

MATH_LIB = -lm

# CPLUSPLUS_LIB = -lstdc++


# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
PMLDFLAGS = -nostartfiles -Wl,-Map=$(TARGET).map,--cref
PMLDFLAGS += -lc
PMLDFLAGS += $(NEWLIBLPC) $(MATH_LIB)
PMLDFLAGS += -lc -lgcc
PMLDFLAGS += $(CPLUSPLUS_LIB)
PMLDFLAGS += $(patsubst %,-L%,$(EXTRA_LIBDIRS))
PMLDFLAGS += $(patsubst %,-l%,$(EXTRA_LIBS))

PMLDFLAGS +=-T$(LINKERSCRIPT)

# Define programs and commands.
SHELL = sh
CC = $(TCHAIN)gcc
CPP = $(TCHAIN)g++
AR = $(TCHAIN)ar
OBJCOPY = $(TCHAIN)objcopy
OBJDUMP = $(TCHAIN)objdump
SIZE = $(TCHAIN)size
NM = $(TCHAIN)nm
AR = $(TCHAIN)ar
REMOVE = rm -f
REMOVEDIR = rm -f -r
COPY = cp

# Define all object files.
COBJ      = $(SRC:.c=.o)
AOBJ      = $(ASRC:.S=.o)
COBJARM   = $(SRCARM:.c=.o)
AOBJARM   = $(ASRCARM:.S=.o)
CPPOBJ    = $(CPPSRC:.cpp=.o)
CPPOBJARM = $(CPPSRCARM:.cpp=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(ASRCARM:.S=.lst) $(SRC:.c=.lst) $(SRCARM:.c=.lst)
LST += $(CPPSRC:.cpp=.lst) $(CPPSRCARM:.cpp=.lst)

# Compiler flags to generate dependency files.
### GENDEPFLAGS = -Wp,-M,-MP,-MT,$(*F).o,-MF,.dep/$(@F).d
#GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS  = -mcpu=$(MCU) $(THUMB) $(THUMB_IW) -I. $(PMCFLAGS) $(GENDEPFLAGS)
ALL_ASFLAGS = -mcpu=$(MCU) $(THUMB) $(THUMB_IW) -I. -x assembler-with-cpp $(ASFLAGS)


# LIBMC1322X: Variables to duplicate libmc1322x/tests/Makefile
MC1322X := libmc1322x
BOARD := redbee-econotag
COBJS :=
TARGETS :=
# this space is initialized with a rom call to rom_data_init
TARGETS_WITH_ROM_VARS :=
# This includes the default rule at the top; it must be included first
-include $(MC1322X)/Makefile.include


all: pmfeatures.h pmvm build

ifeq ($(FORMAT),ihex)
build: elf hex bin lss sym
hex: $(TARGET).hex
IMGEXT=hex
else
ifeq ($(FORMAT),binary)
build: elf bin lss sym
bin: $(TARGET).bin
IMGEXT=bin
else
ifeq ($(FORMAT),both)
build: elf hex bin lss sym
hex: $(TARGET).hex
bin: $(TARGET).bin
else
$(error "$(MSG_FORMATERROR) $(FORMAT)")
endif
endif
endif   

elf: $(TARGET).elf
lss: $(TARGET).lss
sym: $(TARGET).sym

libmc1322x:
	make -C libmc1322x/tests ../lib/libmc1322x.a
	TARGET_ROM_VARS=1 make -C libmc1322x/tests ../src/src.a
	cd libmc1322x/src && ln -s src.a libsrc.a

once1:
	@echo "Obtaining third-party library, libmc1322x, and setting toolchain"
	git clone -n git://git.devl.org/git/malvira/libmc1322x.git

once2:
	cd libmc1322x && git checkout -q a6813372bfc38c83e61a90952f9b9301852f1c17 \
	&& cp Makefile.include Makefile.include.bak \
	&& sed 's/arm-linux-/$(TCHAIN)/g' Makefile.include > Makefile.include.tmp \
	&& mv Makefile.include.tmp Makefile.include \
	&& patch -p 1 -i ../patch_libmc1322x_types.patch
	patch -p 0 -i patch_bi.patch

once3: libmc1322x

once: once1 once2 once3

load:
	libmc1322x/tools/mc1322x-load.pl -f $(TARGET).bin -t $(PM_SER_DEV)

loadpy:
	./red-bsl.py -f $(TARGET).bin -t $(PM_SER_DEV)

pmfeatures.h : pmfeatures.py $(PMGENPMFEATURES)
	$(PMGENPMFEATURES) pmfeatures.py > $@

# PyMite: Build the VM archive if it doesn't exist
pmvm : $(PM_LIB_PATH)

$(PM_LIB_PATH) :
	make -C ../../vm

# Display compiler version information.
gccversion :
	@$(CC) --version

# Create final output file (.hex) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O ihex $< $@

# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O binary $< $@


# Create extended listing file from ELF output file.
# testing: option -C
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C $< > $@


# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@


# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(STARTOBJ) $(CPPOBJARM)
%.elf:  $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(STARTOBJ) $(CPPOBJARM)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(THUMB) $(ALL_CFLAGS) $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(STARTOBJ) $(CPPOBJARM) --output $@ $(PMLDFLAGS)
#	$(CPP) $(THUMB) $(ALL_CFLAGS) $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) $(CPPOBJ) $(CPPOBJARM) --output $@ $(PMLDFLAGS)

# Compile: create object files from C source files. ARM/Thumb
$(COBJ) : %.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(THUMB) $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@

# Compile: create object files from C source files. ARM-only
$(COBJARM) : %.o : %.c
	@echo
	@echo $(MSG_COMPILING_ARM) $<
	$(CC) -c $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@

# Compile: create object files from C++ source files. ARM/Thumb
$(CPPOBJ) : %.o : %.cpp
	@echo
	@echo $(MSG_COMPILINGCPP) $<
	$(CPP) -c $(THUMB) $(ALL_CFLAGS) $(CPPFLAGS) $< -o $@

# Compile: create object files from C++ source files. ARM-only
$(CPPOBJARM) : %.o : %.cpp
	@echo
	@echo $(MSG_COMPILINGCPP_ARM) $<
	$(CPP) -c $(ALL_CFLAGS) $(CPPFLAGS) $< -o $@


# Compile: create assembler files from C source files. ARM/Thumb
## does not work - TODO - hints welcome
##$(COBJ) : %.s : %.c
##	$(CC) $(THUMB) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files. ARM/Thumb
$(AOBJ) : %.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(THUMB) $(ALL_ASFLAGS) $< -o $@


# Assemble: create object files from assembler source files. ARM-only
$(AOBJARM) : %.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING_ARM) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

# Assemble using GCC with assembly flags
$(STARTOBJ) : %.o : %.s
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

# PyMite: Generate native code and module images from the python source
$(TARGET)_nat.c $(TARGET)_img.c : $(PM_USR_SOURCES) pmfeatures.py
	$(PMIMGCREATOR) -f pmfeatures.py -c -u -o $(TARGET)_img.c --native-file=$(TARGET)_nat.c $(PM_USR_SOURCES)

../../vm/pmstdlib_img.c ../../vm/pmstdlib_nat.c :
	$(MAKE) -C ../../vm pmstdlib_img.c pmstdlib_nat.c


# Target: clean project.
clean:
	$(MAKE) -C ../../vm clean
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).bin
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(COBJ)
	$(REMOVE) $(CPPOBJ)
	$(REMOVE) $(AOBJ)
	$(REMOVE) $(COBJARM)
	$(REMOVE) $(CPPOBJARM)
	$(REMOVE) $(AOBJARM)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) $(SRCARM:.c=.s)
	$(REMOVE) $(SRCARM:.c=.d)
	$(REMOVE) $(CPPSRC:.cpp=.s)
	$(REMOVE) $(CPPSRC:.cpp=.d)
	$(REMOVE) $(CPPSRCARM:.cpp=.s)
	$(REMOVE) $(CPPSRCARM:.cpp=.d)
	$(REMOVE) $(TARGET)_img.c
	$(REMOVE) $(TARGET)_nat.c
	$(REMOVE) pmfeatures.h
	$(REMOVEDIR) .dep | exit 0


# Include the dependency files.
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)


# Listing of phony targets.
.PHONY : all finish sizebefore sizeafter gccversion \
build elf hex bin lss sym clean clean_list program pmvm libmc1322x zip


export CC OBJCOPY NM PMCFLAGS ALL_CFLAGS AR IPM PM_LIB_FN