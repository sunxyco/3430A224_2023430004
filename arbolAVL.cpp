#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
using namespace std;

enum { IZQUIERDO, DERECHO };

struct Nodo {
    int dato;
    int FE;  // Factor de Equilibrio
    Nodo* derecho;
    Nodo* izquierdo;
    Nodo* padre;
};

typedef Nodo* pNodo;
typedef Nodo* Arbol;

// Función para validar que la entrada del usuario sea un entero
int obtenerNumeroValido(const string& mensaje) {
    string ingreso_usuario;
    bool valid = false;
    int numero = 0;

    while (!valid) {
        cout << mensaje;
        cin >> ingreso_usuario;

        try {
            numero = stoi(ingreso_usuario);  // Intenta convertir la entrada a un entero
            valid = true;  // Si la conversión es exitosa, salimos del bucle
        } catch (const invalid_argument& e) {
            cout << "Entrada inválida, por favor ingresa un número entero válido.\n";
        } catch (const out_of_range& e) {
            cout << "Número fuera de rango, intenta de nuevo.\n";
        }
    }

    return numero;  // Devuelve el número entero validado
}

/* Insertar en arbol ordenado: */
void Insertar(Arbol* raiz, int dat);
/* Borrar un elemento: */
void Borrar(Arbol* raiz, int dat);
/* Comprobar si es un nodo hoja: */
int EsHoja(pNodo r);
/* Contar numero de nodos: */
int NumeroNodos(Arbol raiz, int* c);
/* Calcular la altura de un arbol: */
int AlturaArbol(Arbol raiz, int* altura);
/* Calcular altura de un dato: */
int Altura(Arbol raiz, int dat);
/* Generar salida para Graphviz */
void PreOrden(Arbol, ofstream &fp);

// Funciones de equilibrado:
void Equilibrar(Arbol* raiz, pNodo nodo, int, int);
void RotaDerechaDerecha(Arbol* raiz, pNodo nodo);
void RotaIzquierdaIzquierda(Arbol* raiz, pNodo nodo);
void RotaDerechaIzquierda(Arbol* raiz, pNodo nodo);
void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo);

/* Funciones auxiliares: */
void Podar(Arbol* a);
void auxContador(Arbol a, int*);
void auxAltura(Arbol a, int, int*);

void MenuPrincipal();
void GenerarGrafo(Arbol);

void Borrar(Arbol* raiz, int dat) {
    pNodo nodo = *raiz;

    if (nodo == NULL) {
        cout << "La información no se encuentra en el árbol" << endl;
        return;
    }

    if (dat < nodo->dato) {
        Borrar(&nodo->izquierdo, dat);
        Equilibrar(raiz, nodo, IZQUIERDO, FALSE);
    } else if (dat > nodo->dato) {
        Borrar(&nodo->derecho, dat);
        Equilibrar(raiz, nodo, DERECHO, FALSE);
    } else {
        pNodo otro = nodo;

        if (otro->derecho == NULL) {
            if (otro->padre == NULL) {
                *raiz = otro->izquierdo;
            } else if (otro->padre->izquierdo == otro) {
                otro->padre->izquierdo = otro->izquierdo;
            } else {
                otro->padre->derecho = otro->izquierdo;
            }

            if (otro->izquierdo != NULL) {
                otro->izquierdo->padre = otro->padre;
            }
        } else if (otro->izquierdo == NULL) {
            if (otro->padre == NULL) {
                *raiz = otro->derecho;
            } else if (otro->padre->izquierdo == otro) {
                otro->padre->izquierdo = otro->derecho;
            } else {
                otro->padre->derecho = otro->derecho;
            }

            if (otro->derecho != NULL) {
                otro->derecho->padre = otro->padre;
            }
        } else {
            pNodo aux = otro->izquierdo;
            bool boolFlag = FALSE;

            while (aux->derecho != NULL) {
                aux = aux->derecho;
                boolFlag = TRUE;
            }

            otro->dato = aux->dato;

            if (aux->padre == otro) {
                otro->izquierdo = aux->izquierdo;
            } else {
                aux->padre->derecho = aux->izquierdo;
            }

            if (aux->izquierdo != NULL) {
                aux->izquierdo->padre = aux->padre;
            }

            otro = aux;
        }

        free(otro);
        Equilibrar(raiz, nodo, IZQUIERDO, TRUE);
    }
}

/* Funcion de busqueda: */
int Buscar(Arbol raiz, int dat) {
    if (raiz == nullptr) {
        cout << "\nNO SE ENCONTRO EL NUMERO" << endl;
        return FALSE;
    } else if (raiz->dato == dat) {
        cout << "\nSE ENCONTRO EL dat" << endl;
        return TRUE;
    } else if (dat < raiz->dato) {
        return Buscar(raiz->izquierdo, dat);
    } else {
        return Buscar(raiz->derecho, dat);
    }
}

int main() {
    Arbol ArbolInt = NULL;
    int opcion = 0;
    int valor;

    while (opcion != 6) {
        MenuPrincipal();
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: //ingreso numero
                cout << "Ingrese su numero: ";
                valor = obtenerNumeroValido("Ingrese el numero> ");
                Insertar(&ArbolInt, valor);
                break;
            case 2: //Busqueda numero
                valor = obtenerNumeroValido("Ingrese el numero buscar> ");
                Buscar(ArbolInt, valor);
                break;
            case 3: //Eliminar numero
                cout << "Eliminando numero\n";
                valor = obtenerNumeroValido("Ingrese nodo borrar> ");
                Borrar(&ArbolInt, valor);
                break;
            case 4: //modificar elemento (eliminar/ingresar)
                cout << "Modificando elemento\n";
                break;
            case 5:
                GenerarGrafo(ArbolInt);
                break;
        }
    }

    /* Liberar memoria asociada al arbol. */
    Podar(&ArbolInt);
    return 0;
}

void GenerarGrafo(Arbol ArbolInt) {
    ofstream fp("grafo.txt");

    fp << "digraph G {\n";
    fp << "node [style=filled fillcolor=pink];\n";

    if (ArbolInt) {
        fp << "nullraiz [shape=point];\n";
        fp << "nullraiz->" << ArbolInt->dato << " [label=" << ArbolInt->FE << "];\n";
        PreOrden(ArbolInt, fp);
    } else {
        cout << "El árbol está vacío. No se puede generar el gráfico.\n";
    }

    fp << "}\n";
    fp.close();

    system("dot -Tpng -ografo.png grafo.txt");
    system("start grafo.png &");
}

void PreOrden(Arbol a, ofstream &fp) {
    static int nullCount = 0;  // Para numerar los nodos nulos

    if (a) {
        // Escribir el nodo actual
        fp << a->dato << " [style=filled fillcolor=pink];\n";

        // Si el hijo izquierdo existe, agregar la arista
        if (a->izquierdo) {
            fp << a->dato << "->" << a->izquierdo->dato << " [label=" << a->izquierdo->FE << "];\n";
            PreOrden(a->izquierdo, fp);
        } else {
            // Si no existe, agregar un nodo nulo
            fp << "null" << nullCount << " [shape=point];\n";
            fp << a->dato << "->null" << nullCount << ";\n";
            nullCount++;
        }

        // Si el hijo derecho existe, agregar la arista
        if (a->derecho) {
            fp << a->dato << "->" << a->derecho->dato << " [label=" << a->derecho->FE << "];\n";
            PreOrden(a->derecho, fp);
        } else {
            // Si no existe, agregar un nodo nulo
            fp << "null" << nullCount << " [shape=point];\n";
            fp << a->dato << "->null" << nullCount << ";\n";
            nullCount++;
        }
    }
}

void MenuPrincipal() {
    cout << "\n";
    cout << "<1> Ingresar numero\n";
    cout << "<2> Busqueda numero\n";
    cout << "<3> Eliminar numero\n";
    cout << "<4> Modificar elemento ingresado\n";
    cout << "<5> Generar Grafo\n";
    cout << "<6> Salir\n";
    cout << "\n";
}

void Podar(Arbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        free(*a);
        *a = NULL;
    }
}


/**/

void Insertar(Arbol* a, int dat) {
    pNodo padre = NULL;
    pNodo actual = *a;

    while (actual != NULL && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }

    //se imprime si ya se encuentra el nodo en el arbol
    if (actual != NULL){
        cout << "El nodo ya se encuentra en el árbol: " << dat << "\n";
        return;
    }

    if (padre == NULL) {
        *a = new Nodo{dat, 0, NULL, NULL, NULL};
    } else if (dat < padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->izquierdo = actual;
        Equilibrar(a, padre, IZQUIERDO, TRUE);
    } else if (dat > padre->dato) {
        actual = new Nodo{dat, 0, NULL, NULL, padre};
        padre->derecho = actual;
        Equilibrar(a, padre, DERECHO, TRUE);
    }
}

void Equilibrar(Arbol* a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo){
            if (rama == IZQUIERDO){
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        }
        else{
            if (rama == IZQUIERDO){
                nodo->FE += 1;
            } 
            else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0)
            salir = TRUE;
        else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == 1)
                RotaIzquierdaDerecha(a, nodo);
            else
                RotaIzquierdaIzquierda(a, nodo);
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == -1)
                RotaDerechaIzquierda(a, nodo);
            else
                RotaDerechaDerecha(a, nodo);
            salir = TRUE;
        }

        if (nodo->padre) {
            if (nodo->padre->derecho == nodo) {
                rama = DERECHO;
            } else {
                rama = IZQUIERDO;
            }
        }
        nodo = nodo->padre;
    }
}

void RotaIzquierdaDerecha(Arbol* raiz, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo R = Q->derecho;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        }
        else {
            Padre->izquierdo = R;
        }
    }
    else
        *raiz = R;

    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    switch (R->FE) {
        case -1: Q->FE = 0; P->FE = 1; break;
        case 0: Q->FE = 0; P->FE = 0; break;
        case 1: Q->FE = -1; P->FE = 0; break;
    }

    R->FE = 0;
    Q->FE = 0;
    P->FE = 0;
}

void RotaDerechaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo R = Q->izquierdo;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    }
    else
        *a = R;

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;    
    if (C) C->padre = Q;

    switch (R->FE) {
        case -1: P->FE = 0; Q->FE = 1; break;
        case 0: P->FE = 0; Q->FE = 0; break;
        case 1: P->FE = -1; Q->FE = 0; break;
    }

    R->FE = 0;
    Q->FE = 0;
    P->FE = 0;
}

void RotaIzquierdaIzquierda(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo B = Q->derecho;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->izquierdo = B;
    Q->derecho = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void RotaDerechaDerecha(Arbol* a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo B = Q->izquierdo;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        *a = Q;

    P->derecho = B;
    Q->izquierdo = P;

    P->padre = Q;
    
    if (B){
        B->padre = P;
    } 
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}