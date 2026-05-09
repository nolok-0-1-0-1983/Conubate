#include <iostream>

using namespace std;

short de_caractere_para_num(char c) {
    string definicoes = "0123456789ABCDEF";
    short n = 0;

    for (short i = 0; i < short(definicoes.size()); i++) {
        if (c == definicoes[i]) {
            n = i;
        }
    }

    return n;
}

char de_num_para_caractere(short n) {
    string definicoes = "0123456789ABCDEF";
    char c = '\0';

    for (short i = 0; i < short(definicoes.size()); i++) {
        if (n == i) {
            c = definicoes[i];
        }
    }

    return c;
}



void separar_fracionario(string &parte_inteira, string &parte_fracionaria){


	string num = parte_inteira;
	string numero_separado[2];
	bool esta_na_parte_fracionaria = false;

	for(int i = 0; i < int(num.size()); i++){
		if(num[i] == '.' || num[i] == ','){
			esta_na_parte_fracionaria = true;
		}else{
			numero_separado[esta_na_parte_fracionaria] += num[i];
		}
	}
	parte_inteira = numero_separado[0];
	parte_fracionaria = numero_separado[1];

}


string fracionario_de_10_para_x(string num_x, int base_y){

	double num_x_fun = 0;;//copia de num
	int resto = 0;
	string num_y = "";//resultado

	for(short i = short(num_x.size())-1; i >= 0;i--){
		num_x_fun = (num_x_fun/10) + de_caractere_para_num(num_x[i]);

	}
	num_x_fun/= 10;
	//cout << "numero identificado:" << num_x_fun;
	while(num_x_fun != 0 && num_y.size() < 16){
		resto = num_x_fun*base_y;
		//cout << "resto : " << resto << " ----";
		num_x_fun *= base_y;
		//cout << "numx : " << num_x_fun << "----";
		num_x_fun -= resto;
		//cout << "numx - resto : " << num_x_fun << "|\n";
		num_y = num_y + de_num_para_caractere(resto);



	}


	return num_y;

}




string inteiro_de_10_para_x(string num_x, int base_y) {
    string num_y;
    int num_x_fun = 0;
    short resto;

    for (short i = 0; i < short(num_x.size()); i++) {
        num_x_fun = (num_x_fun * 10) + de_caractere_para_num(num_x[i]);
    }

	if(num_x_fun == 0){
		num_y = '0';
	}
    for (num_x_fun; num_x_fun != 0; num_x_fun /= base_y) {
        resto = num_x_fun % base_y;
        num_y = de_num_para_caractere(resto) + num_y;
    }

    return num_y;
}

string de_10_para_x(string num_x, int base_y){
	string parte_fracionaria;
	string parte_inteira = num_x;

	separar_fracionario(parte_inteira, parte_fracionaria);
	//cout << parte_inteira << "   " << parte_fracionaria;


	string resposta = inteiro_de_10_para_x(parte_inteira, base_y);

	if(parte_fracionaria.size() > 0){
		resposta += '.' + fracionario_de_10_para_x(parte_fracionaria,base_y);
	}


	return resposta;
};


int main(){
	string x;
	int y;

	cin >> x >> y;


	cout << de_10_para_x(x, y);

	return 0;
}
