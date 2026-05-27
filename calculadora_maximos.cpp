# include <iostream>
# include <string>
// ^ somente calculadora_maximos.cpp usa <string>

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
    long long num_y_fun = 0;
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

// calculadora_maximos.cpp:
int main() {
    short k_digitos;
    string maximo_base_x;
    char maior_digito;
    string maximo_base_10;

    cout << "k_digitos = ";
    cin >> k_digitos;

    cout << "Com k_digitos = " << k_digitos << " digitos,"
        << " pode-se representar até (incluso):" << endl;
    for (short base_x = 2; base_x <= 36; base_x++) {
        maximo_base_x.clear();
        maximo_base_10.clear();

        maior_digito = de_num_para_caractere(base_x - 1);
        
        for (short digitos_colocados = 0; digitos_colocados < k_digitos; digitos_colocados++) {
            maximo_base_x += maior_digito;
        }

        maximo_base_10 = de_base_x_para_10(maximo_base_x, base_x, false);

        cout << maximo_base_10 << " (" << maximo_base_x << ") na base " << base_x << endl;
    }

    return 0;
}
// fim de calculadora_maximos.cpp