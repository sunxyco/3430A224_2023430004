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
            return " Bajo peso";
        } else if (imc_paciente >= 18.5 && imc_paciente <= 24.9) {
            return " Peso normal";
        } else if (imc_paciente >= 25 && imc_paciente <= 29.9) {
            return " Sobrepeso";
        } else if (imc_paciente >= 30) {
            return " Obesidad";
        } else {
            return "ERROR";
        }
}

double calcular_promedio_edad(const Paciente* head)
{
    double suma_edades = 0;
    const Paciente* actual = head;
    int i = 0;

    while (actual != nullptr){
        suma_edades += actual->edad;

        actual = actual -> siguiente;
        i = i + 1;
    }

    double promedio_edad = suma_edades / (i);

    return promedio_edad;
}

double calcular_promedio_peso(const Paciente* head)
{
    double suma_peso = 0;
    const Paciente* actual = head;
    int i = 0;

    while (actual != nullptr){
        suma_peso += actual->peso;

        actual = actual -> siguiente;
        i = i + 1;
    }

    double promedio_peso = suma_peso / (i);

    return promedio_peso;
}

double obtener_imc(const Paciente* actual)
{   
    double imc = ((actual->peso) / ((actual->altura) * (actual->altura)));

    return imc;
}

void imprimir_imc_pacientes(const Paciente* head)
{
    const Paciente* actual = head;
    while (actual != nullptr)
    {
        double imc_paciente = obtener_imc(actual);
        
        cout << "IMC de " << actual->nombre << " ~ " << imc_paciente << mensaje_imc(imc_paciente) << "\n";

        actual = actual -> siguiente;
    }
}

void imprimir_pacientes(const Paciente* head)
{
    const Paciente* actual = head;
    int i = 1;
    while (actual != nullptr) {
        cout << "Paciente " << i << " nombre: " << actual->nombre << " edad: " << actual->edad << " altura: " << actual->altura << "m peso: " << actual->peso << "kg\n";

        actual = actual->siguiente;
        i++;
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

void imprimir_datos(Paciente*& head)
{
    double promedio_edades = calcular_promedio_edad(head);
    cout << "El promedio de edades es: " << promedio_edades << " años\n";

    double promedio_peso = calcular_promedio_peso(head);
    cout << "El promedio de Peso es: " << promedio_peso << "kg\n\n";

    imprimir_imc_pacientes(head);
}

int main ()
{

    //puntero principal
    Paciente* head = nullptr;

    //se agregan las personas a la lista
    agregar_persona(head, "Martin", 11, 1.50, 33);
    agregar_persona(head, "Carlota", 23, 1.70, 61);
    agregar_persona(head, "Gonzalo", 45, 1.9, 120);
    agregar_persona(head, "Daniel", 19, 1.79, 79);
    agregar_persona(head, "Oscar", 24, 1.82, 55);
    agregar_persona(head, "Marcelo", 64, 1.87, 90);

    cout << "Pacientes actuales \n\n";
    imprimir_pacientes(head);
    cout << "\nDatos de los pacientes:\n\n";
    imprimir_datos(head);

    //eliminar paciente
    eliminarPaciente(head, "Gonzalo");

    cout << "\n~~~~ Se elimino a Gonzalo ~ Nueva lista ~~~~\n\n";
    //se imprime la lsita actual con un paciente eliminado
    imprimir_pacientes(head);
    cout << "\nDatos de los pacientes:\n\n";
    imprimir_datos(head);


    //se libera la memoria
    while (head != nullptr) {
        Paciente* temporal = head;
        head = head->siguiente;
        delete temporal;
    }

    return 0;
}