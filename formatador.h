#ifndef FORMATADOR_H
#define FORMATADOR_H

short de_caractere_para_num(char c);

char de_num_para_caractere(short n);

char descobre_sinal(std::string *num);

void separar_fracionario(std::string num, std::string *parte_inteira, std::string *parte_fracionaria);

#endif
