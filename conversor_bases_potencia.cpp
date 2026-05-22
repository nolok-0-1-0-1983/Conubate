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

string agrupa_digitos(string num_x, short base_x, short expoente_agrupa) {
    short t_num_x;
    string num_y;
    string trecho_x;
    short t_trecho_x = expoente_agrupa;
    int trecho_x_fun = 0;
    
    // cout << expoente_agrupa << endl;
    for (t_num_x = num_x.size(); (t_num_x % expoente_agrupa) != 0; t_num_x = num_x.size()) {
        // cout << num_x << endl;
        num_x = "0" + num_x;
    }
    // cout << num_x << endl;

    for (int i_num_x = 0; i_num_x < t_num_x; i_num_x += expoente_agrupa) {
        for (int i_trecho_x = i_num_x; i_trecho_x < (i_num_x + expoente_agrupa); i_trecho_x++) {
            trecho_x += num_x[i_trecho_x];
        }
        // cout << trecho_x << endl;

        for (int i_trecho_x = 0; i_trecho_x < t_trecho_x; i_trecho_x++) {
            trecho_x_fun *= base_x;
            trecho_x_fun += de_caractere_para_num(trecho_x[i_trecho_x]);
        }
        // cout << trecho_x_fun << endl;
        num_y += de_num_para_caractere(trecho_x_fun);
        // cout << num_y << endl;

        trecho_x = "\0";
        trecho_x_fun = 0;
    }

    return num_y;
}

string separa_digitos(string num_x, short base_y, short expoente_separa) {
    short t_num_x = num_x.size();
    string num_y;
    short digito_x;
    string trecho_y;
    short t_trecho_y;
    short resto;

    if (num_x == "0") {
        num_y = "0";
    } else {
        for (short i_num_x = 0; i_num_x < t_num_x; i_num_x++) {
            digito_x = de_caractere_para_num(num_x[i_num_x]);
            // cout << "o dígito no número original é: " << digito_x << endl;

            for (/*digito_x*/; digito_x != 0; digito_x /= base_y) {
                // cout << "digito_x = " << digito_x << endl;
                resto = digito_x % base_y;
                trecho_y = de_num_para_caractere(resto) + trecho_y;
                // cout << "trecho_y = " << trecho_y << endl;
            }

            t_trecho_y = trecho_y.size();

            if ((i_num_x != 0) && ((t_trecho_y % expoente_separa) != 0)) {
                for (/*t_trecho_y*/; (t_trecho_y % expoente_separa) != 0; t_trecho_y = trecho_y.size()) {
                    trecho_y = "0" + trecho_y;
                }
            }

            num_y += trecho_y;
            // cout << num_y << endl;

            trecho_y = "\0";
        }
    }

    return num_y;
}

string entre_bases_potencia(string num_x, short base_x, short base_y, short potencia_bases[4]) {
    string parte_inteira_x;
	string parte_fracionaria_x;
    short t_parte_fracionaria_x;
    short qtd_casas_decimais;
    char sinal;
    string num_y;

    sinal = descobre_sinal(&num_x);  

	separar_fracionario(num_x, &parte_inteira_x, &parte_fracionaria_x);
    t_parte_fracionaria_x = parte_fracionaria_x.size();

    if (potencia_bases[1] == 1) {
        // agrupa dígitos
        num_y += agrupa_digitos(parte_inteira_x, base_x, potencia_bases[3]);
    } else if (potencia_bases[3] == 1) {
        // separa dígitos
        num_y += separa_digitos(parte_inteira_x, base_y, potencia_bases[1]);
    } else {
        // separa dígitos (vai para base_pot^1),
        num_y += separa_digitos(parte_inteira_x, potencia_bases[0], potencia_bases[1]);
        // depois agrupa dígitos (vai para base_pot^expoente_b)
        num_y = agrupa_digitos(num_y, potencia_bases[0], potencia_bases[3]);
    }

    if (t_parte_fracionaria_x > 0) {
        cout << "O seu número é decimal. Entre quantas casas você quer para num_y:" << endl
            << "qtd_casas_decimais = ";
        cin >> qtd_casas_decimais;
		num_y += '.' + fracionario_de_10_para_base_y(fracionario_de_base_x_para_10(parte_fracionaria_x, base_x),base_y,qtd_casas_decimais);
		
	}

    num_y = sinal + num_y;

    return num_y;
}
