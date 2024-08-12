#include <iostream>

/*
● Lea desde la entrada estándar: Leer un número y almacenarlo en una variable. ~ si
● Imprima en la salida estándar: Imprimir el número ingresado en la salida     ~ si
estándar.
● Crear una función: Crear una función que determine si el número es para o no. ~ si
○ Usar la función: Se debe utilizar la función con el número ingresado por el   ~ si
usuario y también para todos los números del 1 al 10.
● Crear una función: Crear una función que determine la longitud de un string.      ~crear funcion
○ Usar la función: Se debe solicitar al usuario ingresar un “string” utilizar la    ~solicitar al usuario un string y
función para entregar la longitud además se debe utilizar también para               usar string almacenado en codigo
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

void imprimir_par_impar(int numero)
{

    bool residuo = par(numero);

    //segun el bool de la funcion anterior se imprime el mensaje si es par  o impar
    if (residuo)
    {
        std::cout << numero << " ~par\n";
    } else
    {
        std::cout << numero << " ~impar\n";
    }
}

int longitud(std::string cadena_de_texto)
{
    int longitud = 0;
    //procesamiento de la cadena de texto

    //arreglar bucle
    /*
    for char in cadena_de_texto;
        longitud = longitud + 1

    return longitud_de_la_cadena
    */
}

int main()
{
    std::cout << "Ingrese un numero\n";

    //se define la varible vacia
    int user_input = 0;

    //se llama a std::cin para que lea la linea, el usuario ingresa un numero
    //luego el numero ingresado se guarda en la variable
    std::cin >> user_input;

    //se imprime el numero ingresado
    std::cout << "\nnumero ingresado por el usuario ~" << user_input << "~\n\n";


    std::cout << "numeros del 1 al 10\n";

    //true si es par ~ false si es impar   
    imprimir_par_impar(1);
    imprimir_par_impar(2);
    imprimir_par_impar(2);
    imprimir_par_impar(3);
    imprimir_par_impar(4);
    imprimir_par_impar(5);
    imprimir_par_impar(6);
    imprimir_par_impar(7);
    imprimir_par_impar(8);
    imprimir_par_impar(9);
    imprimir_par_impar(10);
    imprimir_par_impar(user_input);

    //funcion leer string ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    std::string mi_cadena = "Hola Mundo";
    std::cout << "Cadena de ejemplo --> ""(Hola Mundo)""\n";

    //longitud_cadena = longitud(mi_cadena);


    /*
    //ambas funciones devuelven el mismo numero
    int longitud1 = mi_cadena.size();
    std::cout << "El tamaño de la cadena es de " << longitud1 << " caracteres (.size())\n\n";

    int longitud2 = mi_cadena.length();
    std::cout << "El tamaño de la cadena es de " << longitud2 << " caracteres (.length())";*/

    return 0;

}