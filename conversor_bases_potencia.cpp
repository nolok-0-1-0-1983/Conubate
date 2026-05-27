#include <iostream>
#include <cmath>

#include "conversor_bases_potencia.h"
#include "formatador.h"
#include "conversor_base_x_para_10.h"
#include "conversor_10_para_base_y.h"

using namespace std;

void descobre_potencia(short num_a, short num_b, short potencia_bases[4]) {
    short base_pot_a;
    short expoente_a;
    short base_pot_b;
    short expoente_b;
    bool achou_base_expoente = false;
    
    for (short base_expoente_tratados = 1; base_expoente_tratados <= 2; base_expoente_tratados++) {
        for (short base_pot_teste = 2; !(achou_base_expoente); base_pot_teste++) {
            for (short expoente_teste = 1; (pow(base_pot_teste, expoente_teste) <= 36) && !(achou_base_expoente); expoente_teste++) {
                if ((base_expoente_tratados == 1) && pow(base_pot_teste, expoente_teste) == num_a) {
                    base_pot_a = base_pot_teste;
                    expoente_a = expoente_teste;
                    achou_base_expoente = true;
                } else if ((base_expoente_tratados == 2) && pow(base_pot_teste, expoente_teste) == num_b) {
                    base_pot_b = base_pot_teste;
                    expoente_b = expoente_teste;
                    achou_base_expoente = true;
                }
            }
        }

        achou_base_expoente = false;
    }

    potencia_bases[0] = base_pot_a;
    potencia_bases[1] = expoente_a;
    potencia_bases[2] = base_pot_b;
    potencia_bases[3] = expoente_b;
}

string agrupa_digitos(string num_x, short base_x, short expoente_agrupa, bool passo_a_passo) {
    short t_num_x;
    string num_y;
    string trecho_x;
    short t_trecho_x = expoente_agrupa;
    short trecho_x_fun = 0;
    short num_trecho = 1;
    
    if (passo_a_passo == true) {
        cout << endl
            << "Ajeitando num_x para que seja possível dividí-lo"
            << " em trechos de " << expoente_agrupa << " dígitos cada." << endl
            << endl;
    }
    for (t_num_x = num_x.size(); (t_num_x % expoente_agrupa) != 0; t_num_x = num_x.size()) {
        if (passo_a_passo == true) {
            cout << num_x << endl;
        }
        num_x = "0" + num_x;
    }
    if (passo_a_passo == true) {
        cout << num_x << endl
            << endl
            << "É possível dividir num_x. Converte-se os trechos:" << endl;
    }
    
    for (short i_num_x = 0; i_num_x < t_num_x; i_num_x += expoente_agrupa) {
        for (short i_trecho_x = i_num_x; i_trecho_x < (i_num_x + expoente_agrupa); i_trecho_x++) {
            trecho_x += num_x[i_trecho_x];
        }
        if (passo_a_passo == true) {
            cout << endl
                << "O " << num_trecho << "º trecho de num_x é " << trecho_x << endl;
        }

        for (short i_trecho_x = 0; i_trecho_x < t_trecho_x; i_trecho_x++) {
            trecho_x_fun *= base_x;
            trecho_x_fun += de_caractere_para_num(trecho_x[i_trecho_x]);
        }
        if (passo_a_passo == true) {
            cout << "na base " << base_x  
                << ", o trecho fica " << de_num_para_caractere(trecho_x_fun) << endl;
        }

        num_y += de_num_para_caractere(trecho_x_fun);
        if (passo_a_passo == true) {
            cout << "juntando com o que havia antes, o todo resulta em " << num_y << "." << endl;
        }

        trecho_x = "\0";
        trecho_x_fun = 0;
        num_trecho++;
    }

    if (passo_a_passo == true) {
        cout << endl
            << "Assim, a parte inteira de num_y é " << num_y << "." << endl;
    }

    return num_y;
}

string separa_digitos(string num_x, short base_y, short expoente_separa, bool passo_a_passo) {
    short t_num_x = num_x.size();
    string num_y;
    short digito_x;
    string trecho_y;
    short t_trecho_y;
    short resto;

    if (num_x == "0") {
        num_y = "0";
        if (passo_a_passo == true) {
            cout << endl
                << "A parte inteira de num_x é nula," << endl
                << "logo, a parte inteira de num_y também é nula." << endl;
        }
    } else {
        for (short i_num_x = 0; i_num_x < t_num_x; i_num_x++) {
            digito_x = de_caractere_para_num(num_x[i_num_x]);
            if (passo_a_passo == true) {
                cout << endl
                    << "O "<< i_num_x + 1 << "º dígito em num_x é " << digito_x << endl;
            } 

            for (/*digito_x*/; digito_x != 0; digito_x /= base_y) {
                resto = digito_x % base_y;
                trecho_y = de_num_para_caractere(resto) + trecho_y;
            }
            if (passo_a_passo == true) {
                cout << "em " << base_y << ", ele fica " << trecho_y << endl;
            }

            t_trecho_y = trecho_y.size();

            if ((i_num_x != 0) && ((t_trecho_y % expoente_separa) != 0)) {
                if (passo_a_passo == true) {
                    cout << "como este não é o 1º trecho" 
                        << " e ele não possui " << expoente_separa << " dígitos,"
                        << " precisa-se completar com 0's:" << endl;
                }
                for (/*t_trecho_y*/; (t_trecho_y % expoente_separa) != 0; t_trecho_y = trecho_y.size()) {
                    if (passo_a_passo == true) {
                        cout << trecho_y << endl;
                    }
                    trecho_y = "0" + trecho_y;
                }
                if (passo_a_passo == true) {
                    cout << trecho_y << endl;
                }
            }

            num_y += trecho_y;
            if (passo_a_passo == true) {
                cout << "juntando com o que havia antes, o todo fica " << num_y << "." << endl;
            }

            trecho_y = "\0";
        }
    }

    if (passo_a_passo == true) {
        cout << endl
            << "Assim, a parte inteira de num_y é " << num_y << "." << endl;
    }
    

    return num_y;
}

string entre_bases_potencia(string num_x, short base_x, short base_y, short potencia_bases[4] , bool passo_a_passo) {
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

    if (potencia_bases[1] == 1) {
        if (passo_a_passo == true) {
            cout << endl
                << base_x << " elevado a " << potencia_bases[3]
                << " é igual a " << base_y << "." << endl
                << "Tratando parte inteira (" << parte_inteira_x << ")"
                << " via agrupamento de dígitos em grupos de " << potencia_bases[3] << ":" << endl;
        }
        num_y += agrupa_digitos(parte_inteira_x, base_x, potencia_bases[3], passo_a_passo);
    } else if (potencia_bases[3] == 1) {
        if (passo_a_passo == true) {
            cout << endl
                << base_y << " elevado a " << potencia_bases[1]
                << " é igual a " << base_x << "." << endl
                << "Tratando parte inteira (" << parte_inteira_x << ")"
                << " via separação de dígitos em grupos de " << potencia_bases[1] << ":" << endl;
        }
        num_y += separa_digitos(parte_inteira_x, base_y, potencia_bases[1], passo_a_passo);
    } else {
        if (passo_a_passo == true) {
            cout << endl
                << potencia_bases[0] << " elevado a " << potencia_bases[1]
                << " é igual a " << base_x << "," << endl
                << "e " << potencia_bases[2] << " elevado a " << potencia_bases[3]
                << " é igual a " << base_y << "." << endl
                << "Assim, primeiro se transporta a parte inteira para base " << potencia_bases[0] << "." << endl
                << endl
                << "Tratando parte inteira (" << parte_inteira_x << ")"
                << " via separação de dígitos em grupos de " << potencia_bases[1] << ":" << endl;
        }
        num_y += separa_digitos(parte_inteira_x, potencia_bases[0], potencia_bases[1], passo_a_passo);

        if (passo_a_passo == true) {
            cout << endl
                << "Agora, este novo valor é tratado"
                << " como a entrada para a transformação para base " << base_y << "." << endl
                << endl
                <<  "Tratando parte inteira (" << parte_inteira_x << ")"
                << " via agrupamento de dígitos em grupos de " << potencia_bases[3] << ":" << endl;
        }
        num_y = agrupa_digitos(num_y, potencia_bases[0], potencia_bases[3], passo_a_passo);
    }

    if (t_parte_fracionaria_x > 0) {
        if (passo_a_passo == true) {
            cout << endl; // questão de espaçamento
        }

        cout << "num_x é decimal. Entre quantas casas você quer para num_y:" << endl
            << "qtd_casas_decimais = ";
        cin >> qtd_casas_decimais;

		num_y += '.' + fracionario_de_base_x_para_10(parte_fracionaria_x, base_x, passo_a_passo);
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
