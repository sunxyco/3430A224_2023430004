#include <iostream>
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

    //para trakear nodos
    string vector_caracteres[N] = {"a", "b", "c", "d", "e", "f"};
    //para saber si estan presentes ya en el arbol minimos
    bool banderas[N] = {false, false, false, false, false, false};

    //valores minimios de las conexiones y a quien pertenecen las conexiones
    int valores_minimos[N];
    int padres_valores_minimos[N];


    //relaciones "(x,y)" para el arbol
    string arbol_minimo[N];

    //vamos a empezar con el nodo a
    string buscar = "a";
    int posicion_nodo = buscar_nodo(vector_caracteres, buscar, n);
    //cout << posicion_nodo;

    banderas[posicion_nodo] = true;
    //el nodo raiz será vector_caracter[posicion_nodo]
    //                         banderas[posicion_nodo] = true

    //comparar valores minimos con conexiones al arbol
    for (int i = 0; i < n; i++) {
        if (banderas[i]) {//esta presente en el arbol
            for (int j = 0; j < n; j++) {
                //reocrre todas las conexiones que tiene el arbol
                //cout << mi_matriz_ejemplo[i][j] << ", ";
                //calcular pesos minimos y padres
                if (mi_matriz_ejemplo[i][j] > 0) {
                    cout << "nodos candidatos " << vector_caracteres[j] << " = " << mi_matriz_ejemplo[i][j] << "\n";
                }
            }
        }
    }


    return 0;
}