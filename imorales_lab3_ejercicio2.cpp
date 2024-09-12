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
    void eliminar_contenedor(string contenedor_a_eliminar){
        //mi_puerto.bloques_pilas[1]->contenedores[0] -> almacena string

        /* objetivo~
        se quiere sacar contenedor "1/EMP1"

        1 -> recorrer cada pila y localizar el contenedor, recorrer cada bloque - recorrer cada pila segun su tope
        2 -> obtener indice el contenedor
        3 -> comparar con el indice del tope del contenedor
        4 -> pop() contenedores que estan por encima y repocisionarlos en otra pila que tenga espacio
        5 -> eliminar contenedor X
        */
   
        // Recorremos todas las pilas
        for (int bloque = 0; bloque < espacios_disponibles; bloque++) {
            cout << "Buscando en pila " << bloque + 1 << "\n";
            
            // Recorremos los elementos presentes en la pila
            for (int indice_contenedor = 0; indice_contenedor < bloques_pilas[bloque]->tope; indice_contenedor++) {
                // Comparar si el contenedor actual es el que queremos eliminar
                if (bloques_pilas[bloque]->contenedores[indice_contenedor] == contenedor_a_eliminar) {
                    cout << "Contenedor encontrado en la pila " << bloque + 1 << ", posición " << indice_contenedor << "\n";

                                    if (indice_contenedor == bloques_pilas[bloque]->tope - 1) {
                        bloques_pilas[bloque]->pop(); // Si es el último, simplemente hacer pop
                    } else {
                        // Implementa la lógica para mover contenedores si es necesario
                        cout << "El contenedor no está en el tope, necesita reubicación.\n";
                        // Aquí iría el código para reubicar contenedores.
                    }

                    return;
                }
            }
        } 
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

    cout << "\n\nBuscar contenedor ~ 2/EMP3\n";
    mi_puerto.eliminar_contenedor("2/EMP3");

    return 0;
}