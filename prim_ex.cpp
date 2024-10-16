#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib> // para system
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

void imprimir_grafo(int **matriz, string *vector, int n) {
    ofstream archivo("grafo.txt");

    if (archivo.is_open()) {
        archivo << "graph G {\n";
        archivo << "graph [rankdir=LR]\n";
        archivo << "node [style=filled fillcolor=\"#00ff005f\"];\n";

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) { // Recorre solo la mitad superior de la matriz - porque sino se generan las conexiones dos veces
                if (matriz[i][j] > 0) {
                    archivo << vector[i] << " -- " << vector[j] << " [label=" << matriz[i][j] << "];\n";
                }
            }
        }

        archivo << "}\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo.\n";
        return;
    }

    // Ejecutar comandos del sistema para generar la imagen y abrirla
    system("dot -Tpng -ografo.png grafo.txt");
    system("grafo.png &"); // En Windows usa 'start', en Linux usa 'xdg-open' o 'open' en Mac
}

void generar_arbol(string *conexiones, int n) {
    ofstream archivo("arbol01.txt");

    if (archivo.is_open()) {
        archivo << "graph G {\n";
        archivo << "graph [rankdir=LR]\n";
        archivo << "node [style=filled fillcolor=\"#00ff005f\"];\n";
        
        //escribe conexiones a-b .......
        
        //cout << "Impresion arreglo conexiones";
        for(int i = 0; i < n; i++) {
            archivo << "\n" << conexiones[i];
        }
        
        archivo << "}\n";
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo.\n";
        return;
    }

    // Ejecutar comandos del sistema para generar la imagen y abrirla
    system("dot -Tpng -oarbol01.png arbol01.txt");
    system("arbol01.png &"); // En Windows usa 'start', en Linux usa 'xdg-open' o 'open' en Mac
}

void inicializar_banderas(bool *banderas, int n) {
    for (int i = 0; i < n; i++) {
        banderas[i] = false;
    }
}

void inicializar_vector_caracter(string *vector_caracteres, int n) {
    char letters[n]; // Declaracion del arreglo de caracteres

    // Llenar el arreglo con letras de 'A' a 'F'
    for (int i = 0; i < n; ++i) {
        //letters[i] = 'A' + i; // Asignar valores ASCII de 'A' a 'F'
        letters[i] = 97 + i; // Asignar valores ASCII de 'a' a 'f'
        //letters[i] = 65 + i; // Asignar valores ASCII de 'A' a 'F' 
        vector_caracteres[i] = string(1, letters[i]);
    }
}

int main() {
    cout << "Hola, mundo!" << endl;
    int n = N;

    //matriz adyacencia
    // Declaración de la matriz dinamica 
    int **mi_matriz_ejemplo = new int*[n]; // Reservar memoria para las filas
    for (int i = 0; i < n; i++) {
        mi_matriz_ejemplo[i] = new int[n]; // Reservar memoria para las columnas en cada fila
    }

    //hacer que el usuario ingrese las conexiones de la matriz
    int valores[6][6] = 
    {{0, 3, 1, -1, -1, 7},
    {3, 0, 4, 2, -1, 6},
    {1, 4, 0, 5, 8, -1},
    {-1, 2, 5, 0, 3, 4},
    {-1, -1, 8, 3, 0, 5},
    {7, 6, -1, 4, 5, 0}};

    // Copiar los valores de la matriz estática a la matriz dinámica
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mi_matriz_ejemplo[i][j] = valores[i][j];
        }
    }

    //para trakear nodos - a,b,c,d,e,f,g....
    string vector_caracteres[n];
    inicializar_vector_caracter(vector_caracteres, n);
    //para saber si estan presentes ya en el arbol minimos -> si estan presentes es true, tienen el mismo indice que las letras
    bool banderas[n];
    inicializar_banderas(banderas, n);

    //relaciones "(x,y)" para el arbol
    string arbol_minimo[n];
    int contador_arbol = 0;

    //vamos a empezar con el nodo a ~ hacer que el usuario elija el iniciañ
    string buscar = "a";
    int posicion_nodo = buscar_nodo(vector_caracteres, buscar, n);
    banderas[posicion_nodo] = true;

    imprimir_grafo(mi_matriz_ejemplo, vector_caracteres, n);

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
        string conexion = vector_caracteres[nodo_origen] + " -- " + vector_caracteres[indice_minimo];
        //escribir esto en el arbol
        cout << conexion << " [Label=" << minimo << "];" << endl;

        arbol_minimo[contador_arbol] = conexion + " [label=" + to_string(minimo) + "];";

        contador_arbol++;
        //out << "Conexion minima " << vector_caracteres[indice_minimo] << "--" << vector_caracteres[indice_minimo] << " = " << minimo;
    }

    cout << "Impresion arreglo conexiones";
    for(int i = 0; i < n; i++) {
        cout << "\n" << arbol_minimo[i];
    }

    generar_arbol(arbol_minimo, n);

    return 0;
}