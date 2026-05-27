# include <iostream>
# include <string>
// ^ somente formatador.cpp usa <string>
# include <cmath>
// ^ somente conversor_bases_potencia.cpp usa <cmath>
// # include <iomanip>
// ^ para debug com doubles

using namespace std;

// formatador.cpp:
short de_caractere_para_num(char c) {
    string definicoes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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
    short t_definicoes = definicoes.size();
    char c = '\0';

    if ((n >= 0) && (n < t_definicoes)) {
        c = definicoes[n];
    }

    return c;
}

char descobre_sinal(string *num) {
    string num_copia = *num;
    // short t_num_copia = num_copia.size();
    char primeiro_caractere = num_copia[0];
    char sinal;

    if ((primeiro_caractere == '+') || (primeiro_caractere == '-')) {
        sinal = primeiro_caractere;
        
        num_copia.erase(num_copia.begin());
        
        /* num_copia[0] = '\0';

        for (short i_num_copia = 0; i_num_copia < t_num_copia; i_num_copia++) {
            if (i_num_copia < (t_num_copia - 1)) {
                num_copia[i_num_copia] = num_copia[i_num_copia + 1];
            } else { // i_num_copia == (t_num_copia - 1)
                num_copia[i_num_copia] = '\0';
            }
        } */
        // ^ maneira alternativa

        *num = num_copia;
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

	for (num_x_fun; (num_x_fun != 0) && (t_num_y < qtd_casas_decimais); num_x_fun = (num_x_fun * base_y) - resto) {
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
        for (num_x_fun; num_x_fun != 0; num_x_fun /= base_y) {
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
// fim de conversor_de_10_para_base_y.cpp

// conversor_de_base_x_para_10.cpp:
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
                << "O dígito (trás pra frente) em num_x é " << num_x[i_num_x] << endl
                << "somando com o que havia antes, fica " <<  num_y_fun << endl
                << "divindo por " << base_x << " (" << t_num_x - i_num_x << "ª vez),"
                << " fica " << num_y_fun / base_x << "." << endl;
        }
        num_y_fun /= base_x;
    }

    for (num_y_fun; num_y_fun != 0; num_y_fun = (num_y_fun * 10) - resto) {
        resto = short(num_y_fun * 10);
        num_y += de_num_para_caractere(resto);
    }

    if (passo_a_passo == true) {
        cout << endl
            << "Assim, desconsiderando o 0 e o ponto,"
            << " a parte fracionária de num_y é " << num_y << "." << endl;
    }

    return num_y;
}

string inteiro_de_base_x_para_10(string num_x, short base_x, bool passo_a_passo) {
    short t_num_x = num_x.size();
    string num_y;
    int num_y_fun = 0;
    short resto;
    
    for (short i_num_x = 0; i_num_x < t_num_x; i_num_x++) {
        num_y_fun *= base_x;
        num_y_fun += de_caractere_para_num(num_x[i_num_x]);
        if (passo_a_passo == true) {
            cout << endl
                << "O dígito em num_x é " << num_x[i_num_x] << endl
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
        for (num_y_fun; num_y_fun != 0; num_y_fun /= 10) {
            resto = num_y_fun % 10;
            num_y = de_num_para_caractere(resto) + num_y;
        }
    }

    if (passo_a_passo == true) {
        cout << endl
            << "Assim, a parte inteira de num_y é " << num_y << "." << endl;
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
            << ") via somatório posicional dos dígitos, considerando base " << base_x << ":" << endl;
    }
    num_y = inteiro_de_base_x_para_10(parte_inteira_x, base_x, passo_a_passo);

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
                << ") via somatório posicional dos dígitos, considerando base " << base_x << ":" << endl;
        }
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

            for (digito_x; digito_x != 0; digito_x /= base_y) {
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
                for (t_trecho_y; (t_trecho_y % expoente_separa) != 0; t_trecho_y = trecho_y.size()) {
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
// fim de conversor_bases_pontencia.cpp

// pseudo_verificador:
int main() {
    string num_x;
    short base_x;

    string num_y;
    short base_y;

    short potencia_bases[4];

    bool passo_a_passo = false;
    string entrada_passo_a_passo;
    // ^ não é char de propósito

    cout << "num_x = ";
    cin >> num_x;
    cout << "base_x = ";
    cin >> base_x;
    cout << "base_y = ";
    cin >> base_y;
    cout << "Ativar modo passo-a-passo? [s/n] ";
    cin >> entrada_passo_a_passo;

    if ((entrada_passo_a_passo == "s") || (entrada_passo_a_passo == "S")) {
        passo_a_passo = true;
    } /* else if ((entrada_passo_a_passo != "n") && (entrada_passo_a_passo != "N")) {
        cout << "Somente as letras s, S, n e N são aceitas como resposta. Tente novamente." << endl;
    } */
    // ^ um rascunho de algo que o verificador pode fazer

    // assumindo que são bases diferentes:
    if (base_x == 10) {
        num_y = de_10_para_base_y(num_x, base_y, passo_a_passo);
    } else if (base_y == 10) {
        num_y = de_base_x_para_10(num_x, base_x, passo_a_passo);
    } else {
        descobre_potencia(base_x, base_y, potencia_bases);
        if (potencia_bases[0] == potencia_bases[2]) {
            num_y = entre_bases_potencia(num_x, base_x, base_y, potencia_bases, passo_a_passo);
        } else {
            num_y = de_base_x_para_10(num_x, base_x, passo_a_passo);

            if (passo_a_passo == true) {
                cout << endl
                    << "Agora, este num_y é a nova entrada,"
                    << " isto é, considera-se que num_x agora vale" << num_y << ";" << endl
                    << "Convertendo ele para a base final, " << base_y << "." << endl;
            }

            num_y = de_10_para_base_y(num_y, base_y, passo_a_passo);
        }
    }

    if (passo_a_passo == true) {
        cout << endl; // questão de espaçamento
    }
    cout << "num_y = " << num_y << endl;

    return 0;
}
// fim de pseudo_verificador