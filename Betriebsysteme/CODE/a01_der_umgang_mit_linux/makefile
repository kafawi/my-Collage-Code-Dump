# latex make file
# make shure, that your default python compiler is python2
# if not, just type "alias python=python2" to chance
LATEX=/usr/bin/pdflatex
MINTEDFLAG=--shell-escape
PDFREADER=foxitreader
#PDFREADER=acroread

.PHONY: clean clc

default: protokoll clean
	#	${PDFREADER} Protokoll01.pdf &

debug: protokoll
	less Protokoll01.log

protokoll: Protokoll01.pdf filecount.sh

entwurf: Entwurf01.pdf lfilecound.sh

%.pdf:%.tex ./filecount.sh
	${LATEX} $(MINTEDFLAG) $<
clean:
	rm -rdf _minted* *.aux *.log *.out *.toc
clc: clean
	rm *.pdf

gzipp: Protokoll01.pdf filecount.sh typescript
	tar cfvz BSP_A1_Mendel_Witte.tar.gz Protokoll01.pdf filecount.sh typescript
