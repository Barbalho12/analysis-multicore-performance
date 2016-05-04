#include <thread>
#include <cstdio>
#include <chrono>
#include <vector>
#include <sched.h>
#include <math.h>       /* sin */
#include <iostream>
#include <fstream>
using namespace std;

#define NUMTHREADS 4
#define TAMANHO_VETOR 100*1000*1000

/*Criar um vetor float com 100*1000*1000 (100M) elementos*/
float vetor [TAMANHO_VETOR];

#define ANALISE_1_1 "dados-coletados/analise1_1.dat"
#define ANALISE_1_2 "dados-coletados/analise1_2.dat"
#define ANALISE_1_3 "dados-coletados/analise1_3.dat"
#define ANALISE_2_1 "dados-coletados/analise2_1.dat"
#define ANALISE_2_2 "dados-coletados/analise2_2.dat"
#define ANALISE_2_3 "dados-coletados/analise2_3.dat"
#define ANALISE_3_1 "dados-coletados/analise3_1.dat"
#define ANALISE_3_2 "dados-coletados/analise3_2.dat"
#define ANALISE_3_3 "dados-coletados/analise3_3.dat"

/**
 * Apaga os arquivos da execução anterior, caso existam.
 */
void clearFiles() {

    const string files[] = {ANALISE_1_1, ANALISE_1_2, ANALISE_1_3,
                    ANALISE_2_1, ANALISE_2_2, ANALISE_2_3,
                    ANALISE_3_1, ANALISE_3_2, ANALISE_3_3};

    for (int i = 0; i < 6; i++){
        ofstream init;
        // Abre o arquivo
        init.open(files[i], ios_base::in);
        // Verifica se o arquivo existe
        if (init) {
            // Fecha o arquivo
            init.close();
            if( files[i] == ANALISE_1_1){
                remove(ANALISE_1_1);
            }else if( files[i] == ANALISE_1_2){
                remove(ANALISE_1_2);
            }else if( files[i] == ANALISE_1_3){
                remove(ANALISE_1_3);
            }else if( files[i] == ANALISE_2_1){
                remove(ANALISE_2_1);
            }else if( files[i] == ANALISE_2_2){
                remove(ANALISE_2_2);
            }else if( files[i] == ANALISE_2_3){
                remove(ANALISE_2_3);
            }else if( files[i] == ANALISE_3_1){
                remove(ANALISE_3_1);
            }else if( files[i] == ANALISE_3_2){
                remove(ANALISE_3_2);
            }else if( files[i] == ANALISE_3_3){
                remove(ANALISE_3_3);
            }

        }
    }
}

void saveInFile(string content, string path){
    ofstream out;
    out.open(path, ios::app);
    out << content << endl;
    out.close();
}

void saveInFile(int sizeVetor, double media ,double dp_inf, double dp_sup, string path){
    ofstream out;
    out.open(path, ios::app);
    out << sizeVetor << " " << media << " " << dp_inf << " " << dp_sup << endl;
    out.close();
}



/*Valores aleatórios entre -1 e 1*/
double initVetor(){
    auto t1 = std::chrono::high_resolution_clock::now();
    srand((unsigned)time(NULL));
    for(int i = 0; i < TAMANHO_VETOR; i++){
        vetor[i] = (rand() % 3) -1;
    }
    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*Somatório de todos os valores do vetor*/
int function1_SOMA(int it){
    //cout << "Thread" << it << "está executando no núcleo " << sched_getcpu() << endl;

    int soma = 0;

    for(int i = 0; i < TAMANHO_VETOR; i++){
        soma += vetor[i];
    }

    return soma;
}

/*Somatório de todos os valores sin[elemento i] do vetor*/
int function2_SIN(int it){
    //cout << "Thread" << it << "está executando no núcleo " << sched_getcpu() << endl;

    int soma = 0;

    for(int i = 0; i < TAMANHO_VETOR; i++){
        soma += sin(vetor[i]);
    }

    return soma;
}

/*Somatório de todos os valores log[elemento i] do vetor */
int function3_LOG(int it){
    //cout << "Thread" << it << "está executando no núcleo " << sched_getcpu() << endl;

    int soma = 0;

    for(int i = 0; i < TAMANHO_VETOR; i++){
        soma += log(vetor[i]);
    }

    return soma;
}


/*Para cada função: Executar em uma thread e apenas um core*/

/*ANÁLISE 1 - FUNÇÃO 1*/
double analise1_1(){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    thread thr_soma(function1_SOMA, 0);
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_soma.native_handle(), sizeof(cpu_set_t), &cpuset);
    thr_soma.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*ANÁLISE 1 - FUNÇÃO 2*/
double analise1_2(){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    thread thr_sin(function2_SIN, 0);
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_sin.native_handle(), sizeof(cpu_set_t), &cpuset);
    thr_sin.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*ANÁLISE 1 - FUNÇÃO 3*/
double analise1_3(){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    thread thr_log(function3_LOG, 0);
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_log.native_handle(), sizeof(cpu_set_t), &cpuset);
    thr_log.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*Para cada função: Executar duas instâncias da função em duas threads e em cores diferentes*/

/*ANÁLISE 2 - FUNÇÃO 1*/
double analise2_1(){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    thread thr_soma0(function1_SOMA, 0);
    thread thr_soma1(function1_SOMA, 1);

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_soma0.native_handle(), sizeof(cpu_set_t), &cpuset);

    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(thr_soma1.native_handle(), sizeof(cpu_set_t), &cpuset);

    thr_soma0.join();
    thr_soma1.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*ANÁLISE 2 - FUNÇÃO 2*/
double analise2_2(){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    thread thr_sin0(function2_SIN, 0);
    thread thr_sin1(function2_SIN, 1);

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_sin0.native_handle(), sizeof(cpu_set_t), &cpuset);

    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(thr_sin1.native_handle(), sizeof(cpu_set_t), &cpuset);

    thr_sin0.join();
    thr_sin1.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*ANÁLISE 2 - FUNÇÃO 3*/
double analise2_3(){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    thread thr_log0(function3_LOG, 0);
    thread thr_log1(function3_LOG, 1);

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_log0.native_handle(), sizeof(cpu_set_t), &cpuset);

    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(thr_log1.native_handle(), sizeof(cpu_set_t), &cpuset);

    thr_log0.join();
    thr_log1.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*Para cada função: Executar duas instâncias da função em duas threads e em um mesmo core*/

/*ANÁLISE 3 - FUNÇÃO 1*/
double analise3_1(){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    thread thr_soma0(function1_SOMA, 0);
    thread thr_soma1(function1_SOMA, 1);

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_soma0.native_handle(), sizeof(cpu_set_t), &cpuset);

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_soma1.native_handle(), sizeof(cpu_set_t), &cpuset);

    thr_soma0.join();
    thr_soma1.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*ANÁLISE 3 - FUNÇÃO 2*/
double analise3_2(){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    thread thr_sin0(function2_SIN, 0);
    thread thr_sin1(function2_SIN, 1);

    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(thr_sin0.native_handle(), sizeof(cpu_set_t), &cpuset);

    CPU_ZERO(&cpuset);
    CPU_SET(1, &cpuset);
    pthread_setaffinity_np(thr_sin1.native_handle(), sizeof(cpu_set_t), &cpuset);

    thr_sin0.join();
    thr_sin1.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

/*ANÁLISE 3 - FUNÇÃO 3*/
double analise3_3(){
    auto t1 = std::chrono::high_resolution_clock::now();
    cpu_set_t cpuset;

    thread thr_log0(function3_LOG, 0);
    thread thr_log1(function3_LOG, 1);

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_log0.native_handle(), sizeof(cpu_set_t), &cpuset);

    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    pthread_setaffinity_np(thr_log1.native_handle(), sizeof(cpu_set_t), &cpuset);

    thr_log0.join();
    thr_log1.join();

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}


int main(int argc, char *argv[]){
    system("mkdir dados-coletados");
	// Apaga os arquivos da execução anterior
	clearFiles();

    // Quantidade de cores do computador
    unsigned int n = thread::hardware_concurrency();
    cout << "Minha CPU possui " << n << " núcleos\n";
    cout << "--------------------------------------" << "\n";

    cout << "Tempo de Criação do Vetor: " << initVetor() << "\n";
    cout << "--------------------------------------" << "\n";

    // Aux
    double value;
    string path;

    ofstream out;

    value = analise1_1();
    cout << "Analise 1 - Função 1: " << value << "\n";
    path = ANALISE_1_1;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    value = analise1_2();
    cout << "Analise 1 - Função 2: " << value << "\n";
    path = ANALISE_1_2;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    value = analise1_3();
    cout << "Analise 1 - Função 3: " << value << "\n";
    path = ANALISE_1_3;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    cout << "--------------------------------------" << "\n";

    value = analise2_1();
    cout << "Analise 2 - Função 1: " << value << "\n";
    path = ANALISE_2_1;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    value = analise2_2();
    cout << "Analise 2 - Função 2: " << value << "\n";
    path = ANALISE_2_2;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    value = analise2_3();
    cout << "Analise 2 - Função 3: " << value << "\n";
    path = ANALISE_2_3;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    cout << "--------------------------------------" << "\n";

    value = analise3_1();
    cout << "Analise 3 - Função 1: " << value << "\n";
    path = ANALISE_3_1;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    value = analise3_2();
    cout << "Analise 3 - Função 2: " << value << "\n";
    path = ANALISE_3_2;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    value = analise3_3();
    cout << "Analise 3 - Função 3: " << value << "\n";
    path = ANALISE_3_3;
    out.open(path, ios::app);
    out << TAMANHO_VETOR << " " << value << endl;
    out.close();

    // -------------------------------------------------------------------- //


    string script_gnuplot_dp = "set encoding iso_8859_1 \n"
                                "set grid \n"
                                "set key top left \n"
                                "set title 'Análise de desempenho com a função Clock' \n"
                                "set xlabel 'Tamanho do vetor' \n"
                                "set ylabel 'Tempo (segundos)' \n"
                                "# Analise 1.1 \n"
                                "plot 'analise1_1.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise1_1.dat' using 1:2:3:4 t 'Analise 1.1' with yerrorbars ls 1 lt 8 \n"
                                "# Analise 1.2 \n"
                                "plot 'analise1_2.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise1_2.dat' using 1:2:3:4 t 'Analise 1.2' with yerrorbars ls 1 lt 8 \n"
                                "# Analise 1.3 \n"
                                "plot 'analise1_3.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise1_3.dat' using 1:2:3:4 t 'Analise 1.3' with yerrorbars ls 1 lt 8 \n"
                                "# Analise 2.1 \n"
                                "plot 'analise2_1.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise2_1.dat' using 1:2:3:4 t 'Analise 2.1' with yerrorbars ls 1 lt 8 \n"
                                "# Analise 2.2 \n"
                                "plot 'analise2_2.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise2_2.dat' using 1:2:3:4 t 'Analise 2.2' with yerrorbars ls 1 lt 8 \n"
                                "# Analise 2.3 \n"
                                "plot 'analise2_3.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise2_3.dat' using 1:2:3:4 t 'Analise 2.3' with yerrorbars ls 1 lt 8 \n"
                                "# Analise 3.1 \n"
                                "plot 'analise3_1.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise3_1.dat' using 1:2:3:4 t 'Analise 3.1' with yerrorbars ls 1 lt 8 \n"
                                "# Analise 3.2 \n"
                                "plot 'analise3_2.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise3_2.dat' using 1:2:3:4 t 'Analise 3.2' with yerrorbars ls 1 lt 8 \n"
                                "# Analise 3.3 \n"
                                "plot 'analise3_3.dat' using 1:2 notitle with linespoints ls 1 lt 8 \n"
                                "rep 'analise3_3.dat' using 1:2:3:4 t 'Analise 3.3' with yerrorbars ls 1 lt 8 \n"
                                "set terminal png \n"
                                "set output 'grafico.png' \n"
                                "replot \n";


    saveInFile(script_gnuplot_dp, "dados-coletados/script_gnuplot.gnu");

    system("cd dados-coletados && gnuplot script_gnuplot.gnu");

    return 0;
}
