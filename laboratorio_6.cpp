/*
 * g++ ejemplo_matriz.cpp -o matriz
 */
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib> // para system
using namespace std;

// Inicializa utilizando código ASCII.
void leer_nodos(string *vector, int n) {
    int inicio = 65;
  
    for (int i = 0; i < n; i++) {
        vector[i] = inicio + i;
    }
}

// Función para validar que la entrada del usuario sea un entero
int obtenerNumeroValido(const string& mensaje) {
    string ingreso_usuario;
    bool valid = false;
    int numero = 0;

    while (!valid) {
        cout << mensaje;
        cin >> ingreso_usuario;

        if (ingreso_usuario == "x" || ingreso_usuario == "X") {
            return -1;
        }

        try {
            numero = stoi(ingreso_usuario);  // Intenta convertir la entrada a un entero
            valid = true;  // Si la conversión es exitosa, salimos del bucle
        }
        catch (const invalid_argument& e) {
            cout << "Entrada inválida, por favor ingresa un número entero válido.\n";
        }
        catch (const out_of_range& e) {
            cout << "Número fuera de rango, intenta de nuevo.\n";
        }
    }

    return numero;  // Devuelve el número entero validado
}

// inicializa un vector. recibe el vector como un puntero.
void inicializar_vector_caracter (string *vector, int n) {
    int col;
  
    // recorre el vector.
    for (col=0; col<n; col++) {
        vector[col] = ' ';
    }
}


// imprime un vector. recibe el vector como un puntero.//a,b,c,b???
void imprimir_vector_caracter(string *vector, int n) {
    cout << endl;
    for (int i=0; i<n; i++) {
        cout << "vector[" << i << "]: " << vector[i] << " ~ ";
    }
    cout << endl;
}

// inicializa matriz nxn. recibe puntero a la matriz.
void inicializar_matriz_enteros (int **matriz, int n) {
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            matriz[fila][col] = -1;
        }
    }
}

// imprime matriz.
void imprimir_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            cout << matriz[fila][col] << " ";
        }
        cout << endl;
    }
}

int **inicializar_matriz_1(int argc, char **argv, int n){
    
    // valida cantidad de parámetros mínimos.
    if (argc<2) {
        cout << "Uso: \n./matriz n" << endl;
        //return;
    }


    //
    string V[n];


    // inicializa e imprime vectores. - que vectores hay en la matriz
    inicializar_vector_caracter(V, n);

    // Lee nodos ~ agrega letras a los nodos de V
    leer_nodos(V, n);

    imprimir_vector_caracter(V, n);

    // crea matriz nxn de enteros.
    int **matriz;
    matriz = new int*[n];
    for(int i=0; i<n; i++)
        matriz[i] = new int[n];

    return matriz;
}

void generar_conexiones(int **matriz, int n, string *vector_v){
    //suponiendo que es 3x3, preguntar, el vector 
    //a que conexion tiene con b-c
    //b que conexion tiene con a-c
    //c que conexion tiene con a-b
    cout << "MENU Generar Conexiones\n-ingrese el peso de las conexiones si es que existen, de lo contrario ingrese x\n\n";
    for (int i = 0; i < n; i++) {
        //cout << "Iteración: " << i + 1 << "\n";
        int ingreso = 0;

        for (int j = 0; j < n; j++) {
            if (i == j) {
                int valor = 0;
                matriz[i][j] = valor;
            }
            //cout << "subiteracion " << i + 1 << "\n";
            if (i != j){

                cout << "ingrese el peso entre el nodo[" << vector_v[i] << "] ~ nodo[" << vector_v[j] << "] > ";
                ingreso = obtenerNumeroValido("");

                matriz[i][j] = ingreso;

                cout << "\n";
            }
        }
    }
}

void imprimir_grafo(int **matriz, string *vector, int n) {
    ofstream archivo("grafo.txt");

    if (archivo.is_open()) {
        archivo << "digraph G {\n";
        archivo << "graph [rankdir=LR]\n";
        archivo << "node [style=filled fillcolor=yellow];\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
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
        cerr << "No se pudo abrir el archivo.\n";
        return;
    }

    // Ejecutar comandos del sistema para generar la imagen y abrirla
    system("dot -Tpng -ografo.png grafo.txt");
    system("grafo.png &"); // En Windows usa 'start', en Linux usa 'xdg-open' o 'open' en Mac
}

// Copia contenido inicial a D[] desde la matriz M[][].
void inicializar_vector_D(int *vector_D, int **matriz, int n) {
    int col;
  
    for (col = 0; col < n; col++) {
        vector_D[col] = matriz[0][col];
    }
}

void imprimir_vector_entero(int *vector, int n) {
    int i;
  
    for (i = 0; i < n; i++) {
        // printf("D[%d]: %d ", i, vector[i]);
        cout << "D[" << i << "]: " << vector[i]; 
    }
    cout << "\n";
}

// agrega vértice a S[].
void agrega_vertice_a_S(string *vector_s, string vertice, int n) {
    int i;

    // Recorre buscando un espacio vacío.
    for (i = 0; i < n; i++) {
        if (vector_s[i] == " ") {
            vector_s[i] = vertice;
            return;
        }
    }  
}

// Busca la aparición de un carácter en un vector de caracteres.
int busca_caracter(string c, string *vector, int n) {
    int j;
  
    for (j = 0; j < n; j++) {
        if (c == vector[j]) {
            return true;
        }
    }
  
    return false;
}

// Actualiza VS[] cada vez que se agrega un elemento a S[].
void actualizar_VS(string *vector_v, string *vector_s, string *vector_vs, int n) {
    int j;
    int k = 0;
  
    inicializar_vector_caracter(vector_vs, n);
  
    for (j = 0; j < n; j++) {
        // Por cada carácter de V[], evalúa si está en S[],
        // si no está, lo agrega a VS[].
        if (busca_caracter(vector_v[j], vector_s, n) != true) {
            vector_vs[k] = vector_v[j];
            k++;
        }
    }
}

// Retorna el índice del carácter consultado.
int buscar_indice_caracter(string *vector_v, string caracter, int n) {
    int i;
  
    for (i = 0; i < n; i++) {
        if (vector_v[i] == caracter) {
            return i;
        }
    }
  
    return i; // Si no se encuentra, retorna N (o el valor de i).
}

// elige vértice con menor peso en VS[].
// busca su peso en D[].
string elegir_vertice(string *vector_vs, int *vector_D, string *vector_V, int n) {
    int i = 0;
    int menor = -1;
    int peso;
    string vertice;

    while (vector_vs[i] != " ") {
        peso = vector_D[buscar_indice_caracter(vector_V, vector_vs[i], n)];

        // Descarta valores infinitos (-1) y 0.
        if ((peso != -1) && (peso != 0)) {
            if (i == 0) {
                menor = peso;
                vertice = vector_vs[i];
            } else {
                if (peso < menor) {
                    menor = peso;
                    vertice = vector_vs[i];
                }
            }
        }

        i++;
    }

    // printf("\nvertice: %c\n\n", vertice);
    cout << "\nvertice: " << vertice << "\n\n";
    return vertice;
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

// 
void actualizar_pesos(int *D, string *VS, int **M, string *V, string v, int n) {
    int i = 0;
    int indice_w, indice_v;

    cout << "\n> Actualiza pesos en D[]\n";
  
    indice_v = buscar_indice_caracter(V, v, n);
    while (VS[i] != " ") {
        if (VS[i] != v) {
            indice_w = buscar_indice_caracter(V, VS[i], n);
            D[indice_w] = calcular_minimo(D[indice_w], D[indice_v], M[indice_v][indice_w]);
        }
        i++;
    }
}

// aplica el algoritmo.
void aplicar_dijkstra(string *vector_V, string *vector_S, string *vector_VS, int *vector_D, int **matriz, int n) {
    int i;
    string v;

    // Inicializar vector D[] según datos de la matriz M[][] 
    // Estado inicial.
    inicializar_vector_D(vector_D, matriz, n);

    cout << "--------- Estados iniciales ---------------------------------------\n";
    imprimir_matriz(matriz, n);
    cout << "\n";
    imprimir_vector_caracter(vector_S, n);
    imprimir_vector_caracter(vector_VS, n);
    imprimir_vector_entero(vector_D, n);
    cout << "------------------------------------------------------------------\n\n";

    // Agrega primer vértice.
    cout << "> Agrega primer valor V[0] a S[] y actualiza VS[]\n\n";
    agrega_vertice_a_S(vector_S, vector_V[0], n);
    imprimir_vector_caracter(vector_S, n);

    // Actualiza VS[]
    actualizar_VS(vector_V, vector_S, vector_VS, n);

    imprimir_vector_caracter(vector_VS, n);
    imprimir_vector_entero(vector_D, n);

    // Bucle principal para aplicar el algoritmo de Dijkstra
    for (i = 1; i < n; i++) {
        // Elige un vértice en v de VS[] tal que D[v] sea el mínimo
        cout << "\n> Elige vértice menor en VS[] según valores en D[]\n";
        cout << "> Lo agrega a S[] y actualiza VS[]\n";

        v = elegir_vertice(vector_VS, vector_D, vector_V, n);

        // Agrega el vértice a S[]
        agrega_vertice_a_S(vector_S, v, n);
        imprimir_vector_caracter(vector_S, n);

        // Actualiza VS[]
        actualizar_VS(vector_V, vector_S, vector_VS, n);
        imprimir_vector_caracter(vector_VS, n);

    
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Actualiza pesos
        actualizar_pesos(vector_D, vector_VS, matriz, vector_V, v, n);
        imprimir_vector_entero(vector_D, n);
    }
    
}

void mostrar_arreglo_D(int *D, int n) {
    // Bucle for basado en rango para imprimir cada elemento

    cout << "Arreglo D-> ";

    for (int i = 0; i < n; i++) 
    cout << "  " << D[i];
    
}

//
int main(int argc, char **argv) {
    // número de elementos.
    int n;

    // convierte string a entero.
    n = atoi(argv[1]);

    //vectores de caracteres necesarios para el algoritmo
    string V[n], S[n], VS[n];
    int D[n];

    // Inicializa los vectores de caracteres.
    inicializar_vector_caracter(V, n);
    inicializar_vector_caracter(S, n);
    inicializar_vector_caracter(VS, n);
  
    // Lee nodos ~ agrega letras a los nodos de V
    leer_nodos(V, n);

    int **matriz = inicializar_matriz_1(argc, argv, n);

    inicializar_matriz_enteros(matriz, n);
    imprimir_matriz(matriz, n);

    //generar conexiones de los nodos atraves de la matriz de prosimidad ~ donde se le piden al usuario los pesos entre nodos
    generar_conexiones(matriz, n, V);

    cout << "matriz actual";

    //imprimir vectores caracteres
    imprimir_vector_caracter(V, n);
    imprimir_matriz(matriz, n);

    //agregar algoritmo de distrak
    // Aplica el algoritmo de Dijkstra.
    //aplicar_dijkstra(V, S, VS, D, M);
    //como no esta definido el n, hay que ingresarlo aparte para que funciones X
    aplicar_dijkstra(V, S, VS, D, matriz, n);
    //(string *vector_V, string *vector_S, string *vector_VS, int *vector_D, int **matriz, int n)

    mostrar_arreglo_D(D, n);

    //imprimir grafo
    imprimir_grafo(matriz, V, n);

    return 0;
}