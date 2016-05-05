set encoding iso_8859_1 
set grid 
set key top left 
set xlabel 'Análise' 
set ylabel 'Tempo (segundos)' 
# Função 1 
set title 'Tempo para execução da Função-1 em cada Análise' 
plot 'func1.dat' using 1:2 notitle with linespoints 
set terminal png 
set output 'f1.png' 
replot 
# Função 2 
set title 'Tempo para execução da Função-2 em cada Análise' 
plot 'func2.dat' using 1:2 notitle with linespoints 
set terminal png 
set output 'f2.png' 
replot 
# Função 3 
set title 'Tempo para execução da Função-3 em cada Análise' 
plot 'func3.dat' using 1:2 notitle with linespoints 
set terminal png 
set output 'f3.png' 
replot 

