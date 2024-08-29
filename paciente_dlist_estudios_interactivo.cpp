/*Escriba un programa en C++ que permita trabajar con la gestión de pacientes a través
de opciones interactivas. Es de interés poder incorporar un menú que permita a un
usuario navegar por las opciones que existen y utilizar todas las funcionalidades
(funciones desarrolladas). Además se debe sumar la posibilidad de realizar la carga
de información desde un archivo de texto plano o CSV.
*/


//menu que permita utilizar todas las funciones desarrolladas
//cargar informacion desde un texto plano ~ csv

#include <iostream>
using namespace std;

int main()
{
    string ingreso_usuario;
    ingreso_usuario = "hola mundo";

    while (ingreso_usuario != "salir")
    {
        cout << "Hello, World!\n\n1~ Agregar Paciente\n2~ Eliminar Paciente\n3~ Imprimir Pacientes Actuales\n4~ Imprimir promedio de Edad\n4~ Imprimir promedio de Peso\n6~ Imprimir IMC pacientes\nsalir~ cerrar el programa\n\n~~";
        cin >> ingreso_usuario;

        cout << "\n\n\n~~" << ingreso_usuario;
    }
    
}