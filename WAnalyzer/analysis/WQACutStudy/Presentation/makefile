.SUFFIXES : .tex .dvi

NAME = beamer
TEX = latex
OBJ = $(NAME).dvi
SRC = $(NAME).tex

all : pdf

#ps	: $(OBJ)
#	dvips $(OBJ) -o
#	rm -rf *.toc *.lot *.log *.lof *.blg *.bbl *.aux
#	gv $(NAME).ps

pdf : $(SRC)
#	dvipdfm $(OBJ)
	pdflatex $(SRC)
	rm -rf *.toc *.lot *.log *.lof *.blg *.bbl *.aux *.nav *.out *.snm
#	kpdf $(NAME).pdf
	

#$(OBJ) :
#	latex $(NAME)
#	bibtex $(NAME)
#	latex $(NAME)


clean :
	rm -rf *.nav  *.out  *.snm *.toc *.lot *.log *.lof *.dvi *.blg *.bbl *.aux *.dvi *.ps *.pdf

