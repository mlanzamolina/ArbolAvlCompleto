#include "ArbolAvl.h"

Tree::Tree() {
	root = NULL;
}

void Tree::cargarDatos() {
	ifstream in("datab_jc.dat", ios::in | ios::binary);
	if(!in.is_open()) {
		std::cout << "could not open file" << std::endl;
		return;
	}
	registro nuevoRegistro;
	in.seekg(0, ios::end);
	int end = in.tellg();
	in.seekg(0, ios::beg);
	while(in.tellg() < end) {
		int currentPos = in.tellg();
		in.read((char*)&nuevoRegistro, sizeof(registro));
		addNode(nuevoRegistro.lastname, nuevoRegistro.name, currentPos);
	}
	in.close();
}

void Tree::cargarPocosDatos() {
	ifstream in("datab_jc.dat", ios::in | ios::binary);
	if(!in.is_open()) {
		std::cout << "could not open file" << std::endl;
		return;
	}
	registro nuevoRegistro;

	for(int i = 0; i < 50000; i++) {
		int currentPos = in.tellg();
		in.read((char*)&nuevoRegistro, sizeof(registro));
		addNode(nuevoRegistro.lastname, nuevoRegistro.name, currentPos);
	}
}

void Tree::addNode(char lastname[], char name[], int position) {
	AVL* newNode = new AVL(lastname);
	addNode(newNode, &root, name, position);
}

void Tree::addNode(AVL* nuevo, AVL** raiz, char name[], int position) {
	if (*raiz == NULL) {
		*raiz = nuevo;
		registro_nodo nuevoElemento;
		strcpy(nuevoElemento.name, name); 
		nuevoElemento.position = position;
		(*raiz)->listaNombres.push_back(nuevoElemento);
	}
	else {
		if (strcmp(nuevo->lastname, (*raiz)->lastname) < 0) {
			addNode(nuevo, &(*raiz)->izq, name, position);
			
		}
		else if (strcmp(nuevo->lastname, (*raiz)->lastname) > 0) {
			addNode(nuevo, &(*raiz)->dere, name, position);
		}
		else  {
			//agregar nombre a la lista de este apellido
			delete nuevo;
			
			int posicionRepetido = (*raiz)->searchForName(name);
			//si el nombre que intentamos agregar ya existe, entonces lo agregamos a la lista de repetidos
			if(posicionRepetido != -1) {
				registro_repetido nuevoElemento;
				strcpy(nuevoElemento.name, name); 
				nuevoElemento.position = position;
				//agregar nuevo registro a la lista de nombres repetidos 
				(*raiz)->listaNombres[posicionRepetido].repetidos.push_back(nuevoElemento);
			}
			//si el nombre aun no existe, vamos a agregarlo a la lista de los nodos
			else {
				registro_nodo nuevoElemento;
				strcpy(nuevoElemento.name, name); 
				nuevoElemento.position = position;
				//agregar nuevo registro a la lista de nombres
				(*raiz)->listaNombres.push_back(nuevoElemento);
			}
		}
	}
	balanciar(raiz);
}

AVL* Tree::minValueNode(AVL* raiz) {
	AVL* actual = raiz;

	while (actual->izq != NULL) {
		actual = actual->izq;
	}

	return actual;
}


int Tree::getHeight(AVL* raiz) {
	if (raiz == NULL)
		return 0;
	else {
		int izquierda = getHeight(raiz->izq);
		int derecha = getHeight(raiz->dere);
		if (izquierda > derecha)
			return izquierda + 1;
		else
			return derecha + 1;
	}
}

int Tree::getSize(AVL* raiz) {
	if (raiz == NULL)
		return 0;
	return (getSize(raiz->izq) + 1 + getSize(raiz->dere));
}

void Tree::RotaIzq(AVL** raiz) {
	AVL* derecha = (*raiz)->dere;
	(*raiz)->dere = derecha->izq;
	derecha->izq = *raiz;
	*raiz = derecha;
}

void Tree::RotaDere(AVL** raiz) {
	AVL* izquierda = (*raiz)->izq;
	(*raiz)->izq = izquierda->dere;
	izquierda->dere = *raiz;
	*raiz = izquierda;
}

void Tree::DobleRotaIzq(AVL** raiz) {
	AVL* derecha = (*raiz)->dere;
	RotaDere(&derecha);
	RotaIzq(raiz);
}

void Tree::DobleRotaDere(AVL** raiz) {
	AVL* izquierda = (*raiz)->izq;
	RotaIzq(&izquierda);
	RotaDere(raiz);
}

void Tree::balanciar(AVL** raiz) {
	if ((getHeight((*raiz)->izq) - getHeight((*raiz)->dere)) < 2)
		return;

	if (getHeight((*raiz)->dere) > getHeight((*raiz)->izq)) {
		if (getHeight((*raiz)->dere->dere) >= getHeight((*raiz)->dere->izq))
			RotaIzq(raiz);
		else
			DobleRotaIzq(raiz);
	}
	else {
		if (getHeight((*raiz)->izq->izq) >= getHeight((*raiz)->dere))
			RotaDere(raiz);
		else
			DobleRotaDere(raiz);
	}
}

registro Tree::findByLastname(AVL* raiz, char lastname[], char name[]) {
	AVL* subroot = getLastnameNode(&raiz, lastname); //retorna NULL en caso que no encuentre nada
	registro reg;
	reg.id = -1; //retornar con id -1 en caso que no se haya encontrado nada

	//si no se encontro nada
    if (subroot == NULL) {
		return reg;
	}
	//si el apellido coincide
	else {
		for(int i = 0; i < subroot->listaNombres.size(); i++) {
			//si el nombre coincide, ir a buscar el registro al archivo binario y devolverlo
			if(strcmp(subroot->listaNombres[i].name, name) == 0) {
				ifstream in("datab_jc.dat", ios::in | ios::binary);
				in.seekg(subroot->listaNombres[i].position);
				in.read((char*)&reg, sizeof(registro));
				return reg;
			}
		}
		//si no se encuentra el nombre, devolver un registro con id -1
		return reg;
	}
}

bool Tree::deleteName(AVL* raiz, char name[], char lastname[]) {
	AVL *subroot = getLastnameNode(&root, lastname);

	//si no se encuentra el apellido
	if(subroot == NULL) {
		return false;
	}

	//si se ha encontrado un nodo con este apellido, entonces buscamos el nombre
	for(int i = 0; i < subroot->listaNombres.size(); i++) {
		//si el nombre coincide, ir a buscar el registro al archivo binario y devolverlo

		if(strcmp(subroot->listaNombres[i].name, name) == 0) {
			subroot->listaNombres.erase(subroot->listaNombres.begin() + i);
			//si el nodo ya no tiene mas nombres, borrar por completo este nodo del arbol
			if(subroot->listaNombres.empty()) {
				deleteNode(root, lastname);
			}
			return true;
		}
	}
	//si no se encuentra el nombre, devolver false
	return false;
}

AVL* Tree::deleteNode(AVL* raiz, char lastname[]) {
	//caso base
	if (raiz == NULL) {
		return raiz;
	}

	if(strcmp(lastname, raiz->lastname) < 0) {
		raiz->izq = deleteNode(raiz->izq, lastname);
	}

	if(strcmp(lastname, raiz->lastname) > 0) {
		raiz->dere = deleteNode(raiz->dere, lastname);
	}

	else {
		//nodo con un solo hijo o con ninguno
		if (raiz->izq == NULL) {
			AVL* temp = raiz->dere;
			delete raiz;
			return temp;
		}
		else if (raiz->dere == NULL) {
			AVL* temp = raiz->izq;
			delete raiz;
			return temp;
		}

		AVL* temp = minValueNode(raiz->dere);
		strcpy(raiz->lastname, temp->lastname);
		raiz->listaNombres = temp->listaNombres;

		raiz->dere = deleteNode(raiz->dere, temp->lastname);
	}
	return raiz;
}

void Tree::preOrden(AVL* raiz) {
	if (raiz == NULL)
		return;

	cout << raiz->lastname << endl;

	if (raiz->izq != NULL)
		preOrden(raiz->izq);
	if (raiz->dere != NULL)
		preOrden(raiz->dere);
}

void Tree::inOrden(AVL* raiz) {
	if (raiz == NULL)
		return;
	if (raiz->izq != NULL)
		inOrden(raiz->izq);
	cout << raiz->lastname << endl;
	if (raiz->dere != NULL)
		inOrden(raiz->dere);
}

void Tree::postOrden(AVL* raiz) {
	if (raiz == NULL)
		return;
	if (raiz->izq != NULL)
		postOrden(raiz->izq);
	if (raiz->dere != NULL)
		postOrden(raiz->dere);
	cout << raiz->lastname << endl;
}

AVL* Tree::getLastnameNode(AVL** raiz, char lastname[]) {
	//si no se encontro nada o si el apellido se encuentra
    if (*raiz == NULL) {
		return *raiz;
	}
	else if(strcmp(lastname, (*raiz)->lastname) == 0) {
		return *raiz;
	}
    
    // en caso de que el cmp sea menor
    if (strcmp((*raiz)->lastname, lastname) < 0) {
		return getLastnameNode(&(*raiz)->dere, lastname);
	}
       
 
    // en caso que el cmp sea mayor
    return getLastnameNode(&(*raiz)->izq, lastname);
}

void Tree::printNodeNames(char lastname[]) {
	AVL* subroot = getLastnameNode(&root, lastname);
	if(subroot == NULL) { 
		cout << "No se ha encontrado ese apellido dentro del arbol" << endl;
	}
	else {
		registro reg;
		ifstream in("datab_jc.dat", ios::in | ios::binary);
		for(int i = 0; i < subroot->listaNombres.size(); i++) {
			//imprimir el nombre que encontremos
			in.seekg(subroot->listaNombres[i].position);
			in.read((char*)&reg, sizeof(registro));
			reg.printRegister();
			cout << "" << endl;
			//imprimir los nombres repetidos, en caso de que los haya
			if(!subroot->listaNombres[i].repetidos.empty()) {
				cout << "Imprimiendo lista de repetidos" << endl;
				for(int j = 0; j < subroot->listaNombres[i].repetidos.size(); j++) {
					in.seekg(subroot->listaNombres[i].repetidos[j].position);
					in.read((char*)&reg, sizeof(registro));
					reg.printRegister();
					cout << "" << endl;
				}
			}
		}
		in.close();
	}
}