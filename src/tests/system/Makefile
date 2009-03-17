SHELL = /bin/sh

# PyMite Configuration
PLATFORM ?= desktop
PM_LIB_ROOT = pmvm.$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
PM_USR_SOURCES = $(SOURCES:.c=.py)
PM_HEAP_SIZE = 0x2000
PMIMGCREATOR := ../../tools/pmImgCreator.py
DEBUG = false

SOURCES = $(wildcard t???.c)
EXECS = $(SOURCES:.c=.out)
IMG_SOURCES = $(subst .py,_img.c, $(PM_USR_SOURCES))
NAT_SOURCES = $(subst .py,_nat.c, $(PM_USR_SOURCES))

CDEFS = -DHEAP_SIZE=$(PM_HEAP_SIZE)
ifeq ($(DEBUG),true)
	CDEFS += -g -ggdb -D__DEBUG__=1
endif
CFLAGS = -Os -Wall -Wstrict-prototypes -Werror $(CDEFS) -I../../vm


# Build an executable from the C sources
%.out : %*_nat.c %*_img.c %.c plat.o
	$(CC) $(CFLAGS) -o $@ $*_nat.c $*_img.c $*.c plat.o $(PM_LIB_PATH)
ifeq ($(PLATFORM), desktop)
	$(addprefix ./,$@)
endif

# The module images and native code are generated from python source
%*_nat.c %*_img.c : %.py
	$(PMIMGCREATOR) -c -u -o $*_img.c --native-file=$*_nat.c $*.py $(PMSTDLIB_SOURCES)
%*_nat.c %*_img.c : %a.py %b.py
	$(PMIMGCREATOR) -c -u -o $*_img.c --native-file=$*_nat.c $*a.py $*b.py $(PMSTDLIB_SOURCES)

.PHONY: all check clean

export CFLAGS HEAP_SIZE PM_LIB_FN

# Default action is to build tests; run tests if target is desktop
all : check

check : $(PM_LIB_PATH) $(EXECS)

$(PM_LIB_PATH) : ../../vm/*.c ../../vm/*.h
	make -C ../../vm

plat.o : plat.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Removes files made by default make
clean :
	$(RM) $(EXECS)
	$(RM) $(IMG_SOURCES)
	$(RM) $(NAT_SOURCES)
	$(RM) plat.o
