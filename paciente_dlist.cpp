/*Escriba programa en C++ que permita almacenar la información de pacientes en
una estructura para trabajar con una lista dinámica. Aquí no se puede utilizar la librería
list y debe realizar la actualización de la estructura, la inclusión de las funciones para
agregar, imprimir y eliminar. Dentro de la función main debe incorporar los ejemplos de
pacientes y dejar en evidencia todas las funciones desarrolladas*/

/*Escriba un programa en C++ que permita almacenar la información de los pacientes
(estructura) en un arreglo. Dentro de la función main debe incorporar los ejemplos de
“pacientes” utilizados anteriormente, almacenarlos en el arreglo y entregar la
información de cada uno de ellos por la salida estándar.*/


#include <iostream>
using namespace std;

//la estructura de tipo paciente
struct Paciente
{
    string nombre;
    int edad;
    double altura;

    Paciente* siguiente;
};

//se agrega cada nuevo paciente y se genera una conexion entra cada uno 
void agregar_persona(Paciente*& head, const string& nombre, int edad, double altura)
{
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente->nombre = nombre;
    nuevoPaciente->edad = edad;
    nuevoPaciente->siguiente = head;
    nuevoPaciente->altura = altura;
    head = nuevoPaciente;
}



void imprimir_personas(const Paciente* head)
{

    const Paciente* current = head;
    int i = 1;
    while (current != nullptr) {
        cout << "Paciente" << i << "\nnombre: " << current->nombre << " edad: " << current->edad << " altura: " << current->altura << "\n\n";
        current = current->siguiente;
        i = i + 1;
    }

}

int main ()
{

    //puntero principal
    Paciente* head = nullptr;

    //se agregan las personas a la lista
    agregar_persona(head, "Martin", 11, 1.50);
    agregar_persona(head, "Carlota", 23, 1.70);
    agregar_persona(head, "Gonzalo", 45, 1.90);

    cout << "Pacientes actuales \n\n";
    imprimir_personas(head);

    return 0;
}