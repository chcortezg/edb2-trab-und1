#pragma once

// métodos utilitários
double medirTempo(int (*func)(int[], int, int), int vetor[], int tamanho, int chave);
void gerarVetor(int vetor[], int tamanho);
void ordenarVetor(int vetor[], int tamanho);