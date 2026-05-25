#include <iostream>
#include <fstream>

#include "verificador.h"
#include "quiz.h"
#include "leitor_csv.h"

using namespace std;

int main(){

	int pontuacao_quiz = 0;
	bool repetir = true;
	string resposta;
	do{
		cout << "1 - converter numero\n2 - ler aquivo csv\n3 - modo quiz\n4 - sair\n";
		cin >> resposta;

		if(resposta == "1"){
			verificar_e_converter();

		}else if(resposta == "2"){
			cout << "insira o nome do arquivo\n";
			cin >> resposta;
			ifstream entrada(resposta);
			ler_e_converter_csv(&entrada);
			cout << "arquivo 'saida.csv' foi gerado\n";

		}else if(resposta == "3"){
			bool continuar_quiz = true;
			int dificuldade = 1;
			while(continuar_quiz){
				cout << "sua pontuação total no quiz é " << pontuacao_quiz << ", aperte p para gerar uma nova pergunta ou q para sair\n";
				cin >> resposta;
				if(resposta == "q"){continuar_quiz = false;}else
				if(resposta == "p"){pontuacao_quiz += gerar_conversao(dificuldade);} 
			}

		}else if(resposta == "4"){
			repetir = false;
		}else{
			cout << "resposta invalida, tente novamente\n";
		}



	}while(repetir);



	return 0;
}
