#include <iostream>
#include <vector>
using namespace std;

struct Nodo {
    string nombre;
    int nacimiento;
    int fallecimiento;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(string nom, int nac, int fall)
        : nombre(nom), nacimiento(nac), fallecimiento(fall), izquierda(NULL), derecha(NULL) {}
};

// Inserción con verificación de duplicados
Nodo* insertar(Nodo* raiz, string nombre, int nac, int fall) {
    if (!raiz) return new Nodo(nombre, nac, fall);
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre, nac, fall);
    else if (nombre > raiz->nombre)
        raiz->derecha = insertar(raiz->derecha, nombre, nac, fall);
    else
        cout << "Ya existe un miembro con ese nombre O.O\n";
    return raiz;
}

Nodo* buscar(Nodo* raiz, string nombre) {
    if (!raiz || raiz->nombre == nombre) return raiz;
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierda, nombre);
    else
        return buscar(raiz->derecha, nombre);
}

Nodo* minimo(Nodo* nodo) {
    while (nodo && nodo->izquierda)
        nodo = nodo->izquierda;
    return nodo;
}

Nodo* eliminar(Nodo* raiz, string nombre) {
    if (!raiz) return NULL;

    if (nombre < raiz->nombre)
        raiz->izquierda = eliminar(raiz->izquierda, nombre);
    else if (nombre > raiz->nombre)
        raiz->derecha = eliminar(raiz->derecha, nombre);
    else {
        if (!raiz->izquierda && !raiz->derecha) {
            delete raiz;
            return NULL;
        } else if (!raiz->izquierda || !raiz->derecha) {
            Nodo* hijo = raiz->izquierda ? raiz->izquierda : raiz->derecha;
            delete raiz;
            return hijo;
        } else {
            Nodo* sucesor = minimo(raiz->derecha);
            raiz->nombre = sucesor->nombre;
            raiz->nacimiento = sucesor->nacimiento;
            raiz->fallecimiento = sucesor->fallecimiento;
            raiz->derecha = eliminar(raiz->derecha, sucesor->nombre);
        }
    }
    return raiz;
}

void mostrarJerarquia(Nodo* nodo, int nivel = 0) {
    if (!nodo) return;

    mostrarJerarquia(nodo->derecha, nivel + 1);

    for (int i = 0; i < nivel; ++i) cout << "    ";
    cout << nodo->nombre << " (" << nodo->nacimiento << "-" << nodo->fallecimiento << ")\n";

    mostrarJerarquia(nodo->izquierda, nivel + 1);
}

void inorden(Nodo* nodo) {
    if (nodo) {
        inorden(nodo->izquierda);
        cout << "Nombre: " << nodo->nombre << ", Nacimiento: " << nodo->nacimiento << ", Fallecimiento: " << nodo->fallecimiento << endl;
        inorden(nodo->derecha);
    }
}

void preorden(Nodo* nodo) {
    if (nodo) {
        cout << "Nombre: " << nodo->nombre << ", Nacimiento: " << nodo->nacimiento << ", Fallecimiento: " << nodo->fallecimiento << endl;
        preorden(nodo->izquierda);
        preorden(nodo->derecha);
    }
}

void postorden(Nodo* nodo) {
    if (nodo) {
        postorden(nodo->izquierda);
        postorden(nodo->derecha);
        cout << "Nombre: " << nodo->nombre << ", Nacimiento: " << nodo->nacimiento << ", Fallecimiento: " << nodo->fallecimiento << endl;
    }
}

bool mostrarAncestros(Nodo* raiz, string nombre) {
    if (!raiz) return false;
    if (raiz->nombre == nombre) return true;
    if (mostrarAncestros(raiz->izquierda, nombre) || mostrarAncestros(raiz->derecha, nombre)) {
        cout << raiz->nombre << " -> ";
        return true;
    }
    return false;
}

int main() {
    setlocale(LC_CTYPE, "Spanish");
    Nodo* raiz = NULL;
    int opcion;
    string nombre;
    int nac, fall;

    do {
        cout << "\n======= MENÚ ÁRBOL GENEALÓGICO =======\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Eliminar miembro\n";
        cout << "3. Modificar miembro\n";
        cout << "4. Buscar miembro\n";
        cout << "5. Mostrar jerarquía\n";
        cout << "6. Mostrar Inorden\n";
        cout << "7. Mostrar Preorden\n";
        cout << "8. Mostrar Postorden\n";
        cout << "9. Mostrar ancestros\n";
        cout << "10. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\nNombre: ";
                cin >> nombre;
                cout << "Año de nacimiento: ";
                cin >> nac;
                cout << "Año de fallecimiento: ";
                cin >> fall;
                raiz = insertar(raiz, nombre, nac, fall);
                break;
            case 2:
                cout << "\nNombre a eliminar: ";
                cin >> nombre;
                raiz = eliminar(raiz, nombre);
                break;
            case 3:
                cout << "\nNombre del miembro a modificar: ";
                cin >> nombre;
                {
                    Nodo* nodoMod = buscar(raiz, nombre);
                    if (nodoMod) {
                        cout << "¿Qué desea modificar?\n";
                        cout << "1. Nombre\n2. Año de nacimiento\n3. Año de fallecimiento\nOpción: ";
                        int opMod;
                        cin >> opMod;

                        switch (opMod) {
                            case 1: {
                                string nuevoNombre;
                                cout << "Nuevo nombre: ";
                                cin >> nuevoNombre;
                                if (buscar(raiz, nuevoNombre)) {
                                    cout << "Ya existe un miembro con ese nombre O.O\n";
                                } else {
                                    int nac = nodoMod->nacimiento;
                                    int fall = nodoMod->fallecimiento;
                                    raiz = eliminar(raiz, nodoMod->nombre);
                                    raiz = insertar(raiz, nuevoNombre, nac, fall);
                                    cout << "Nombre modificado con éxito ^^\n";
                                }
                                break;
                            }
                            case 2:
                                cout << "Nuevo año de nacimiento: ";
                                cin >> nodoMod->nacimiento;
                                cout << "Nacimiento actualizado.\n";
                                break;
                            case 3:
                                cout << "Nuevo año de fallecimiento: ";
                                cin >> nodoMod->fallecimiento;
                                cout << "Fallecimiento actualizado ^^\n";
                                break;
                            default:
                                cout << "Opción inválida TnT\n";
                        }
                    } else {
                        cout << "Miembro no encontrado ^u^\n";
                    }
                }
                break;
            case 4:
                cout << "\nNombre a buscar: ";
                cin >> nombre;
                if (buscar(raiz, nombre)) {
                    cout << nombre << " fue encontrado ^u^\n";
                } else {
                    cout << nombre << " no se encuentra en el árbol TnT\n";
                }
                break;
            case 5:
                cout << "\n--- Árbol Genealógico ---\n";
                mostrarJerarquia(raiz);
                break;
            case 6:
                cout << "\n--- Recorrido Inorden ---\n";
                inorden(raiz);
                break;
            case 7:
                cout << "\n--- Recorrido Preorden ---\n";
                preorden(raiz);
                break;
            case 8:
                cout << "\n--- Recorrido Postorden ---\n";
                postorden(raiz);
                break;
            case 9:
                cout << "\nNombre para ver ancestros: ";
                cin >> nombre;
                cout << "Ancestros: ";
                if (!mostrarAncestros(raiz, nombre)) {
                    cout << "No se encontraron ancestros o el miembro no existe TnT\n";
                } else {
                    cout << nombre << endl;
                }
                break;
            case 10:
                cout << "Saliendo del programa ^u^\n";
                break;
            default:
                cout << "Opción inválida O.O\n";
        }
    } while (opcion != 10);

    return 0;
}

