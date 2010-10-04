# PyMite Configuration
PLATFORM := $(notdir $(CURDIR))
PM_LIB_ROOT = pmvm_$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
PM_USR_SOURCES = pic24_dspic33.py main.py \
    # sample_lib.py # Uncomment to run sample code
PM_TEST_USR_SOURCES = pic24_dspic33.py system_test/main.py
PMIMGCREATOR := ../../tools/pmImgCreator.py
PMGENPMFEATURES := ../../tools/pmGenPmFeatures.py
IPM = true
DEBUG = false
# The PIC30 compiler binaries must be in your path.
CC = pic30-gcc.exe
AR = pic30-ar.exe
B2H = pic30-bin2hex.exe
CPU = 24HJ128GP502
# Per docs, the PIC$(CPU) define should already exist. Not sure why this is necessary.
# If running in simulation, include the -DSIM below; otherwise, remove it.
CDEFS = -D__PIC$(CPU)__ # -DSIM

TARGET = main
PIC24_LIB_SOURCES = common/pic24_clockfreq.c \
	common/pic24_configbits.c common/pic24_uart.c \
	common/pic24_util.c common/pic24_serial.c \
	common/pic24_timer.c common/pic24_pyports.c \
    common/pic24_adc.c
SOURCES = $(TARGET).c plat.c $(TARGET)_nat.c $(TARGET)_img.c \
	pyFuncsInC.c pyToC.c $(PIC24_LIB_SOURCES)
OBJS = $(SOURCES:.c=.o)

ifeq ($(DEBUG),true)
	CDEFS += -g -D__DEBUG__=1
endif

# Note: using $(abspath .) produces a path with /cygdrive/c/..., which isn't
# recognized by pic30-gcc. The use of cygpath solves this; thanks to Tyler 
# Wilson for this fix.
CINCS = -I$(shell cygpath -m $(abspath .)) -I$(shell cygpath -m $(abspath include))
CFLAGS = -mcpu=$(CPU) -Wall -O1 -Wdeclaration-after-statement -I../../vm $(CDEFS) $(CINCS)
# A generous stack -- too small will cause stack overflows.
# A bit of heap, in case user C code wants to malloc (can't imagine why, though).
LDFLAGS = -Wl,--script="p$(CPU).gld",--stack=400,--heap=50,--report-mem

export CFLAGS IPM PM_LIB_FN CC AR LDFLAGS


.PHONY: all clean

all : pmfeatures.h $(TARGET).hex $(TARGET)_nat.c $(TARGET)_img.c

bytecode: $(TARGET)_nat.c $(TARGET)_img.c pmfeatures.h
	make -C ../../vm bytecode PLATFORM=pic24

bytecode-test: system_test/$(TARGET)_nat.c system_test/$(TARGET)_img.c pmfeatures.h
	make -C ../../vm bytecode PLATFORM=pic24

$(PM_LIB_PATH) : ../../vm/*.c ../../vm/*.h
	make -C ../../vm

pmfeatures.h : pmfeatures.py $(PMGENPMFEATURES)
	$(PMGENPMFEATURES) pmfeatures.py > $@

$(TARGET).hex : $(OBJS) $(PM_LIB_PATH)
	$(CC) $(LDFLAGS) -o $(TARGET).cof $(OBJS) $(PM_LIB_PATH)
	$(B2H) $(TARGET).cof

# Generate native code and module images from the python source
$(TARGET)_nat.c $(TARGET)_img.c: $(PM_USR_SOURCES) $(PMIMGCREATOR) pmfeatures.py
	$(PMIMGCREATOR) -f pmfeatures.py -c -u -o $(TARGET)_img.c --native-file=$(TARGET)_nat.c $(PM_USR_SOURCES)

system_test/$(TARGET)_nat.c system_test/$(TARGET)_img.c: $(PM_TEST_USR_SOURCES) $(PMIMGCREATOR) pmfeatures.py
	$(PMIMGCREATOR) -f pmfeatures.py -c -u -o system_test/$(TARGET)_img.c --native-file=system_test/$(TARGET)_nat.c $(PM_TEST_USR_SOURCES)

clean :
	$(MAKE) -C ../../vm clean
	$(RM) $(TARGET).out $(OBJS) $(TARGET)_img.* $(TARGET)_nat.* pmfeatures.h
