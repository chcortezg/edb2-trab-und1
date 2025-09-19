#include "utils.h"
#include <chrono>
#include <iostream>
#include <cmath>
using namespace std;

// para medir o tempo usando chrono
double medirTempo(int (*func)(int[], int, int), int vetor[], int tamanho, int chave) {
    auto inicio = chrono::high_resolution_clock::now();
    func(vetor, tamanho, chave);
    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> duracao = fim - inicio;
    return duracao.count();
}

// para gerar vetores aleatórios
void gerarVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) vetor[i] = rand() % 100000;
}

// para ordenar vetores na execução da busca binária
void ordenarVetor(int vetor[], int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int key = vetor[i];
        int j = i - 1;
        while (j >= 0 && vetor[j] > key) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = key;
    }
}
