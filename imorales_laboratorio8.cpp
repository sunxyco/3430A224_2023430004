#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <chrono>//timepo
using namespace std;

//se generan dos arreglos iguales
void llenarArreglo(int **arr, int size) {
    // Llenar el arreglo con numeros aleatorios entre 1 y size
    for (int i = 0; i < size; ++i) {
        int numero = rand() % size + 1;
        arr[0][i] = numero; // Genera un numero entre 1 y size
        arr[1][i] = numero;
    }
}

void mostrarArreglo(int **arr, int size) {
    // Mostrar los valores del arreglo
    for (int i = 0; i < 2; ++i) {
        cout << "Fila " << i << "> ";
        for (int j = 0; j < size; j++) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << endl;
}

//selection
int selection(int *arr, int n) {
    int i;
    int menor;
    int k;

    for (int i = 0; i < n - 1; i++) {
        menor = arr[i];
        k = i;

        for (int j = i+1; j < n; j++) {
            if (arr[j] < menor) {
                menor = arr[j];
                k = j;
            }
        }
        arr[k] = arr[i];
        arr[i] = menor;
    }

    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//quicksort
//intercambia los valores de los punteros
void intercambio(int* a, int* b)
{
    int temporal = *a;
    *a = *b;
    *b = temporal;
}

int particion(int arr[], int indice_izquierda, int indice_derecha)
{
    //como pivote se toma al elemento de mas a la derecha
    int pivote = arr[indice_derecha];
    int i = (indice_izquierda - 1);

    //se recorren todos los elementos de el arrglo y se comparan con el pivote
    for (int j = indice_izquierda; j <= indice_derecha- 1; j++)
    {
        if (arr[j] <= pivote)
        {
            i++;
            intercambio(&arr[i], &arr[j]);
        }
    }
    intercambio(&arr[i + 1], &arr[indice_derecha]);
    return (i + 1);
}

//funcion de ordenamiento recursiva donde los subarreglos son cada vez mas pequeños
void quick_sort(int arr[], int indice_izquierda, int indice_derecha)
{
    if (indice_izquierda < indice_derecha)
    {
        int pivote = particion(arr, indice_izquierda, indice_derecha);

        quick_sort(arr, indice_izquierda, pivote - 1);
        quick_sort(arr, pivote + 1, indice_derecha);
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//se ordenan los arreglo, se calcula y se imprime cuanto tiempo se demoro en ordenarse
void ordenamiento(int **arr, int size) {
    cout << "ordenando fila 1 ~ selection sort > ";
    auto start = chrono::high_resolution_clock::now();
    selection(arr[0], size);
    auto end = chrono::high_resolution_clock::now();
    //calcularduracion
    chrono::duration<double> variable1 = (end - start);
    //cout << " duracion> " << to_string(variable1) << "x";
    cout << "Tiempo de ejecucion: " << (variable1.count())*1000 << " milisegundos" << endl;


    cout << "ordenando fila 2 ~ quick sort";
    auto start1 = chrono::high_resolution_clock::now();
    quick_sort(arr[1], 0, size - 1);
    auto end2 = chrono::high_resolution_clock::now();
    //calcularduracion
    chrono::duration<double> variable2 = (end2 - start1);
    cout << "Tiempo de ejecucion: " << (variable2.count())*1000 << " milisegundos\n" << endl;
}

//se toman dos parametros al ejecutar el programa
int main(int argc, char **argv) {

    //se verifica que se entrego el parametro de tamaño de los arreglos
    if (argc < 2) {
        cerr << "Error: Debe proporcionar al menos un número como argumento." << endl;
        return 1;
    }

    int n = atoi(argv[1]);

    string mostrar = "";

    //se verifica que se entrego el parametro para mostrar los arreglos
    if (argc >= 3) {
        mostrar = argv[2];
    } else {
        cout << "No se ingreso segundo parametro, por lo que no se mostraran los arreglos\n";
    }

    //si se ingresa el segundo parametro "x" se coloca true y se imprimiran los arreglos
    bool bandera_imprimir = false;
    if (mostrar == "x" || mostrar == "X") {
        bandera_imprimir = true;
    }

    //se inicializan los dos arrelgos vacios
    int **arr = new int*[2];
    //se inicializa el arreglo
    for (int i = 0; i < 2; i++) {
        arr[i] = new int[n];
    }


    // Inicializa la semilla para numeros aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // seleccion
    llenarArreglo(arr, n);

    if (bandera_imprimir) {
        cout << "Arreglo de numeros enteros:\n";
        mostrarArreglo(arr, n);
    }

    //se ordenan los dos arreglos
    ordenamiento(arr, n);

    if (bandera_imprimir) {
        cout << "Arreglo de numeros ordenados:\n";
        mostrarArreglo(arr, n);
    }
   
    return 0;
}