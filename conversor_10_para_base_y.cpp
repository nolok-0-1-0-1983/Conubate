#include <iostream>
//^ esse arquivo não usa <iostream diretamente, no entanto como planejamos
//adicionar a função passo a passo ele vai provavelmente ser necessario

#include "conversor_10_para_base_y.h"
#include "formatador.h"

using namespace std;


string fracionario_de_10_para_base_y(string num_x, short base_y, short qtd_casas_decimais) {
    short t_num_x = num_x.size();
	string num_y;
    short t_num_y = 0;
	double num_x_fun = 0;
	short resto = 0;

	for (short i_num_x = (t_num_x - 1); i_num_x >= 0; i_num_x--) {
		num_x_fun = (num_x_fun / 10) + de_caractere_para_num(num_x[i_num_x]);
	}
	num_x_fun /= 10;
    /* cout << fixed;
    cout << setprecision(60);
    cout << num_x_fun << endl; */

	for (/*num_x_fun*/; (num_x_fun != 0) && (t_num_y < qtd_casas_decimais); num_x_fun = (num_x_fun * base_y) - resto) {
		resto = num_x_fun * base_y;
		num_y = num_y + de_num_para_caractere(resto);
        t_num_y = num_y.size();
	}

	return num_y;
}

string inteiro_de_10_para_base_y(string num_x, short base_y) {
    short t_num_x = num_x.size();
    string num_y;
    int num_x_fun = 0;
    short resto;

    for (short i_num_x = 0; i_num_x < t_num_x; i_num_x++) {
        num_x_fun = (num_x_fun * 10) + de_caractere_para_num(num_x[i_num_x]);
    }

	if (num_x_fun == 0) {
		num_y = "0";
	} else {
        for (/*num_x_fun*/; num_x_fun != 0; num_x_fun /= base_y) {
            resto = num_x_fun % base_y;
            num_y = de_num_para_caractere(resto) + num_y;
        }
    }

    return num_y;
}

string de_10_para_base_y(string num_x, short base_y) {
	string parte_inteira_x;
	string parte_fracionaria_x;
    short t_parte_fracionaria_x;
    short qtd_casas_decimais;
    char sinal;
    string num_y;

    sinal = descobre_sinal(&num_x);

	separar_fracionario(num_x, &parte_inteira_x, &parte_fracionaria_x);
    t_parte_fracionaria_x = parte_fracionaria_x.size();
	// cout << parte_inteira_x << endl
    //      << parte_fracionaria_y << endl;

	num_y = inteiro_de_10_para_base_y(parte_inteira_x, base_y);

	if (t_parte_fracionaria_x > 0) {
        cout << "O seu número é decimal. Entre quantas casas você quer para num_y:" << endl
            << "qtd_casas_decimais = ";
        cin >> qtd_casas_decimais;
		num_y += '.' + fracionario_de_10_para_base_y(parte_fracionaria_x, base_y, qtd_casas_decimais);
	}

    num_y = sinal + num_y;

	return num_y;
}
