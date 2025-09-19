#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include "buscas.h"
#include "utils.h"

using namespace std;

// funções assintóticas teóricas para comparação
double f_n(int n) { return n; }
double f_logN(int n) { return log2(n); }

int main() {
    srand((unsigned) time(nullptr)); // inicializando gerador de números aleatórios

    // definindo os tamanhos das entradas e número de repetições
    const int numTamanhos = 10;
    int tamanhos[numTamanhos] = {10000, 20000, 30000, 40000, 50000,
                                 60000, 70000, 80000, 90000, 100000};
    int repeticoes = 30;

    // arrays para armazenar o tempo médio de cada algoritmo para cada tamanho
    double temposSeq[numTamanhos] = {0.0};
    double temposBin[numTamanhos] = {0.0};

    cout << "Coletando os tempos de execução \n";

    // coletando de dados para cada tamanho de entrada
    for (int i = 0; i < numTamanhos; ++i) {
        int n = tamanhos[i];
        double acumSeq = 0.0; // acumulador de tempo para a busca sequencial
        double acumBin = 0.0; // acumulador de tempo para busca binária

        // Rrepetições para minimizar efitos externos
        for (int r = 0; r < repeticoes; ++r) {
            int *v = new int[n];       // aloca um vetor dinâmico
            gerarVetor(v, n);          // preenche com números aleatórios
            int chave = v[rand() % n]; // escolhe  uma chave aleatória para busca

            // medindo tempo da busca sequencial
            acumSeq += medirTempo(buscaSequencial, v, n, chave);

            // ordenando vetor para a busca binária
            ordenarVetor(v, n);

            // medindo tempo da busca binária
            acumBin += medirTempo(buscaBinaria, v, n, chave);

            delete[] v; // liberando memória
        }

        // calcula o tempo médio para cada algoritmo
        temposSeq[i] = acumSeq / repeticoes;
        temposBin[i] = acumBin / repeticoes;

        // exibe resultados médio
        cout << "N = " << n
             << " - Busca sequencial = " << temposSeq[i] << "s"
             << " - Busca binária = " << temposBin[i] << "s \n";
    }

    // ajuste das funções assintóticas aos tempos experimentais
    // multiplicadores k para aproximar escala experimental
    double kSeq = temposSeq[0] / f_n(tamanhos[0]);
    double kBin = temposBin[0] / f_logN(tamanhos[0]);

    // salvando dados em arquivo para plotagem no gnuplot
    ofstream arq("dados_comparacao.dat");
    for (int i = 0; i < numTamanhos; i++) {
        arq << tamanhos[i] << " "
            << temposSeq[i] << " "
            << temposBin[i] << " "
            << kSeq * f_n(tamanhos[i]) << " "
            << kBin * f_logN(tamanhos[i]) << "\n";
    }
    arq.close();

    // gerando gráfico no gnuplot
    system(
        "gnuplot -e \"set terminal png size 1000,600; set output 'analise.png'; "
        "set title 'Comparação de complexidades'; "
        "set xlabel 'Tamanho da entrada'; set ylabel 'Tempo (s)'; "
        "set logscale y; set grid; "
        "plot 'dados_comparacao.dat' using 1:2 with linespoints lw 2 pt 7 title 'Busca sequencial experimental', "
        "'dados_comparacao.dat' using 1:3 with linespoints lw 2 pt 7 title 'Busca binária experimental', "
        "'dados_comparacao.dat' using 1:4 with lines lw 2 title 'O(n) teórico', "
        "'dados_comparacao.dat' using 1:5 with lines lw 2 title 'O(log n) teórico'\""
    );

    cout << "Gráfico gerado: analise.png \n";

    return 0;
}
