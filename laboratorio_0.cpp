#include <iostream>
#include <string>
//using namespace se uso para que el codigo fuera mas legible
using namespace std;

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
void longitud(string cadena_de_texto)
{
    //en c++ los string tambien funcionan como arrays hmm
    int longitud = 0;
    //for (inicialización; condición; actualización)
    //se itera hasta que llegue a \0 -> final de la cadena
    for (int i = 0; cadena_de_texto[i] != '\0'; i = i + 1)
    {
        //se sumara 1 a la longitud por cada caracter en la cadena
        longitud = longitud + 1;
    }
    cout << "longitud: " << longitud << " caracteres ~ Cadena: " << cadena_de_texto << "\n";
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
    contar_numeros_1_10();

    cout << "Numero del usuario\n>";
    imprimir_par_impar(user_input);

    //funcion leer cadena ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    string mi_cadena = "Hola Mundo";
    string mi_cadena_usuario;
    
    cout << "\ningrese una cadena de texto\n>";

    //↓↓ se pusó dos veces el .getline ya que en el primero se toma el "\n" como un caracter valido y continua la execucion sin pedirle
    //al usuario realmente la cadena de texto, en la segunda ahora si se le pide al usuario que ingrese una cadena de texto
    getline(cin, mi_cadena_usuario);
    //en la ejecucion se ve como si solo existiera un solo getline
    getline(cin, mi_cadena_usuario);

    cout << "\nCadena almacenada en codigo > " << mi_cadena << "\n";
    cout << "Cadena del usuario          > " << mi_cadena_usuario << "\n\n";
    
    /*//ambas funciones devuelven el mismo numero
    podria haber usado estas funciones para saber el largo de la cadena, 
    pero se opto por hacer una funcion propia
    int longitud1 = mi_cadena.size();
    int longitud2 = mi_cadena.length();*/

    longitud(mi_cadena);
    longitud(mi_cadena_usuario);
    return 0;
}