//23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80 y 64

#include <iostream>
using namespace std;

int mi_hash(int numero, int cantidad) {
    int index;

    index = numero % cantidad;

    return index;
}

void mostrar_arreglo(int *array, int espacios) {

    cout << "Arreglo Final\n";

    for(int i = 0; i < espacios; i++) {
        cout << "[" << i << "] = " << array[i] << "\n"; 
    }
}

int main() {
    cout << "Hola, Mundo" << endl;

    //numeros que despues tendran que ser aleatorios
    int mis_numeros_ejemplo[15] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};

    //espacios del arreglo ~ lo ingresa el usuario
    int espacios_totales = 15;

    int mi_array_para_ordenar[100]; //aki es donde se van a ordenar los arrays
    
    for(int i = 0; i < espacios_totales; i++) {
        mi_array_para_ordenar[i] = -1;
    }

    //hacer hash -> meter a un array con maximo de 100

    //hash
    for(int i = 0; i < espacios_totales; i++) {
        int index = mi_hash(mis_numeros_ejemplo[i], espacios_totales);
        cout << index << "\n";

        //como el array se inicializa en -1 para ver si esta vacio se ve si es que tiene algun numeor que es menor que 0
        if(mi_array_para_ordenar[index] < 0){
            //espacio disponible
            cout << "espacio disponiblle\n";
            mi_array_para_ordenar[index] = mis_numeros_ejemplo[i];
        }else{
            //existe colision
            cout << "existe colision hay que resolver\n";
            //resolver colicion
        }
    }

    mostrar_arreglo(mi_array_para_ordenar, espacios_totales);

    //si hay coliciones
    //• Reasignaci´on Prueba Lineal (L). 
    //• Reasignaci´on Prueba Cuadr´atica (C).
    //• Reasignaci´on Doble Direcci´on Hash (D). (Defina una segunda funci´on)

    //L -> recorrer todo para encontrar un lugar libre
    //C -> sumarle un i^2 y ver si hay espacio en la nueva posicion
    //D -> otra funcion que hace un hash (nose)
    return 0;
}
