#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <set>
using namespace std;

struct Pila {
    int maximo;
    int tope;
    string* contenedores; // Usamos un puntero para manejar el array dinámicamente

    // Constructor para inicializar la pila
    Pila(int max) : maximo(max), tope(0) {
        contenedores = new string[maximo]; // Asignamos memoria para el array
    }

    // Método para agregar un elemento a la pila
    void push(string nombre_contenedor) {
        if (tope < maximo) {
            contenedores[tope] = nombre_contenedor; // Agrega el elemento y aumenta el tope
            tope = tope + 1;
        } else {
            cout << "Pila llena, imposible agregar elemento " << nombre_contenedor << "\n\n";
        }
    }

    // Método para eliminar el último elemento de la pila
    void pop() {
        if (tope == 0) { // Verificar si la pila está vacía
            cout << "No hay elementos para eliminar" << "\n\n";
        } else {
            tope = tope - 1; // Simplemente disminuye el tope
            //cout << "Se eliminó el último elemento" << "\n\n";
        }
    }

    // Método para mostrar los elementos de la pila
    void mostrar() {
        cout << "[";
        for (int i = 0; i < tope; i++) {
            cout << contenedores[i];

            if (tope != i + 1) {
                cout << ", ";
            }
        }
        cout << "]\n";
    }
};

// Estructura referente a un array de pilas
struct Puerto {
    int espacios_disponibles;  // Cantidad de pilas en el puerto
    Pila** bloques_pilas;      // Puntero a un array dinámico de punteros a Pilas

    // Constructor para inicializar el puerto con pilas dinámicas
    Puerto(int num_pilas, int capacidad_pilas) : espacios_disponibles(num_pilas) {
        bloques_pilas = new Pila*[espacios_disponibles]; // Asignamos memoria para el array de punteros a Pilas
        for (int i = 0; i < espacios_disponibles; i++) {
            bloques_pilas[i] = new Pila(capacidad_pilas); // Inicializamos cada pila con capacidad dinámica
        }
    }

    // Método para mostrar el contenido de todas las pilas en el puerto
    void mostrar_puerto() {
        cout << "\n~~Contenedores actuales en el Puerto~~\n\n";
        for (int i = 0; i < espacios_disponibles; i++) {
            cout << "Pila " << i + 1 << ": ";
            bloques_pilas[i]->mostrar();
        }
        cout << "\n\n";
    };

    // Método para agregar elementos aleatorios sin repetición
    void agregar_elementos_aleatorios() {
        // Inicializar generador aleatorio
        srand(static_cast<unsigned int>(time(0))); // Semilla para el generador aleatorio

        set<string> contenedores_unicos; // Conjunto para evitar duplicados

        for (int i = 0; i < espacios_disponibles; i++) {
            int num_elementos = rand() % (bloques_pilas[i]->maximo + 1); // Número aleatorio de elementos a agregar
            for (int j = 0; j < num_elementos; j++) {
                string contenedor;
                do {
                    // Generar un string en el formato "x/EMPy"
                    int x = rand() % espacios_disponibles + 1; // Número aleatorio entre 1 y cantidad de pilas
                    int y = rand() % bloques_pilas[i]->maximo + 1; // Número aleatorio entre 1 y capacidad de las pilas
                    contenedor = to_string(x) + "/EMP" + to_string(y);
                } while (contenedores_unicos.find(contenedor) != contenedores_unicos.end()); // Asegura que no se repita

                contenedores_unicos.insert(contenedor);
                bloques_pilas[i]->push(contenedor);
            }
        }
    }

    // Método para eliminar un contenedor en específico
    void eliminar_contenedor(string contenedor_a_eliminar) {

        cout << "\n\nComenzando Procedimiento Elimindar Contenedor\n\n";
        for (int bloque = 0; bloque < espacios_disponibles; bloque++) {
            cout << "Buscando en pila " << bloque + 1 << "\n";

            for (int indice_contenedor = 0; indice_contenedor < bloques_pilas[bloque]->tope; indice_contenedor++) {
                if (bloques_pilas[bloque]->contenedores[indice_contenedor] == contenedor_a_eliminar) {
                    cout << "Contenedor encontrado en la pila " << bloque + 1 << ", posición " << indice_contenedor << "\n";

                    if (indice_contenedor == bloques_pilas[bloque]->tope - 1) {
                        // Si es el último contenedor, simplemente hacer pop
                        bloques_pilas[bloque]->pop();
                    } else {
                        cout << "El contenedor no está en el tope, necesita reubicación.\n";

                        // Mover los contenedores que están por encima uno por uno
                        for (int i = bloques_pilas[bloque]->tope - 1; i > indice_contenedor; i--) {
                            //copia contenedor
                            string contenedor_a_mover = bloques_pilas[bloque]->contenedores[i];

                            // Reubicar el contenedor en otra pila con espacio disponible
                            bool reubicado = false;
                            for (int j = 0; j < espacios_disponibles; j++) {
                                if (j != bloque && bloques_pilas[j]->tope < bloques_pilas[j]->maximo) {
                                    // Reubicar solo en pilas diferentes a la actual (j != bloque)
                                    bloques_pilas[j]->push(contenedor_a_mover);
                                    reubicado = true;
                                    cout << "Contenedor " << contenedor_a_mover << " reubicado en la pila " << j + 1 << ".\n";
                                    break;
                                }
                            }

                            if (reubicado) {
                                bloques_pilas[bloque]->pop();
                                mostrar_puerto();
                            }

                            // Si no se pudo reubicar, mostrar un mensaje de error
                            if (!reubicado) {
                                cout << "Error: No se pudo reubicar el contenedor " << contenedor_a_mover << ".\n";
                            }
                        }

                        // Actualizamos el tope para eliminar el contenedor
                        bloques_pilas[bloque]->tope = indice_contenedor;
                        cout << "Contenedor " << contenedor_a_eliminar << " eliminado.\n";
                    }

                    return;  // Salir de la función una vez que se encontró y eliminó el contenedor
                }
            }
        }

        cout << "Contenedor no encontrado.\n";
    }
};

int main() {
    string ingreso_num_pilas;
    string ingreso_num_capacidad;

    cout << "Ingrese numero de Pilas\n>";
    cin >> ingreso_num_pilas;
    cout << "Ingrese Capacidad de las Pilas\n> ";
    cin >> ingreso_num_capacidad;

    // n
    int num_pilas = stoi(ingreso_num_pilas);
    // m
    int capacidad_pilas = stoi(ingreso_num_capacidad);

    Puerto mi_puerto(num_pilas, capacidad_pilas);

    // Agregar elementos a las pilas
    mi_puerto.agregar_elementos_aleatorios();

    // Mostrar el contenido del puerto
    mi_puerto.mostrar_puerto();

    string string_ingreso;
    string_ingreso = "holamundo";

    while (string_ingreso != "salir") {
        cout << "Ingrese El NOMBRE de el contenedor que desea eliminar ~ ('1/EMP1')\nSalir ~ (salir)\n> ";
    
        cin >> string_ingreso;

        if (string_ingreso != "salir") {
            mi_puerto.eliminar_contenedor(string_ingreso);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~Puerto Actual~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
            mi_puerto.mostrar_puerto();
        } else {
            break;
        }
    }
    /*
    cout << "Buscar contenedor ~ 1/EMP1\n";
    mi_puerto.eliminar_contenedor("1/EMP1");

    mi_puerto.mostrar_puerto();

    cout << "\n\nBuscar contenedor ~ 2/EMP3\n";
    mi_puerto.eliminar_contenedor("2/EMP3");

    mi_puerto.mostrar_puerto();
    */

    return 0;
}