#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//estructura paciente, el atributo sig_diab solo se usara para generar conexiones entre pacientes diabeticos prioritarios
struct Paciente
{
    string nombre;
    int edad;
    double altura;
    int peso;
    double imc;
    double ac1;
    double puntaje_prioridad;
    Paciente* sig_diab;

    Paciente* siguiente;
};


// Variable global para la cabeza de la lista de prioridades de diabéticos
Paciente* cabeza_prioridad = nullptr;

//se cuentan a las personas actuales en la lista de espera de atencion diabetica
void contarPacientes(const Paciente* punto_inicio_lista_diabeticos) {

    if (punto_inicio_lista_diabeticos == nullptr) {
        cout << "\n\nNo hay pacientes en la lista de espera\n\n";
    }

    const Paciente* contador = punto_inicio_lista_diabeticos;

    int i = 0;
    while (contador != nullptr) {
        i = i + 1;
        contador = contador->sig_diab;
    }

    cout << "\n\nActualmente hay " << i << " Pacientes en la lista de espera\n\n";
}

// Imprimir a la gente de la cola de atencion diabetica
void printColaDiabetin(const Paciente* head) {
    const Paciente* temp = head;

    if (temp == nullptr) {
        cout << "\n\nNo hay pacientes actualmentes en la Cola de Atencion de Personas Diabeticas";
        return;
    }

    while (temp != nullptr) {
        cout << "Nombre: " << temp->nombre << "Edad: " << temp->edad << " imc: " << temp->imc << " Paciente con Ac1: " << temp->ac1 << " y Puntaje de Prioridad: " << temp->puntaje_prioridad << "\n";
        temp = temp->sig_diab;
    }

    cout << "\n\n>Cola de Atencion Impresa Correctamente\n\n";
}

// Funcion para desencolar pacientes
void desencolarPaciente(int pacientes_atendidos, Paciente*& punto_inicio_lista_diabeticos) {

    if(punto_inicio_lista_diabeticos == nullptr) {
        return;
    }

    for (int i = 0; i < pacientes_atendidos && punto_inicio_lista_diabeticos != nullptr; ++i) {
        Paciente* temporal = punto_inicio_lista_diabeticos;  // Guardamos el nodo actual
        punto_inicio_lista_diabeticos = punto_inicio_lista_diabeticos->sig_diab;  // Avanzamos al siguiente
        delete temporal;  // Eliminamos el nodo anterior
    }

    cout << "\n\n>A la cola se le desencolarón " << pacientes_atendidos << " Pacientes Diabeticos\n\n";
    //printColaDiabetin(punto_inicio_lista_diabeticos);
}

// Funcion vaciar cola
void vaciarListaPrioridad(Paciente* inicio_lista_prioridad) {

    while (inicio_lista_prioridad != nullptr) {
        desencolarPaciente(1, inicio_lista_prioridad);
    }

    //printColaDiabetin(inicio_lista_prioridad);

    cout << "\n\n¡Cola de atencion Vaciada Con Exito!\n\n";
}

// Función para insertar un paciente en la lista ordenada por puntaje de prioridad
void insertarOrdenado(Paciente* diabetin) {
    if (cabeza_prioridad == nullptr || diabetin->puntaje_prioridad > cabeza_prioridad->puntaje_prioridad) {
        diabetin->sig_diab = cabeza_prioridad; // Conectar con el siguiente en la lista ordenada
        cabeza_prioridad = diabetin; // Insertar diabetin en la cabeza de la lista ordenada
    } else {
        Paciente* actual = cabeza_prioridad;
        while (actual->sig_diab != nullptr && actual->sig_diab->puntaje_prioridad >= diabetin->puntaje_prioridad) {
            actual = actual->sig_diab;
        }
        diabetin->sig_diab = actual->sig_diab; // Conectar con el siguiente en la lista ordenada
        actual->sig_diab = diabetin; // Insertar diabetin en la lista ordenada
    }
}

// Función para generar la lista de prioridad de diabéticos ~ solo se agregan a la cola los pacientes que tenga un nivel alto de AC1
void generar_lista_prioridad(Paciente* head) {
    // Recorrer todos los pacientes y añadirlos a la lista de prioridades
    Paciente* actual = head;

    while (actual != nullptr) {
        if (actual->puntaje_prioridad > 0) {
            // Insertar paciente en la lista de prioridades
            insertarOrdenado(actual);
        }
        actual = actual->siguiente;
    }

    cout << "\n\n~Cola de pacientes Diabeticos Generada con Exito~\n\n";
}

//para calcular el puntade de prioridad
double calcular_puntaje_prioridad(int edad, double imc, double ac1){
    
    //si la persona tiene un buen imc y un nivel adecuado de AC1 este no tiene prioridad
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
    if (ac1 > 5.7){
        factor_riesgo = 3;
    }
    if (ac1 > 6.5){
        factor_riesgo = 4;
    }

    double puntaje_prioridad = (0.5*edad)+(1.0*imc)+(1.5*ac1)+(10*factor_riesgo);

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

//se imprimen a todos los pacinetes actuales
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

//Apenas arranca el programa este carga a los pacientes desde el csv
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

    cout << "\n\nPacientes Cargados Exitosamente desde CSV\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

//se imprime a los pacientes segun el rango de su IMC
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

//se imprime a los pacientes segun el rango de su AC1
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

int main()
{
    //puntero principal
    Paciente* head = nullptr;

    string ingreso_usuario;
    ingreso_usuario = "hola mundo";

    string ingreso_usuario_secundario;
    ingreso_usuario_secundario = "mundo hola";

    string ingreso_terciario;
    ingreso_terciario = "oal undo";

    string ruta_ejemplo = "patient_list.csv";
    cout << "Cargando pacientes desde CSV\n";
    cargar_pacientes_desde_csv(head, ruta_ejemplo);

    while (ingreso_usuario != "salir")
    {
        cout << "Opciones de Ingreso:\n\n0~ Imprimir Todos los Pacientes Actuales\n1~ Sobre IMC\n2~ Sobre AC1\n3~ Sobre Pacientes Diabeticos\nsalir~ salir del programa\n\n>";
        cin >> ingreso_usuario;
        /* boseto del menú
        0~ Imprimir todos los pacientes actuales
        1~ Sobre IMC
                1.1 Imprimir bajopeso
                1.2 imprimir peso normal
                1.3 Imprimir sobrepeso
                1.4 imprimir obesidad
        2~ Sobre AC1
                2.1 imprimir normal
                2.2 imprimir prediabetes
                2.3 imprimir diabetes
        3~ Sobre Pacientes Diabeticos
                3.1 Generar lista de prioridad
                3.2 Imprimir lista de prioridad actual
                3.3 Desencolar pacientes que ya fueron atendidos
                3.4 Vaciar lista de espera
                3.5 Contar personas en la lista de espera

        "salir"~ cerrar el programa*/

        if (ingreso_usuario == "0") {
            cout << "\nImprimiendo Pacientes\n";
            imprimir_pacientes(head);
        }

        //sobre IMC ~ se imprime a los pacientes segun su IMC
        if (ingreso_usuario == "1") {
            cout << "   1~ imprimir bajopeso\n   2~ imprimir peso normal\n   3~ imprimir sobrepeso\n   4~ imprimir obesidad\n\n>";
            cin >> ingreso_usuario_secundario;
            // IMC -> bajo peso: x < 18.5; peso normal: 18.5 <= x < 25; sobrepeso: 25 <= x < 30; obesidad: x >= 30
            if (ingreso_usuario_secundario == "1"){
                cout << "\n\nSe imprimirán a los de bajo peso\n\n";
                // Rango de IMC: (0, 18.5)
                imprimir_pacientes_imc(0, 18.5, head, "Bajo Peso");}
            if (ingreso_usuario_secundario == "2"){
                cout << "\n\nSe imprimirán a los de peso normal\n\n";
                // Rango de IMC: [18.5, 24.9]
                imprimir_pacientes_imc(18.5, 25.0, head, "Peso Normal");}
            if (ingreso_usuario_secundario == "3"){
                cout << "\n\nSe imprimirán a los de sobrepeso\n\n";
                // Rango de IMC: [25, 29.9]
                imprimir_pacientes_imc(25.0, 30.0, head, "SobrePeso");}
            if (ingreso_usuario_secundario == "4"){
                cout << "\n\nSe imprimirán a los de obesidad\n\n";
                // Rango de IMC: [30, 100] (o un valor alto según tu criterio)
                imprimir_pacientes_imc(30.0, 100, head, "Obesidad");}
        }
        
        //sobre A1C ~ se imprime el los pacienetes segun el rango de su AC1
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
            cout << "   1~ Generar Cola de prioridad\n   2~ Imprimir Cola de prioridad actual\n   3~ Desencolar pacientes que ya fueron atendidos\n   4~ Vaciar Cola de espera\n   5~ Contar personas en la Cola de espera\n\n>";
            cin >> ingreso_usuario_secundario;

            //se genera la cola de Priorirdad
            if (ingreso_usuario_secundario == "1") {
                cout << "\n\n~Generando Cola de prioridad de pacientes~\n\n";
                //leer todos los pacientes y generar la lista
                generar_lista_prioridad(head);
                //imprimir_lista_prioridad(head);
                //printColaDiabetin(cabeza_prioridad);
                //cout << "\n\n";
                }

            //imprime la cola de personas en la lista de prioridad diabeticas
            if (ingreso_usuario_secundario == "2") {
                cout << "\n\n~~Imprimiendo cola de prioridad actual~~\n\n";
                printColaDiabetin(cabeza_prioridad);}

            //se desencolan X pacientes
            if (ingreso_usuario_secundario == "3") {
                cout << "\n~Cuantos pacientes fueron atendidos?\n\n>";
                cin >> ingreso_terciario;
                cout << "\n\n~Atendiendo pacientes~~\n\n";
                int ingreso_terciario_numero = stoi(ingreso_terciario);
                desencolarPaciente(ingreso_terciario_numero, cabeza_prioridad);}

            //se vacia la cola de atencion
            if (ingreso_usuario_secundario == "4") {
                cout << "\n\nVaciando Cola de Atencion";
                vaciarListaPrioridad(cabeza_prioridad);}

            //se cuentan los pacientes actuales en la cola
            if (ingreso_usuario_secundario == "5") {
                cout << "\n\nContando Pacientes";
                contarPacientes(cabeza_prioridad);}

        //se sale del programa
        if (ingreso_usuario == "salir") {
            cout << "\n\n A Salido Correctamente del Programa :)";
        }
            
    }
}
}
