#include <thread>
#include <cstdio>
#include <chrono>
#include <vector>
#include <sched.h>
#include <math.h>       /* sin */
#include <iostream>
using namespace std;

#define NUMTHREADS 4
#define TAMANHO_VETOR 100*1000*1000

/*Criar um vetor float com 100*1000*1000 (100M) elementos*/
float vetor [TAMANHO_VETOR];


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
    unsigned int n = thread::hardware_concurrency();
    cout << "Minha CPU possui " << n << " núcleos\n";
    cout << "--------------------------------------" << "\n";
    cout << "Tempo de Criação do Vetor: " << initVetor() << "\n";
    cout << "--------------------------------------" << "\n";
    cout << "Analise 1 - Função 1: " << analise1_1() << "\n";
    cout << "Analise 1 - Função 2: " << analise1_2() << "\n";
    cout << "Analise 1 - Função 3: " << analise1_3() << "\n";
    cout << "--------------------------------------" << "\n";
    cout << "Analise 2 - Função 1: " << analise2_1() << "\n";
    cout << "Analise 2 - Função 2: " << analise2_2() << "\n";
    cout << "Analise 2 - Função 3: " << analise2_3() << "\n";
    cout << "--------------------------------------" << "\n";
    cout << "Analise 3 - Função 1: " << analise3_1() << "\n";
    cout << "Analise 3 - Função 2: " << analise3_2() << "\n";
    cout << "Analise 3 - Função 3: " << analise3_3() << "\n";



    return 0;
}
