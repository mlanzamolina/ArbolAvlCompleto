#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include "avl.h"
#include "registro.h"
#include "registro_repetido.h"

using namespace std;

class Tree {
public:
    Tree();
    void cargarDatos();
    void cargarPocosDatos();
    void addNode(char lastname[], char name[], int position);
    registro findByLastname(AVL*, char lastname[], char name[]);
	AVL* root;
    vector<string>list;
	void addNode(AVL*, AVL**, char name[], int position);
    AVL* minValueNode(AVL*);
    AVL* deleteNode(AVL*, char lastname[]);
    bool deleteName(AVL*, char name[], char lastname[]);
    void preOrden(AVL*);
    void inOrden(AVL*);
    void postOrden(AVL*);
    AVL* getLastnameNode(AVL**, char lastname[]);
    void printNodeNames(char lastname[]);
    int getHeight(AVL*);
    int getSize(AVL*);

    //funciones para balancear el arbol
    void balanciar(AVL**);
    void RotaIzq(AVL**);
    void RotaDere(AVL**);
    void DobleRotaIzq(AVL**);
    void DobleRotaDere(AVL**);
};

#endif