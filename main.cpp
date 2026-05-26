#include <iostream>
#include <fstream>

#include "verificador.h"
#include "quiz.h"
#include "leitor_csv.h"
#include "calculadora_maximos.h"

using namespace std;

int main(){

	int pontuacao_quiz = 0;
	bool repetir = true;
	string resposta;
	do{
		cout << "1 - converter numero\n2 - ler arquivo csv\n3 - modo quiz\n4 - calculadora de maximos\n5 - sair\n";
		cin >> resposta;

		if(resposta == "1"){
			verificar_e_converter();

		}else if(resposta == "2"){
			cout << "insira o nome do arquivo\n";
			cin >> resposta;
			ifstream entrada(resposta);
			if(entrada.good()){
				ler_e_converter_csv(&entrada);
				cout << "arquivo 'saida.csv' foi gerado\n";
			}else{
				cout << "O arquivo nao existe\n";
			}
		}else if(resposta == "3"){
			bool continuar_quiz = true;
			int dificuldade = 1;
			while(continuar_quiz){
				cout << "sua pontuação total no quiz é " << pontuacao_quiz << ", a dificuladade atual é " << dificuldade << ".\n1 - gerar nova pergunta\n2 - aumentar dificuldade\n3 - diminuir dificuldade\n4 - sair\n";
				cin >> resposta;
				if(resposta == "4"){continuar_quiz = false;}else
				if(resposta == "1"){pontuacao_quiz += gerar_conversao(dificuldade);}else
				if(resposta == "2"){if(dificuldade < 5){dificuldade++;}}else
				if(resposta == "3"){if(dificuldade > 1){dificuldade--;}}else
				{cout << "resposta invalida\n";}
			}

		}else if(resposta == "4"){
			calcular_maximos();
		}else if(resposta == "5"){
			repetir = false;
		}else{
			cout << "resposta invalida, tente novamente\n";
		}



	}while(repetir);



	return 0;
}
