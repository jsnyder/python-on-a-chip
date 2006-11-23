SHELL = /bin/sh

TARGET ?= DESKTOP
HEAP_SIZE ?= 0x1000

CDEFS = -DHEAP_SIZE=$(HEAP_SIZE) -DTARGET_$(TARGET) -D__DEBUG__=1
CFLAGS = -g -I../../vm $(CDEFS)
UT_SOURCES = $(wildcard ut*.c)
ALL_SOURCES = runTests.c CuTest.c $(UT_SOURCES)
OBJS = $(ALL_SOURCES:.c=.o)
PRODUCT = runTests.out

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
	make -C ../../vm DEBUG=true

# Removes files made by default make
clean :
	$(RM) $(OBJS)
	$(RM) $(PRODUCT)
