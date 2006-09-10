SHELL = /bin/sh
PMIMGCREATOR := ../tools/pmImgCreator.py
CFLAGS += -I../vm
LDFLAGS = -L../vm -lpmvm
SOURCES = $(wildcard t???.c)
PY_SOURCES = $(SOURCES:.c=.py)
EXECS = $(SOURCES:.c=.out)
IMG_SOURCES = $(subst .py,_img.c, $(PY_SOURCES))
NAT_SOURCES = $(subst .py,_nat.c, $(PY_SOURCES))
PMSTDLIB_SOURCES = ../lib/__bi.py \
                   ../lib/sys.py


# Build an executable from the C sources
%.out : %*_nat.c %*_img.c %.c
	$(CC) $(CFLAGS) -g -o $@ $*_nat.c $*_img.c $*.c ../vm/libpmvm.a
ifeq ($(TARGET), DESKTOP)
	$(addprefix ./,$@)
endif

# The module images and native code are generated from python source
%*_nat.c %*_img.c : %.py
	$(PMIMGCREATOR) -c -o $*_img.c --native-file=$*_nat.c $*.py $(PMSTDLIB_SOURCES)


.PHONY: all check clean

# Default action is to build tests; run tests if target is desktop
all : check

check : $(EXECS)

# Removes files made by default make
clean :
	$(RM) $(EXECS)
	$(RM) $(IMG_SOURCES)
	$(RM) $(NAT_SOURCES)