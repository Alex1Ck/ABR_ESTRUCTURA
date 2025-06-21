#include <iostream>
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

// Inserta un nodo en el Arbol
Nodo* insertar(Nodo* raiz, string nombre, int nac, int fall) {
    if (!raiz) return new Nodo(nombre, nac, fall);
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre, nac, fall);
    else if (nombre > raiz->nombre)
        raiz->derecha = insertar(raiz->derecha, nombre, nac, fall);
    return raiz;
}



// Mínimo (para eliminar)
Nodo* minimo(Nodo* nodo) {
    while (nodo && nodo->izquierda)
        nodo = nodo->izquierda;
    return nodo;
}

// Eliminar nodo
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

// Mostrar árbol como jerarquía (sin setw)
void mostrarJerarquia(Nodo* nodo, int nivel = 0) {
    if (!nodo) return;

    mostrarJerarquia(nodo->derecha, nivel + 1);

    for (int i = 0; i < nivel; ++i) cout << "    ";
    cout << nodo->nombre << " (" << nodo->nacimiento << "-" << nodo->fallecimiento << ")\n";

    mostrarJerarquia(nodo->izquierda, nivel + 1);
}

// Recorridos
void inorden(Nodo* nodo) {
    if (!nodo) return;
    inorden(nodo->izquierda);
    cout << nodo->nombre << " (" << nodo->nacimiento << "-" << nodo->fallecimiento << ")\n";
    inorden(nodo->derecha);
}

void preorden(Nodo* nodo) {
    if (!nodo) return;
    cout << nodo->nombre << " (" << nodo->nacimiento << "-" << nodo->fallecimiento << ")\n";
    preorden(nodo->izquierda);
    preorden(nodo->derecha);
}

void postorden(Nodo* nodo) {
    if (!nodo) return;
    postorden(nodo->izquierda);
    postorden(nodo->derecha);
    cout << nodo->nombre << " (" << nodo->nacimiento << "-" << nodo->fallecimiento << ")\n";
}

// Mostrar ancestros
bool mostrarAncestros(Nodo* raiz, string nombre) {
    if (!raiz) return false;
    if (raiz->nombre == nombre) return true;
    if (mostrarAncestros(raiz->izquierda, nombre) || mostrarAncestros(raiz->derecha, nombre)) {
        cout << raiz->nombre << " ? ";
        return true;
    }
    return false;
}

// Menú principal
int main() {
	setlocale(LC_CTYPE, "Spanish");
    Nodo* raiz = NULL;
    int opcion;
    string nombre;
    int nac, fall;

    do {
        cout << "\n======= ARBOL GENEALOGICO =======\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Eliminar miembro\n";
        cout << "3. Buscar miembro\n";
        cout << "4. Mostrar jerarquía\n";
        cout << "5. Mostrar Inorden\n";
        cout << "6. Mostrar Preorden\n";
        cout << "7. Mostrar Postorden\n";
        cout << "8. Mostrar ancestros\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";
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
                cout << "\nNombre a buscar: ";
                cin >> nombre;
                if (buscar(raiz, nombre)) {
                    cout << nombre << " fue encontrado.\n";
                } else {
                    cout << nombre << " no se encuentra en el árbol.\n";
                }
                break;
            case 4:
                cout << "\n--- Árbol Genealógico (Jerárquico) ---\n";
                mostrarJerarquia(raiz);
                break;
            case 5:
                cout << "\n--- Inorden ---\n";
                inorden(raiz);
                break;
            case 6:
                cout << "\n--- Preorden ---\n";
                preorden(raiz);
                break;
            case 7:
                cout << "\n--- Postorden ---\n";
                postorden(raiz);
                break;
            case 8:
                cout << "\nNombre para ver ancestros: ";
                cin >> nombre;
                cout << "Ancestros: ";
                if (!mostrarAncestros(raiz, nombre)) {
                    cout << "No se encontraron ancestros o el miembro no existe.\n";
                } else {
                    cout << nombre << endl;
                }
                break;
            case 9:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 9);

    return 0;
}

