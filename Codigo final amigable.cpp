#include <iostream>
#include <vector>
using namespace std;

// Estructura que representa un nodo del árbol genealógico
struct Nodo {
    string nombre;         //Nombre del familiar
    int nacimiento;       //Año de nacimiento
    int fallecimiento;   //Año de fallecimiento
    Nodo* izquierda;    // Puntero al hijo izquierdo (menor)
    Nodo* derecha;     // Puntero al hijo derecho (mayor)

	//Contructor para inicializar un nodo
    Nodo(string nom, int nac, int fall)
        : nombre(nom), nacimiento(nac), fallecimiento(fall), izquierda(NULL), derecha(NULL) {}
};

// Funcuñon para insertar un nuevo nodo en el árbol
Nodo* insertar(Nodo* raiz, string nombre, int nac, int fall) {
    if (!raiz) {
    	//Si la raíz está vacía, se crea un nuevo nodo
        cout << "¡Miembro agregado con éxito! ^^" << endl;
        return new Nodo(nombre, nac, fall);
    }
    //Inserción ordenada según el nombre
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre, nac, fall);
    else if (nombre > raiz->nombre)
        raiz->derecha = insertar(raiz->derecha, nombre, nac, fall);
    else
        cout << "Ya existe un miembro con ese nombre O.O\n";
    return raiz;
}

//Función para buscar un miembro por su nombre
Nodo* buscar(Nodo* raiz, string nombre) {
    if (!raiz || raiz->nombre == nombre) return raiz;  //Retorna si lo encuentra
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierda, nombre);  //Busca a la izquierda
    else
        return buscar(raiz->derecha, nombre);  //Busca a la derecha
}

//Función para encontrar el nodo con el valor más bajo (más a la izquierda)
Nodo* minimo(Nodo* nodo) {
    while (nodo && nodo->izquierda)
        nodo = nodo->izquierda;
    return nodo;
}

// Función para eliminar un nodo del árbol
Nodo* eliminar(Nodo* raiz, string nombre) {
    if (!raiz) {
        cout << "Miembro no encontrado T.T\n";
        return NULL;
    }

    if (nombre < raiz->nombre)
        raiz->izquierda = eliminar(raiz->izquierda, nombre);
    else if (nombre > raiz->nombre)
        raiz->derecha = eliminar(raiz->derecha, nombre);
    else {
    	//Nodo encontrado
        cout << "Eliminando miembro T.T\n";
        
        // Caso 1: sin hijos
        if (!raiz->izquierda && !raiz->derecha) {
            delete raiz;
            cout << "Miembro eliminado sin descendencia ^^" << endl;
            return NULL;
        } 
		// Caso 2: un solo hijo
		else if (!raiz->izquierda || !raiz->derecha) {
            Nodo* hijo = raiz->izquierda ? raiz->izquierda : raiz->derecha;
            delete raiz;
            cout << "Miembro eliminado con un solo descendiente ^^" << endl;
            return hijo;
        } 
		// Caso 3: dos hijos
		else {
            Nodo* sucesor = minimo(raiz->derecha);
            raiz->nombre = sucesor->nombre;
            raiz->nacimiento = sucesor->nacimiento;
            raiz->fallecimiento = sucesor->fallecimiento;
            //Eliminar el sucesor
            raiz->derecha = eliminar(raiz->derecha, sucesor->nombre);
            cout << "Miembro reemplazado por su sucesor ^^" << endl;
        }
    }
    return raiz;
}

//Muestra el árbol jerárquicamente 
void mostrarJerarquia(Nodo* nodo, int nivel = 0) {
    if (!nodo) return;

    mostrarJerarquia(nodo->derecha, nivel + 1); //Mostrar lado derecho

    for (int i = 0; i < nivel; ++i) cout << "    ";  //según nivel
    cout << nodo->nombre << " (" << nodo->nacimiento << "-" << nodo->fallecimiento << ")\n";

    mostrarJerarquia(nodo->izquierda, nivel + 1); //Mostrar lado izquierdo
}

//Recorrido inordern: izquierda, raíz, derecha 
void inorden(Nodo* nodo) {
    if (nodo) {
        inorden(nodo->izquierda);
        cout << "Nombre: " << nodo->nombre << ", Nacimiento: " << nodo->nacimiento << ", Fallecimiento: " << nodo->fallecimiento << endl;
        inorden(nodo->derecha);
    }
}

//Recorrido preorden: raíz, izquierda, derecha
void preorden(Nodo* nodo) {
    if (nodo) {
        cout << "Nombre: " << nodo->nombre << ", Nacimiento: " << nodo->nacimiento << ", Fallecimiento: " << nodo->fallecimiento << endl;
        preorden(nodo->izquierda);
        preorden(nodo->derecha);
    }
}

//Recorrido post orden: izquierda, derecha, raíz
void postorden(Nodo* nodo) {
    if (nodo) {
        postorden(nodo->izquierda);
        postorden(nodo->derecha);
        cout << "Nombre: " << nodo->nombre << ", Nacimiento: " << nodo->nacimiento << ", Fallecimiento: " << nodo->fallecimiento << endl;
    }
}

//Muestra los ancestros de un miembro, desde la raíz hasta el miembro
bool mostrarAncestros(Nodo* raiz, string nombre) {
    if (!raiz) return false;
    if (raiz->nombre == nombre) return true;
    if (mostrarAncestros(raiz->izquierda, nombre) || mostrarAncestros(raiz->derecha, nombre)) {
        cout << raiz->nombre << " -> ";
        return true;
    }
    return false;
}

//Función principal
int main() {
    setlocale(LC_CTYPE, "Spanish");
    Nodo* raiz = NULL;
    int opcion;
    string nombre;
    int nac, fall;

	//Menú principal
    do {
        cout << "\n======= MENÚ ÁRBOL GENEALÓGICO =======\n";
        cout << "1. Insertar miembro ^^\n";
        cout << "2. Eliminar miembro T.T\n";
        cout << "3. Modificar miembro UwU\n";
        cout << "4. Buscar miembro O.O\n";
        cout << "5. Mostrar jerarquía :3\n";
        cout << "6. Mostrar Inorden\n";
        cout << "7. Mostrar Preorden\n";
        cout << "8. Mostrar Postorden\n";
        cout << "9. Mostrar ancestros\n";
        cout << "10. Salir =(\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        	
            case 1: //Insertar
                cout << "\nIngrese los datos del nuevo miembro ^^" << endl;
                cout << "Nombre: ";
                cin >> nombre;
                cout << "Año de nacimiento: ";
                cin >> nac;
                cout << "Año de fallecimiento: ";
                cin >> fall;
                raiz = insertar(raiz, nombre, nac, fall);
                break;
                
            case 2: //Eliminar
                cout << "\nNombre a eliminar (snif snif T.T): ";
                cin >> nombre;
                raiz = eliminar(raiz, nombre);
                break;
                
            case 3: //Modificar los datos
                cout << "\nNombre del miembro a modificar: ";
                cin >> nombre;
                {
                    Nodo* nodoMod = buscar(raiz, nombre);
                    if (nodoMod) {
                        cout << "¿Qué desea modificar de este miembro tan especial? UwU\n";
                        cout << "1. Nombre\n2. Año de nacimiento\n3. Año de fallecimiento\nOpción: ";
                        int opMod;
                        cin >> opMod;

                        switch (opMod) {
                        	
                            case 1: {
                            	//Cambiar nombre
                                string nuevoNombre;
                                cout << "Nuevo nombre: ";
                                cin >> nuevoNombre;
                                if (buscar(raiz, nuevoNombre)) {
                                    cout << "Ya existe un miembro con ese nombre O.O\n";
                                } else {
                                    int nac = nodoMod->nacimiento;
                                    int fall = nodoMod->fallecimiento;
                                    raiz = eliminar(raiz, nodoMod->nombre); //Eliminar antiguo
                                    raiz = insertar(raiz, nuevoNombre, nac, fall); //Insertar nuevo
                                    cout << "Nombre modificado con éxito ^^\n";
                                }
                                break;
                            }
                            
                            case 2:
                            	//Cambiar fecha de nacimiento
                                cout << "Nuevo año de nacimiento: ";
                                cin >> nodoMod->nacimiento;
                                cout << "Nacimiento actualizado exitosamente UwU\n";
                                break;
                                
                            case 3:
                            	//Cambiar fecha de fallecimiento
                                cout << "Nuevo año de fallecimiento: ";
                                cin >> nodoMod->fallecimiento;
                                cout << "Fallecimiento actualizado T.T\n";
                                break;
                            default:
                                cout << "Opción inválida O.O\n";
                        }
                    } else {
                        cout << "Miembro no encontrado T-T\n";
                    }
                }
                break;
                
            case 4: //buscar miembro
                cout << "\nNombre a buscar: ";
                cin >> nombre;
                if (buscar(raiz, nombre)) {
                    cout << nombre << " fue encontrado en el árbol familiar ^u^\n";
                } else {
                    cout << nombre << " no se encuentra en el árbol TnT\n";
                }
                break;
                
            case 5: //Mostrar jerar
                cout << "\n--- Árbol Genealógico ---\n";
                mostrarJerarquia(raiz);
                break;
                
            case 6: //In order
                cout << "\n--- Recorrido Inorden (de menor a mayor) ---\n";
                inorden(raiz);
                break;
                
            case 7: //Pre orden
                cout << "\n--- Recorrido Preorden ---\n";
                preorden(raiz);
                break;
                
            case 8: //Post orden
                cout << "\n--- Recorrido Postorden (los hijos al final) ---\n";
                postorden(raiz);
                break;
                
            case 9: //Mostrar ancestros
                cout << "\nNombre para ver ancestros: ";
                cin >> nombre;
                cout << "Ancestros: ";
                if (!mostrarAncestros(raiz, nombre)) {
                    cout << "No se encontraron ancestros o el miembro no existe TnT\n";
                } else {
                    cout << nombre << endl;
                }
                break;
                
            case 10: //Salir 
                cout << "Saliendo del programa, hasta luego ^u^\n";
                break;
            default:
                cout << "Opción inválida, inténtalo otra vez O.O\n";
        }
    } while (opcion != 10); //Repite el menú mientras no se elija salir

    return 0;
}

