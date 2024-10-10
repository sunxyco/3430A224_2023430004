#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstdlib> // para system
using namespace std;

#define TRUE 0
#define FALSE 1
#define N 5

void leer_nodos (char vector[N]);
void inicializar_vector_D (int D[N], int M[N][N]);
void inicializar_vector_caracter (char vector[N]);
void aplicar_dijkstra (char V[N], char S[N], char VS[N], int D[N], int M[N][N]);
void actualizar_VS(char V[N], char S[N], char VS[N]);
int buscar_indice_caracter(char V[N], char caracter);
void agrega_vertice_a_S(char S[N], char vertice);
int elegir_vertice(char VS[N], int D[N], char V[N]);
void actualizar_pesos (int D[N], char VS[N], int M[N][N], char V[N], char v);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_caracter(char vector[N], char *);
void imprimir_vector_entero(int vector[N]);
void imprimir_matriz(int matriz[N][N]);
void mostrar_arreglo_D(int D[N]);
void imprimir_grafo(int matriz[N][N], char vector[N]);

int main(int argc, char **argv) {
    char V[N], S[N], VS[N];
    int D[N];

    // Valores de prueba 1.
    /*int M[N][N] = {
        { 0,  4, 11, -1, -1},
        {-1,  0, -1,  6,  2},
        {-1,  3,  0,  6, -1},
        {-1, -1, -1,  0, -1},
        {-1, -1,  5,  3,  0}
    };*/
  
    // Valores de prueba 2.
    int M[N][N] = {
        { 0, 2,  1, -1,  3},
        {-1, 0, -1,  4, -1},
        {-1, 1,  0, -1,  1},
        { 1,-1,  3,  0,  5},
        {-1,-1, -1, -1, 0}
    };

    // Inicializa los vectores de caracteres.
    inicializar_vector_caracter(V);
    inicializar_vector_caracter(S);
    inicializar_vector_caracter(VS);
  
    // Lee nodos.
    leer_nodos(V);
  
    // Aplica el algoritmo de Dijkstra.
    aplicar_dijkstra(V, S, VS, D, M);

    // Imprimir el grafo (opcional).
    imprimir_grafo(M, V);

    mostrar_arreglo_D(D);

    return 0;
}

void mostrar_arreglo_D(int D[N]) {
    // Bucle for basado en rango para imprimir cada elemento

    cout << "Arreglo D-> ";

    for (int i = 0; i < N; i++) 
    cout << "  " << D[i];
    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Copia contenido inicial a D[] desde la matriz M[][].
void inicializar_vector_D(int D[N], int M[N][N]) {
    int col;
  
    for (col = 0; col < N; col++) {
        D[col] = M[0][col];
    }
}

// Inicializa con espacios el arreglo de caracteres.
void inicializar_vector_caracter(char vector[N]) {
    int col;
  
    for (col = 0; col < N; col++) {
        vector[col] = ' ';
    }
}

// aplica el algoritmo.
void aplicar_dijkstra(char V[N], char S[N], char VS[N], int D[N], int M[N][N]) {
    int i;
    int v;

    // Inicializar vector D[] según datos de la matriz M[][] 
    // Estado inicial.
    inicializar_vector_D(D, M);

    cout << "--------- Estados iniciales ---------------------------------------\n";
    imprimir_matriz(M);
    cout << "\n";
    imprimir_vector_caracter(S, "S");
    imprimir_vector_caracter(VS, "VS");
    imprimir_vector_entero(D);
    cout << "------------------------------------------------------------------\n\n";

    // Agrega primer vértice.
    cout << "> Agrega primer valor V[0] a S[] y actualiza VS[]\n\n";
    agrega_vertice_a_S(S, V[0]);
    imprimir_vector_caracter(S, "S");

    // Actualiza VS[]
    actualizar_VS(V, S, VS);
    imprimir_vector_caracter(VS, "VS");
    imprimir_vector_entero(D);

    // Bucle principal para aplicar el algoritmo de Dijkstra
    for (i = 1; i < N; i++) {
        // Elige un vértice en v de VS[] tal que D[v] sea el mínimo
        cout << "\n> Elige vértice menor en VS[] según valores en D[]\n";
        cout << "> Lo agrega a S[] y actualiza VS[]\n";
        v = elegir_vertice(VS, D, V);

        // Agrega el vértice a S[]
        agrega_vertice_a_S(S, v);
        imprimir_vector_caracter(S, "S");

        // Actualiza VS[]
        actualizar_VS(V, S, VS);
        imprimir_vector_caracter(VS, "VS");

        // Actualiza pesos
        actualizar_pesos(D, VS, M, V, v);
        imprimir_vector_entero(D);
    }
}

// 
void actualizar_pesos(int D[N], char VS[N], int M[N][N], char V[N], char v) {
    int i = 0;
    int indice_w, indice_v;

    cout << "\n> Actualiza pesos en D[]\n";
  
    indice_v = buscar_indice_caracter(V, v);
    while (VS[i] != ' ') {
        if (VS[i] != v) {
            indice_w = buscar_indice_caracter(V, VS[i]);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
        i++;
    }
}

//
int calcular_minimo(int dw, int dv, int mvw) {

    int min = 0;

    // Comprobación de condiciones
    if (dw == -1) {
        if (dv != -1 && mvw != -1) {
            min = dv + mvw;
        } else {
            min = -1;
        }
    } else {
        if (dv != -1 && mvw != -1) {
            if (dw <= (dv + mvw)) {
                min = dw;
            } else {
                min = (dv + mvw);
            }
        } else {
            min = dw;
        }
    }

    //printf("dw: %d dv: %d mvw: %d min: %d\n", dw, dv, mvw, min);
    cout << "dw: " << dw << " dv: " << " mvw: " << mvw << "min: " << min << " \n";

    return min; 
}

// agrega vértice a S[].
void agrega_vertice_a_S(char S[N], char vertice) {
    int i;

    // Recorre buscando un espacio vacío.
    for (i = 0; i < N; i++) {
        if (S[i] == ' ') {
            S[i] = vertice;
            return;
        }
    }  
}

// elige vértice con menor peso en VS[].
// busca su peso en D[].
int elegir_vertice(char VS[N], int D[N], char V[N]) {
    int i = 0;
    int menor = -1;
    int peso;
    char vertice;

    while (VS[i] != ' ') {
        peso = D[buscar_indice_caracter(V, VS[i])];

        // Descarta valores infinitos (-1) y 0.
        if ((peso != -1) && (peso != 0)) {
            if (i == 0) {
                menor = peso;
                vertice = VS[i];
            } else {
                if (peso < menor) {
                    menor = peso;
                    vertice = VS[i];
                }
            }
        }

        i++;
    }

    // printf("\nvertice: %c\n\n", vertice);
    cout << "\nvertice: " << vertice << "\n\n";
    return vertice;
}

// Retorna el índice del carácter consultado.
int buscar_indice_caracter(char V[N], char caracter) {
    int i;
  
    for (i = 0; i < N; i++) {
        if (V[i] == caracter) {
            return i;
        }
    }
  
    return i; // Si no se encuentra, retorna N (o el valor de i).
}

// Busca la aparición de un carácter en un vector de caracteres.
int busca_caracter(char c, char vector[N]) {
    int j;
  
    for (j = 0; j < N; j++) {
        if (c == vector[j]) {
            return TRUE;
        }
    }
  
    return FALSE;
}

// Actualiza VS[] cada vez que se agrega un elemento a S[].
void actualizar_VS(char V[N], char S[N], char VS[N]) {
    int j;
    int k = 0;
  
    inicializar_vector_caracter(VS);
  
    for (j = 0; j < N; j++) {
        // Por cada carácter de V[], evalúa si está en S[],
        // si no está, lo agrega a VS[].
        if (busca_caracter(V[j], S) != TRUE) {
            VS[k] = V[j];
            k++;
        }
    }
}

// Lee datos de los nodos - asigna las letras al arreglo.
// Inicializa utilizando código ASCII.
void leer_nodos(char vector[N]) {
    int i;
    int inicio = 97;
  
    for (i = 0; i < N; i++) {
        vector[i] = inicio + i;
    }
}

// Imprime el contenido de un vector de caracteres.
void imprimir_vector_caracter(char vector[N], char *nomVector) {
    int i;
  
    for (i = 0; i < N; i++) {
        //printf("%s[%d]: %c ", nomVector, i, vector[i]);
        cout << nomVector << "[" << i << "]: " << vector[i];
    }
    cout << "\n";
}

//
void imprimir_vector_entero(int vector[N]) {
    int i;
  
    for (i = 0; i < N; i++) {
        // printf("D[%d]: %d ", i, vector[i]);
        cout << "D[" << i << "]: " << vector[i]; 
    }
    cout << "\n";
}

// imprime el contenido de una matriz bidimensional de enteros.
void imprimir_matriz(int matriz[N][N]) {
    int i, j;
  
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            // printf("matriz[%d,%d]: %d ", i, j, matriz[i][j]);
            cout << "matriz[" << i << "," << j << "]: " << matriz[i][j];
        }
        cout << "\n";
    }
}//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+

// genera y muestra apartir de una matriz bidimensional de enteros
// el grafo correspondiente.


void imprimir_grafo(int matriz[N][N], char vector[N]) {
    ofstream archivo("grafo.txt");

    if (archivo.is_open()) {
        archivo << "digraph G {\n";
        archivo << "graph [rankdir=LR]\n";
        archivo << "node [style=filled fillcolor=yellow];\n";

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Evalúa la diagonal principal.
                if (i != j && matriz[i][j] > 0) {
                    archivo << vector[i] << "->" << vector[j] 
                            << " [label=" << matriz[i][j] << "];\n";
                }
            }
        }

        archivo << "}\n";
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo.\n";
        return;
    }

    // Ejecutar comandos del sistema para generar la imagen y abrirla
    system("dot -Tpng -ografo.png grafo.txt");
    system("grafo.png &"); // En Windows usa 'start', en Linux usa 'xdg-open' o 'open' en Mac
}
