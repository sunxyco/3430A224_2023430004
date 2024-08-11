#include <iostream>

/*
● Lea desde la entrada estándar: Leer un número y almacenarlo en una variable.
● Imprima en la salida estándar: Imprimir el número ingresado en la salida
estándar.
● Crear una función: Crear una función que determine si el número es para o no.
○ Usar la función: Se debe utilizar la función con el número ingresado por el
usuario y también para todos los números del 1 al 10.
● Crear una función: Crear una función que determine la longitud de un string.
○ Usar la función: Se debe solicitar al usuario ingresar un “string” utilizar la
función para entregar la longitud además se debe utilizar también para
un string almacenado en una variable directamente en el código*/

bool par(int numero)
{
    int residuo = numero % 2;

    //apartir de el ejemplo de bool presente en la documentacion se hizo la siguiente funcion
    switch (residuo) {
    case 0:
        return true;
    case 1:
        return false;
    default:
        std::cout << "nose que hiciste para que salga estó";
        return false;
    } 

    //se retorna un bool dependiendo de si hay o no residuo al dividir el numero
    return residuo;
}

int main()
{
    std::cout << "Ingrese un numero";

    //se define la varible vacia
    int user_input = 0;

    //se llama a std::cin para que lea la linea, el usuario ingresa un numero
    //luego el numero ingresado se guarda en la variable
    std::cin >> user_input;

    //se imprime el numero ingresado
    std::cout << "~ " << user_input;

    //el operador % se utiliza para conocer el residuo de una division (borrar linea)
    int numer2 = user_input % 2 ;
    std::cout << "~ " << numer2 << "\n";

    //true si es par ~ false si es impar
    bool residuo = par(user_input);

    //segun el bool de la funcion anterior se imprime el mensaje si es par  o impar
    if (residuo)
    {
        std::cout << "par";
    } else
    {
        std::cout << "impar";
    }

    return 0;

}