SHELL = /bin/sh

# PyMite Configuration
PLATFORM ?= desktop
PM_LIB_ROOT = pmvm.$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
PM_HEAP_SIZE ?= 0x1000
DEBUG = true

UT_SOURCES = $(wildcard ut*.c)
ALL_SOURCES = runTests.c plat.c CuTest.c $(UT_SOURCES)
OBJS = $(ALL_SOURCES:.c=.o)
PRODUCT = runTests.out

CDEFS = -DHEAP_SIZE=$(PM_HEAP_SIZE)
ifeq ($(DEBUG),true)
	CDEFS += -g -ggdb -D__DEBUG__=1
endif
CFLAGS = -I../../vm $(CDEFS)

.PHONY: all check clean

export CFLAGS IPM HEAP_SIZE PM_LIB_FN

# Default action is to build and run tests
all : check

check : $(PRODUCT)

$(PRODUCT) : $(PM_LIB_PATH) $(OBJS)
	$(CC) -o $@ $(OBJS) $(PM_LIB_PATH)
ifeq ($(PLATFORM), desktop)
	$(addprefix ./,$@)
endif

# The following object can't use CFLAGS because it needs
# the standard string.h, not src/vm/string.h
CuTest.o : CuTest.c
	$(CC) -c -o $@ $<

$(PM_LIB_PATH) : ../../vm/*.c ../../vm/*.h
	make -C ../../vm

# Removes files made by default make
clean :
	$(RM) $(OBJS)
	$(RM) $(PRODUCT)
