#include <iostream>
#include <string>

#include "verificador.h"
#include "formatador.h"
#include "conversor_bases_potencia.h"
#include "conversor_10_para_base_y.h"
#include "conversor_base_x_para_10.h"


using namespace std;

bool numero_valido(string *num, int base, bool permitir_fracionario){
	string definicoes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	bool achou = true;
	for(short i = 0; i < (int)num->size() && achou; i++){
		achou = false;
		for(short j = 0; j < base && !achou; j++){
			if((*num)[i] > 96){(*num)[i]-=32;} //lida com letras minusculas
			if((*num)[i] == definicoes[j] || (permitir_fracionario && (*num)[i] == '.') || (i == 0 && ((*num)[i] == '+' || (*num)[i] == '-'))){achou = true;}
		}
	}
	return achou;

}


int texto_para_numero(string num){
	int numero = 0;
	for(int i = 0; i < (int)num.size(); i++){
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
			cout << "Entrada inválida, a base deve estar entre 2 e 36.\n";
			invalido = true;
		}
	}else{
		cout << "Entrada inválida, a base deve ser um número inteiro na base 10.\n";
		invalido = true;
	}
	return !invalido;

}

string converter(string num_x, short base_x, short base_y, bool passo_a_passo){

	string num_y;
	short potencia_bases[4];

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
   	        num_y = de_10_para_base_y(num_y, base_y, passo_a_passo);
   	    }
    }

	return num_y;
}

void verificar_e_converter(){
	string num_x;
    short base_x;

	string num_y;
    short base_y;

	string temp;

	bool repetir_entrada = false;

	bool passo_a_passo = false;

	do{
		repetir_entrada = false;
		cout << "Deseja ativar o modo passo a passo? [s/n] ";

		cin >> temp;

		if(temp == "s" || temp == "S"){
			passo_a_passo = true;
		}else if(temp == "n" || temp == "N"){
			passo_a_passo = false;
		}else{
			cout << "Resposta inválida, insira 's' para sim ou 'n' para não.\n";
			repetir_entrada = true;
		}


	}while(repetir_entrada);



	do{
		repetir_entrada = false;
		cout << "Insira o número que vai ser convertido: ";
		cin >> num_x;
		if(!numero_valido(&num_x, 36, true)){
			repetir_entrada = true;
			cout << "Entrada inválida, o número contém caracteres especiais.\n";
		}

	}while(repetir_entrada);

	do{
		repetir_entrada = false;
		cout << "Insira a base do número que vai ser convertido: ";
		cin >> temp;
		if(base_valida(temp)){
			base_x = texto_para_numero(temp);
			if(!numero_valido(&num_x, base_x, true)){
				repetir_entrada = true;
				cout << "Entrada inválida, a base " << base_x << "não é compativel com o número " << num_x << ".\n";
			}
		}else{
			repetir_entrada = true;
		}

	}while(repetir_entrada);

	do{
		repetir_entrada = false;
		cout << "Insira a base para qual o número deve ser convertido: ";
		cin >> temp;
		if(base_valida(temp)){
			base_y = texto_para_numero(temp);
			if(base_x == base_y){
				repetir_entrada = true;
				cout << "Entrada inválida, o número inserido já está na base " << base_y << "./n";
			}
		}else{
			repetir_entrada = true;
		}

	}while(repetir_entrada);

	num_y = converter(num_x, base_x, base_y, passo_a_passo);

    cout << "O número " << num_x << " na base " << base_y << " é " << num_y << endl;



}
/*
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
*/
