#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib> // para system
using namespace std;

//declaracion de funcion porque tiraba error
int obtenerNumeroValido(const string& mensaje);

class Grafo {
    private:
        //el atributo limite se usa en los ciclos, toma el numero que ingresa el usuario al compilar 
        int limite;
        int **matriz_adj;

    public:
        //constructor
        Grafo(int n){

            limite = n;
            //matriz adyacencia

            //Declaracion de la matriz ~ se reserva la memoria y se inizializa vacia
            matriz_adj = new int*[n];
            for (int i = 0; i < n; i++) {
                matriz_adj[i] = new int[n];
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    //se inicializan en -2 para hacer la correcta comparacion en generarconexiones(), donde si
                    //el usuario ingresa que no hay conexion directa se coloca un -1
                    matriz_adj[i][j] = -2;
                }
            }
        }


        //Metodos

        //imprime muestra una foto de todo el grafo
        void imprimir_grafo(string *vector) {
            ofstream archivo("grafo.txt");

            if (archivo.is_open()) {
                archivo << "graph G {\n";
                archivo << "graph [rankdir=LR]\n";
                archivo << "node [style=filled fillcolor=\"#00ff005f\"];\n";

                for (int i = 0; i < limite; i++) {
                    for (int j = i + 1; j < limite; j++) {
                        if (matriz_adj[i][j] > 0) {
                            archivo << vector[i] << " -- " << vector[j] << " [label=" << matriz_adj[i][j] << "];\n";
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

        //busca el indice del nodo el cual se quiere usae como raiz
        int buscar_nodo(string *vector, string buscar) {
            for (int i = 0; i < limite; i++) {
                if (vector[i] == buscar) {
                    return i;
                }
            }
            return -1;
        }

        //busca en el arreglo si existe algun false
        bool existe_algun_false(bool *arreglo, int size) {
            for (int i = 0; i < size; i++) {
                if (!arreglo[i]) {
                    return true; //si existe false
                }
            }
            return false; //si no existe false
        }

        //genera una foto de el arbol de pesos minimos
        void generar_arbol(string *conexiones) {
            ofstream archivo("arbol01.txt");

            if (archivo.is_open()) {
                archivo << "graph G {\n";
                archivo << "graph [rankdir=LR]\n";
                archivo << "node [style=filled fillcolor=\"#00ff005f\"];\n";

                for (int i = 1; i < limite; i++) {
                    archivo << "\n" << conexiones[i];
                }

                archivo << "}\n";
                archivo.close();
            } else {
                cerr << "No se pudo abrir el archivo.\n";
                return;
            }

            system("dot -Tpng -oarbol01.png arbol01.txt");
            system("arbol01.png &");
        }

        //el array banderas contiene segun el indice si el nodo esta presente en el arbol de peso minimo
        void inicializar_banderas(bool *banderas) {
            for (int i = 0; i < limite; i++) {
                banderas[i] = false;
            }
        }

        //el usuario ingresa los pesos de las conexiones entre nodos
        void generar_conexiones(string *vector_caracteres) {
            cout << "MENU Generar Conexiones\n-ingrese el peso de las conexiones si es que existen, de lo contrario ingrese x\n\n";
            for (int i = 0; i < limite; i++) {
                int ingreso = 0;

                for (int j = 0; j < limite; j++) {
                    if (i == j) {
                        matriz_adj[i][j] = 0;
                    }
                    if (i != j && matriz_adj[i][j] == -2) {
                        cout << "Ingrese el peso entre el nodo[" << vector_caracteres[i] << "] ~ nodo[" << vector_caracteres[j] << "] > ";
                        ingreso = obtenerNumeroValido("");
                        matriz_adj[i][j] = ingreso;
                        matriz_adj[j][i] = ingreso;
                    }
                }
            }
        }

        //imprime la matriz de adyacencia que ingreso el usuario
        void imprimir_matriz(string *vector_caracteres) {
            cout << "\nMatriz de adyacencia\n\n";
            cout << "   ";
            for (int i = 0; i < limite; i++) {
                cout << vector_caracteres[i] << "  ";
            }
            cout << endl;
            for (int fila = 0; fila < limite; fila++) {
                cout << vector_caracteres[fila] << "  ";
                for (int col = 0; col < limite; col++) {
                    cout << matriz_adj[fila][col] << ", ";
                }
                cout << endl;
            }
            cout << "\n\n";
        }

        void algoritmo_prim(bool *banderas, string *vector_caracteres, int n) {
            int contador_arbol = 0;
            string conexiones[n];
            //relaciones "(x,y)" para el arbol
            string arbol_minimo[n];


            //comparar valores minimos con conexiones al arbol
            while (existe_algun_false(banderas, n)) {
                int minimo = INT_MAX;
                int indice_minimo;
                int nodo_origen;

                for (int i = 0; i < n; i++) {

                    if (banderas[i]) {//esta presente en el arbol
                        //se revisan las conexiones que tiene el nodo que si esta conectado al arbol y se busca el menor y se guarda con su indice

                        for (int j = 0; j < n; j++) {

                            if (matriz_adj[i][j] > 0 && matriz_adj[i][j] <= minimo && !banderas[j]) {
                                minimo = matriz_adj[i][j];
                                nodo_origen = i;
                                indice_minimo = j;
                            } 
                        }
                    }
                }


                banderas[indice_minimo] = true;
                string conexion = vector_caracteres[nodo_origen] + " -- " + vector_caracteres[indice_minimo];
                
                conexiones[contador_arbol] = "(" + vector_caracteres[nodo_origen] + "-" + vector_caracteres[indice_minimo] + ")";

                arbol_minimo[contador_arbol] = conexion + " [label=" + to_string(minimo) + "];";

                contador_arbol++;
            }

            //muestra foto de el arbol minimo
            generar_arbol(arbol_minimo);
            cout << "Foto del arbol minimo generada\n";

            cout << "Impresion arreglo conexiones\n";
            for(int i = 0; i < n; i++) {
                cout << "\n" << arbol_minimo[i];
            }

            cout << "\n\nContenido Arreglo L = {";
            for (int i = 0; i < n-1; i++) {
                cout << conexiones[i];
                
                if (i != n-2) {
                    cout << ", ";
                } else {
                    cout << "}\n\n";
                }
            }
        }
};

//se inicializa segun el parametro que haya ingresado el usuario, se usan para darle letras a los nodos
void inicializar_vector_caracter(string *vector_caracteres, int n) {
    char letters[n]; // Declaracion del arreglo de caracteres

    // Llenar el arreglo con letras de 'A' a 'F'
    for (int i = 0; i < n; ++i) {
        letters[i] = 97 + i; // Asignar valores ASCII de 'a' a 'f'
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

int main(int argc, char **argv) {
    int n = atoi(argv[1]);

    //grafo a partir de una matriz n x n
    Grafo mi_grafo(n);

    //para trakear nodos - a,b,c,d,e,f,g....
    string vector_caracteres[n];
    inicializar_vector_caracter(vector_caracteres, n);

    //arreglo de booleanos que van a la par con el indice de los nodos, 
    //nodo A presente en el arbol = nodo "vector_caracter[i]" "banderas[i] = (true)"
    bool banderas[n];
    mi_grafo.inicializar_banderas(banderas);

    mi_grafo.generar_conexiones(vector_caracteres);
    mi_grafo.imprimir_matriz(vector_caracteres);
    mi_grafo.imprimir_grafo(vector_caracteres);
    cout << "Foto del grafo generada.\n";
    mi_grafo.algoritmo_prim(banderas, vector_caracteres, n);
    cout << "Algoritmo de prim generado\n";

    return 0;
}