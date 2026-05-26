# include <iostream>
# include <string>

#include "formatador.h"
#include "conversor_base_x_para_10.h"
#include "calculadora_maximos.h"
using namespace std;

void calcular_maximos() {
    short k_digitos;
    string maximo_base_x;
    char maior_digito;
    string maximo_base_10;

    cout << "k_digitos = ";
    cin >> k_digitos;

    cout << "Com k_digitos = " << k_digitos << " digitos,"
        << " pode-se representar até (incluso):" << endl;
    for (short base_x = 2; base_x <= 36; base_x++) {
        maximo_base_x.clear();
        maximo_base_10.clear();

        maior_digito = de_num_para_caractere(base_x - 1);
        
        for (short digitos_colocados = 0; digitos_colocados < k_digitos; digitos_colocados++) {
            maximo_base_x += maior_digito;
        }

        maximo_base_10 = de_base_x_para_10(maximo_base_x, base_x, false);

        cout << maximo_base_10 << " (" << maximo_base_x << ") na base " << base_x << endl;
    }
}
// fim de calculadora_maximos.cpp
