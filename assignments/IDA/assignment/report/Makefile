TEX = pandoc
src = template.tex details.yml
FLAGS = --pdf-engine=xelatex

resume.pdf : $(src)
	$(TEX) $(filter-out $<,$^ )  $< $(FLAGS) -o $@

.PHONY: clean
clean :
	rm resume.pdf
