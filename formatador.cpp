
#include <iostream>
//^ esse arquivo não usa <iostream diretamente, no entanto como planejamos
//adicionar a função passo a passo ele vai provavelmente ser necessario

#include "formatador.h"

using namespace std;


short de_caractere_para_num(char c) {
    string definicoes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // ^ nesta fita, o índice de um caractere é igual ao seu valor em decimal
    short t_definicoes = definicoes.size();
    short n = 0;
    short i_definicoes_comeca = 0;
    short i_definicoes_termina = t_definicoes - 1;
    short i_definicoes_meio;
    bool achou_c = false;

    while ((i_definicoes_comeca <= i_definicoes_termina) && !(achou_c)) {
        i_definicoes_meio = (i_definicoes_comeca + i_definicoes_termina) / 2;

        if (definicoes[i_definicoes_meio] == c) {
            n = i_definicoes_meio;
            achou_c = true;
        } else { // definicoes[i_definicoes_meio] != c
            if (short(definicoes[i_definicoes_meio]) > short(c)) {
                i_definicoes_termina = i_definicoes_meio - 1;
            } else { // short(definicoes[i_definicoes_meio]) < short(c)
                i_definicoes_comeca = i_definicoes_meio + 1;
            }
        }
    }

    return n;
}

char de_num_para_caractere(short n) {
    string definicoes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // ^ nesta fita, o valor de um caractere em decimal é igual ao seu índice
    short t_definicoes = definicoes.size();
    char c = '\0';

    if ((n >= 0) && (n < t_definicoes)) {
        c = definicoes[n];
    }

    return c;
}

char descobre_sinal(string *num) {
    char primeiro_caractere = (*num)[0]; // não é casting, é dereferência do ponteiro de num!
    char sinal;

    if ((primeiro_caractere == '+') || (primeiro_caractere == '-')) {
        sinal = primeiro_caractere;
        (*num)[0] = '\0';
    } else {
        sinal = '\0';
    }

    return sinal;
}

void separar_fracionario(string num, string *parte_inteira, string *parte_fracionaria) {
	string num_copia = num;
    short t_num_copia = num_copia.size();
	string num_separado[2];
	bool esta_na_parte_fracionaria = false;

	for (short i_num_copia = 0; i_num_copia < t_num_copia; i_num_copia++) {
		if ((num_copia[i_num_copia] == '.') || (num_copia[i_num_copia] == ',')) {
			esta_na_parte_fracionaria = true;
		} else { // num_copia[i_num_copia] é um dígito numérico
            if (esta_na_parte_fracionaria == false) {
                num_separado[0] += num_copia[i_num_copia];
            } else { // esta_na_parte_fracionaria == true
                num_separado[1] += num_copia[i_num_copia];
            }
		}
	}

	*parte_inteira = num_separado[0];
	*parte_fracionaria = num_separado[1];
}
