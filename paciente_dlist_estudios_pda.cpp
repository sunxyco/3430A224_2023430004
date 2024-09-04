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
    double puntaje_prioridad;

    Paciente* siguiente;
};

double calcular_puntaje_prioridad(int edad, double imc, double ac1){
    
    //factor de riesgo FR= 3,2,1,0; ac1> 180, imc > 30 (obesidad), imc > 18.5 (bajo peso), todos los datos normales
    if (ac1 < 5.7 && imc >= 18.5 && imc < 25.0){
        //la persona no tiene prioridad
        return 0;
    }

    int factor_riesgo = 0;
    //factor de riesgo FR= 3,2,1,0; ac1> 180, imc > 30 (obesidad), imc > 18.5 (bajo peso), todos los datos normales

    if (imc > 18.5){
        factor_riesgo = 1;
    }
    if (imc > 30){
        factor_riesgo = 2;
    }
    if (ac1>180){
        factor_riesgo = 5;
    }

    double puntaje_prioridad = (0.5*edad)+(0.3*imc)+(0.7*ac1)+(10*factor_riesgo);

    return puntaje_prioridad;
}

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
    nuevoPaciente->puntaje_prioridad = calcular_puntaje_prioridad(edad, (peso / (altura * altura)), ac1);
    head = nuevoPaciente;
}

void imprimir_pacientes(const Paciente* head)
{
    const Paciente* actual = head;
    int i = 1;
    while (actual != nullptr) {
        cout << "Paciente " << i << "\nNombre: " << actual->nombre << " Edad: " << actual->edad << " Altura: " << actual->altura << "m Peso: " << actual->peso << "kg IMC: " << actual->imc <<" Ac1: " << actual->ac1 << " Puntaje Prioridad: " << actual->puntaje_prioridad << "\n";
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

void imprimir_pacientes_imc(double rango_minimo, double rango_maximo, const Paciente* head, string mensaje){
    const Paciente* actual = head;
    int i = 0;
    while (actual != nullptr) {
        if (actual->imc >= rango_minimo && actual->imc < rango_maximo){
            cout << "Paciente " << i << "\nNombre: " << actual->nombre << " Edad: " << actual->edad << " Altura: " << actual->altura << "m Peso: " << actual->peso << "kg IMC: " << actual->imc <<" Ac1: " << actual->ac1 << "\n";
            i++;
        }
        actual = actual->siguiente;
    }
    cout << "\n\n Pacientes Totales con " << mensaje << " ~ " << i << " Pacientes";
}

void imprimir_pacientes_AC1(double rango_minimo, double rango_maximo, const Paciente* head, string mensaje){
    const Paciente* actual = head;
    int i = 0;
    while (actual != nullptr) {
        if (actual->ac1 >= rango_minimo && actual->ac1 < rango_maximo){
            cout << "Paciente " << i << "\nNombre: " << actual->nombre << " Edad: " << actual->edad << " Altura: " << actual->altura << "m Peso: " << actual->peso << "kg IMC: " << actual->imc <<" Ac1: " << actual->ac1 << "\n";
            i++;
        }
        actual = actual->siguiente;
    }
    cout << "\n\n Pacientes Totales con " << mensaje << " ~ " << i << " Pacientes";
}

void generar_lista_prioridad(const Paciente* head){
    //se van a recorrer a todos los pacientes y se generara una cola donde el primero sera el paciente con mas prioridad

    //calcular porcentaje de prioridad de todos los pacientes y almacenarlo en su atributo || hacer la cola y despues orrdenarla

    //persona1 -> calcular prioridad -> almecenarlo en la structura -> recorrer personas y segun los valores de prioridad encolarllos
}

int main()
{
    //puntero principal
    Paciente* head = nullptr;

    string ingreso_usuario;
    ingreso_usuario = "hola mundo";

    string ingreso_usuario_secundario;
    ingreso_usuario_secundario = "mundo hola";

    string ruta_ejemplo = "patient_list.csv";
    cout << "Nuevos Pacientes Cargados desde CSV\n\n";
    cargar_pacientes_desde_csv(head, ruta_ejemplo);
    imprimir_pacientes(head);

    while (ingreso_usuario != "salir")
    {
        cout << "Opciones de Ingreso:\n\n1~ Sobre IMC\n2~ Sobre AC1\n3~ Generar lista de prioridad\nsalir~ salir del programa\n\n>";
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
        3~ Generar lista de prioridad
        "salir"~ cerrar el programa*/

        //sobre IMC
        if (ingreso_usuario == "1") {
            cout << "   1~ imprimir bajopeso\n   2~ imprimir peso normal\n   3~ imprimir sobrepeso\n   4~ imprimir obesidad\n\n>";
            cin >> ingreso_usuario_secundario;

            // IMC -> bajo peso: x < 18.5; peso normal: 18.5 <= x < 25; sobrepeso: 25 <= x < 30; obesidad: x >= 30
            if (ingreso_usuario_secundario == "1"){
                cout << "\n\nSe imprimirán a los de bajo peso\n\n";
                // Rango de IMC: (0, 18.5)
                imprimir_pacientes_imc(0, 18.5, head, "Bajo Peso");
            }
            if (ingreso_usuario_secundario == "2"){
                cout << "\n\nSe imprimirán a los de peso normal\n\n";
                // Rango de IMC: [18.5, 24.9]
                imprimir_pacientes_imc(18.5, 25.0, head, "Peso Normal");
            }
            if (ingreso_usuario_secundario == "3"){
                cout << "\n\nSe imprimirán a los de sobrepeso\n\n";
                // Rango de IMC: [25, 29.9]
                imprimir_pacientes_imc(25.0, 30.0, head, "SobrePeso");
            }
            if (ingreso_usuario_secundario == "4"){
                cout << "\n\nSe imprimirán a los de obesidad\n\n";
                // Rango de IMC: [30, 100] (o un valor alto según tu criterio)
                imprimir_pacientes_imc(30.0, 100, head, "Obesidad");
            }
        }
        
        //sobre A1C
        if (ingreso_usuario == "2") {
            cout << "   1~ imprimir normal\n   2~ imprimir prediabetes\n   3~ imprimir Diabetes\n\n>";
            cin >> ingreso_usuario_secundario;
            //AC1 -> nomral 5,7 > x; prediabetes 5,7 <= x <= 6,5 ; diabetes 6,5 < x;
            if (ingreso_usuario_secundario == "1"){
                cout << "\n\nSe imprimiran a los de AC1 Normal\n\n";
                //(0,5.7)
                imprimir_pacientes_AC1(0.0, 5.7, head, "Normal");
            }
            if (ingreso_usuario_secundario == "2"){
                cout << "\n\nSe imprimiran a los de AC1 Prediabetes\n\n";
                //(5.7,6.5)
                imprimir_pacientes_AC1(5.7, 6.5, head, "Prediabetes");
            }
            if (ingreso_usuario_secundario == "3"){
                cout << "\n\nSe imprimiran a los de AC1 Diabetes\n\n";
                //(6.5,10)
                imprimir_pacientes_AC1(6.5, 10, head, "Diabetes");
            }
        }

        if (ingreso_usuario == "3") {
            cout << "\n\n~Generando lista de prioridad de pacientes~\n\n";
            //leer todos los pacientes y generar la lista
            generar_lista_prioridad(head);
        }

        if (ingreso_usuario == "salir") {
            cout << "\n\n A Salido Correctamente del Programa :)";
        }
            
    }
}