SHELL = /bin/sh

TARGET ?= DESKTOP
HEAP_SIZE ?= 0xF000

PMIMGCREATOR := ../../tools/pmImgCreator.py
VM_LIB := ../../vm/libpmvm.a
CDEFS = -DHEAP_SIZE=$(HEAP_SIZE) -DTARGET_$(TARGET) -D__DEBUG__=1
CFLAGS = -g -ggdb -Os -Wall -gstabs -Wstrict-prototypes -Werror -ansi $(CDEFS)
CFLAGS += -I../../vm
SOURCES = main.c
PY_SOURCES = main.py
EXECS = $(SOURCES:.c=.out)
IMG_SOURCES = $(subst .py,_img.c, $(PY_SOURCES))
NAT_SOURCES = $(subst .py,_nat.c, $(PY_SOURCES))

# Build an executable from the C sources
%.out : %*_nat.c %*_img.c %.c
	$(CC) $(CFLAGS) -o $@ $*_nat.c $*_img.c $*.c ../../vm/libpmvm.a

# The module images and native code are generated from python source
%*_nat.c %*_img.c : %.py
	$(PMIMGCREATOR) -c -u -o $*_img.c --native-file=$*_nat.c $*.py $(PMSTDLIB_SOURCES)

.PHONY: all vm clean

# Default action is to build main; run main if target is desktop
all : vm $(EXECS)

vm : $(VM_LIB)
	make -C ../../vm

# Removes files made by default make
clean :
	$(RM) $(EXECS)
	$(RM) $(IMG_SOURCES)
	$(RM) $(NAT_SOURCES)
