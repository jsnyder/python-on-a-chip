# PyMite Configuration
PLATFORM := $(notdir $(CURDIR))
PM_LIB_ROOT = pmvm.$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
PM_USR_SOURCES = main.py
PM_HEAP_SIZE = 0x2000
PMIMGCREATOR := ../../tools/pmImgCreator.py

TARGET = main
SOURCES = $(TARGET).c plat.c $(TARGET)_nat.c $(TARGET)_img.c
OBJS = $(SOURCES:.c=.o)

CDEFS = -DHEAP_SIZE=$(PM_HEAP_SIZE)
ifeq ($(DEBUG),true)
	CDEFS += -g -ggdb -D__DEBUG__=1
endif
CFLAGS = -Os -Wall -gstabs -Wstrict-prototypes -Werror -ansi -I../../vm $(CDEFS)

%.out : %*_nat.c %*_img.c %.c
	$(CC) $(CFLAGS) -o $@ $*_nat.c $*_img.c $*.c ../../vm/libpmvm.a

.PHONY: all clean

export CFLAGS IPM HEAP_SIZE PM_LIB_FN

all : $(TARGET).out

$(PM_LIB_PATH) : ../../vm/*.c ../../vm/*.h
	make -C ../../vm IPM=true

$(TARGET).out : $(OBJS) $(PM_LIB_PATH)
	$(CC) -o $@ $(OBJS) $(PM_LIB_PATH)

# Generate native code and module images from the python source
$(TARGET)_nat.c $(TARGET)_img.c: $(PM_USR_SOURCES)
	$(PMIMGCREATOR) -c -u -o $(TARGET)_img.c --native-file=$(TARGET)_nat.c $(PM_USR_SOURCES)

clean :
	$(MAKE) -C ../../vm clean
	$(RM) $(OBJS) $(TARGET)_img.* $(TARGET)_nat.*
