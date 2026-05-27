# include <iostream>
# include <cmath>

using namespace std;

short de_caractere_para_num(char c) {
    string definicoes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    short n = 0;

    for (short i = 0; i < short(definicoes.size()); i++) {
        if (c == definicoes[i]) {
            n = i;
        }
    }

    return n;
}

char de_num_para_caractere(short n) {
    string definicoes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char c = '\0';

    for (short i = 0; i < short(definicoes.size()); i++) {
        if (n == i) {
            c = definicoes[i];
        }
    }

    return c;
}

void separar_fracionario(string num, string &parte_inteira, string &parte_fracionaria) {
	string num_copia = num;
	string numero_separado[2];
	bool esta_na_parte_fracionaria = false;

	for (int i = 0; i < int(num_copia.size()); i++) {
		if ((num_copia[i] == '.') || (num_copia[i] == ',')) {
			esta_na_parte_fracionaria = true;
		} else {
			numero_separado[esta_na_parte_fracionaria] += num[i];
		}
	}

	parte_inteira = numero_separado[0];
	parte_fracionaria = numero_separado[1];
}

string fracionario_de_base_x_para_10(string parte_fracionaria_x, int base_x) {
    string num_y;
    double num_y_double = 0;
    int expoente = 1;
    
    for (int i = 0; i < int(parte_fracionaria_x.size()); i++) {
        num_y_double += (de_caractere_para_num(parte_fracionaria_x[i])) * (double(1) / pow(base_x, expoente));
        expoente++;
    }

    for (num_y_double; num_y_double != 0; num_y_double = (num_y_double * 10) - int(num_y_double * 10)) {
        num_y += (de_num_para_caractere(int(num_y_double * 10)));
    }

    return num_y;
}

string inteiro_de_base_x_para_10(string parte_inteira_x, int base_x) {
    string num_y;
    int num_y_int = 0;
    int expoente = 0;
    
    for (int i = (parte_inteira_x.size() - 1); i >= 0; i--) {
        num_y_int += (de_caractere_para_num(parte_inteira_x[i])) * pow(base_x, (expoente));
        expoente++;
    }

    for (num_y_int; num_y_int != 0; num_y_int /= 10) {
        num_y = (de_num_para_caractere(num_y_int % 10)) + num_y;
    }

    return num_y;
}

string de_base_x_para_10(string num_x, int base_x) {
	string parte_inteira_x;
	string parte_fracionaria_x;

	separar_fracionario(num_x, parte_inteira_x, parte_fracionaria_x);

    string num_y = inteiro_de_base_x_para_10(parte_inteira_x, base_x);

	if (parte_fracionaria_x.size() > 0) {
		num_y += '.' + fracionario_de_base_x_para_10(parte_fracionaria_x, base_x);
	}

	return num_y;
}

int main(){
	string num_x;
	int base_x;

	cin >> num_x >> base_x;

    cout << de_base_x_para_10(num_x, base_x) << endl;

	return 0;
}