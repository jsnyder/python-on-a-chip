SHELL = /bin/sh

RST2HTML := rst2html.py
MKDIR := mkdir -p
MV := mv
HTML_DEST := ../html
DOC_SOURCES := $(wildcard *.txt)
DOC_HTML := $(DOC_SOURCES:.txt=.html)


.PHONY: all html clean

# Builds html from restructured text source
%.html : %.txt
	$(RST2HTML) $< $@

# Default action is to build html docs
all : html

# Creates html documentation
html : $(DOC_HTML)
	$(MKDIR) $(HTML_DEST)
	$(MV) *.html $(HTML_DEST)

# Removes files made by default make
clean :
	$(RM) -r $(HTML_DEST)
