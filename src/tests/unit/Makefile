SHELL = /bin/sh

# PyMite Configuration
PLATFORM ?= desktop
PM_LIB_ROOT = pmvm_$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
PMGENPMFEATURES := ../../tools/pmGenPmFeatures.py
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
CFLAGS = -Os -fno-strict-aliasing -Wall -Wstrict-prototypes $(CDEFS) $(CINCS) 

.PHONY: all check clean $(PRODUCT)

export CFLAGS IPM PM_LIB_FN

# Default action is to build and run tests
all : check

check : pmfeatures.h $(PRODUCT)

pmfeatures.h : ../../platform/$(PLATFORM)/pmfeatures.py $(PMGENPMFEATURES)
	$(PMGENPMFEATURES) ../../platform/$(PLATFORM)/pmfeatures.py > ../../platform/$(PLATFORM)/$@

$(PRODUCT) : $(OBJS) $(PM_LIB_PATH) ../../platform/$(PLATFORM)/plat.o
	$(CC) -lm -o $@ $(OBJS) $(PM_LIB_PATH) ../../platform/$(PLATFORM)/plat.o
ifeq ($(PLATFORM), desktop)
	$(addprefix ./,$@)
endif

$(PM_LIB_PATH) : ../../vm/*.c ../../vm/*.h
	make -C ../../platform/$(PLATFORM)

# Removes files made by default make
clean :
	$(RM) $(OBJS)
	$(RM) $(PRODUCT)
