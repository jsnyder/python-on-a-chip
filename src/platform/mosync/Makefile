# PyMite Configuration
PLATFORM := $(notdir $(CURDIR))
PM_LIB_ROOT = pmvm_$(PLATFORM)
PM_LIB_FN = lib$(PM_LIB_ROOT).a
PM_LIB_PATH = ../../vm/$(PM_LIB_FN)
PM_USR_SOURCES = main.py ma.py 
PMIMGCREATOR := ../../tools/pmImgCreator.py
PMGENPMFEATURES := ../../tools/pmGenPmFeatures.py
#IPM = true
#DEBUG = true

TARGET = main

.PHONY: all clean

all : pmfeatures.h $(TARGET)_nat.c $(TARGET)_img.c ../../vm/pmstdlib_img.c ../../vm/pmstdlib_nat.c

pmfeatures.h : pmfeatures.py $(PMGENPMFEATURES)
	$(PMGENPMFEATURES) pmfeatures.py > $@

# Build the standard libraries
../../vm/pmstdlib_img.c ../../vm/pmstdlib_nat.c :
	$(MAKE) PLATFORM=mosync -C ../../vm bytecode

# Generate native code and module images from the python source
$(TARGET)_nat.c $(TARGET)_img.c: $(PM_USR_SOURCES) pmfeatures.py
	$(PMIMGCREATOR) -f pmfeatures.py -c -u -o $(TARGET)_img.c --native-file=$(TARGET)_nat.c $(PM_USR_SOURCES)

clean :
	$(RM) $(TARGET)_img.* $(TARGET)_nat.* pmfeatures.h ../../vm/pmstdlib_img.c ../../vm/pmstdlib_nat.c
