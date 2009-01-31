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

pathsearch = $(firstword $(wildcard $(addsuffix /$(1),$(subst :, ,$(PATH)))))
PYCSCOPE := $(call pathsearch,pycscope.py)

# The value of UART_BAUD must match that found in src/tools/ipm.py
# and the F_CPU (below) must be set to match the target device's core frequency
# for the interactive interaface to work.
UART_BAUD = 19200UL

VPATH := . src/vm src/lib docs/src

# Build configuration
TARGET := DESKTOP
HEAP_SIZE = 0x2000

# Changes for an embedded target
ifeq ($(TARGET), AVR)
	# TARGET_MCU should equal avr-gcc option "-mmcu" possible values.
	TARGET_MCU := atmega103
	HEAP_SIZE = 0x0D00
	F_CPU = 4000000UL
else
ifeq ($(TARGET), AT91SAM7)
	# TARGET_MCU should equal arm-elf-gcc option "-mcpu" possible values.
	TARGET_MCU := arm7tdmi
	HEAP_SIZE = 0x2000
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

indent :
	$(MAKE) -C src/vm indent

TAGS :
	$(TAGS) -R *
	$(CSCOPE) -b -c -R
	$(if $(PYCSCOPE), cd src/tools && $(PYCSCOPE) -R *.py)

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

