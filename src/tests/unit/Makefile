SHELL = /bin/sh

# PyMite Configuration
PLATFORM ?= desktop
PM_LIB_ROOT = pmvm_$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
DEBUG = true

UT_SOURCES = $(wildcard ut*.c)
ALL_SOURCES = runTests.c CuTest.c $(UT_SOURCES)
OBJS = $(ALL_SOURCES:.c=.o)
PRODUCT = runTests.out

ifeq ($(DEBUG),true)
	CDEFS += -g -ggdb -D__DEBUG__=1
endif
CINCS = -I../../vm -I../../platform/desktop
# Removed -Werror until Issue 53 is resolved.
CFLAGS = -Os -Wall -Wstrict-prototypes $(CDEFS) $(CINCS) 

.PHONY: all check clean $(PRODUCT)

export CFLAGS IPM PM_LIB_FN

# Default action is to build and run tests
all : check

check : $(PRODUCT)

$(PRODUCT) : $(OBJS) $(PM_LIB_PATH) ../../platform/$(PLATFORM)/plat.o
	$(CC) -o $@ $(OBJS) $(PM_LIB_PATH) ../../platform/$(PLATFORM)/plat.o
ifeq ($(PLATFORM), desktop)
	$(addprefix ./,$@)
endif

$(PM_LIB_PATH) : ../../vm/*.c ../../vm/*.h
	make -C ../../platform/$(PLATFORM)

# Removes files made by default make
clean :
	$(RM) $(OBJS)
	$(RM) $(PRODUCT)
