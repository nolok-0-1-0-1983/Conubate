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
            << "Assim, a parte fracionária de num_y é " << num_y << "." << endl;
    }

	return num_y;
}

string inteiro_de_10_para_base_y(string num_x, short base_y, bool passo_a_passo) {
    short t_num_x = num_x.size();
    string num_y;
    int num_x_fun = 0;
    short resto;

    for (short i_num_x = 0; i_num_x < t_num_x; i_num_x++) {
        num_x_fun = (num_x_fun * 10) + de_caractere_para_num(num_x[i_num_x]);
    }

	if (num_x_fun == 0) {
		num_y = "0";
        if (passo_a_passo == true) {
            cout << endl
                << "A parte inteira de num_x é nula," << endl
                << "logo, a parte inteira de num_y também é nula." << endl;
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
            << "Assim, a parte inteira de num_y é " << num_y << "." << endl;
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
                    << "Tirando o sinal (" << sinal << "), num_x é:" << endl
                    << num_x << endl;
                break;
            default:
                cout << endl 
                    << "num_x está sem sinal." << endl;
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
        cout << "num_x é decimal. Entre quantas casas você quer para num_y:" << endl
            << "qtd_casas_decimais = ";
        cin >> qtd_casas_decimais;

        if (passo_a_passo == true) {
            cout << endl
                << "Tratando a parte fracionária (" << parte_fracionaria_x 
                << ") via multiplicações sucessivas pela base " << base_y << ":" << endl;
        }
		num_y += '.' + fracionario_de_10_para_base_y(parte_fracionaria_x, base_y, qtd_casas_decimais, passo_a_passo);
        if (passo_a_passo == true) {
            cout << endl
                << "Juntando as duas partes, o num_y, sem sinal, é:" << endl
                << num_y << endl;
        }
	} else if (passo_a_passo == true) {
        cout << endl 
            << "A parte fracionária do num_x (" << num_x << ") é nula. Assim, num_y, sem sinal, é" << endl
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
                    << "Colocando o sinal (" << sinal << ") em num_y, fica: " << endl
                    << num_y << endl;
                break;
            default:
                cout << endl
                    << "Não há sinal a ser colocado." << endl;
        }

        cout << endl
            << "Portanto, ao todo, num_y é: " << endl
            << num_y << endl;
    }

	return num_y;
}
