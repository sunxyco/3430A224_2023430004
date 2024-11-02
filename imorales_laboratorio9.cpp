//23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80 y 64
//Escriba un programa en C++ que permita el ingreso y la b´usqueda de informaci´on

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

void resolver_colicion_lineal(int *v, int n, int clave) {
    int d = mi_hash(clave, n);
    int index_comparacion = d;

    while ((index_comparacion <= n) && (v[index_comparacion] != -1) && (index_comparacion != d - 1)) {        
        index_comparacion = index_comparacion + 1;

        if(index_comparacion >= n) {
            index_comparacion = 0;
        }
        cout << "\n~ " << index_comparacion;
    }

    if((v[index_comparacion] < 0) || (index_comparacion == d)){
        cout << "hay un espacio disponible en " << index_comparacion << endl;
        v[index_comparacion] = clave;
    } else {
        cout << "no hay espacios disponibles\n";
    }

    //return index_comparacion;
}

void resolver_colicion_cuadrado(int *v, int n, int clave) {
    int d = mi_hash(clave, n);
    int index_comparacion = d;
    int i = 0;

    while ((index_comparacion <= n) && (v[index_comparacion] != -1) && (index_comparacion != d - 1)) {        
        i = i + 1;
        index_comparacion = d + (i * i);

        //estudiar que pasa si el indice de comparacion es mas grande que el n (se me quedaron los apuntes en la casa x)
        if(index_comparacion >= n) {
            index_comparacion = 0;
            i = 0;
            d = 0;
        }

        cout << "\n~ " << index_comparacion;
    }

    if((v[index_comparacion] < 0) || (index_comparacion == d)){
        cout << "hay un espacio disponible en " << index_comparacion << endl;
        v[index_comparacion] = clave;
    } else {
        cout << "no hay espacios disponibles\n";
    }
}

int main() {
    cout << "Hola, Mundo" << endl;

    //numeros que despues tendran que ser aleatorios
    int mis_numeros_ejemplo[15] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};

    //espacios del arreglo ~ lo ingresa el usuario
    int espacios_totales = 15;

    int mi_array_para_ordenar[100]; //aki es donde se van a ordenar los arrays
    
    for(int i = 0; i < espacios_totales; i++) { //se inicializan los espacios que se usaran
        mi_array_para_ordenar[i] = -1;
    }

    //hacer hash -> meter a un array con maximo de 100

    //hash
    for(int i = 0; i < espacios_totales; i++) {
        int index = mi_hash(mis_numeros_ejemplo[i], espacios_totales);
        //cout << index << "\n";

        //como el array se inicializa en -1 para ver si esta vacio se ve si es que tiene algun numeor que es menor que 0
        cout << mis_numeros_ejemplo[i] << " ";
        if(mi_array_para_ordenar[index] < 0){
            //espacio disponible
            cout << "espacio disponiblle\n";
            mi_array_para_ordenar[index] = mis_numeros_ejemplo[i];
        }else{
            //existe colision
            cout << "existe colision hay que resolver\n";
            //resolver_colicion_lineal(mi_array_para_ordenar, espacios_totales, mis_numeros_ejemplo[i]);
            resolver_colicion_cuadrado(mi_array_para_ordenar, espacios_totales, mis_numeros_ejemplo[i]);
        }
    }

    mostrar_arreglo(mi_array_para_ordenar, espacios_totales);

    //busqueda_linead(mi_array_para_ordenar, espacios_totales, 66);

    //si hay coliciones
    //• Reasignaci´on Prueba Lineal (L). 
    //• Reasignaci´on Prueba Cuadr´atica (C).
    //• Reasignaci´on Doble Direcci´on Hash (D). (Defina una segunda funci´on)

    //L -> recorrer todo para encontrar un lugar libre
    //C -> sumarle un i^2 y ver si hay espacio en la nueva posicion
    //D -> otra funcion que hace un hash (nose)
    return 0;
}
