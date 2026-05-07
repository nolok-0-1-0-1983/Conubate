# include <iostream>

using namespace std;

short de_caractere_para_num(char c) {
    string definicoes = "0123456789";
    short n = 0;

    for (short i = 0; i < short(definicoes.size()); i++) {
        if (c == definicoes[i]) {
            n = i;
        }
    }

    return n;
}

char de_num_para_caractere(short n) {
    string definicoes = "0123456789";
    char c = '\0';

    for (short i = 0; i < short(definicoes.size()); i++) {
        if (n == i) {
            c = definicoes[i];
        }
    }

    return c;
}

string de_10_para_menor_que_10(string num_x, int base_y) {
    string num_y;
    int num_x_fun = 0;
    short resto;

    for (short i = 0; i < short(num_x.size()); i++) {
        num_x_fun = (num_x_fun * 10) + de_caractere_para_num(num_x[i]);
    }

    for (num_x_fun; num_x_fun != 0; num_x_fun /= base_y) {
        resto = num_x_fun % base_y;
        num_y = de_num_para_caractere(resto) + num_y;
    }

    return num_y;
}

int main() {
    string num_x;
    int base_y;

    cin >> num_x >> base_y;

    cout << de_10_para_menor_que_10(num_x, base_y) << endl;

    return 0;
}