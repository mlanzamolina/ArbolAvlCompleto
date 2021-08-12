#include <cstdio>
#include <ctime>
#include "ArbolAvl.h"

registro buscarRegistroEnArchivo(char lastname[]) {
	ifstream in("datab_jc.dat", ios::in | ios::binary);
	registro reg;
	in.seekg(0, ios::end);
	int end = in.tellg();
	in.seekg(0, ios::beg);
	while(in.tellg() < end) {
		int currentPos = in.tellg();
		in.read((char*)&reg, sizeof(registro));
		if(strcmp(reg.lastname, lastname) == 0) {
			return reg;
		}
	}
	reg.id = -1;
	return reg;
}

int main() {
	Tree t;
	/*
	
	cout << "imprimir datos" << endl;
	t.preOrden(t.root);
	*/
	int opcion;

	do {
		cout << "1. Cargar datos al arbol AVL" << endl;
		cout << "2. Buscar dato y comparar tiempos" << endl;
		cout << "3. Eliminar registro del arbol" << endl;
		cout << "4. Imprimir todos los nombres con un apellido en especifico" << endl;
		cout << "5. Salir" << endl;
		cout << "6. Cargar pocos datos al arbol AVL" << endl;
		cout << "Opcion: ";
		cin >> opcion;

		switch(opcion) {
			case 1: {
				cout << "cargando datos" << endl;
				t.cargarDatos();
				cout << "datos cargados exitosamente" << endl;
				break;
			}
			case 2: {
				char name[30];
				char lastname[30];
				registro reg;

				cout << "Ingrese nombre: ";
				cin >> name;
				cout << "Ingrese apellido: ";
				cin >> lastname;

				std::clock_t start;
    			double duration;
				cout << endl;
				cout << "Busqueda en arbol avl" << endl;
    			start = std::clock();
				reg = t.findByLastname(t.root, lastname, name);
				if(reg.id == -1) {
					cout << "No se ha encontrado un registro con ese nombre" << endl;
					break;
				}

				reg.printRegister();

				duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
				cout << "duracion de la busqueda: " << duration << endl; 

				cout << " " << endl;

				cout << "Busqueda en archivo binario" << endl;

				start = std::clock();
				reg = buscarRegistroEnArchivo(lastname);

				reg.printRegister();

				duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
				cout << "duracion de la busqueda: " << duration << endl; 
				cout << endl;

				break;
			}
			case 3: {
				char name[30];
				char lastname[30];
				registro reg;

				cout << "Ingrese nombre: ";
				cin >> name;
				cout << "Ingrese apellido: ";
				cin >> lastname;
				if(t.deleteName(t.root, name, lastname)) {
					cout << "Se ha eliminado el registro del arbol binario con exito" << endl;
				}
				else {
					cout << "No se ha encontrado un registro con ese apellido/nombre" << endl;
				}
				break;
			}
			case 4: {
				char lastname[30];

				cout << "Ingrese apellido: ";
				cin >> lastname;
				cout << endl;
				t.printNodeNames(lastname);
				break;
			}
			case 5: {
				cout << "Saliendo del programa" << endl;
				break;
			}
			case 6: {
				cout << "cargando datos" << endl;
				t.cargarPocosDatos();
				cout << "datos cargados exitosamente" << endl;
				break;
			}
			case 7: {
				t.inOrden(t.root);
				break;
			}
			default: cout << "opcion incorrecta";
		}
		cout << " " << endl;
	} while(opcion != 5);
	

    return 0;
}