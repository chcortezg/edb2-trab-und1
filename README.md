# Análise empírica de complexidade de algoritmos

Este programa mede o tempo de execução de algoritmos de busca sequencial e binária para diferentes tamanhos de vetor e compara com funções assintóticas teóricas O(n) e O(log n). Após isso, gera um gráfico que mostra o crescimento do tempo em função do tamanho da entrada para os algoritmos de busca e as funções.

## Estrutura
- `main.cpp`: coleta dados, calcula médias e gera o gráfico  
- `buscas.h/cpp`: implementa as buscas sequencial e binária  
- `utils.h/cpp`: funções utilitárias  
- `Makefile`: compila o projeto
- `dados_analise.dat`: dados gerados para o gráfico  
- `analise.png`: gráfico final plotado com gnuplot

## Uso
1. Instale o gnuplot.
2. Compile:
   ```bash
   make
3. Execute:
   ```bash
   ./analise
