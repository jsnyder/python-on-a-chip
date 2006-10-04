SHELL = /bin/sh

TARGET ?= DESKTOP
CDEFS = -DHEAP_SIZE=0x0D00
CFLAGS = -I../../vm $(CDEFS)
UT_SOURCES = $(wildcard ut*.c)
ALL_SOURCES = runTests.c CuTest.c $(UT_SOURCES)
OBJS = $(ALL_SOURCES:.c=.o)
PRODUCT = runTests.out

ifeq ($(TARGET), DESKTOP)
	CDEFS += -DTARGET_DESKTOP
endif

.PHONY: all check

# Default action is to build and run tests
all : check

check : $(PRODUCT)

$(PRODUCT) : vm $(OBJS)
	$(CC) -o $@ $(OBJS) -L../../vm/ -lpmvm
ifeq ($(TARGET), DESKTOP)
	$(addprefix ./,$@)
endif

# The following object can't use CFLAGS because it needs
# the standard string.h, not src/vm/string.h
CuTest.o : CuTest.c
	$(CC) -c -o $@ $<

vm :
	make -C ../../vm

# Removes files made by default make
clean :
	$(RM) $(OBJS)
	$(RM) $(PRODUCT)
