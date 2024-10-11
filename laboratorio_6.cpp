/*
 * g++ ejemplo_matriz.cpp -o matriz
 */
#include <stdlib.h>
#include <iostream>
using namespace std;

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
        cout << "vector[" << i << "]: " << vector[i] << " ";
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
    imprimir_vector_caracter(V, n);

    // crea matriz nxn de enteros.
    int **matriz;
    matriz = new int*[n];
    for(int i=0; i<n; i++)
        matriz[i] = new int[n];

    return matriz;
}

void generar_conexiones(int **matriz, int n){
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

                cout << "ingrese el peso entre el nodo" << i << " y nodo" << j << "> ";
                ingreso = obtenerNumeroValido("");

                matriz[i][j] = ingreso;

                cout << "\n";
            }
        }
    }
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
  
    // Lee nodos.
    //leer_nodos(V);


    int **matriz = inicializar_matriz_1(argc, argv, n);

    inicializar_matriz_enteros(matriz, n);
    imprimir_matriz(matriz, n);

    //generar conexiones de los nodos atraves de la matriz de prosimidad
    generar_conexiones(matriz, n);

    cout << "matriz actual";
    imprimir_matriz(matriz, n);

    return 0;
}