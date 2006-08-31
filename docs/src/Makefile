SHELL = /bin/sh
RST2HTML := rst2html.py
HTML_DEST := ../html/
DOC_SOURCES := $(wildcard *.txt)
DOC_HTML := $(addprefix $(HTML_DEST),$(DOC_SOURCES:.txt=.html))


.PHONY: all html clean

# Generates html from restructured text source
$(HTML_DEST)%.html : %.txt
	$(RST2HTML) $< $@

# Default action is to generate html docs
all : html

# Generates html documentation
html : $(DOC_HTML)

# Removes files made by default make
clean :
	$(RM) $(DOC_HTML)
