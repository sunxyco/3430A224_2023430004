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
};

int main () {

    //hacer arreglo qui
    Paciente mis_pacientes[3];

    mis_pacientes[0].nombre = "Martin";
    mis_pacientes[0].edad = 11;
    mis_pacientes[0].altura = 1.50;

    mis_pacientes[1].nombre = "Carlota";
    mis_pacientes[1].edad = 23;
    mis_pacientes[1].altura = 1.70;

    mis_pacientes[2].nombre = "Gonzalo";
    mis_pacientes[2].edad = 45;
    mis_pacientes[2].altura = 1.90;


    for (int i = 0; i < 3; ++i) {
        cout << "Paciente " << i+1 << "\n";
        cout << "Nombre: " << mis_pacientes[i].nombre << " ";
        cout << "Edad: " << mis_pacientes[i].edad << " ";
        cout << "Altura: " << mis_pacientes[i].altura << " ";
        cout << "\n\n";
    }

    return 0;
}