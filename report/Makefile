OUT = report

${OUT}.pdf: ${OUT}.tex
	pdflatex $^

clean:
	rm -f ${OUT}.{ps,pdf,log,aux,out,dvi,bbl,blg}
