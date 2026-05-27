#include <iostream>

#include "conversor_10_para_base_y.h"
#include "formatador.h"

using namespace std;

string fracionario_de_10_para_base_y(string num_x, short base_y, short qtd_casas_decimais, bool passo_a_passo) {
    short t_num_x = num_x.size();
	string num_y;
    short t_num_y = 0;
	double num_x_fun = 0;
	short resto = 0;

	for (short i_num_x = (t_num_x - 1); i_num_x >= 0; i_num_x--) {
		num_x_fun = (num_x_fun / 10) + de_caractere_para_num(num_x[i_num_x]);
	}
	num_x_fun /= 10;

	for (/*num_x_fun*/; (num_x_fun != 0) && (t_num_y < qtd_casas_decimais); num_x_fun = (num_x_fun * base_y) - resto) {
		resto = num_x_fun * base_y;
		num_y = num_y + de_num_para_caractere(resto);
        t_num_y = num_y.size();
        if (passo_a_passo == true) {
            cout << endl
                << num_x_fun << " * " << base_y << " = " << num_x_fun * base_y << endl
                << "a parte inteira é " << resto << endl
                << "colocando à direita, fica " << num_y << "." << endl;
        }
	}

    if (passo_a_passo == true) {
        cout << endl
            << "Assim, a parte fracionária do número resultante é " << num_y << "." << endl;
    }

	return num_y;
}

string inteiro_de_10_para_base_y(string num_x, short base_y, bool passo_a_passo) {
    short t_num_x = num_x.size();
    string num_y;
    long long num_x_fun = 0;
    short resto;

    for (short i_num_x = 0; i_num_x < t_num_x; i_num_x++) {
        num_x_fun = (num_x_fun * 10) + de_caractere_para_num(num_x[i_num_x]);
    }

	if (num_x_fun == 0) {
		num_y = "0";
        if (passo_a_passo == true) {
            cout << endl
                << "A parte inteira do número de entrada é nula," << endl
                << "logo, a parte inteira do número de saída também é nula." << endl;
        }
	} else {
        for (/*num_x_fun*/; num_x_fun != 0; num_x_fun /= base_y) {
            resto = num_x_fun % base_y;
            num_y = de_num_para_caractere(resto) + num_y;
            if (passo_a_passo == true) {
                cout << endl
                    << num_x_fun << " / " << base_y << " = " << num_x_fun / base_y << endl
                    << "sobra " << resto << endl
                    << "colocando à esquerda, fica " << num_y << "." << endl;
            }
        }
    }

    if (passo_a_passo == true) {
        cout << endl
            << "Assim, a parte inteira do número resultante é " << num_y << "." << endl;
    }

    return num_y;
}

string de_10_para_base_y(string num_x, short base_y, bool passo_a_passo) {
	string parte_inteira_x;
	string parte_fracionaria_x;
    short t_parte_fracionaria_x;
    short qtd_casas_decimais;
    char sinal;
    string num_y;

    sinal = descobre_sinal(&num_x);
    if (passo_a_passo == true) {
        switch (sinal) {
            case '+':
            case '-':
                cout << endl
                    << "Tirando o sinal (" << sinal << "), o número a ser convertido é:" << endl
                    << num_x << endl;
                break;
            default:
                cout << endl 
                    << "O número a ser convertido está sem sinal." << endl;
        }
    }

	separar_fracionario(num_x, &parte_inteira_x, &parte_fracionaria_x);
    t_parte_fracionaria_x = parte_fracionaria_x.size();
    
    if (passo_a_passo == true) {
        cout << endl 
            << "Tratando a parte inteira (" << parte_inteira_x 
            << ") via divisões sucessivas pela base " << base_y << ":" << endl;
    }
	num_y = inteiro_de_10_para_base_y(parte_inteira_x, base_y, passo_a_passo);

	if (t_parte_fracionaria_x > 0) {
        if (passo_a_passo == true) {
            cout << endl; // questão de espaçamento
        }
        cout << num_x << " é decimal. Entre quantas casas você quer para a saída: ";
        cin >> qtd_casas_decimais;

        if (passo_a_passo == true) {
            cout << endl
                << "Tratando a parte fracionária (" << parte_fracionaria_x 
                << ") via multiplicações sucessivas pela base " << base_y << ":" << endl;
        }
		num_y += '.' + fracionario_de_10_para_base_y(parte_fracionaria_x, base_y, qtd_casas_decimais, passo_a_passo);
        if (passo_a_passo == true) {
            cout << endl
                << "Juntando as duas partes, o número convertido, sem sinal, é:" << endl
                << num_y << endl;
        }
	} else if (passo_a_passo == true) {
        cout << endl 
            << "A parte fracionária do número original (" << num_x << ") é nula."
            << " Assim, o seu equivalente na base " << base_y << ", sem sinal, é" << endl
            << num_y << endl;
    }

    if (sinal != '\0') {
        num_y = sinal + num_y;
    }
    if (passo_a_passo == true) {
        switch (sinal) {
            case '+':
            case '-':
                cout << endl
                    << "Colocando o sinal (" << sinal << ") no número convertido, fica: " << endl
                    << num_y << endl;
                break;
            default:
                cout << endl
                    << "Não há sinal a ser colocado." << endl;
        }

        cout << endl
            << "Portanto, ao todo, o resultado da conversão é: " << endl
            << num_y << endl << endl;
    }

	return num_y;
}
