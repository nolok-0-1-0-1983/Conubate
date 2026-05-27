#include <fstream>
#include <iostream>
#include <string>

#include "verificador.h"
#include "leitor_csv.h"


using namespace std;

void ler_e_converter_csv(ifstream *arquivo){
	ofstream saida("saida.csv");



	while(!arquivo->eof()){
		string linha_saida = "";
		string num_x;
		short base_x;
		short base_y;

		bool erro = false;

		string temp;
		getline(*arquivo, temp, ';');

		if(temp == ""){erro = true;}
		while(temp[0] == ' '){temp.erase(0,1);}


		if(numero_valido(&temp, 36, true)){
			num_x = temp;
			linha_saida += (num_x + ";");
		}else{
			erro = true;
			saida << "ERRO: número a ser convertido possui caracteres especiais.\n";
		}

		getline(*arquivo, temp, ';');
		while(temp[0] == ' '){temp.erase(0,1);}
		if(numero_valido(&temp, 10, false) && !erro){
			base_x = texto_para_numero(temp);
			if(base_x < 2 || base_x > 36){
				erro = true;
				saida << "ERRO: a base deve ser um número inteiro de 2 a 36.\n";
			}
			if(!erro && !numero_valido(&num_x, base_x, true)){
				erro = true;
				saida << "ERRO: a base não é válida para o número inserido.\n";
			}
			if(!erro){
				linha_saida += (temp + ";");
			}
		}else if(!erro){
			erro = true;
			saida << "ERRO: a base do número a ser convertido possui caracteres especiais.\n";
		}

		getline(*arquivo, temp);
		while(temp[0] == ' '){temp.erase(0,1);}
		if(numero_valido(&temp, 10, false) && !erro){
			base_y = texto_para_numero(temp);
			if(base_y < 2 || base_y > 36){
				erro = true;
				saida << "ERRO: a base na qual o número vai ser convertido deve ser um numero inteiro de 2 a 36.\n";
			}
			if(!erro && base_y == base_x){
				erro = true;
				saida << "ERRO: a base do número é igual a base a ser convertida.\n";
			}
			if(!erro){
				linha_saida += (temp + ";");
			}
		}else if(!erro){
			erro = true;
			saida << "ERRO: a base na qual o número vai ser convertido possui caracteres especiais.\n";
		}

		if(!erro){
			saida << linha_saida;
			saida << converter(num_x, base_x, base_y,false) << "\n";
		}


	}
	saida.close();



}
/*
int main(){

	ifstream entrada("entrada.csv");

	ler_e_converter_csv(&entrada);

	return 0;


}
*/
