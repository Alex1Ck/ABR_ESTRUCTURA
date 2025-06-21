#include <iostream>
#include <vector>
using namespace std;

// Estructura de un Nodo en el arbol genealogico
struct Nodo {
    string nombre;
    int nacimiento;
    int fallecimiento;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo(string nom, int nac, int fall)
        : nombre(nom), nacimiento(nac), fallecimiento(fall), izquierda(NULL), derecha(NULL) {}
};

// Vector para almacenar miembros insertados
vector<Nodo*> miembros;

// Funcion para insertar un nodo en el arbol
Nodo* insertar(Nodo* raiz, string nombre, int nac, int fall) {
    if (!raiz) {
        Nodo* nuevo = new Nodo(nombre, nac, fall);
        miembros.push_back(nuevo); // Guardar referencia
        return nuevo;
    }
    if (nombre < raiz->nombre)
        raiz->izquierda = insertar(raiz->izquierda, nombre, nac, fall);
    else if (nombre > raiz->nombre)
        raiz->derecha = insertar(raiz->derecha, nombre, nac, fall);
    return raiz;
}

// Buscar un nodo por nombre
Nodo* buscar(Nodo* raiz, string nombre) {
    if (!raiz || raiz->nombre == nombre) return raiz;
    if (nombre < raiz->nombre)
        return buscar(raiz->izquierda, nombre);
    else
        return buscar(raiz->derecha, nombre);
}

// Encontrar el nodo minimo (usado en eliminacion)
Nodo* minimo(Nodo* nodo) {
    while (nodo && nodo->izquierda)
        nodo = nodo->izquierda;
    return nodo;
}

// Eliminar un nodo por nombre
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

// Recorridos
void inorden(Nodo* nodo) {
    if (nodo) {
        inorden(nodo->izquierda);
        cout << "Nombre: " << nodo->nombre
             << ", Nacimiento: " << nodo->nacimiento
             << ", Fallecimiento: " << nodo->fallecimiento << endl;
        inorden(nodo->derecha);
    }
}

void preorden(Nodo* nodo) {
    if (nodo) {
        cout << "Nombre: " << nodo->nombre
             << ", Nacimiento: " << nodo->nacimiento
             << ", Fallecimiento: " << nodo->fallecimiento << endl;
        preorden(nodo->izquierda);
        preorden(nodo->derecha);
    }
}

void postorden(Nodo* nodo) {
    if (nodo) {
        postorden(nodo->izquierda);
        postorden(nodo->derecha);
        cout << "Nombre: " << nodo->nombre
             << ", Nacimiento: " << nodo->nacimiento
             << ", Fallecimiento: " << nodo->fallecimiento << endl;
    }
}

// Mostrar jerarquia
void mostrarJerarquia(Nodo* nodo, int nivel = 0) {
    if (!nodo) return;
    mostrarJerarquia(nodo->derecha, nivel + 1);
    for (int i = 0; i < nivel; ++i) cout << "    ";
    cout << nodo->nombre << " (" << nodo->nacimiento << "-" << nodo->fallecimiento << ")\n";
    mostrarJerarquia(nodo->izquierda, nivel + 1);
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

// Programa principal
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
        cout << "8. Mostrar Ancestros\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\nNombre: "; cin >> nombre;
                cout << "Año de nacimiento: "; cin >> nac;
                cout << "Año de fallecimiento: "; cin >> fall;
                raiz = insertar(raiz, nombre, nac, fall);
                break;
            case 2:
                cout << "\nNombre a eliminar: "; cin >> nombre;
                raiz = eliminar(raiz, nombre);
                break;
            case 3:
                cout << "\nNombre a buscar: "; cin >> nombre;
                if (buscar(raiz, nombre))
                    cout << nombre << " fue encontrado ^^\n";
                else
                    cout << nombre << " no se encuentra en el árbol TnT\n";
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
                cout << "\nNombre para ver ancestros: "; cin >> nombre;
                cout << "Ancestros: ";
                if (!mostrarAncestros(raiz, nombre))
                    cout << "No se encontraron ancestros o el miembro no existe TnT\n";
                else
                    cout << nombre << endl;
                break;
            case 9:
                cout << "Saliendo del programa ^^\n";
                break;
            default:
                cout << "Opción inválida O.O\n";
        }
    } while (opcion != 0);

    return 0;
}

