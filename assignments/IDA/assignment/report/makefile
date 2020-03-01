TEX = pandoc
src = elsarticle-template-num.tex elsarticle-template-harv.tex
FLAGS = --pdf-engine=pdflatex

report:
	pdflatex -jobname=$@ elsarticle-template-num.tex elsarticle-template-harv.tex

.PHONY: clean
clean :
	rm  *.log *.pdf


