# Analysis multicore performance #

Este projeto tem como objetivo de analisar o desempenho do ALGORITMO em relação a afinidade de CPU.
O testes serão feitos utilizando a execução normal do algoritmo e a exercução limitando a quantidade de 
CPUs que o programa irá poder utilizar.

## Índice ##

1. Requisitos para fazer a análise
2. Gnuplot Tutorial
3. Resultados
4. Conclusão
	4. Instalar o gnuplot
	4. Gerando o gráfico
5. Membros
6. Fontes

## 1. Requisitos para fazer a análise ##

* Use um computador com alguma distribuição Linux (Indicamos o Ubuntu).
* Instale os seguintes pacotes para atualizar o C++.

		sudo apt-get install gcc-5-multilib g++-5-multilib

* [Baixe](http://goo.gl/q8zaor) e instale o SDK Texas Instruments e instale usando os comandos a seguir e avance todas as opções clicando em "Next".

		chmod +x nomedoarquivobaixado

		./nomedoarquivobaixado

## 2. Gnuplot Tutorial ##

O gnuplot é um software que falicita a criação de gráficos (2D e 3D) para vários ambientes (UNIX, Windows, Macintosh, etc.). A seguir teremos alguns comandos básicos para a utilização desta ferramenta.

###i. Instalar o gnuplot ###

	sudo apt-get install gnuplot-x11

###ii. Gerando o gráfico ###

1. Acessa o diretório que contém os arquivos "clock.dat" e "time.dat" (que foram gerados pela execução dos métodos) e "grafico.gnu" (Script de execução do gnuplot) pelo terminal:

	cd data

2. Digita o omando no Terminal:

	gnuplot grafico.gnu

Para criar os gráficos basta executar o gnuplot utilizando o script gnuplot deste projeto.

	gnuplot performance.gnuplot

##3. Resultados ##

Nessa seção, temos os resultados dos testes dos algoritmos BubbleSort, QuickSort e MergeSort.

(IMPORTANTE) Nos gráficos, no eixo das "Análises" ignore os números 1,5 e 2,5, pois não correspondem a nenhuma análise. O conteúdo foi publicado dessa forma pois não foi conseguido utilizar gráfico de barras.

O programa executou sozinho no computador. Para cada função foram realizadas 3 Análises diferentes:

1. Executar a função em uma thread e apenas um core;
2. Executar duas instâncias da mesma função em duas threads e em cores diferentes;
3. Executar duas instâncias da mesma função em duas threads e em um mesmo core.

Dessa forma construimos 3 Gráficos, um para cada função, na qual é exibido os tempos de execução 
de para cada uma das análises:

![f1](MulticorePerformance/dados-coletados/f1.png?raw=true "Análises da Função 1")

![f2](MulticorePerformance/dados-coletados/f2.png?raw=true "Análises da Função 2")

![f3](MulticorePerformance/dados-coletados/f3.png?raw=true "Análises da Função 3")

![log](log.png?raw=true "Log de Eventos")

## 4. Conclusão ##

Esse trabalho apresentou uma análise de eficiência das diferentes possibilidades de execução de um programa em ambientes multicore que o hardware oferece. Analisando os gráficos das analises de tempo das funções a execução da função 1 é a mais rápida em todas as análises, o que é o esperado, pois é a função mais simples. A função 2 é mais lenta na execução da primeira análise, tendo mais de 2s de duração. Na segunda análise temos que há praticamente um empate entre as funções 2 e 3 com aproximadamente 2,5s de duração. Na terceira análise a função 3 está mais rápida que a função 2 com diferença de aproximadamente 0,2s.

Como podemos notar nos gráficos, ao se usar dois núcleos executando duas intâncias da mesma função, cada uma em uma thread, o tempo de execução cai pela metade, comparado a execução em um único núcleo. Dessa forma, notamos o quanto é importante no desenvolvimento de sistemas de software, o conhecimento sobre a capacidade de hardware da máquina, e aplicação de conceitos de programação distribuida.

## 5. Membros ##

* Breno Maurício de Freitas Viana
* Felipe Barbalho Rocha

## 6. Fontes ##

* [Usando Gnuplot para gerar bons gráficos](http://www.dicas-l.com.br/arquivo/usando_gnuplot_para_gerar_bons_graficos.php)
* [Gnuplot - Manual simplificado para iniciantes](http://www.ebah.com.br/content/ABAAAgUS4AF/gnuplot-manual-simplificado-iniciantes?part=1)
