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

    // Método para eliminar el último elemento de la pila
    void pop() {
        if (tope == 0) { // Verificar si la pila está vacía
            cout << "No hay elementos para eliminar" << "\n\n";
        } else {
            tope--; // Simplemente disminuye el tope
            cout << "Se eliminó el último elemento" << "\n\n";
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
    Pila mi_pila(5);
    cout << "Se creó la pila de 5 elementos" << "\n\n";

    // Agregar elementos a la pila
    cout << "Se le intento agregar los elementos 1, 2, 3, 4, 5, 6; como la pila es de 5 elementos el 6 no se agregó\n\n";
    mi_pila.push(1);
    mi_pila.push(2);
    mi_pila.push(3);
    mi_pila.push(4);
    mi_pila.push(5);
    mi_pila.push(6); // Intento de agregar un quinto elemento

    // Mostrar los elementos de la pila
    mi_pila.mostrar();

    mi_pila.pop();

    cout << "se eliminio el elemento en ultima posicion" << "\n\n";

    mi_pila.mostrar();

    cout << "Se agrego intento agregar los elementos 7, 8, 9; en este caso los elementos 8 y 9 no pueden agregar \n\n";
    mi_pila.push(7);
    mi_pila.push(8);
    mi_pila.push(9);

    mi_pila.mostrar();

    return 0;
}