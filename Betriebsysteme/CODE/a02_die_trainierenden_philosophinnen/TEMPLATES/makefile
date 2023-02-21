# makefile for tex using latexmk
LATEX="/usr/bin/latexmk"
FORMATFLAG="--pdf"
MINTEDFLAG="--shell-escape"

# zip it up
ZIP=/usr/bin/tar
ZIPOPT=cfvz
ZIPFILE="archive.tar.gz"
CONTENT="*.pdf *.c *.h"

.PHONY: clean clc

%.pdf: %.tex
	${LATEX} $(MINTEDFLAG) $(FORMATFLAG) $<

clean:
	rm -rdf _minted* *.aux *.log *.out *.toc
	rm -f *.o *~

clc: clean
	rm -f *.pdf
	rm *.tar.gz
	rm -rf .depend

zip: ${CONTENT}
	${ZIP} ${ZIPOT} ${ZIPFILE} ${CONTENT}

# make for c
CC=/usr/bin/gcc
#CFLAGS=-I/usr/include/nptl -D_REENTRANT
CFLAGS=-D_REENTRANT -ggdb -Wall -ansi
#LDFLAGS=-L/usr/lib/nptl -lpthread
LDFLAGS=-lpthread

OBJ = datei1.o datei2.o datei3.o datei4.o datei5.o
SRC = $(OBJ:%.o=%.c)

DEPENDFILE = .depend

dep: $(SRC)
        $(CC) $(CFLAGS) -MM $(SRC) > $(DEPENDFILE)

prog: $(OBJ)
        $(CC) $(CFLAGS) -o prog $(OBJ) $(LDFLAGS)

%.o: %.c
        $(CC) $(CFLAGS) -c $<

ifeq (.depend,$(wildcard .depend))
include .depend
endif
