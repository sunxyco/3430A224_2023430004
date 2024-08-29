#include <iostream>
using namespace std;

//la estructura de tipo paciente
struct Paciente
{
    string nombre;
    int peso;
    int edad;
    double altura;
};

int main () {
    //se crea un arreglo de 3 instancias de tipo Paciente
    Paciente mis_pacientes[3];

    //se modifica el arreglo con los datos de nuestros pacientes
    mis_pacientes[0].nombre = "Martin";
    mis_pacientes[0].peso = 43;
    mis_pacientes[0].edad = 11;
    mis_pacientes[0].altura = 1.50;

    mis_pacientes[1].nombre = "Carlota";
    mis_pacientes[1].peso = 65;
    mis_pacientes[1].edad = 23;
    mis_pacientes[1].altura = 1.70;

    mis_pacientes[2].nombre = "Gonzalo";
    mis_pacientes[2].peso = 140;
    mis_pacientes[2].edad = 45;
    mis_pacientes[2].altura = 1.90;


    //se imprimen los datos de nuestros pacientes
    for (int i = 0; i < 3; ++i) {
        cout << "Paciente " << i+1 << "\n";
        cout << "Nombre: " << mis_pacientes[i].nombre << " ";
        cout << "Peso: " << mis_pacientes[i].peso << "kg ";
        cout << "Edad: " << mis_pacientes[i].edad << " ";
        cout << "Altura: " << mis_pacientes[i].altura << "m ";
        cout << "\n\n";
    }

    return 0;
}