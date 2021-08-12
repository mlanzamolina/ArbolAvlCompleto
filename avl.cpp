#include "avl.h"

AVL::AVL(char lastname[]) {
	strcpy(this->lastname, lastname);
	izq = NULL;
	dere = NULL;
}

int AVL::searchForName(char name[]) {
	for(int i = 0; i < listaNombres.size(); i++) {
		if(strcmp(name, listaNombres[i].name) == 0) {
			return i;
		}
	}
	return -1;
}