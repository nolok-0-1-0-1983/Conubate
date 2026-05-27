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
		cout << "\nConubate - Conversor Númerico Baseado em Texto\n1.0.0 --- 27/05/26\nPelos alunos de graduação do 1º período, Natan Uchôa e João Marcelo Firmino, sob a direção de Prof. Rafael Durelli\nUniversidade Federal de Lavras (UFLA), DCC\n1 - Converter número\n2 - Ler arquivo CSV\n3 - Modo quiz\n4 - Calculadora de máximos\n5 - Sair\n";
		cin >> resposta;

		if(resposta == "1"){
			verificar_e_converter();

		}else if(resposta == "2"){
			cout << "Insira o nome do arquivo: ";
			cin >> resposta;
			ifstream entrada(resposta);
			if(entrada.good()){
				ler_e_converter_csv(&entrada);
				cout << "Arquivo 'saida.csv' foi gerado.\n";
			}else{
				cout << "O arquivo não existe.\n";
			}
		}else if(resposta == "3"){
			bool continuar_quiz = true;
			int dificuldade = 1;
			while(continuar_quiz){
				cout << "Sua pontuação total no quiz é " << pontuacao_quiz << ", a dificuladade atual é " << dificuldade << ".\n1 - Gerar nova pergunta\n2 - Aumentar dificuldade\n3 - Diminuir dificuldade\n4 - Sair\n";
				cin >> resposta;
				if(resposta == "4"){continuar_quiz = false;}else
				if(resposta == "1"){pontuacao_quiz += gerar_conversao(dificuldade);}else
				if(resposta == "2"){if(dificuldade < 5){dificuldade++;}}else
				if(resposta == "3"){if(dificuldade > 1){dificuldade--;}}else
				{cout << "Resposta inválida.\n";}
			}

		}else if(resposta == "4"){
			calcular_maximos();
		}else if(resposta == "5"){
			repetir = false;
		}else{
			cout << "Resposta inválida, tente novamente.\n";
		}



	}while(repetir);



	return 0;
}
