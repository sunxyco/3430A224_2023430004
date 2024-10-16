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

void generar_conexiones(int **matriz, string *vector_caracteres, int n) {
    //necesito generar las conexiones para generar la matriz de adyacencia, *procurar que es matriz simetrica

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
            //se ven los espacios originales de la matriz inicializada donde no hay conexiones
            if (i != j && matriz[i][j] == -2){

                cout << "ingrese el peso entre el nodo[" << vector_caracteres[i] << "] ~ nodo[" << vector_caracteres[j] << "] > ";
                ingreso = obtenerNumeroValido("");

                //se generan las conexiones entre los dos nodos
                matriz[i][j] = ingreso;
                matriz[j][i] = ingreso;

                cout << "\n";
            }
        }
    }

}

void imprimir_matriz(int **matriz, int n) {
    cout << endl;
    for (int fila=0; fila<n; fila++) {
        for (int col=0; col<n; col++) {
            cout << matriz[fila][col] << ", ";
        }
        cout << endl;
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

    /*
    //hacer que el usuario ingrese las conexiones de la matriz
    int valores[6][6] = 
    {{0, 3, 1, -1, -1, 7},
    {3, 0, 4, 2, -1, 6},
    {1, 4, 0, 5, 8, -1},
    {-1, 2, 5, 0, 3, 4},
    {-1, -1, 8, 3, 0, 5},
    {7, 6, -1, 4, 5, 0}};
    */

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //se inicializan en -2 para hacer la correcta comparacion en generarconexiones(), donde si el usuario ingresa que no hay conexion directa se chanta un -1
            mi_matriz_ejemplo[i][j] = -2;
        }
    }


    //para trakear nodos - a,b,c,d,e,f,g....
    string vector_caracteres[n];
    inicializar_vector_caracter(vector_caracteres, n);
    //para saber si estan presentes ya en el arbol minimos -> si estan presentes es true, tienen el mismo indice que las letras
    bool banderas[n];
    inicializar_banderas(banderas, n);


    //para que el usuario genere las conexiones entre los nodos
    generar_conexiones(mi_matriz_ejemplo, vector_caracteres, n);


    imprimir_matriz(mi_matriz_ejemplo, n);

    //relaciones "(x,y)" para el arbol
    string arbol_minimo[n];
    int contador_arbol = 0;

    //vamos a empezar con el nodo a ~ hacer que el usuario elija el iniciañ
    string buscar = "a";
    int posicion_nodo = buscar_nodo(vector_caracteres, buscar, n);
    banderas[posicion_nodo] = true;

    imprimir_grafo(mi_matriz_ejemplo, vector_caracteres, n);

    string conexiones[n];

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
        
        conexiones[contador_arbol] = "(" + vector_caracteres[nodo_origen] + "-" + vector_caracteres[indice_minimo] + ")";

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

    cout << "\nContenido Arreglo L = {";
    for (int i = 0; i < n-1; i++) {
        cout << conexiones[i];
        
        if (i != n-2) {
            cout << ", ";
        } else {
            cout << "}";
        }
    }



    generar_arbol(arbol_minimo, n);

    return 0;
}