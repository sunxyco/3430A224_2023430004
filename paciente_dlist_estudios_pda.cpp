//se va a leer datos de csv -> Name,Age,Height (m),Weight (kg),AC1

//->puntaje de prioridad -> edad, imc, AC1

//pila->pacientes / cola->lista de atencion

//actualizar estructura para almacenar IMC ~ AC1
//cargar csv
//buscar IMC ~ AC1
//puntaje prioridad

//AC1 -> nomral 5,7 > x; prediabetes 5,7 <= x <= 6,5 ; diabetes 6,5 < x;

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
    double imc;
    double ac1;

    Paciente* siguiente;
};

//se agrega cada nuevo paciente y se genera una conexion entra cada uno 
void agregar_persona(Paciente*& head, const string& nombre, int edad, double altura, int peso, double ac1)
{
    Paciente* nuevoPaciente = new Paciente();
    nuevoPaciente->nombre = nombre;
    nuevoPaciente->edad = edad;
    nuevoPaciente->siguiente = head;
    nuevoPaciente->altura = altura;
    nuevoPaciente->peso = peso;
    nuevoPaciente->imc = (peso / (altura * altura));
    nuevoPaciente->ac1 = ac1;
    head = nuevoPaciente;
}

void imprimir_pacientes(const Paciente* head)
{
    const Paciente* actual = head;
    int i = 1;
    while (actual != nullptr) {
        cout << "Paciente " << i << "\nNombre: " << actual->nombre << " Edad: " << actual->edad << " Altura: " << actual->altura << "m Peso: " << actual->peso << "kg IMC: " << actual->imc <<" Ac1: " << actual->ac1 << "\n";
        actual = actual->siguiente;
        i++;
    }
    cout << "\n\n";
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
        string nombre, edad_str, altura_str, peso_str, ac1_str;

        // Leer cada campo separado por ','
        getline(ss, nombre, ',');
        getline(ss, edad_str, ',');
        getline(ss, altura_str, ',');
        getline(ss, peso_str, ',');
        getline(ss, ac1_str, '\n');

        // Convertir los campos a los tipos correctos
        int edad = stoi(edad_str);
        double altura = stod(altura_str);
        int peso = stoi(peso_str);
        double ac1 = stod(ac1_str);

        agregar_persona(head, nombre, edad, altura, peso, ac1);

        contador++;
    }

    archivo.close();

    cout << "\n\n";
}

int main()
{
    //puntero principal
    Paciente* head = nullptr;

    string ingreso_usuario;
    ingreso_usuario = "hola mundo";

    string ruta_ejemplo = "patient_list.csv";
    cout << "Nuevos Pacientes Cargados desde CSV\n\n";
    cargar_pacientes_desde_csv(head, ruta_ejemplo);
    imprimir_pacientes(head);

    while (ingreso_usuario != "salir")
    {
        cout << "Opciones de Ingreso:\n\n1~ Sobre IMC\n2~ Sobre AC1\nsalir~ salir del programa\n\n>";
        cin >> ingreso_usuario;

        /*
        1~ Sobre IMC
                1.1 Imprimir bajopeso
                1.2 imprimir peso normal
                1.3 Imprimir sobrepeso
                1.4 imprimir obesidad
        2~ Sobre AC1
                2.1 imprimir normal
                2.2 imprimir prediabetes
                2.3 imprimir diabetes
        "salir"~ cerrar el programa*/

        //sobre IMC
        if (ingreso_usuario == "1") {
            cout << "   1~ imprimir bajopeso\n   2~ imprimir peso normal\n   3~ imprimir sobrepeso\n   4~ imprimir obesidad\n\n>";
            cin >> ingreso_usuario;
            if (ingreso_usuario == "1"){
                cout << "\n\nSe imprimiran a los de bajo peso\n\n";
            }
            if (ingreso_usuario == "2"){
                cout << "\n\nSe imprimiran a los de peso normal\n\n";
            }
            if (ingreso_usuario == "3"){
                cout << "\n\nSe imprimiran a los de sobrepeso\n\n";
            }
            if (ingreso_usuario == "4"){
                cout << "\n\nSe imprimiran a los de obesidad\n\n";
            }
        }
        
        //sobre A1C
        if (ingreso_usuario == "2") {
            cout << "   1~ imprimir normal\n   2~ imprimir prediabetes\n   3~ imprimir Diabetes\n\n>";
            cin >> ingreso_usuario;
            if (ingreso_usuario == "1"){
                cout << "\n\nSe imprimiran a los de AC1 Normal\n\n";
            }
            if (ingreso_usuario == "2"){
                cout << "\n\nSe imprimiran a los de AC1 Prediabetes\n\n";
            }
            if (ingreso_usuario == "3"){
                cout << "\n\nSe imprimiran a los de AC1 Diabetes\n\n";
            }
        }

        if (ingreso_usuario == "salir") {
            cout << "\n A Salido Correctamente del Programa :)";
        }
            
    }
}