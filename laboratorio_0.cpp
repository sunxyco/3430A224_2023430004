#include <iostream>
#include <string>
using namespace std;

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
        cout << "nose que hiciste para que salga estó";
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
        cout << numero << " ~par\n";
    } else
    {
        cout << numero << " ~impar\n";
    }
}

//la funcion cuenta todos los espacios que tenga una cadena de texto
int longitud(string cadena_de_texto)
{
    //procesamiento de la cadena de texto


    //en c++ los string tambien funcionan como arrays hmm
    int longitud = 0;
    //for (inicialización; condición; actualización)
    //se iterara cada caracter mientras que el caracter no sea \0 que es el final de la cadena
    for (int i = 0; cadena_de_texto[i] != '\0'; i = i + 1)
    {
        //se sumara 1 a la longitud por cada caracter en la cadena
        longitud = longitud + 1;
    }

    return longitud;
    
}

void contar_numeros_1_10()
{
    //for (inicialización; condición; actualización)
    for (int i = 1; i <= 10; i = i+1)
    {
        imprimir_par_impar(i);
    }
}

int main()
{
    cout << "Ingrese un numero\n>";

    //se define la varible vacia
    int user_input = 0;

    //se llama a cin para que lea la linea, el usuario ingresa un numero
    //luego el numero ingresado se guarda en la variable
    cin >> user_input;

    

    //se imprime el numero ingresado
    cout << "\nnumero ingresado por el usuario ~" << user_input << "~\n\n";


    cout << "numeros del 1 al 10\n";

    //implementar for (hecho)
    contar_numeros_1_10();

    imprimir_par_impar(user_input);

    //funcion leer cadena ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    string mi_cadena = "Hola Mundo";
    string mi_cadena_usuario;

    /* aver vamos a intentar almacenar la variable en una ::string
    //se pide la cadena sin espacios porque si se toma un espacio la variable guarda la cadena hasta el espacio
    //escribe ~ "Hola Mundo", se guarda ~ "Hola"
    cout << "\n\nCadena almacenada en el codigo --> " << mi_cadena << "\n\nIngrese una cadena de texto\nSIN ESPACIOS\n";
    */

    cout << "ingrese una cadena de texto\n>";

    //↓↓ se pusó dos veces el .getline ya que en el primero se toma el "\n" como un caracter valido y continua la execucion sin pedirle
    //al usuario realmente la cadena de texto, en la segunda ahora si se le pide al usuario que ingrese una cadena de texto
    getline(cin, mi_cadena_usuario);
    //en la ejecucion se ve como si solo existiera un solo getline
    getline(cin, mi_cadena_usuario);

    //se guarda la cadena que ingrese el usuario
    //string user_input_cadena = "0";
    //cin >> user_input_cadena;
    //(borrar)

    cout << "\n\nCadena del usuario --> " << mi_cadena_usuario << "\n";
    
    /*//ambas funciones devuelven el mismo numero ~ podria haber usado estas funciones para saber el largo de la cadena, pero se opto por hacer una funcion propia
    int longitud1 = mi_cadena.size();
    cout << "El tamaño de la cadena es de " << longitud1 << " caracteres (.size())\n\n";
    int longitud2 = mi_cadena.length();
    cout << "El tamaño de la cadena es de " << longitud2 << " caracteres (.length())";*/

    int longitud_cadena1 = longitud(mi_cadena);
    int longitud_cadena2 = longitud(mi_cadena_usuario);

    cout << "\n\nlongitud: " << longitud_cadena1 << "caracteres ~ Cadena: " << mi_cadena << "\n";
    cout << "\nlongitud: " << longitud_cadena2 << "caracteres ~ Cadena: " << mi_cadena_usuario << "\n";

    return 0;
}