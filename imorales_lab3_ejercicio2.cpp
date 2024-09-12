#include <iostream>
#include <string>
using namespace std;

struct Pila {
    int maximo;
    int tope;
    int* valores; // Usamos un puntero para manejar el array dinámicamente

    // Constructor para inicializar la pila - usado para cuando se crea la pila
    Pila(int max) : maximo(max), tope(0) {
        valores = new int[maximo]; // Asignamos memoria para el array
    }

    // Método para agregar un elemento a la pila
    void push(int valor) {
        if (tope < maximo) {
            valores[tope] = valor; // Agrega el elemento y aumenta el tope
            tope = tope + 1;
        } else {
            cout << "Pila llena, imposible agregar elemento " << valor << "\n\n";
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
            cout << valores[i];

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
    int num_pilas = 3;
    //m
    int capacidad_pilas = 5;
    Puerto mi_puerto(num_pilas, capacidad_pilas);

    // Agregar elementos a las pilas
    mi_puerto.bloques_pilas[0]->push(10);
    mi_puerto.bloques_pilas[0]->push(20);
    mi_puerto.bloques_pilas[1]->push(30);
    mi_puerto.bloques_pilas[2]->push(40);
    mi_puerto.bloques_pilas[2]->push(50);

    // Mostrar el contenido del puerto
    mi_puerto.mostrar_puerto();

    //contenedores ~ 1/EMP1 - 2/EMP1 - 1/EMP2 - 1/EMP3
    //crear puerto con m pilas de n elementos

    return 0;
}