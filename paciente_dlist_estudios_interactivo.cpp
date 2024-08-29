/*Escriba un programa en C++ que permita trabajar con la gestión de pacientes a través
de opciones interactivas. Es de interés poder incorporar un menú que permita a un
usuario navegar por las opciones que existen y utilizar todas las funcionalidades
(funciones desarrolladas). Además se debe sumar la posibilidad de realizar la carga
de información desde un archivo de texto plano o CSV.
*/


//menu que permita utilizar todas las funciones desarrolladas
//cargar informacion desde un texto plano ~ csv

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Paciente
{
    string nombre;
    int edad;
    double altura;
    int peso;

    Paciente* siguiente;
};

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

void cargar_pacientes_desde_csv(Paciente*& head, const std::string& ruta)
{
    ifstream archivo(ruta);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo: " << ruta << endl;
        return;
    }

    string linea;
    int contador = 1;

    // Leer cada línea del archivo
    getline(archivo, linea); // Leer y ignorar la línea de encabezado

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre, edad_str, altura_str, peso_str;

        // Leer cada campo separado por ';'
        getline(ss, nombre, ';');
        getline(ss, edad_str, ';');
        getline(ss, altura_str, ';');
        getline(ss, peso_str, ';');

        // Convertir los campos a los tipos correctos
        int edad = stoi(edad_str);
        double altura = stod(altura_str);
        int peso = stoi(peso_str);

        agregar_persona(head, nombre, edad, altura, peso);

        // Imprimir la información del paciente
        cout << "Paciente " << contador << " - Nombre: " << nombre
                  << ", Edad: " << edad
                  << ", Altura: " << altura
                  << ", Peso: " << peso << std::endl;
        
        contador++;
    }

    archivo.close();
}

void guardar_pacientes_en_csv(Paciente* head, const string& ruta)
{
    ofstream archivo(ruta);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escritura: " << ruta << endl;
        return;
    }

    // Escribir la línea de encabezado
    archivo << "Nombre;Edad;Altura;Peso\n";

    // Recorrer la lista de pacientes y escribir cada uno en el archivo
    Paciente* actual = head;
    while (actual != nullptr) {
        archivo << actual->nombre << ";"
                << actual->edad << ";"
                << actual->altura << ";"
                << actual->peso << "\n";
        actual = actual->siguiente;
    }

    archivo.close();
    cout << "Datos guardados en " << ruta << endl;
}

int main()
{
    string ingreso_usuario;
    ingreso_usuario = "hola mundo";

    //puntero principal
    Paciente* head = nullptr;

    while (ingreso_usuario != "salir")
    {
        cout << "Opciones de Ingreso:\n\n1~ Agregar Paciente\n2~ Eliminar Paciente\n3~ Imprimir Pacientes Actuales\n4~ Imprimir promedio de Edad\n5~ Imprimir promedio de Peso\n6~ Imprimir IMC pacientes\n7~ cargar pacientes desde archivo\n8~ guardar pacientes en un archivo\nsalir~ cerrar el programa\n\n~~";
        cin >> ingreso_usuario;

        cout << "\n\n\n~~" << ingreso_usuario;

        /*1~ Agregar Paciente
        2~ Eliminar Paciente
        3~ Imprimir Pacientes Actuales
        4~ Imprimir promedio de Edad
        5~ Imprimir promedio de Peso
        6~ Imprimir IMC pacientes
        7~ cargar pacientes desde archivo
        8~ guardar pacientes en un archivo
        "salir"~ cerrar el programa*/

        //se cargan datos por defecto   lsito
        if (ingreso_usuario == "0") {
        cout << "0";
            agregar_persona(head, "Martin", 11, 1.50, 33);
            agregar_persona(head, "Carlota", 23, 1.70, 61);
            agregar_persona(head, "Gonzalo", 45, 1.9, 120);        
        }

        //1 agregar paciente            lsito
        if (ingreso_usuario == "1") {
            cout << "1";
            //se le pide que agregue nombre, edad, altura, peso
            string nombre;
            int edad;
            double altura;
            int peso;

            cout << "Ingrese el Nombre:\n";
            cin >> nombre;

            // Solicita la edad
            cout << "Ingrese la Edad:\n";
            cin >> edad;

            // Solicita la altura
            cout << "Ingrese la Altura (en m(decimal)):\n";
            cin >> altura;

            // Solicita el peso
            cout << "Ingrese el Peso (en kg(entero)):\n";
            cin >> peso;

            agregar_persona(head, nombre, edad, altura, peso);
        }

        //eliminar paciente             lsito
        if (ingreso_usuario == "2") {
            cout << "2";
            //segun el nombre ingresado se elimina el paciente
            string paciente_a_eliminar;
            cin >> paciente_a_eliminar;
            eliminarPaciente(head, paciente_a_eliminar);
        }

        //imprime los pacientes actuales lsito
        if (ingreso_usuario == "3") {
            cout << "3";
            cout << "Pacientes actuales \n\n";
            imprimir_pacientes(head);

        }

        //imprimir promedio de edad
        if (ingreso_usuario == "4") {
            cout << "4";
            double promedio_edades = calcular_promedio_edad(head);
            cout << "El promedio de edades es: " << promedio_edades << "\n";
        }

        //imprimir promedio de peso
        if (ingreso_usuario == "5") {
            cout << "5";
            double promedio_peso = calcular_promedio_peso(head);
            cout << "El promedio de Peso es: " << promedio_peso << "\n\n";
        }

        //imprimir IMC pacientes
        if (ingreso_usuario == "6") {
            cout << "6";
            imprimir_imc_pacientes(head);
        }

        //cargar pacientes desde archivo
        if (ingreso_usuario == "7") {
            cout << "7";
            string ruta_ejemplo = "datos.csv";
            cargar_pacientes_desde_csv(head, ruta_ejemplo);
        }

        //guardar pacientes en un archivo
        if (ingreso_usuario == "8") {
            cout << "8";
            string ruta_ejemplo = "datos.csv";
            guardar_pacientes_en_csv(head, ruta_ejemplo);
        }

        if (ingreso_usuario == "salir") {
            cout << "salido";
        }
            
    }
}