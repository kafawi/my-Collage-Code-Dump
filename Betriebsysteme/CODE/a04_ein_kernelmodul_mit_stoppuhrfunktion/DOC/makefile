# makefile for tex using latexmk
LATEX="/usr/bin/latexmk"
FORMATFLAG="--pdf"
MINTEDFLAG="--shell-escape"
ENTWURF=entwurf
PROTOKOLL=protokoll

.PHONY: clean clc

$(PROTOKOLL): $(PROTOKOLL).pdf
$(ENTWURF): $(ENTWURF).pdf

%.pdf: %.tex
	${LATEX} $(MINTEDFLAG) $(FORMATFLAG) $<

clean:
	rm -rdf _minted* *.aux *.log *.out *.toc *_latexmk *~ .*~ *.fls

clc: clean
	rm -f *.pdf
