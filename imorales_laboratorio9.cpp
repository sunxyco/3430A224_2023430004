#include <iostream>
using namespace std;
#include <cstdlib> // Para rand() y srand()


//hash normal
int mi_hash(int numero, int cantidad) {
    int index;

    index = numero % cantidad;

    return index;
}

//para el metodo de doble hash
int mi_segundo_hash(int numero, int cantidad) {
    int index;

    index = (((numero + 1) % cantidad) + 1);

    if(index >= cantidad) {
        index = 0;
    }

    return index;
}

//funcion para mostrar el arreglo donde se guardan los datos

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
        cout << "revisando~ [" << index_comparacion << "]";
    }

    if((v[index_comparacion] < 0) || (index_comparacion == d)){
        cout << "hay un espacio disponible en " << index_comparacion << endl;
        v[index_comparacion] = clave;
    } else {
        cout << "no hay espacios disponibles\n";
    }
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
            index_comparacion = mi_hash(index_comparacion, n);
        }
        cout << "\nrevisando~ [" << index_comparacion << "]";

        contador_intentos = contador_intentos + 1;
        if(contador_intentos == 100) {
            cout << "muchos intentos para intentar introducir el dato, se opto por no introducirlo" << endl;
            return;
        }
    }

    if((v[index_comparacion] < 0) || (index_comparacion == d)){
        cout << "hay un espacio disponible en [" << index_comparacion << "]" << endl;
        v[index_comparacion] = clave;
    } else {
        cout << "no hay espacios disponibles\n";
    }
}

void resolver_collision_doblehash(int *v, int n, int clave) {
    int d = mi_hash(clave, n);
    int index_comparacion = d;

    while ((index_comparacion < n) && (v[index_comparacion] != -1)) {
        index_comparacion = mi_segundo_hash(index_comparacion, n);
        cout << "revisando [" << index_comparacion << "]" << endl;
    }
    
    if((v[index_comparacion] < 0) || (index_comparacion == d)){
        cout << "hay un espacio disponible en [" << index_comparacion << "]" << endl;
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

void obtener_array_aleatorio(int cantidad_numeros, int *array){

    cout << "los numeros que estaran en el arreglo \n[";
    for (int i = 0; i < cantidad_numeros; ++i) {
        array[i] = rand() % 100 + 1; // Genera un numero entre 1 y 100
        cout << array[i] << ", ";
    }
    cout << "]\n\n";
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

    // Inicializa la semilla para numeros aleatorios
    srand(static_cast<unsigned int>(time(0)));
    // ------------------------------------------

    //cantidad de numeros en el arreglo
    int user_input_cantidad = obtenerNumeroValido("Ingrese el la cantidad de numeros que tendra el arreglo (max = 100)\n> ");

    int mis_numeros[100];
    obtener_array_aleatorio(user_input_cantidad, mis_numeros);//se llena el array con numeros aleatorios

    int array_contienehash[100]; //aqui es donde se van a ordenar los arrays
    for(int i = 0; i < user_input_cantidad; i++) {//se inicializan los espacios que se usaran
        array_contienehash[i] = -1;
    }

    //hash
    for(int i = 0; i < user_input_cantidad; i++) {
        int index = mi_hash(mis_numeros[i], user_input_cantidad);
        //como el array se inicializa en -1 para ver si esta vacio se ve si es que tiene algun numeor que es menor que 0
        cout << mis_numeros[i] << " ";
        if(array_contienehash[index] < 0){
            //espacio disponible
            cout << "Hash -> [" << index << "] espacio disponiblle\n";
            array_contienehash[index] = mis_numeros[i];
        }else{
            //existe colision
            cout << "Hash -> [" << index << "] existe colision\n";
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

    cout << "Buscar (ingrese numero negativo para salir)\n";
    bool buscar = true;

    while(buscar) {
        int clave = obtenerNumeroValido("Ingrese numero a buscar\n> ");
        if(clave > 0){
            busqueda(array_contienehash, user_input_cantidad, clave);
        } else {
            cout << "Saliendo...";
            buscar = false;
            break;
        }
    }
    return 0;
}
