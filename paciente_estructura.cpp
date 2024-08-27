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

    Paciente paciente1;
    paciente1.nombre = "Martin";
    paciente1.edad = 11;
    paciente1.altura = 1.50;

    Paciente paciente2;
    paciente2.nombre = "Carlota";
    paciente2.edad = 23;
    paciente2.altura = 1.70;

    Paciente paciente3;
    paciente3.nombre = "Gonzalo";
    paciente3.edad = 45;
    paciente3.altura = 1.90;


    cout << "Pacientes\n\nPaciente 1\n" << "Nombre:" << paciente1.nombre << " Edad: " << paciente1.edad << " altura: "<< paciente1.altura <<"\n";
    cout << "\nPaciente 2\n" << "Nombre:" << paciente2.nombre << " Edad: " << paciente2.edad << " altura: "<< paciente2.altura <<"\n";
    cout << "\nPaciente 3\n" << "Nombre:" << paciente3.nombre << " Edad: " << paciente3.edad << " altura: "<< paciente3.altura <<"\n";

    return 0;
}
