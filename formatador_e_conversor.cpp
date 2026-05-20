# include <iostream>
# include <cmath>
// ^ somente conversor_bases_potencia.cpp usa <cmath>
// # include <iomanip>
// ^ para debug com doubles

using namespace std;

// formatador.cpp:
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
// fim de formatador.cpp

// conversor_de_10_para_base_y.cpp:
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

	for (num_x_fun; (num_x_fun != 0) && (t_num_y < qtd_casas_decimais); num_x_fun = (num_x_fun * base_y) - resto) {
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
        for (num_x_fun; num_x_fun != 0; num_x_fun /= base_y) {
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
// fim de conversor_de_10_para_base_y.cpp

// conversor_de_base_x_para_10.cpp:
string fracionario_de_base_x_para_10(string num_x, short base_x) {
    short t_num_x = num_x.size();
    string num_y;
    double num_y_fun = 0;
    short resto;
    
    for (int i_num_x = (t_num_x - 1); i_num_x >= 0; i_num_x--) {
        num_y_fun += (de_caractere_para_num(num_x[i_num_x]));
        num_y_fun /= base_x;
    }

    for (num_y_fun; num_y_fun != 0; num_y_fun = (num_y_fun * 10) - resto) {
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
        for (num_y_fun; num_y_fun != 0; num_y_fun /= 10) {
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
// fim de conversor_de_base_x_para_10.cpp

// conversor_bases_potencia.cpp:
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

            for (digito_x; digito_x != 0; digito_x /= base_y) {
                // cout << "digito_x = " << digito_x << endl;
                resto = digito_x % base_y;
                trecho_y = de_num_para_caractere(resto) + trecho_y;
                // cout << "trecho_y = " << trecho_y << endl;
            }

            t_trecho_y = trecho_y.size();

            if ((i_num_x != 0) && ((t_trecho_y % expoente_separa) != 0)) {
                for (t_trecho_y; (t_trecho_y % expoente_separa) != 0; t_trecho_y = trecho_y.size()) {
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
		num_y += '.' + fracionario_de_base_x_para_10(parte_fracionaria_x, base_x);
	}

    num_y = sinal + num_y;

    return num_y;
}
// fim de conversor_bases_pontencia.cpp

// pseudo_verificador:
int main() {
    string num_x;
    short base_x;

    string num_y;
    short base_y;

    short potencia_bases[4];

    cout << "num_x = ";
    cin >> num_x;
    cout << "base_x = ";
    cin >> base_x;
    cout << "base_y = ";
    cin >> base_y;

    // assumindo que são bases diferentes:
    if (base_x == 10) {
        num_y = de_10_para_base_y(num_x, base_y);
    } else if (base_y == 10) {
        num_y = de_base_x_para_10(num_x, base_x);
    } else {
        descobre_potencia(base_x, base_y, potencia_bases);
        if (potencia_bases[0] == potencia_bases[2]) {
            num_y = entre_bases_potencia(num_x, base_x, base_y, potencia_bases);
        } else {
            num_y = de_base_x_para_10(num_x, base_x);
            num_y = de_10_para_base_y(num_y, base_y);
        }
    }

    cout << "num_y = " << num_y << endl;

    return 0;
}
// fim de pseudo_verificador