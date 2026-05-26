#include <iostream>
#include <cstdlib>
#include <ctime>

#include "verificador.h"
#include "formatador.h"
#include "quiz.h"


using namespace std;

string gerar_numero_aleatorio(int tamanho, int base){
	srand(time(0));
	string numero = "";
	for(short i = 0; i < tamanho; i++){
		numero += de_num_para_caractere(rand() % base);
	}

	return numero;
}


int gerar_conversao(int dificuldade){

	string num_x;
	short base_x;
	short base_y;

	if(dificuldade == 1){
		base_x = 10;
		num_x = gerar_numero_aleatorio(2,base_x);
		base_y  = 2;
	}else if(dificuldade == 2){
		base_x = 10;
		num_x = gerar_numero_aleatorio(3,base_x);
		base_y = rand() % 3;
		if(base_y == 0){
			base_y = 2;
		}else if(base_y == 1){
			base_y = 8;
		}else if(base_y == 2){
			base_y = 16;
		}

	}else if(dificuldade == 3){
		base_x = rand() % 3;
		if(base_x == 0){
			base_x = 2;
		}else if(base_x == 1){
			base_x = 8;
		}else if(base_x == 2){
			base_x = 16;
		}
		base_y = rand() % 3;
		if(base_y == 0){
			base_y = 2;
		}else if(base_y == 1){
			base_y = 8;
		}else if(base_y == 2){
			base_y = 16;
		}

		if(base_x == base_y){
			if(base_x == 2){base_x = 8;}else{base_x = 2;}
		}
		num_x = gerar_numero_aleatorio(4,base_x);


	}else if(dificuldade == 4){
		base_x = (rand() % 15) + 2;
		base_y = (rand() % 15) + 2;

		if(base_x == base_y){
			if(base_x == 2){base_x = 8;}else{base_x = 2;}
		}

		num_x = gerar_numero_aleatorio(4,base_x);

	}else if(dificuldade == 5){
		base_x = (rand() % 35) + 2;
		base_y = (rand() % 35) + 2;

		if(base_x == base_y){
			if(base_x == 2){base_x = 8;}else{base_x = 2;}
		}

		num_x = gerar_numero_aleatorio(4,base_x);


	}

	std::cout << "converta o numero " << num_x << " na base " << base_x << " para a base " << base_y << ":\n";

	string resposta;

	cin >> resposta;

	string convertido = converter(num_x,base_x,base_y,false);

	if(resposta == convertido){
		cout << "parabens, voce acertou!";
		return dificuldade * dificuldade * 4;

	}else{
		cout << "que pena, voce errou... A resposta correta é " << convertido << "\n";
	}
	return 0;

}
