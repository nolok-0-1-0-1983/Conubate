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

void descobre_potencia(int num_a, int num_b, int potencia_bases[4]) { // retorn expoente
    int base_pot_a = 0;
    int expoente_a = 0;
    bool achou_base_expoente = false;
    
    for (int base_pot_teste = 2; !(achou_base_expoente); base_pot_teste++) {
        for (int expoente_teste = 1; (pow(base_pot_teste, expoente_teste) <= 36) && !(achou_base_expoente); expoente_teste++) {
            if (pow(base_pot_teste, expoente_teste) == num_a) {
                base_pot_a = base_pot_teste;
                expoente_a = expoente_teste;
                achou_base_expoente = true;
            }
        }
    }

    int base_pot_b = 0;
    int expoente_b = 0;
    achou_base_expoente = false;

    for (int base_pot_teste = 2; !(achou_base_expoente); base_pot_teste++) {
        for (int expoente_teste = 1; (pow(base_pot_teste, expoente_teste) <= 36) && !(achou_base_expoente); expoente_teste++) {
            if (pow(base_pot_teste, expoente_teste) == num_b) {
                base_pot_b = base_pot_teste;
                expoente_b = expoente_teste;
                achou_base_expoente = true;
            }
        }
    }

    potencia_bases[0] = base_pot_a;
    potencia_bases[1] = expoente_a;
    potencia_bases[2] = base_pot_b;
    potencia_bases[3] = expoente_b;
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

string agrupa_digitos(string parte_inteira_x, int base_x, int expoente_agrupa) {
    string num_y;
    string trecho_x;
    int trecho_x_int = 0;
    
    // cout << expoente_agrupa << endl;
    for (parte_inteira_x; (int(parte_inteira_x.size()) % expoente_agrupa) != 0; parte_inteira_x = "0" + parte_inteira_x) {
        // cout << parte_inteira_x << endl;
    }
    // cout << parte_inteira_x << endl;

    for (int i = 0; i < int(parte_inteira_x.size()); i += expoente_agrupa) {
        for (int j = i; j < (i + expoente_agrupa); j++) {
            trecho_x += parte_inteira_x[j];
        }
        // cout << trecho_x << endl;

        for (int k = 0; k < int(trecho_x.size()); k++) {
            trecho_x_int *= base_x;
            trecho_x_int += de_caractere_para_num(trecho_x[k]);
        }
        // cout << trecho_x_int << endl;
        num_y += de_num_para_caractere(trecho_x_int);
        // cout << num_y << endl;

        trecho_x = "\0";
        trecho_x_int = 0;
    }

    return num_y;
}

string separa_digitos(string parte_inteira_x, int base_y, int expoente_separa) {
    string num_y;
    string trecho_y;
    int digito_x;

    if (parte_inteira_x == "0") {
        num_y = "0";
    } else {
        for (int i = 0; i < int(parte_inteira_x.size()); i++) {
            digito_x = de_caractere_para_num(parte_inteira_x[i]);
            cout << "o dígito no número original é: " << digito_x << endl;

            for (digito_x; digito_x != 0; digito_x /= base_y) {
                cout << "digito_x = " << digito_x << endl;
                trecho_y = de_num_para_caractere(digito_x % base_y) + trecho_y;
                cout << "trecho_y = " << trecho_y << endl;
            }

            if ((i != 0) && ((int(trecho_y.size()) % expoente_separa) != 0)) {
                for (trecho_y; (int(trecho_y.size()) % expoente_separa) != 0; trecho_y = "0" + trecho_y) {}
            }

            num_y += trecho_y;
            cout << num_y << endl;

            trecho_y = "\0";
        }
    }

    return num_y;
}

string bases_potencia(string num_x, int base_x, int base_y, int potencia_bases[4]) {
    string parte_inteira_x;
	string parte_fracionaria_x;

	separar_fracionario(num_x, parte_inteira_x, parte_fracionaria_x);

    string num_y;

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

    return num_y;
}

int main() {
    cout << "pseudo_verificador:" << endl;

    string num_x;
    int base_x;

    string num_y;
    int base_y;

    int potencia_bases[4];

    cin >> num_x >> base_x >> base_y;

    descobre_potencia(base_x, base_y, potencia_bases);

    if (potencia_bases[0] == potencia_bases[2]) {
        cout << bases_potencia(num_x, base_x, base_y, potencia_bases) << endl;
    } else {
        cout << "aqui, as outras partes entram no show:" << endl
            << "conversão de base_x para 10" << endl
            << "e conversão de 10 para base_y!" << endl;
    }

    return 0;
}