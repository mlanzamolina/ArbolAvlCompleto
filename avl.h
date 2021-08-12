#ifndef _AVL_H_
#define _AVL_H_

#include <vector>
#include <string.h>
#include "registro_nodo.h"

struct AVL {

	char lastname[30];
	AVL * izq;
	AVL* dere;
    std::vector<registro_nodo> listaNombres;

	//int peso();
	AVL(char lastname[]);

	int searchForName(char name[]);

};

#endif