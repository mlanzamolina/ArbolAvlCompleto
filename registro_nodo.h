#ifndef _REGISTRO_NODO_H_
#define _REGISTRO_NODO_H_

#include <vector>
#include "registro_repetido.h"

struct registro_nodo {
    char name[30];
    int position; //posicion en el archivo del registro
    std::vector<registro_repetido> repetidos;
};

#endif