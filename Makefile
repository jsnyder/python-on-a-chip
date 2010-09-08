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
PYCSCOPE := $(abspath src/tools/pycscope.py)
PMDIST := src/tools/pmDist.py

pathsearch = $(firstword $(wildcard $(addsuffix /$(1),$(subst :, ,$(PATH)))))

VPATH := . src/vm src/lib docs/src

# Default target
PLATFORM = desktop


.PHONY: all vm ipm html dox indent TAGS dist check clean

all :
	$(MAKE) -C src/platform/$(PLATFORM)

ipm :
	$(MAKE) -C src/platform/desktop
	cd src/tools && ./ipm.py -f ../platform/desktop/pmfeatures.py -d

html : docs/src/*.txt dox
	$(MKDIR) docs/html
	$(MAKE) -C docs/src

dox :
	$(MKDIR) docs/html
	doxygen

indent :
	$(MAKE) -C src/vm indent

TAGS :
	$(TAGS) -R *
	$(CSCOPE) -b -c -R
	cd src/tools && $(PYCSCOPE) *.py
#	cd src/lib && $(PYCSCOPE) *.py

dist :
ifndef PM_RELEASE
	$(error Must define PM_RELEASE=RR)
else
	$(PMDIST) $(PM_RELEASE)
endif

check :
	$(MAKE) -C src/tests/unit
	$(MAKE) -C src/tests/system

# Removes all files created during default make
clean :
	$(MAKE) -C src/platform/$(PLATFORM) clean

# Removes files made by make check
check-clean :
	$(MAKE) -C src/tests/unit clean
	$(MAKE) -C src/tests/system clean

# Removes files made by ipm
ipm-clean :
	$(MAKE) -C src/sample/desktop-ipm clean

# Remove files made by html / dox
html-clean :
	$(RM) -rf docs/html
