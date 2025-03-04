[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/k3hxmOSc)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=18519579)
## Para entregar

1. **Crie dois executáveis para a parte de multiplicação de matrizes: um que percorre em ordem de linha e outro que percorre em ordem de coluna.**

   Faça agora a multiplicação de matrizes considerando:  
   
   $A * B = C$, onde:

  1. Dimensões de A: M x N

  2. Dimensões de B: N x X (qq dimensão razoável, mas não um vetor)

  3. Consequentemente, dimensões de C: M x X

  se quiser, pode utilizar matrizes quadradas.

2. **Crie um terceiro executável para utilizar corretamente o cache (hierarquia de memória)**:

   Para utilizar corretamente o cache (L1, L2) utilizando a abordagem de **blocagem** apresentada no [artigo da Intel](https://www.intel.com/content/www/us/en/developer/articles/technical/putting-your-data-and-code-in-order-optimization-and-memory-part-1.html).

   Você deve fazer a análise da velocidade do seu algoritmo compilando o código da seguinte forma:

  a. desligando todas as otimizações do compilador, como indicado acima.

  b. ligando a otimização máxima.

   Para cada opção, você deve medir o tempo de execução, seguindo o exemplo mostrado nos trechos de código acima.

3. **Valgrind**

  Faça também uma análise do padrão de acesso ao cache de todas as versões utilizando o utilitário `valgrind`. Veja abaixo um exemplo de saída que o **`valgrind`** dá:

```
$ valgrind --tool=cachegrind ./matmulcol
==23104== Cachegrind, a cache and branch-prediction profiler
==23104== Copyright (C) 2002-2015, and GNU GPL'd, by Nicholas Nethercote et al.
==23104== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==23104== Command: ./matmulcol
==23104==
--23104-- warning: L3 cache found, using its data for the LL simulation.
Column order; tempo para multiplicar coluna: 0.085526 secs
==23104==
==23104== I   refs:      17,994,092
==23104== I1  misses:         1,051
==23104== LLi misses:         1,040
==23104== I1  miss rate:       0.01%
==23104== LLi miss rate:       0.01%
==23104==
==23104== D   refs:      12,641,331  (7,385,328 rd   + 5,256,003 wr)
==23104== D1  misses:     1,117,327  (    2,580 rd   + 1,114,747 wr)
==23104== LLd misses:       134,009  (    2,378 rd   +   131,631 wr)
==23104== D1  miss rate:        8.8% (      0.0%     +      21.2%  )
==23104== LLd miss rate:        1.1% (      0.0%     +       2.5%  )
==23104==
==23104== LL refs:        1,118,378  (    3,631 rd   + 1,114,747 wr)
==23104== LL misses:        135,049  (    3,418 rd   +   131,631 wr)
==23104== LL miss rate:         0.4% (      0.0%     +       2.5%  )


$ valgrind --tool=cachegrind ./matmulrow
==23161== Cachegrind, a cache and branch-prediction profiler
==23161== Copyright (C) 2002-2015, and GNU GPL'd, by Nicholas Nethercote et al.
==23161== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==23161== Command: ./matmulrow
==23161==
--23161-- warning: L3 cache found, using its data for the LL simulation.
Row order; tempo para multiplicar: 0.053935 secs
==23161==
==23161== I   refs:      17,993,582
==23161== I1  misses:         1,049
==23161== LLi misses:         1,038
==23161== I1  miss rate:       0.01%
==23161== LLi miss rate:       0.01%
==23161==
==23161== D   refs:      12,641,128  (7,385,188 rd   + 5,255,940 wr)
==23161== D1  misses:       134,287  (    2,579 rd   +   131,708 wr)
==23161== LLd misses:       134,009  (    2,378 rd   +   131,631 wr)
==23161== D1  miss rate:        1.1% (      0.0%     +       2.5%  )
==23161== LLd miss rate:        1.1% (      0.0%     +       2.5%  )
==23161==
==23161== LL refs:          135,336  (    3,628 rd   +   131,708 wr)
==23161== LL misses:        135,047  (    3,416 rd   +   131,631 wr)
==23161== LL miss rate:         0.4% (      0.0%     +       2.5%  )
```

## Entregas

1. Você deve entregar um código fonte para cada versão do algoritmo implementado.
2. Você deve entregar um relatório em PDF com as evidências de todas as **compilações** e **execuções** dos códigos.
3. Você deve fazer uma análise da saída do **`valgrind`**  para o **item 3** discutindo os resultados.
