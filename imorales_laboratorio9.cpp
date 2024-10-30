//23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80 y 64

#include <iostream>
using namespace std;

int mi_hash(int numero, int cantidad) {
    int index;

    int index = numero % cantidad;

    return index;
}

int main() {
    cout << "Hola, Mundo!" << endl;

    int mis_numeros_ejemplo[15] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};
    int espacios_necesarios = 15;

    int mi_array_para_ordenar[100]; //aki es donde se van a ordenar los arrays

    //hacer hash -> meter a un array con maximo de 100

    int test = 15 % 10;

    cout << test;

    //si hay coliciones
    //• Reasignaci´on Prueba Lineal (L). 
    //• Reasignaci´on Prueba Cuadr´atica (C).
    //• Reasignaci´on Doble Direcci´on Hash (D). (Defina una segunda funci´on)

    //L -> recorrer todo para encontrar un lugar libre
    //C -> sumarle un i^2 y ver si hay espacio en la nueva posicion
    //D -> otra funcion que hace un hash (nose)



    return 0;
}
