/*Escriba un programa en C++ que permita obtener algunos datos del espacio muestral
de pacientes que se maneja y se encuentra almacenado en la lista. Es de interés
poder conocer el promedio de edad y el promedio de peso del grupo presente
además del IMC de cada uno de los pacientes. Dentro de la función main debe
incorporar los ejemplos de pacientes y dejar en evidencia todas las funciones
desarrolladas.
Respecto al IMC o Índice de Masa Corporal (IMC):
Este es uno de los indicadores más utilizados para determinar si una persona tiene
sobrepeso, obesidad o bajo peso.
IMC = peso/altura².
“Un IMC dentro de los rangos normales indica un peso saludable, mientras que un IMC
muy alto o muy bajo puede ser un signo de riesgo para diversas enfermedades”*/

/*Bajo peso: IMC menor de 18.5
Peso normal: IMC entre 18.5 y 24.9
Sobrepeso: IMC entre 25 y 29.9
Obesidad: IMC de 30 o más*/

//cosas que hacer 
//agregar atributo peso~hecho
//funciones -promedio edad -promedio peso -promedio altura -imc (peso/altura^2) -> para imprimir estos datos podria almacenarlos a medida que se van impimiendo
#include <iostream>
using namespace std;


//la estructura de tipo paciente
struct Paciente
{
    string nombre;
    int edad;
    double altura;
    int peso;

    Paciente* siguiente;
};

//se agrega cada nuevo paciente y se genera una conexion entra cada uno 
void agregar_persona(Paciente*& head, const string& nombre, int edad, double altura, int peso)
{
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente->nombre = nombre;
    nuevoPaciente->edad = edad;
    nuevoPaciente->siguiente = head;
    nuevoPaciente->altura = altura;
    nuevoPaciente->peso = peso;
    head = nuevoPaciente;
}

string mensaje_imc(double imc_paciente)
{
    if (imc_paciente < 18.5) {
            return "Bajo peso";
        } else if (imc_paciente >= 18.5 && imc_paciente <= 24.9) {
            return "Peso normal";
        } else if (imc_paciente >= 25 && imc_paciente <= 29.9) {
            return "Sobrepeso";
        } else if (imc_paciente >= 30) {
            return "Obesidad";
        } else {
            return "ERROR";
        }
}

void imprimir_personas(const Paciente* head)
{
    //-promedio edad -promedio peso -promedio altura -imc (peso/altura^2)
    int suma_edades = 0;
    int suma_peso = 0;
    double altura = 0;

    const Paciente* actual = head;
    int i = 1;
    while (actual != nullptr) {
        double imc_paciente = ((actual->peso) / ((actual->altura)*(actual->altura)));

        string mensaje_sobre_imc = mensaje_imc(imc_paciente);

        cout << "Paciente " << i << " nombre: " << actual->nombre << " edad: " << actual->edad << " altura: " << actual->altura << " peso: " << actual->peso << " imc: " << imc_paciente << " " << mensaje_sobre_imc << "\n";
        actual = actual->siguiente;
        i = i + 1;
    }
}

void eliminarPaciente(Paciente*& head, const string& nombre) {
    Paciente* actual = head;
    Paciente* previous = nullptr;

    while (actual != nullptr && actual->nombre != nombre) {
        previous = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr) {
        if (previous == nullptr) {
            head = actual->siguiente;
        } else {
            previous->siguiente = actual->siguiente;
        }
        delete actual;
    }
}

int main ()
{

    //puntero principal
    Paciente* head = nullptr;

    //se agregan las personas a la lista
    agregar_persona(head, "Martin", 11, 1.50, 47);
    agregar_persona(head, "Carlota", 23, 1.70, 61);
    agregar_persona(head, "Gonzalo", 45, 1.9, 77);
    agregar_persona(head, "Daniel", 19, 1.79, 120);

    cout << "Pacientes actuales \n\n";
    imprimir_personas(head);

    //eliminar paciente
    eliminarPaciente(head, "Gonzalo");


    cout << "\nSe elimino a Gonzalo ~ Nueva lista\n\n";
    //se imprime la lsita actual con un paciente eliminado
    imprimir_personas(head);

    //se libera la memoria
    while (head != nullptr) {
        Paciente* temporal = head;
        head = head->siguiente;
        delete temporal;
    }

    return 0;
}