#include <iostream>

#include "conversor_base_x_para_10.h"
#include "formatador.h"

using namespace std;

string fracionario_de_base_x_para_10(string num_x, short base_x, bool passo_a_passo) {
    short t_num_x = num_x.size();
    string num_y;
    double num_y_fun = 0;
    short resto;
    
    if (passo_a_passo == true) {
        cout << endl
            << "NOTE QUE" << endl
            << "(I) agora, os dígitos serão lidos de trás para frente;" << endl
            << "(II) em questão de se tratar de um somatório posicional," << endl
            << "    será preciso dividir em todas as vezes que for feita a soma," 
            << " até na última vez (" << base_x << " elevado a -1 é diferente de 1)." << endl;
    }

    for (int i_num_x = (t_num_x - 1); i_num_x >= 0; i_num_x--) {
        num_y_fun += (de_caractere_para_num(num_x[i_num_x]));
        if (passo_a_passo == true) {
            cout << endl
                << "O dígito (trás pra frente) no número a ser convertido é " << num_x[i_num_x] << endl
                << "somando com o que havia antes, fica " <<  num_y_fun << endl
                << "divindo por " << base_x << " (" << t_num_x - i_num_x << "ª vez),"
                << " fica " << num_y_fun / base_x << "." << endl;
        }
        num_y_fun /= base_x;
    }

    for (/*num_y_fun*/; num_y_fun != 0; num_y_fun = (num_y_fun * 10) - resto) {
        resto = short(num_y_fun * 10);
        num_y += de_num_para_caractere(resto);
    }

    if (passo_a_passo == true) {
        cout << endl
            << "Assim, desconsiderando o 0 e o ponto,"
            << " a parte fracionária do número convertido é " << num_y << "." << endl;
    }

    return num_y;
}

string inteiro_de_base_x_para_10(string num_x, short base_x, bool passo_a_passo) {
    short t_num_x = num_x.size();
    string num_y;
    long long num_y_fun = 0;
    short resto;
    
    for (short i_num_x = 0; i_num_x < t_num_x; i_num_x++) {
        num_y_fun *= base_x;
        num_y_fun += de_caractere_para_num(num_x[i_num_x]);
        if (passo_a_passo == true) {
            cout << endl
                << "O dígito na entrada é " << num_x[i_num_x] << endl
                << "somando com o que havia antes, fica " <<  num_y_fun << endl;
            if (i_num_x < t_num_x - 1) {
                cout << "multiplicando por " << base_x << " (" << i_num_x + 1 << "ª vez),"
                    << " fica " << num_y_fun * base_x << "." << endl;
            } else { // i_num_x == t_num_x - 1
                cout << base_x << " elevado a 0 é igual a 1, portanto,"
                    << " não precisamos multiplicar por " << base_x 
                    << " uma " << i_num_x + 1 << "ª vez." << endl;
            }
        }
    }

    if (num_y_fun == 0) {
		num_y = "0";
	} else {
        for (/*num_y_fun*/; num_y_fun != 0; num_y_fun /= 10) {
            resto = num_y_fun % 10;
            num_y = de_num_para_caractere(resto) + num_y;
        }
    }

    if (passo_a_passo == true) {
        cout << endl
            << "Assim, a parte inteira da saída é " << num_y << "." << endl;
    }

    return num_y;
}

string de_base_x_para_10(string num_x, short base_x, bool passo_a_passo) {
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
                    << "Tirando o sinal (" << sinal << "), o número original é:" << endl
                    << num_x << endl;
                break;
            default:
                cout << endl 
                    << "Este número está sem sinal." << endl;
        }
    }    

	separar_fracionario(num_x, &parte_inteira_x, &parte_fracionaria_x);
    t_parte_fracionaria_x = parte_fracionaria_x.size();

    if (passo_a_passo == true) {
        cout << endl 
            << "Tratando a parte inteira (" << parte_inteira_x 
            << ") via somatório posicional dos dígitos, considerando base " << base_x << ":" << endl;
    }
    num_y = inteiro_de_base_x_para_10(parte_inteira_x, base_x, passo_a_passo);

	if (t_parte_fracionaria_x > 0) {
        if (passo_a_passo == true) {
            cout << endl; // questão de espaçamento
        }

        cout << num_x << " é decimal. Entre quantas casas você quer para o novo número: ";
        cin >> qtd_casas_decimais;

        if (passo_a_passo == true) {
            cout << endl
                << "Tratando a parte fracionária (" << parte_fracionaria_x 
                << ") via somatório posicional dos dígitos, considerando base " << base_x << ":" << endl;
        }
		num_y += '.' + fracionario_de_base_x_para_10(parte_fracionaria_x, base_x, passo_a_passo);
        if (passo_a_passo == true) {
            cout << endl
                << "Juntando as duas partes, o novo número, sem sinal, é:" << endl
                << num_y << endl;
        }
	} else if (passo_a_passo == true) {
        cout << endl 
            << "A parte fracionária da entrada (" << num_x << ") é nula. Assim, a saída, sem sinal, é" << endl
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
            << "Portanto, ao todo, o número original na nova base é: " << endl
            << num_y << endl << endl;
    }
    
	return num_y;
}
