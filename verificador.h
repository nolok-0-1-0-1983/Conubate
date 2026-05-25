#ifndef VERIFICADOR_H
#define VERIFICADOR_H

bool numero_valido(std::string *num, int base, bool permitir_fracionario);

int texto_para_numero(std::string num);

std::string numero_para_texto(int num);

bool base_valida(std::string base);

std::string converter(std::string num_x, short base_x, short base_y, bool passo_a_passo);

void verificar_e_converter();

#endif
