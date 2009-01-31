SHELL = /bin/sh

TARGET ?= DESKTOP
HEAP_SIZE ?= 0x2000
TARGET_MCU ?= atmega103

PMIMGCREATOR := ../../tools/pmImgCreator.py
CDEFS = -DHEAP_SIZE=$(HEAP_SIZE) -DTARGET_$(TARGET) -D__DEBUG__=1
CFLAGS = -g -ggdb -Os -Wall -gstabs -Wstrict-prototypes -Werror $(CDEFS)
CFLAGS += -I../../vm
SOURCES = $(wildcard t???.c)
PY_SOURCES = $(SOURCES:.c=.py)
EXECS = $(SOURCES:.c=.out)
IMG_SOURCES = $(subst .py,_img.c, $(PY_SOURCES))
NAT_SOURCES = $(subst .py,_nat.c, $(PY_SOURCES))

ifeq ($(TARGET), DESKTOP)
	CFLAGS += -ansi
endif
ifeq ($(TARGET), AVR)
	AR = avr-ar
	CC = avr-gcc
	SIZE = avr-size
	CFLAGS += -mmcu=$(TARGET_MCU) -DTARGET_MCU=$(TARGET_MCU)
endif

# Build an executable from the C sources
%.out : %*_nat.c %*_img.c %.c
	$(CC) $(CFLAGS) -o $@ $*_nat.c $*_img.c $*.c ../../vm/libpmvm.a
ifeq ($(TARGET), DESKTOP)
	$(addprefix ./,$@)
endif

# The module images and native code are generated from python source
%*_nat.c %*_img.c : %.py
	$(PMIMGCREATOR) -c -u -o $*_img.c --native-file=$*_nat.c $*.py $(PMSTDLIB_SOURCES)
%*_nat.c %*_img.c : %a.py %b.py
	$(PMIMGCREATOR) -c -u -o $*_img.c --native-file=$*_nat.c $*a.py $*b.py $(PMSTDLIB_SOURCES)

.PHONY: all check clean

# Default action is to build tests; run tests if target is desktop
all : check

check : vm $(EXECS)

vm :
	make -C ../../vm DEBUG=true

# Removes files made by default make
clean :
	$(RM) $(EXECS)
	$(RM) $(IMG_SOURCES)
	$(RM) $(NAT_SOURCES)
