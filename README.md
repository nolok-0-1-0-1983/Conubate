# Conubate
Um conversor que transporta números entre duas bases quaisquer que estejam entre 2 e 36, escrito em português brasileiro. Contém:
- o conversor em si
- um modo passo-a-passo detalhando a conversão
- um leitor de arquivos `.csv`
- um modo quiz
- uma calculadora de máximos com k dígitos em cada base

Todos os quais escritos em C++.

Este software é fruto do trabalho dos aunos de graduação do 1º período de Ciência da Computação, Natan Uchôa e João Marcelo Firmino, como primeiro projeto prático da disciplina Introdução à Computação, ministrada pelo professor Rafael Durelli na Universidade Federal de Lavras (UFLA).

**Conubate** é um acrônimo para "**Co**nversor **nú**merico **ba**seado em **te**xto".

## Instalando e Bootando
Conubate pode ser obtido tal qual um repositório Git público qualquer. Pode-se clonar o repositório ou instalar o arquivo `.zip` e extrair este, por exemplo. Ao final, deverá haver um diretório contendo:
1. os subprogramas em C++ com seus respectivos `.h`, que formam, ao todo, o código-fonte:
  ```
  conversor_base_x_para_10.cpp
  conversor_base_x_para_10.h
  conversor_10_para_base_y.cpp
  conversor_10_para_base_y.h
  conversor_bases_potencia.cpp
  conversor_bases_potencia.h
  formatador.cpp
  formatador.h
  verificador.cpp
  verificador.h
  leitor_csv.cpp
  leitor_csv.h
  quiz.cpp
  quiz.h
  calculadora_maximos.cpp
  calculadora_maximos.h
  main.cpp
  ```
2. um arquivo `.csv`: `entrada.csv`
3. um README: `README.mk`
4. um executável: `conubate`

Pode-se diretamente executar o programa com `./conubate`, ou pode-se recompilar todo o código-fonte com o compilador de preferência. Eis um exemplo com `g++`:
```
g++ -Wall -Wextra calculadora_maximos.cpp conversor_10_para_base_y.cpp conversor_bases_potencia.cpp conversor_base_x_para_10.cpp formatador.cpp leitor_csv.cpp main.cpp quiz.cpp verificador.cpp -o conubate
```

## Usando
Ao iniciar Conubate, haverá 4 opções que se podem selecionar na tela inicial.
```
Conubate - Conversor Númerico Baseado em Texto
1.0.0 --- 27/05/26
Pelos alunos de graduação do 1º período, Natan Uchôa e João Marcelo Firmino, sob a direção de Prof. Rafael Durelli
Universidade Federal de Lavras (UFLA), DCC
1 - Converter número
2 - Ler arquivo CSV
3 - Modo quiz
4 - Calculadora de máximos
5 - Sair
```
### Conversor
Opção 1 da tela de apresentação dá acesso ao conversor.

Ele irá perguntar se `Deseja ativar o modo passo a passo? [s/n]`, o qual, para esta demonstração, considera-se que não (`n` ou `N`).

Ele irá em seguida pedir o número, em que base está e para qual base se deve transportar.
- o número pode possuir sinal (`+` ou `-`) e pode possuir parte fracionária delimitada por `.`.
  
  **NOTE QUE** `,` não é compreendido pelo compilador.

- as bases devem ser naturais de 2 aa 36 (inclusos), sem sinal, e devem ser diferentes entre si.

Fornecidas as entradas, o conversor irá iniciar os cálculos.

Se o número tiver uma parte fracionária (mesmo que nula), durante o processo, ele irá perguntar quantos dígitos o novo número de ter. Dependendo do algoritmo que executa, ele pode fazer a mesma pergunta novamente, considerando um número intermediário entre a entrada e a saída.

Ao final, ele mostrará o resultado.

Eis alguns exemplos:
```
Deseja ativar o modo passo a passo? [s/n] n
Insira o número que vai ser convertido: 1985
Insira a base do número que vai ser convertido: 10
Insira a base para qual o número deve ser convertido: 2
O número 1985 na base 2 é 11111000001
```
```
Deseja ativar o modo passo a passo? [s/n] N
Insira o número que vai ser convertido: +11111000001 
Insira a base do número que vai ser convertido: 2
Insira a base para qual o número deve ser convertido: 10
O número +11111000001 na base 10 é +1985
```
```
Deseja ativar o modo passo a passo? [s/n] n
Insira o número que vai ser convertido: -3701
Insira a base do número que vai ser convertido: 8
Insira a base para qual o número deve ser convertido: 16
O número -3701 na base 16 é -F9
```
```
Deseja ativar o modo passo a passo? [s/n] N
Insira o número que vai ser convertido: 35.3
Insira a base do número que vai ser convertido: 6
Insira a base para qual o número deve ser convertido: 12
35.3 é decimal. Entre quantas casas você quer para o novo número: 16
23.5 é decimal. Entre quantas casas você quer para a saída: 16
O número 35.3 na base 12 é 1B.6
```
```
Deseja ativar o modo passo a passo? [s/n] n
Insira o número que vai ser convertido: -1775.9
Insira a base do número que vai ser convertido: 18
Insira a base para qual o número deve ser convertido: 19
1775.9 é decimal. Entre quantas casas você quer para o novo número: 16
8231.5 é decimal. Entre quantas casas você quer para a saída: 16
O número -1775.9 na base 19 é -13F4.9999999999999999
```
### Modo Passo-a-passo
Se a resposta para `Deseja ativar o modo passo a passo? [s/n]` for sim (`S` ou `s`), após serem fornecidas as outras entradas, o programa irá escrever na saída uma explicação do que ele está fazendo enquanto faz a conversão.

Essa explicação depende de qual algoritmo ele está executando, o qual, por si só depende de quais bases foram fornecidas na entrada:
- a base em que se está é 10
- a base para que se vai é 10
- as duas bases são potências de um número
- as duas bases não satisfazem nenhum dos casos acima

É recomendável ter uma noção de matemática antes de ler a explicação, pois o algoritmo se difere em alguns momentos de como a conversão é usualmente feita, embora, matematicamente, ele é equivalente à forma tradicional.

**NOTE QUE** Conubate irá ainda pedir quantos dígitos decimais o novo número deve ter, no caso de fracionários. Ele pode também fazer mais uma pergunta, considerando um intermediário entre o número original e o número na base em que se pretende chegar.

Eis alguns exemplos:
```
Deseja ativar o modo passo a passo? [s/n] s
Insira o número que vai ser convertido: 1985
Insira a base do número que vai ser convertido: 10
Insira a base para qual o número deve ser convertido: 2

O número a ser convertido está sem sinal.

Tratando a parte inteira (1985) via divisões sucessivas pela base 2:

1985 / 2 = 992
sobra 1
colocando à esquerda, fica 1.

992 / 2 = 496
sobra 0
colocando à esquerda, fica 01.

496 / 2 = 248
sobra 0
colocando à esquerda, fica 001.

248 / 2 = 124
sobra 0
colocando à esquerda, fica 0001.

124 / 2 = 62
sobra 0
colocando à esquerda, fica 00001.

62 / 2 = 31
sobra 0
colocando à esquerda, fica 000001.

31 / 2 = 15
sobra 1
colocando à esquerda, fica 1000001.

15 / 2 = 7
sobra 1
colocando à esquerda, fica 11000001.

7 / 2 = 3
sobra 1
colocando à esquerda, fica 111000001.

3 / 2 = 1
sobra 1
colocando à esquerda, fica 1111000001.

1 / 2 = 0
sobra 1
colocando à esquerda, fica 11111000001.

Assim, a parte inteira do número resultante é 11111000001.

A parte fracionária do número original (1985) é nula. Assim, o seu equivalente na base 2, sem sinal, é
11111000001

Não há sinal a ser colocado.

Portanto, ao todo, o resultado da conversão é: 
11111000001

O número 1985 na base 2 é 11111000001
```

```
Deseja ativar o modo passo a passo? [s/n] S
Insira o número que vai ser convertido: -1775.9
Insira a base do número que vai ser convertido: 18
Insira a base para qual o número deve ser convertido: 19

Tirando o sinal (-), o número original é:
1775.9

Tratando a parte inteira (1775) via somatório posicional dos dígitos, considerando base 18:

O dígito na entrada é 1
somando com o que havia antes, fica 1
multiplicando por 18 (1ª vez), fica 18.

O dígito na entrada é 7
somando com o que havia antes, fica 25
multiplicando por 18 (2ª vez), fica 450.

O dígito na entrada é 7
somando com o que havia antes, fica 457
multiplicando por 18 (3ª vez), fica 8226.

O dígito na entrada é 5
somando com o que havia antes, fica 8231
18 elevado a 0 é igual a 1, portanto, não precisamos multiplicar por 18 uma 4ª vez.

Assim, a parte inteira da saída é 8231.

1775.9 é decimal. Entre quantas casas você quer para o novo número: 16

Tratando a parte fracionária (9) via somatório posicional dos dígitos, considerando base 18:

NOTE QUE
(I) agora, os dígitos serão lidos de trás para frente;
(II) em questão de se tratar de um somatório posicional,
    será preciso dividir em todas as vezes que for feita a soma, até na última vez (18 elevado a -1 é diferente de 1).

O dígito (trás pra frente) em num_x é 9
somando com o que havia antes, fica 9
divindo por 18 (1ª vez), fica 0.5.

Assim, desconsiderando o 0 e o ponto, a parte fracionária de num_y é 5.

Juntando as duas partes, o novo número, sem sinal, é:
8231.5

Colocando o sinal (-) no número convertido, fica: 
-8231.5

Portanto, ao todo, o número original na nova base é: 
-8231.5


Tirando o sinal (-), o número a ser convertido é:
8231.5

Tratando a parte inteira (8231) via divisões sucessivas pela base 19:

8231 / 19 = 433
sobra 4
colocando à esquerda, fica 4.

433 / 19 = 22
sobra 15
colocando à esquerda, fica F4.

22 / 19 = 1
sobra 3
colocando à esquerda, fica 3F4.

1 / 19 = 0
sobra 1
colocando à esquerda, fica 13F4.

Assim, a parte inteira do número resultante é 13F4.

8231.5 é decimal. Entre quantas casas você quer para a saída: 16

Tratando a parte fracionária (5) via multiplicações sucessivas pela base 19:

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 9.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 99.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 9999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 99999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 9999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 99999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 999999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 9999999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 99999999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 999999999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 9999999999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 99999999999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 999999999999999.

0.5 * 19 = 9.5
a parte inteira é 9
colocando à direita, fica 9999999999999999.

Assim, a parte fracionária do número resultante é 9999999999999999.

Juntando as duas partes, o número convertido, sem sinal, é:
13F4.9999999999999999

Colocando o sinal (-) no número convertido, fica: 
-13F4.9999999999999999

Portanto, ao todo, o resultado da conversão é: 
-13F4.9999999999999999

O número -1775.9 na base 19 é -13F4.9999999999999999
```

### Leitor de `.csv`
Opção 2 na tela inicial do programa irá dar acesso ao leitor de arquivos `.csv`.

Considera-se, neste contexto, que o arquivo .csv a ser lido é dividido em três colunas:
1. O número a ser convertido
2. A base de origem
3. A base final

O software irá pedir o nome do arquivo a ser lido. Se a entrada for válida, ele irá realizar as conversões e produzir um novo arquivo (`saida.csv`) que contém uma quarta coluna. Essa quarta coluna consiste das conversões feitas.

**NOTE QUE** se um número a ser convertido possui casa decimais, o conversor irá pedir quantos dígitos após o `.` ele deve colocar. Dependendo do algoritmo que está sendo executado, ele pode inclusive fazer uma segunda pergunta para o número intermediário.

O diretório já vem com um arquivo de teste, `entrada.csv`. Eis ele em execução:

```
Insira o nome do arquivo: entrada.csv
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
11111001001.01 é decimal. Entre quantas casas você quer para o novo número: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
133021.1 é decimal. Entre quantas casas você quer para o novo número: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
3711.2 é decimal. Entre quantas casas você quer para o novo número: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
7C9.4 é decimal. Entre quantas casas você quer para o novo número: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
1U9.8 é decimal. Entre quantas casas você quer para o novo número: 16
1U9.8 é decimal. Entre quantas casas você quer para a saída: 16
11111001001.01 é decimal. Entre quantas casas você quer para a saída: 16
7C9.4 é decimal. Entre quantas casas você quer para a saída: 16
133021.1 é decimal. Entre quantas casas você quer para a saída: 16
3711.2 é decimal. Entre quantas casas você quer para a saída: 16
133021.1 é decimal. Entre quantas casas você quer para a saída: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
11111001001.01 é decimal. Entre quantas casas você quer para o novo número: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
133021.1 é decimal. Entre quantas casas você quer para o novo número: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
3711.2 é decimal. Entre quantas casas você quer para o novo número: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
7C9.4 é decimal. Entre quantas casas você quer para o novo número: 16
1993.25 é decimal. Entre quantas casas você quer para a saída: 16
1U9.8 é decimal. Entre quantas casas você quer para o novo número: 16
1U9.8 é decimal. Entre quantas casas você quer para a saída: 16
11111001001.01 é decimal. Entre quantas casas você quer para a saída: 16
7C9.4 é decimal. Entre quantas casas você quer para a saída: 16
133021.1 é decimal. Entre quantas casas você quer para a saída: 16
3711.2 é decimal. Entre quantas casas você quer para a saída: 16
133021.1 é decimal. Entre quantas casas você quer para a saída: 16
2022.1 é decimal. Entre quantas casas você quer para a saída: 16
AC.5 é decimal. Entre quantas casas você quer para a saída: 16
0.3 é decimal. Entre quantas casas você quer para a saída: 16
0.I é decimal. Entre quantas casas você quer para a saída: 16
0.3 é decimal. Entre quantas casas você quer para a saída: 16
0.I é decimal. Entre quantas casas você quer para a saída: 16
0.3 é decimal. Entre quantas casas você quer para a saída: 16
0.I é decimal. Entre quantas casas você quer para a saída: 16
Arquivo 'saida.csv' foi gerado.
```

O conteúdo de `entrada.csv` é o seguinte:
```
1985; 10; 2
11111000001; 2; 10
1985; 10; 3
2201112; 3; 10
1985; 10; 4
133001; 4; 10
1985; 10; 5
30420; 5; 10
1985; 10; 6
13105; 6; 10
1985; 10; 7
5534; 7; 10
1985; 10; 8
3701; 8; 10
1985; 10; 9
2645; 9; 10
1985; 10; 11
1545; 11; 10
1985; 10; 12
1195; 12; 10
1985; 10; 13
B99; 13; 10
1985; 10; 14
A1B; 14; 10
1985; 10; 15
8C5; 15; 10
1985; 10; 16
7C1; 16; 10
1985; 10; 17
6ED; 17; 10
1985; 10; 18
625; 18; 10
1985; 10; 19
599; 19; 10
1985; 10; 20
4J5; 20; 10
1985; 10; 21
4AB; 21; 10
1985; 10; 22
425; 22; 10
1985; 10; 23
3H7; 23; 10
1985; 10; 24
3AH; 24; 10
1985; 10; 25
34A; 25; 10
1985; 10; 26
2O9; 26; 10
1985; 10; 27
2JE; 27; 10
1985; 10; 28
2EP; 28; 10
1985; 10; 29
2AD; 29; 10
1985; 10; 30
265; 30; 10
1985; 10; 31
221; 31; 10
1985; 10; 32
1U1; 32; 10
1985; 10; 33
1R5; 33; 10
1985; 10; 34
1OD; 34; 10
1985; 10; 35
1LP; 35; 10
1985; 10; 36
1J5; 36; 10
101559956668415; 10; 36
ZZZZZZZZZ; 36; 10
+101559956668415; 10; 36
+ZZZZZZZZZ; 36; 10
-101559956668415; 10; 36
-ZZZZZZZZZ; 36; 10
1993.25; 10; 2
11111001001.01; 2; 10
1993.25; 10; 4
133021.1; 4; 10
1993.25; 10; 8
3711.2; 8; 10
1993.25; 10; 16
7C9.4; 16; 10
1993.25; 10; 32
1U9.8; 32; 10
1U9.8; 32; 2
11111001001.01; 2; 32
7C9.4; 16; 4
133021.1; 4; 16
3711.2; 8; 4
133021.1; 4; 8
+1993.25; 10; 2
+11111001001.01; 2; 10
-1993.25; 10; 4
-133021.1; 4; 10
+1993.25; 10; 8
+3711.2; 8; 10
-1993.25; 10; 16
-7C9.4; 16; 10
+1993.25; 10; 32
+1U9.8; 32; 10
-1U9.8; 32; 2
-11111001001.01; 2; 32
+7C9.4; 16; 4
+133021.1; 4; 16
-3711.2; 8; 4
-133021.1; 4; 8
2022; 5; 25
AC; 25; 5
2022.1; 5; 25
AC.5; 25; 5
1130012; 6; 36
1908; 36; 6
0.3; 6; 36
0.I; 36; 6
+0.3; 6; 36
+0.I; 36; 6
-0.3; 6; 36
-0.I; 36; 6
Feijão com Arroz; 10; 2
Bom dia!; 36; 5
Estes trechos devem dar erro; 7; 9
1985; 101; 2
1985; 1; 0;
1985; -101; 0
1985; 2; 10
1985; 9; 16
NUMERO; 10; 26
1985; Feijão com Arroz; 2
1985; Bom dia!; 5
1985; Estes trechos devem dar erro; 9
1985; 10; 37
1985; 10; -1
1985; 10; 1
1985; 10; 1.14
1985; 10; Feijão com Arroz
1985; 11; Bom dia!
1985; 12; Tome cuidado com os ponto-e-vírgula no final;
```

E o conteúdo de `saida.csv` é o seguinte:
```
1985;10;2;11111000001
11111000001;2;10;1985
1985;10;3;2201112
2201112;3;10;1985
1985;10;4;133001
133001;4;10;1985
1985;10;5;30420
30420;5;10;1985
1985;10;6;13105
13105;6;10;1985
1985;10;7;5534
5534;7;10;1985
1985;10;8;3701
3701;8;10;1985
1985;10;9;2645
2645;9;10;1985
1985;10;11;1545
1545;11;10;1985
1985;10;12;1195
1195;12;10;1985
1985;10;13;B99
B99;13;10;1985
1985;10;14;A1B
A1B;14;10;1985
1985;10;15;8C5
8C5;15;10;1985
1985;10;16;7C1
7C1;16;10;1985
1985;10;17;6ED
6ED;17;10;1985
1985;10;18;625
625;18;10;1985
1985;10;19;599
599;19;10;1985
1985;10;20;4J5
4J5;20;10;1985
1985;10;21;4AB
4AB;21;10;1985
1985;10;22;425
425;22;10;1985
1985;10;23;3H7
3H7;23;10;1985
1985;10;24;3AH
3AH;24;10;1985
1985;10;25;34A
34A;25;10;1985
1985;10;26;2O9
2O9;26;10;1985
1985;10;27;2JE
2JE;27;10;1985
1985;10;28;2EP
2EP;28;10;1985
1985;10;29;2AD
2AD;29;10;1985
1985;10;30;265
265;30;10;1985
1985;10;31;221
221;31;10;1985
1985;10;32;1U1
1U1;32;10;1985
1985;10;33;1R5
1R5;33;10;1985
1985;10;34;1OD
1OD;34;10;1985
1985;10;35;1LP
1LP;35;10;1985
1985;10;36;1J5
1J5;36;10;1985
101559956668415;10;36;ZZZZZZZZZ
ZZZZZZZZZ;36;10;101559956668415
+101559956668415;10;36;+ZZZZZZZZZ
+ZZZZZZZZZ;36;10;+101559956668415
-101559956668415;10;36;-ZZZZZZZZZ
-ZZZZZZZZZ;36;10;-101559956668415
1993.25;10;2;11111001001.01
11111001001.01;2;10;1993.25
1993.25;10;4;133021.1
133021.1;4;10;1993.25
1993.25;10;8;3711.2
3711.2;8;10;1993.25
1993.25;10;16;7C9.4
7C9.4;16;10;1993.25
1993.25;10;32;1U9.8
1U9.8;32;10;1993.25
1U9.8;32;2;11111001001.25
11111001001.01;2;32;1U9.25
7C9.4;16;4;133021.25
133021.1;4;16;1F9.25
3711.2;8;4;133021.25
133021.1;4;8;771.25
+1993.25;10;2;+11111001001.01
+11111001001.01;2;10;+1993.25
-1993.25;10;4;-133021.1
-133021.1;4;10;-1993.25
+1993.25;10;8;+3711.2
+3711.2;8;10;+1993.25
-1993.25;10;16;-7C9.4
-7C9.4;16;10;-1993.25
+1993.25;10;32;+1U9.8
+1U9.8;32;10;+1993.25
-1U9.8;32;2;-11111001001.25
-11111001001.01;2;32;-1U9.25
+7C9.4;16;4;+133021.25
+133021.1;4;16;+1F9.25
-3711.2;8;4;-133021.25
-133021.1;4;8;-771.25
2022;5;25;AC
AC;25;5;2022
2022.1;5;25;AC.2
AC.5;25;5;2022.2
1130012;6;36;1908
1908;36;6;11312
0.3;6;36;0.5
0.I;36;6;0.5
+0.3;6;36;+0.5
+0.I;36;6;+0.5
-0.3;6;36;-0.5
-0.I;36;6;-0.5
ERRO: número a ser convertido possui caracteres especiais.
ERRO: número a ser convertido possui caracteres especiais.
ERRO: número a ser convertido possui caracteres especiais.
ERRO: a base deve ser um número inteiro de 2 a 36.
ERRO: a base deve ser um número inteiro de 2 a 36.
ERRO: a base deve ser um número inteiro de 2 a 36.
ERRO: a base não é válida para o número inserido.
ERRO: a base não é válida para o número inserido.
ERRO: a base não é válida para o número inserido.
ERRO: a base do número a ser convertido possui caracteres especiais.
ERRO: a base do número a ser convertido possui caracteres especiais.
ERRO: a base do número a ser convertido possui caracteres especiais.
ERRO: a base na qual o número vai ser convertido deve ser um numero inteiro de 2 a 36.
ERRO: a base na qual o número vai ser convertido deve ser um numero inteiro de 2 a 36.
ERRO: a base na qual o número vai ser convertido deve ser um numero inteiro de 2 a 36.
ERRO: a base na qual o número vai ser convertido possui caracteres especiais.
ERRO: a base na qual o número vai ser convertido possui caracteres especiais.
ERRO: a base na qual o número vai ser convertido possui caracteres especiais.
ERRO: a base na qual o número vai ser convertido possui caracteres especiais.
```

### Modo quiz
Opção 3 na tela de apresentação de Conubate dá acesso ao modo quiz.

Ele gera perguntas (conversões as quais o usuário deve realizar) com base no nível de dificuldade em que se encontra. Quanto mais respostas corretas, maior é a pontuação no programa.

Ao selecionar o modo quiz, aparecerá uma segunda tela de seleção, pertinente ao próprio quiz.
```
Sua pontuação total no quiz é 0, a dificuladade atual é 1.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
```
Opção 1 gera uma nova pergunta. Se a conversão for corretamente feita, uma mensagem de vitória será impressa, e a se retornará para a tela de seleção com a pontuação incrementada. Senão, será impressa uma mensagem de derrota, mostrando qual seria a resposta correta.

Eis um exemplo:
```
Converta o número 19 na base 10 para a base 2:
10011
Parabéns, você acertou!
Sua pontuação total no quiz é 4, a dificuladade atual é 1.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
1
Converta o número 03 na base 10 para a base 2:
90
Que pena, você errou... A resposta correta é 11.
Sua pontuação total no quiz é 4, a dificuladade atual é 1.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair

```
A dificuldade pode ser alterada usando opções 2 e 3. Existem cerca de cinco níveis de dificuldade, que fornecem níveis crescentes de pontuação no caso de vitória.
Continuando o exemplo de antes:
```
Sua pontuação total no quiz é 4, a dificuladade atual é 1.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
2
Sua pontuação total no quiz é 4, a dificuladade atual é 2.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
1
Converta o número 928 na base 10 para a base 16:
3A0
Parabéns, você acertou!
Sua pontuação total no quiz é 20, a dificuladade atual é 2.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
2
Sua pontuação total no quiz é 20, a dificuladade atual é 3.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
1
Converta o número 5737 na base 8 para a base 16:
BDF
Parabéns, você acertou!
Sua pontuação total no quiz é 56, a dificuladade atual é 3.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
2
Sua pontuação total no quiz é 56, a dificuladade atual é 4.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
1
Converta o número 4129 na base 14 para a base 7:
1666666
Que pena, você errou... A resposta correta é 44452.
Sua pontuação total no quiz é 56, a dificuladade atual é 4.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
2
Sua pontuação total no quiz é 56, a dificuladade atual é 5.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
1
Converta o número 2344 na base 5 para a base 30:
EAF
Que pena, você errou... A resposta correta é BJ.
Sua pontuação total no quiz é 56, a dificuladade atual é 5.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
3   
Sua pontuação total no quiz é 56, a dificuladade atual é 4.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
1
Converta o número 6B10 na base 14 para a base 15:
70
Que pena, você errou... A resposta correta é 57C4.
Sua pontuação total no quiz é 56, a dificuladade atual é 4.
1 - Gerar nova pergunta
2 - Aumentar dificuldade
3 - Diminuir dificuldade
4 - Sair
```

### Calculadora de máximos
Opção 4 da tela de apresentação do programa irá dar acesso à calculadora de máximos.

É possível calcular qual é o maior número (em decimal) que uma base pode representar com um número k de dígitos.

O programa irá pedir qual é o valor de k com `Insira quantos dígitos os valores máximos possuem:` e, assim que fornecida a entrada, irá converter cada máximo de cada base para a base 10.

Conforme ele faz as conversões, ele vai imprimindo na tela o valor em base 10 e o original em na base de origem, entre parênteses, indicando a qual base este pertence logo em seguida.

Eis um exemplo:
```
Insira quantos dígitos os valores máximos possuem: 4
Com 4 digitos, pode-se representar até (incluso):
15 (1111) na base 2
80 (2222) na base 3
255 (3333) na base 4
624 (4444) na base 5
1295 (5555) na base 6
2400 (6666) na base 7
4095 (7777) na base 8
6560 (8888) na base 9
9999 (9999) na base 10
14640 (AAAA) na base 11
20735 (BBBB) na base 12
28560 (CCCC) na base 13
38415 (DDDD) na base 14
50624 (EEEE) na base 15
65535 (FFFF) na base 16
83520 (GGGG) na base 17
104975 (HHHH) na base 18
130320 (IIII) na base 19
159999 (JJJJ) na base 20
194480 (KKKK) na base 21
234255 (LLLL) na base 22
279840 (MMMM) na base 23
331775 (NNNN) na base 24
390624 (OOOO) na base 25
456975 (PPPP) na base 26
531440 (QQQQ) na base 27
614655 (RRRR) na base 28
707280 (SSSS) na base 29
809999 (TTTT) na base 30
923520 (UUUU) na base 31
1048575 (VVVV) na base 32
1185920 (WWWW) na base 33
1336335 (XXXX) na base 34
1500624 (YYYY) na base 35
1679615 (ZZZZ) na base 36
```

## Limitações conhecidas e melhorias que podem ser feitas
Conubate possui diversos aspectos os quais ainda podem ser melhorados e diversas falhas que levam a resultados inesperados durante a execução.

Isso se deve principalmente ao nível de experiência de seus autores e ao tempo disponível que tiveram para construí-lo. Porém, cada limitação também pode ter fatores situacionais adicionais.

Eis o que se pôde observar durante as sessões de teste:

1. Como as conversões entre bases não potência (isto é, bases que não podem ser escritas como potências de um natural) necessitam armazenar a parte inteira do número a ser convertido num `long long` e a parte fracionária num `double`, é possível que hajam overflows quando o número a ser representado é grande demais para tais tipos númericos.
    - Isso facilmente ocorre  na calculadora de máximos, quando o número de dígitos é muito grande (15, por exemplo).
        ```
        Insira quantos dígitos os valores máximos possuem: 15
        Com 15 digitos, pode-se representar até (incluso):
        32767 (111111111111111) na base 2
        14348906 (222222222222222) na base 3
        1073741823 (333333333333333) na base 4
        30517578124 (444444444444444) na base 5
        470184984575 (555555555555555) na base 6
        4747561509942 (666666666666666) na base 7
        35184372088831 (777777777777777) na base 8
        205891132094648 (888888888888888) na base 9
        999999999999999 (999999999999999) na base 10
        4177248169415650 (AAAAAAAAAAAAAAA) na base 11
        15407021574586367 (BBBBBBBBBBBBBBB) na base 12
        51185893014090756 (CCCCCCCCCCCCCCC) na base 13
        155568095557812223 (DDDDDDDDDDDDDDD) na base 14
        437893890380859374 (EEEEEEEEEEEEEEE) na base 15
        1152921504606846975 (FFFFFFFFFFFFFFF) na base 16
        2862423051509815792 (GGGGGGGGGGGGGGG) na base 17
        6746640616477458431 (HHHHHHHHHHHHHHH) na base 18
        0 (IIIIIIIIIIIIIII) na base 19
        0 (JJJJJJJJJJJJJJJ) na base 20
         (KKKKKKKKKKKKKKK) na base 21
        7752859499445190655 (LLLLLLLLLLLLLLL) na base 22
        8380818432457522982 (MMMMMMMMMMMMMMM) na base 23
        6795192965888212991 (NNNNNNNNNNNNNNN) na base 24
        8985370930000934824 (OOOOOOOOOOOOOOO) na base 25
         (PPPPPPPPPPPPPPP) na base 26
        2833654757305440082 (QQQQQQQQQQQQQQQ) na base 27
        6353990894554710015 (RRRRRRRRRRRRRRR) na base 28
        0 (SSSSSSSSSSSSSSS) na base 29
        0 (TTTTTTTTTTTTTTT) na base 30
        1003530086136274398 (UUUUUUUUUUUUUUU) na base 31
         (VVVVVVVVVVVVVVV) na base 32
        5474003383087343072 (WWWWWWWWWWWWWWW) na base 33
        00 (XXXXXXXXXXXXXXX) na base 34
        3351328013648404810 (YYYYYYYYYYYYYYY) na base 35
        8138741398091333631 (ZZZZZZZZZZZZZZZ) na base 36
        ```
    - Quando se converte entre duas bases que são diferentes de 10, se o número intermediário tiver uma dízima muito grande na parte fracionária, overflow ocorre nesta quando se converte da base 10 para a base final.
        ```
        Deseja ativar o modo passo a passo? [s/n] n
        Insira o número que vai ser convertido: 19.9    
        Insira a base do número que vai ser convertido: 11
        Insira a base para qual o número deve ser convertido: 12
        19.9 é decimal. Entre quantas casas você quer para o novo número: 16
        20.81818181818181816566948327817954123020172119140625 é decimal. Entre quantas casas você quer para a saída: 16
        O número 19.9 na base 12 é 18.9999999999999978
        ```
2. O exemplo anterior mostra que o conversor pode colocar um número de casas decimais diferente do inserido pelo usuário.

3. O conversor poderia ignorar a parte fracionária se esta fosse nula.

4. No quiz, é possível que as sequências textuais usadas para representar os números possuam caracteres nulos no início. Isso leva ao formatador incorretamente transformá-los no valor numérico 0, o que leva a certos números aparecerem na tela com o 0 à esquerda. Um exemplo disso ocorrendo pode ser visto na seção referente ao quiz, em que, no segundo bloco de código, ao invés de `3`, aparece `03`.
    - Isso não aparenta impactar em qual é a resposta correta, porém.

5. Certas mensagens de erro aparentam ter erros de gramaticá.
