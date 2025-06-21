#include <iostream>
using namespace std;

struct Nodo {
    string nombre;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(string nom) {
        nombre = nom;
        izquierda = derecha = NULL;
    }
};

Nodo* insertar(Nodo* raiz, string nombre) {
    if (raiz == NULL) {
        return new Nodo(nombre);
    }
    if (nombre < raiz->nombre) {
        raiz->izquierda = insertar(raiz->izquierda, nombre);
    } else if (nombre > raiz->nombre) {
        raiz->derecha = insertar(raiz->derecha, nombre);
    }
    return raiz;
}

Nodo* encontrarMinimo(Nodo* nodo) {
    while (nodo->izquierda != NULL) {
        nodo = nodo->izquierda;
    }
    return nodo;
}

Nodo* eliminar(Nodo* raiz, string nombre) {
    if (raiz == NULL) return NULL;

    if (nombre < raiz->nombre) {
        raiz->izquierda = eliminar(raiz->izquierda, nombre);
    } else if (nombre > raiz->nombre) {
        raiz->derecha = eliminar(raiz->derecha, nombre);
    } else {
        // Caso 1: sin hijos
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            delete raiz;
            return NULL;
        }
        // Caso 2: un solo hijo
        else if (raiz->izquierda == NULL) {
            Nodo* temp = raiz->derecha;
            delete raiz;
            return temp;
        } else if (raiz->derecha == NULL) {
            Nodo* temp = raiz->izquierda;
            delete raiz;
            return temp;
        }
        // Caso 3: dos hijos
        Nodo* temp = encontrarMinimo(raiz->derecha);
        raiz->nombre = temp->nombre;
        raiz->derecha = eliminar(raiz->derecha, temp->nombre);
    }

    return raiz;
}

void mostrarInorden(Nodo* raiz) {
    if (raiz == NULL) return;
    mostrarInorden(raiz->izquierda);
    cout << raiz->nombre << endl;
    mostrarInorden(raiz->derecha);
}

int main() {
    Nodo* raiz = NULL;
    int opcion;
    string nombre;

    do {
        cout << "\n--- MENU PROTOTIPO GENEALOGICO ---\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Eliminar miembro\n";
        cout << "3. Mostrar arbol (Inorden)\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Nombre del miembro: ";
                cin >> nombre;
                raiz = insertar(raiz, nombre);
                break;
            case 2:
                cout << "Nombre del miembro a eliminar: ";
                cin >> nombre;
                raiz = eliminar(raiz, nombre);
                cout << "Miembro eliminado (si existía).\n";
                break;
            case 3:
                cout << "\n-- Miembros en orden alfabetico --\n";
                mostrarInorden(raiz);
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }
    } while (opcion != 4);

    return 0;
}
