#include <iostream>
//#define N 5
#define N 6
using namespace std;

int buscar_nodo(string *vector, string buscar, int n){

    for (int i = 0; i < n; i++) {
        if (vector[i] == buscar) {
            return i; // Retorna el índice del elemento encontrado
        }
    }
    return -1; // Retorna -1 si no se encuentra el elemento
}

bool exsite_algun_false(bool *arreglo, int size) {
    for (int i = 0; i < size; i++) {
        if (!arreglo[i]) {
            return true; // Si hay algún elemento que es false, retorna true -> indica que hay un nodo que no es parte del arbol
        }
    }
    return false; // Si todos son true, retorna false
}

int main() {
    cout << "Hola, mundo!" << endl;
    int n = N;

    //matriz adyacencia
    int mi_matriz_ejemplo[N][N] = 
    {{0,6,1,5,-1,-1},
    {6,0,5,-1,3,-1},
    {-1,5,0,5,6,4},
    {5,-1,5,0,-1,2},
    {-1,3,6,-1,0,6},
    {-1,-1,4,2,6,0}};

    //int mi_matriz_ejemplo[N][N] = {{0,1,3,-1,-1},{1,0,3,6,-1},{3,3,0,4,2},{-1,6,4,0,5},{-1,-1,2,5,0}};

    /*int mi_matriz_ejemplo[N][N] = 
    {{0, 2, -1, 1, 4, -1},
    {2, 0, 3, 2, -1, -1},
    {-1, 3, 0, -1, 5, 6},
    {1, 2, -1, 0, 3, -1},
    {4, -1, 5, 3, 0, 2},
    {-1, -1, 6, -1, 2, 0}};

    int mi_matriz_ejemplo[N][N] = 
    {{0, 3, 1, -1, -1, 7},
    {3, 0, 4, 2, -1, 6},
    {1, 4, 0, 5, 8, -1},
    {-1, 2, 5, 0, 3, 4},
    {-1, -1, 8, 3, 0, 5},
    {7, 6, -1, 4, 5, 0}};

    int mi_matriz_ejemplo[N][N] = 
    {{0, -1, 4, 1, -1, 6},
    {-1, 0, 2, 3, 5, -1},
    {4, 2, 0, -1, 7, 3},
    {1, 3, -1, 0, 6, 2},
    {-1, 5, 7, 6, 0, 1},
    {6, -1, 3, 2, 1, 0}};

    int mi_matriz_ejemplo[N][N] = 
    {{0, 3, -1, 4, -1, 5},
    {3, 0, 7, -1, 2, -1},
    {-1, 7, 0, 6, -1, 4},
    {4, -1, 6, 0, 8, 3},
    {-1, 2, -1, 8, 0, 5},
    {5, -1, 4, 3, 5, 0}};
    */

    //para trakear nodos
    string vector_caracteres[N] = {"a", "b", "c", "d", "e", "f"};
    //para saber si estan presentes ya en el arbol minimos
    bool banderas[N] = {false, false, false, false, false, false};

    //valores minimios de las conexiones y a quien pertenecen las conexiones
    int valores_minimos[N];
    int padres_valores_minimos[N];

    //inicializar vectores
    for (int i = 0; i < n; i++) {
        valores_minimos[i] = INT_MAX; // Inicializa a infinito
        padres_valores_minimos[i] = -1; // Inicializa padres
    }

    //relaciones "(x,y)" para el arbol
    string arbol_minimo[N];

    //vamos a empezar con el nodo a
    string buscar = "a";
    int posicion_nodo = buscar_nodo(vector_caracteres, buscar, n);
    //cout << posicion_nodo;
    banderas[posicion_nodo] = true;
    //el nodo raiz será vector_caracter[posicion_nodo]
    //                         banderas[posicion_nodo] = true
    valores_minimos[posicion_nodo] = 0; // El costo del nodo raíz es 0

 
    //comparar valores minimos con conexiones al arbol
    while (exsite_algun_false(banderas, n)) {
        int minimo = INT_MAX;
        int indice_minimo;
        int nodo_origen;

        for (int i = 0; i < n; i++) {

            //int minimo = INT_MAX;
            //int indice_minimo;
            if (banderas[i]) {//esta presente en el arbol
                //se revisan las conexiones que tiene el nodo que si esta conectado al arbol y se busca el menor y se guarda con su indice

                for (int j = 0; j < n; j++) {
                    // Seleccionar el nodo con el costo mínimo no visitado
                    //calcular pesos minimos y padres
                    //cout << mi_matriz_ejemplo[i][j] << " \n";
                    
                    //cout << "Nodo candidato " << vector_caracteres[i] << "--" << vector_caracteres[j] << "\n";
                    if (mi_matriz_ejemplo[i][j] > 0 && mi_matriz_ejemplo[i][j] <= minimo && !banderas[j]) {
                        minimo = mi_matriz_ejemplo[i][j];
                        nodo_origen = i;
                        indice_minimo = j;
                    }
                    //el nodo j tiene el peso minimo de x
                    //bandera[j] = true;
                    //valores_min[] = +x;
                    //padre[j] = i; 
                }


                //cout << "Nodo minimo " << vector_caracteres[indice_minimo] << "=" << minimo;

                //meter valor minimo e indice minimo al arreglo de presentes en el arbol
                //banderas[indice_minimo] = true;
                //string conexion = vector_caracteres[i] + "--" + vector_caracteres[indice_minimo];
                //cout << conexion;
            }
        }
        banderas[indice_minimo] = true;
        string conexion = vector_caracteres[nodo_origen] + "--" + vector_caracteres[indice_minimo];
        cout << "Conexion minima: " << conexion << " = " << minimo << endl;

        
        //out << "Conexion minima " << vector_caracteres[indice_minimo] << "--" << vector_caracteres[indice_minimo] << " = " << minimo;
    }

    return 0;
}