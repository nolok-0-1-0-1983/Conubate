#include <iostream>
#include <string>

#include "formatador.h"
#include "conversor_bases_potencia.h"
#include "conversor_10_para_base_y.h"
#include "conversor_base_x_para_10.h"

using namespace std;

bool numero_valido(string *num, int base, bool permitir_fracionario){
	string definicoes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	bool achou = true;
	for(int i = 0; i < num->size() && achou; i++){
		achou = false;
		for(int j = 0; j < base && !achou; j++){
			if((*num)[i] > 96){(*num)[i]-=32;} //lida com letras minusculas
			if((*num)[i] == definicoes[j] || (permitir_fracionario && (*num)[i] == '.')){achou = true;}
		}
	}
	return achou;

}


int texto_para_numero(string num){
	int numero = 0;
	for(int i = 0; i < num.size(); i++){
		numero *= 10;
		numero += de_caractere_para_num(num[i]);
	}
	return numero;
}


bool base_valida(string base){

	bool invalido = false;
	if(numero_valido(&base, 10, false)){
		int base_int = texto_para_numero(base);
		if(base_int < 2 || base_int > 36){
			cout << "Entrada invalida, a base deve estar entre 2 e 36\n";
			invalido = true;
		}
	}else{
		cout << "Entrada invalida, a base deve ser um numero inteiro na base 10\n";
		invalido = true;
	}
	return !invalido;

}
void verificar_e_converter(){ 
//não sei como nomear essa função, o objetivo dela é converter um numero inserido pelo usuario, sempre verificando se a entrada é valida
	string num_x;
    short base_x;

	string num_y;
    short base_y;
    short potencia_bases[4];

	string temp;

	bool repetir_entrada = false;
	do{
		repetir_entrada = false;
    	cout << "insira o numero que vai ser convertido: ";
    	cin >> num_x;

		bool repetir_base = false;


		do{
			cout << "insira a base do numero que vai ser convertido: ";
			repetir_base = false;
			cin >> temp;
			if(base_valida(temp)){
				base_x = texto_para_numero(temp);
				if(!numero_valido(&num_x,base_x, true)){
					cout << "A base " << base_x << " não é compativel com o numero " << num_x << "\n";
					repetir_entrada = true;
				}
			}else{
				repetir_base = true;
			}

		}while(repetir_base);

	}while(repetir_entrada);
	do{
		cout << "insira a base para qual o numero deve ser convertido: ";
		cin >> temp;
		repetir_entrada = false;
		if(base_valida(temp)){
			base_y = texto_para_numero(temp);
			if(base_y == base_x){
				cout << "Entrada invalida, o numero inserido já está na base " << base_y << ".";
				repetir_entrada = true;
			}
		}else{
			repetir_entrada = true;
		}
	}while(repetir_entrada);

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
    cout << "O numero " << num_x << " na base " << base_y << " é " << num_y << endl;


}


int main() {

	bool repetir = false;

	do{
		bool entrada_invalida = false;
		string entrada;
		verificar_e_converter();
		cout << "deseja converter outro numero?(s/n)\n";
		do{
			entrada_invalida = false;
			cin >> entrada;
			if(entrada == "s"){repetir = true;}else
			if(entrada == "n"){repetir = false;}else
			{cout << "entrada invalida\n"; entrada_invalida = true;}
		}while(entrada_invalida);

	}while(repetir);

    return 0;
}
