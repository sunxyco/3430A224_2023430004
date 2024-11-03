//23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80 y 64
//Escriba un programa en C++ que permita el ingreso y la b´usqueda de informaci´on

#include <iostream>
using namespace std;

int mi_hash(int numero, int cantidad) {
    int index;

    index = numero % cantidad;

    return index;
}

int mi_segundo_hash(int numero, int cantidad) {
    int index;

    index = ((numero + 1) % cantidad);

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
    int contador_intentos = 0;

    while (v[index_comparacion] != -1) {
        i = i + 1;
        index_comparacion = d + (i * i);

        //indice fuera de rango
        if(index_comparacion >= n) {
            //index_comparacion = 0;
            index_comparacion = mi_hash(index_comparacion, n);
        }
        cout << "\n~ " << index_comparacion;

        contador_intentos = contador_intentos + 1;
        if(contador_intentos == 100) {
            cout << "muchos intentos para intentar introducir el dato, se opto por no introducirlo" << endl;
            return;
        }
    }

    if((v[index_comparacion] < 0) || (index_comparacion == d)){
        cout << "hay un espacio disponible en " << index_comparacion << endl;
        v[index_comparacion] = clave;
    } else {
        cout << "no hay espacios disponibles\n";
    }
}

void resolver_collision_doblehash(int *v, int n, int clave) {
    int d = mi_hash(clave, n);
    int index_comparacion = d;

    /*
    Mientras ((DX <= N) y (V[DX] <> VACIO) y (V[DX] <> K) y (DX <> D) Repetir
        Hacer DX <- H’(DX)*/
    while ((index_comparacion < n) && (v[index_comparacion] != -1) && (index_comparacion != d - 1)) {
        index_comparacion = mi_segundo_hash(index_comparacion, n);
        cout << "revisando " << index_comparacion << endl;
    }
    
    if((v[index_comparacion] < 0) || (index_comparacion == d)){
        cout << "hay un espacio disponible en " << index_comparacion << endl;
        v[index_comparacion] = clave;
    } else {
        cout << "no hay espacios disponibles\n";
    }
}


// Función para validar que la entrada del usuario sea un entero
int obtenerNumeroValido(const string& mensaje) {
    string ingreso_usuario;
    bool valid = false;
    int numero = 0;

    while (!valid) {
        cout << mensaje;
        cin >> ingreso_usuario;

        try {
            numero = stoi(ingreso_usuario);  // Intenta convertir la entrada a un entero
            valid = true;  // Si la conversión es exitosa, salimos del bucle
        } catch (const invalid_argument& e) {
            cout << "Entrada inválida, por favor ingresa un número entero válido.\n";
        } catch (const out_of_range& e) {
            cout << "Número fuera de rango, intenta de nuevo.\n";
        }
    }

    return numero;  // Devuelve el número entero validado
}

void obtener_array(int cantidad_numeros, int *array){

    cout << "los numeros que estaran en el arreglo";

    for(int i = 0; i < cantidad_numeros; i++){
        array[i] = obtenerNumeroValido("");
    }

    //return array;
}

void busqueda(int *v, int n, int clav) {
    int contador_posicion = 0;

    for(int i = 0; i < n + 1; i ++) {
        if( i == n) {
            cout << "la informacion no se encuentra en el arreglo " << endl;
            return;
        } 

        if(v[i] == clav) {
            cout << "la clave " << clav << " se encuentra en la posicon [" << contador_posicion << "]" << endl;
            return;
        }

        contador_posicion = contador_posicion + 1;
    }
}

int main(int argc, char **argv) {

    //se verifica que se entrego el metodo de solucion de colisiones
    if (argc < 1) {
        cerr << "Error: Debe proporcionar al menos un número como argumento." << endl;
        return 1;
    }

    string opcion_colisiones = "";
    opcion_colisiones = argv[1];

    if ((opcion_colisiones != "L") && opcion_colisiones != "C" && opcion_colisiones != "D"){
        cout << opcion_colisiones;
        cout << "porfavor ingresar parametro para resolver coliciones -> " << opcion_colisiones << " no se reconoce como metodo para resolver coliciones";
        return 1;
    }

    //cantidad de numeros en el arreglo
    int user_input_cantidad = 15;
    //int user_input_cantidad = obtenerNumeroValido("Ingrese el la cantidad de numeros que tendra el arreglo (max = 100)");

    //numeros que despues tendran que ser aleatorios
    int mis_numeros[15] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};

    /*int mis_numeros[100];
    obtener_array(user_input_cantidad, mis_numeros);*/


    int array_contienehash[100]; //aki es donde se van a ordenar los arrays
    for(int i = 0; i < user_input_cantidad; i++) {//se inicializan los espacios que se usaran
        array_contienehash[i] = -1;
    }

    //hash
    for(int i = 0; i < user_input_cantidad; i++) {
        int index = mi_hash(mis_numeros[i], user_input_cantidad);
        //cout << index << "\n";

        //como el array se inicializa en -1 para ver si esta vacio se ve si es que tiene algun numeor que es menor que 0
        cout << mis_numeros[i] << " ";
        if(array_contienehash[index] < 0){
            //espacio disponible
            cout << "espacio disponiblle\n";
            array_contienehash[index] = mis_numeros[i];
        }else{
            //existe colision
            cout << "existe colision en [" << index << "] hay que resolver ~\n";
            if (opcion_colisiones == "L") {
                resolver_colicion_lineal(array_contienehash, user_input_cantidad, mis_numeros[i]);
            }
            if (opcion_colisiones == "C") {
                resolver_colicion_cuadrado(array_contienehash, user_input_cantidad, mis_numeros[i]);
            }
            if (opcion_colisiones == "D") {
                resolver_collision_doblehash(array_contienehash, user_input_cantidad, mis_numeros[i]);
            }
        }
    }

    mostrar_arreglo(array_contienehash, user_input_cantidad);

    cout << "Buscar\n";

    int clave = 5;
    busqueda(array_contienehash, user_input_cantidad, clave);
    int clave2 = 23;
    busqueda(array_contienehash, user_input_cantidad, clave2);
    int clave3 = 47;
    busqueda(array_contienehash, user_input_cantidad, clave3);
    int clave4 = 28;
    busqueda(array_contienehash, user_input_cantidad, clave4);
    

    return 0;
}
