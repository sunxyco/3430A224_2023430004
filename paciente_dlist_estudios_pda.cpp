//se va a leer datos de csv -> Name,Age,Height (m),Weight (kg),AC1

//->puntaje de prioridad -> edad, imc, AC1

//pila->pacientes / cola->lista de atencion

//actualizar estructura para almacenar IMC ~ AC1
//cargar csv
//buscar IMC ~ AC1
//puntaje prioridad

//AC1 -> nomral 5,7 > x; prediabetes 5,7 <= x <= 6,5 ; diabetes 6,5 < x;


#include <iostream>
using namespace std;

struct Paciente
{
    string nombre;
    int edad;
    double altura;
    int peso;
    double imc;
    double ac1;
};


int main()
{

    //se crean 3 pacientes segun la estructura
    Paciente mi_paciente;
    mi_paciente.nombre = "Martin";
    mi_paciente.edad = 11;
    mi_paciente.altura = 1.50;
    mi_paciente.peso = 43;
    mi_paciente.imc = (43 / ((1.50)*(1.50)));

    cout << "Pacientes\n\nPaciente 1\n" << "Nombre:" << mi_paciente.nombre << " Edad: " << mi_paciente.edad << " Peso: " << mi_paciente.peso << "kg Altura: "<< mi_paciente.altura <<"m\n";

}