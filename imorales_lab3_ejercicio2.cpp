#include <iostream>
#include <string>
using namespace std;

struct Pila {
    int maximo;
    int tope;
    string* contenedores; // Usamos un puntero para manejar el array dinámicamente

    // Constructor para inicializar la pila - usado para cuando se crea la pila
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

    // Método para eliminar el último elemento de la pila ~ se reduce el tamaño de el array en 1 y se deja el ultimo elemento afuera
    void pop() {
        if (tope == 0) { // Verificar si la pila está vacía
            cout << "No hay elementos para eliminar" << "\n\n";
        } else {
            tope = tope - 1; // Simplemente disminuye el tope
            cout << "Se eliminó el último elemento" << "\n\n";
        }
    }

    // Método para mostrar los elementos de la pila
    void mostrar() {
        cout << "[";
        for (int i = 0; i < tope; i++) {
            cout << contenedores[i];

            if (tope != i + 1){
                cout << ", ";
            }
        }
        cout << "]\n\n";
    }
};

//referente a un array de pilas
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
        for (int i = 0; i < espacios_disponibles; i++) {
            cout << "Pila " << i + 1 << ": ";
            bloques_pilas[i]->mostrar();
        }
    }

    //metodo para eliminar un contenedor en especifico
    void eliminar_contenedor(string contenedor_a_eliminar) {
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
                        for (int i = indice_contenedor + 1; i < bloques_pilas[bloque]->tope; i++) {
                            string contenedor_a_mover = bloques_pilas[bloque]->contenedores[i];

                            // Reubicar el contenedor en otra pila con espacio disponible
                            bool reubicado = false;
                            for (int j = 0; j < espacios_disponibles; j++) {
                                if (bloques_pilas[j]->tope < bloques_pilas[j]->maximo) {
                                    bloques_pilas[j]->push(contenedor_a_mover);
                                    reubicado = true;
                                    cout << "Contenedor " << contenedor_a_mover << " reubicado en la pila " << j + 1 << ".\n";
                                    break;
                                }
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

int main(){
    cout << "Holamundo" << "\n\n";

    //m -> referente a cantidad de pilas

    //puerto almacena m cantidad de pilas

    //una pila almacena n cantidad de contenedores

    //puerto -> array de pilas de contenedores


    //leer por terminal n y m

    //especie de matriz

    //mostrar por pantalla cada movimiento realizado

    // Crear un puerto con 3 pilas, donde cada pila puede almacenar hasta 5 elementos

    //n
    int num_pilas = 4;
    //m
    int capacidad_pilas = 5;
    Puerto mi_puerto(num_pilas, capacidad_pilas);

    // Agregar elementos a las pilas
    mi_puerto.bloques_pilas[0]->push("1/EMP1");
    mi_puerto.bloques_pilas[0]->push("2/EMP1");
    mi_puerto.bloques_pilas[1]->push("1/EMP2");
    mi_puerto.bloques_pilas[2]->push("1/EMP3");
    mi_puerto.bloques_pilas[2]->push("2/EMP3");
    mi_puerto.bloques_pilas[0]->push("3/EMP1");

    // Mostrar el contenido del puerto
    mi_puerto.mostrar_puerto();

    cout << "Buscar contenedor ~ 1/EMP1\n";
    mi_puerto.eliminar_contenedor("1/EMP1");

    mi_puerto.mostrar_puerto();

    cout << "\n\nBuscar contenedor ~ 2/EMP3\n";
    mi_puerto.eliminar_contenedor("2/EMP1");

    mi_puerto.mostrar_puerto();
    return 0;
}