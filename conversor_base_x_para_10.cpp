#include <iostream>

#include "conversor_base_x_para_10.h"
#include "formatador.h"

using namespace std;


string fracionario_de_base_x_para_10(string num_x, short base_x) {
    short t_num_x = num_x.size();
    string num_y;
    double num_y_fun = 0;
    short resto;
    
    for (int i_num_x = (t_num_x - 1); i_num_x >= 0; i_num_x--) {
        num_y_fun += (de_caractere_para_num(num_x[i_num_x]));
        num_y_fun /= base_x;
    }

    for (/*num_y_fun*/; num_y_fun != 0; num_y_fun = (num_y_fun * 10) - resto) {
        resto = short(num_y_fun * 10);
        num_y += de_num_para_caractere(resto);
    }

    return num_y;
}

string inteiro_de_base_x_para_10(string num_x, short base_x) {
    short t_num_x = num_x.size();
    string num_y;
    int num_y_fun = 0;
    short resto;
    
    for (short i_num_x = 0; i_num_x < t_num_x; i_num_x++) {
        num_y_fun *= base_x;
        num_y_fun += de_caractere_para_num(num_x[i_num_x]);
    }

    if (num_y_fun == 0) {
		num_y = "0";
	} else {
        for (/*num_y_fun*/; num_y_fun != 0; num_y_fun /= 10) {
            resto = num_y_fun % 10;
            num_y = de_num_para_caractere(resto) + num_y;
        }
    }

    return num_y;
}

string de_base_x_para_10(string num_x, short base_x) {
	string parte_inteira_x;
	string parte_fracionaria_x;
    short t_parte_fracionaria_x;
    short qtd_casas_decimais;
    char sinal;
    string num_y;

    sinal = descobre_sinal(&num_x);    

	separar_fracionario(num_x, &parte_inteira_x, &parte_fracionaria_x);
    t_parte_fracionaria_x = parte_fracionaria_x.size();

    num_y = inteiro_de_base_x_para_10(parte_inteira_x, base_x);

	if (t_parte_fracionaria_x > 0) {
        cout << "O seu número é decimal. Entre quantas casas você quer para num_y:" << endl
            << "qtd_casas_decimais = ";
        cin >> qtd_casas_decimais;
		num_y += '.' + fracionario_de_base_x_para_10(parte_fracionaria_x, base_x);
	}

    num_y = sinal + num_y;

	return num_y;
}
