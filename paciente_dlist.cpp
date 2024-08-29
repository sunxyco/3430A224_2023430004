#include <iostream>
using namespace std;

//la estructura de tipo paciente actualizada para ser compatible con la lista dinamica
struct Paciente
{
    string nombre;
    int peso;
    int edad;
    double altura;

    Paciente* siguiente;
};

//funcion para agregar personas
void agregar_persona(Paciente*& head, const string& nombre,int peso, int edad, double altura)
{
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente->nombre = nombre;
    nuevoPaciente->peso = peso;
    nuevoPaciente->edad = edad;
    nuevoPaciente->siguiente = head;
    nuevoPaciente->altura = altura;
    head = nuevoPaciente;
}

//funcion imprimir a todos los pacientes actuales
void imprimir_personas(const Paciente* head)
{

    const Paciente* actual = head;
    int i = 1;
    while (actual != nullptr) {
        cout << "Paciente " << i << " Nombre: " << actual->nombre << " Peso: " << actual->peso << "kg Edad: " << actual->edad << " Altura: " << actual->altura << "m\n";
        actual = actual->siguiente;
        i = i + 1;
    }
}

//funcion eliminar personas
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
    agregar_persona(head, "Martin", 45, 11, 1.50);
    agregar_persona(head, "Carlota", 65, 23, 1.70);
    agregar_persona(head, "Gonzalo", 140, 45, 1.90);
    agregar_persona(head, "Daniel", 79, 19, 1.79);

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