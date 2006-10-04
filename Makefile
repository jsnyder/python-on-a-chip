#
# Available arguments:
#     TARGET = [DESKTOP, AVR]
#
# Default values:
#     TARGET = DESKTOP
#
# For target AVR, check options in section "Changes for an embedded target".
#

# Tools configuration
SHELL = /bin/sh
CP := cp
MKDIR := mkdir -p
TAGS := ctags
CSCOPE := cscope

VPATH := . src/vm src/lib docs/src

# Build configuration
TARGET := DESKTOP
HEAP_SIZE = 0x1000

# Changes for an embedded target
ifeq ($(TARGET), AVR)
	# TARGET_MCU should equal avr-gcc option "-mmcu" possible values.
	TARGET_MCU := atmega103
	HEAP_SIZE = 0x0D00
else
ifeq ($(TARGET), ARM)
	# TARGET_MCU should equal arm-elf-gcc option "-mcpu" possible values.
	TARGET_MCU := arm7tdmi
	HEAP_SIZE = 0x0D00
endif
endif

# Export config to child makefiles
export TARGET HEAP_SIZE TARGET_MCU

.PHONY: all vm pmstdlib docs TAGS dist check clean

all : vm

vm :
	$(MAKE) -C src/vm

html : docs/src/*.txt
	$(MKDIR) docs/html
	$(MAKE) -C docs/src

TAGS :
	$(TAGS) -R *
	$(CSCOPE) -b -c -R
	cd src/tools && pycscope.py -R *.py

dist : check docs
ifndef PYMITE_RELEASE
	$(error Must define PYMITE_RELEASE=RR)
else
	# TODO: issue #5
	# Make a script in tools/ that will:
	# 	- make fresh export (no .svn folders),
	#   - build docs
	#   - make pymite-RR.tar.gz
	#	- create release tag in svn repos
endif

check :
	$(MAKE) -C src/tests/unit
	$(MAKE) -C src/tests/system

# Removes all files created during default make
clean :
	$(MAKE) -C src/vm clean

