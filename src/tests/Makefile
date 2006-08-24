SHELL = /bin/sh

CFLAGS += -I../vm
LDFLAGS = -L../vm -lpmvm

# TODO: Hopefully can use the following when issue #52 is resolved
#SOURCES = $(wildcard .c)
SOURCES = t003.c
PY_SOURCES = $(SOURCES:.c=.py)
OBJECTS = $(SOURCES:.c=.o)
EXECS = $(SOURCES:.c=.out)
LIBNATIVE_SOURCES = ../lib/__bi.py \
                    ../lib/sys.py

PMIMGCREATOR := ../tools/pmImgCreator.py

# An executable depends on the native fxn table and the bytecode image
%.out : %*_nat.c %*_img.h %.c
	$(CC) $(CFLAGS) -o $@ $*_nat.c $*.c ../vm/libpmvm.a

# The native fxn table and bytecode image are generated from python source
%*_nat.c %*_img.h : %.py
	$(PMIMGCREATOR) -h -o $*_img.h --native-file=$*_nat.c $*.py $(LIBNATIVE_SOURCES)


.PHONY: all clean

# Default action is to build tests; run tests if target is desktop
all : $(EXECS)
ifeq ($(TARGET), DESKTOP)
	./$<
endif

# Removes files made by default make
# TODO: #50: How to remove *_img.h *_nat.c
clean :
	$(RM) $(EXECS)
