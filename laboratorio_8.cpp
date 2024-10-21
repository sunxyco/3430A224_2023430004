#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <chrono>//timepo
using namespace std;

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
    //int limite = n;
    int i;
    int menor;
    int k;
    //int j;

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
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);

        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                
void ordenamiento(int **arr, int size) {
    cout << "ordenando fila 1 ~ selection sort > ";
    auto start = chrono::high_resolution_clock::now();
    selection(arr[0], size);
    auto end = chrono::high_resolution_clock::now();
    //calcularduracion
    chrono::duration<double> variable1 = (end - start);

    //cout << " duracion> " << to_string(variable1) << "x";
    cout << "Tiempo de ejecucion:" << (variable1.count())*1000 << " milisegundos" << endl;


    cout << "ordenando fila 2 ~ quick sort";
    auto start1 = chrono::high_resolution_clock::now();
    quick_sort(arr[1], 0, size - 1);
    auto end2 = chrono::high_resolution_clock::now();
    //calcularduracion
    chrono::duration<double> variable2 = (end2 - start1);
    cout << "Tiempo de ejecucion:" << (variable2.count())*1000 << " milisegundos\n" << endl;

}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);

    //int **arr;

    int **arr = new int*[2];
    //se inicializa el arreglo
    for (int i = 0; i < 2; i++) {
        arr[i] = new int[n];
    }
    //int arr[2][n];
    //int n = N;

    // Inicializa la semilla para numeros aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // seleccion
    llenarArreglo(arr, n);

    cout << "Arreglo de numeros enteros:\n";
    mostrarArreglo(arr, n);

    //implementar selection~quick_sort
    ordenamiento(arr, n);

    mostrarArreglo(arr, n);

    return 0;
}