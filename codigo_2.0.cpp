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

vector<Nodo*> miembros;  // Almacena todos los nodos insertados

Nodo* insertar(Nodo* raiz, string nombre, int nac, int fall) {
    if (!raiz) {
        Nodo* nuevo = new Nodo(nombre, nac, fall);
        miembros.push_back(nuevo);  // Guardamos en vector
        return nuevo;
    }
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre, nac, fall);
    else if (nombre > raiz->nombre)
        raiz->derecha = insertar(raiz->derecha, nombre, nac, fall);
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

// Muestra los ancestros de un nodo y los guarda en un vector
bool mostrarAncestros(Nodo* raiz, string nombre, vector<string>& ancestros) {
    if (!raiz) return false;
    if (raiz->nombre == nombre) return true;
    if (mostrarAncestros(raiz->izquierda, nombre, ancestros) ||
        mostrarAncestros(raiz->derecha, nombre, ancestros)) {
        ancestros.push_back(raiz->nombre);
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
        cout << "\n======= ÁRBOL GENEALÓGICO =======\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Eliminar miembro\n";
        cout << "3. Buscar miembro\n";
        cout << "4. Mostrar jerarquía\n";
        cout << "5. Mostrar Inorden\n";
        cout << "6. Mostrar Preorden\n";
        cout << "7. Mostrar Postorden\n";
        cout << "8. Mostrar ancestros\n";
        cout << "9. Mostrar todos los miembros\n";
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
                {
                    vector<string> ancestros;
                    if (mostrarAncestros(raiz, nombre, ancestros)) {
                        cout << "Ancestros: ";
                        for (auto it = ancestros.rbegin(); it != ancestros.rend(); ++it)
                            cout << *it << " → ";
                        cout << nombre << endl;
                    } else {
                        cout << "No se encontraron ancestros o el miembro no existe.\n";
                    }
                }
                break;
            case 9:
                cout << "\n--- Miembros registrados (Vector) ---\n";
                for (Nodo* n : miembros)
                    cout << n->nombre << " (" << n->nacimiento << "-" << n->fallecimiento << ")\n";
                break;
            case 10:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 10);

    return 0;
}
