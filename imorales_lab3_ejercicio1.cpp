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
            cout << "Pila llena" << "\n\n";
        }
    }

    // Método para mostrar los elementos de la pila
    void mostrar() {
        for (int i = 0; i < tope; i++) {
            cout << valores[i] << " ";
        }
        cout << "\n\n";
    }
};

int main() {
    cout << "Hola mundo" << "\n\n";

    // Crear pila de 4 espacios
    Pila mi_pila(4);
    cout << "Se creó la pila" << "\n\n";

    // Agregar elementos a la pila
    mi_pila.push(1);
    mi_pila.push(2);
    mi_pila.push(3);
    mi_pila.push(4);
    mi_pila.push(5); // Intento de agregar un quinto elemento

    // Mostrar los elementos de la pila
    mi_pila.mostrar();

    return 0;
}