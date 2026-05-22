#ifndef CONVERSOR_BASES_POTENCIA
#define CONVERSOR_BASES_POTENCIA

void descobre_potencia(short num_a, short num_b, short potencia_bases[4]);

std::string agrupa_digitos(std::string num_x, short base_x, short expoente_agrupa);

std::string separa_digitos(std::string num_x, short base_y, short expoente_separa);

std::string entre_bases_potencia(std::string num_x, short base_x, short base_y, short potencia_bases[4]);

#endif
