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

    //se crean 3 pacientes segun la estructura
    Paciente paciente1;
    paciente1.nombre = "Martin";
    paciente1.peso = 43;
    paciente1.edad = 11;
    paciente1.altura = 1.50;

    Paciente paciente2;
    paciente2.nombre = "Carlota";
    paciente2.peso = 65;
    paciente2.edad = 23;
    paciente2.altura = 1.70;

    Paciente paciente3;
    paciente3.nombre = "Gonzalo";
    paciente3.peso = 140;
    paciente3.edad = 45;
    paciente3.altura = 1.90;

    //se imprimen los 3 pacientes
    cout << "Pacientes\n\nPaciente 1\n" << "Nombre:" << paciente1.nombre << " Edad: " << paciente1.edad << " Peso: " << paciente1.peso << "kg Altura: "<< paciente1.altura <<"m\n";
    cout << "\nPaciente 2\n" << "Nombre:" << paciente2.nombre << " Edad: " << paciente2.edad << " Peso: " << paciente2.peso << "kg Altura: "<< paciente2.altura <<"m\n";
    cout << "\nPaciente 3\n" << "Nombre:" << paciente3.nombre << " Edad: " << paciente3.edad << " Peso: " << paciente3.peso << "kg Altura: "<< paciente3.altura <<"m\n";

    return 0;
}
