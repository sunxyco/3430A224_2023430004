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

int main() {
    cout << "Hola mundo" << "\n\n";

    string cantidad_pila = "holamundo";

    cout << "Ingrese tamaño Maximo de la pila\n\n> ";

    cin >> cantidad_pila;
    
    int ingreso_int =  stoi(cantidad_pila);

    // Crear pila de x espacios
    Pila mi_pila(ingreso_int);
    cout << "Se creó la pila de " << ingreso_int << " elementos" << "\n\n";

    string ingreso_opcion;
    ingreso_opcion = "oal mundo";

    string ingreso_secundario;
    ingreso_secundario = "oda undo";

    while (ingreso_opcion != "0") {
        cout << "Agregar/push [1]\nRemover/pop  [2]\nVer pila     [3]\nSalir        [0]\n~~~~~~~~~~~~~~~~\nOpcion> ";

        cin >> ingreso_opcion;

        if (ingreso_opcion == "1") {
            //agregar elemento
            cout << "Ingrese el valor que se almacenara en la pila\n> ";
            cin >> ingreso_secundario;
            int dato_numero = stoi(ingreso_secundario);
            mi_pila.push(dato_numero);

        } else if (ingreso_opcion == "2")
        {
            //eliminar ultimo elemento

            mi_pila.pop();

        } else if (ingreso_opcion == "3")
        {
            //Ver pila

            mi_pila.mostrar();

        } else if (ingreso_opcion == "0")
        {
            //salir
        } 
        
    }

    return 0;
}