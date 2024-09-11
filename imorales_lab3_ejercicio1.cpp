#include <iostream>
#include <string>

struct Pila{
    int maximo;
    int tope;
    int mi_array[maximo];
    bool band_vacio;
    bool band_lleno;
};

void crear_pila(int max){
    //crear array con un numeor {maximo} de espacios
}

void push(int dato){
    //añadir al array
}

void pop(int dato){
    //recorrer el array y remover el dato - reposicionar los demas datos
}

//chequea si la pila está vacia - ve si el ultimo elemento agregado esta en la posicion 0
void pila_vacia(tope, band){
    si tope == 0 {
        hacer band <- verdadero
    sino 
        hacer band <- falso
    }
}

//chequea si la pila esta llena
void pila_llena(tope, max, band){
    si tope == max
        hacer band <- verdadero
    sino
        hacer band <- falso
}

// PILA y TOPE por referencia.
void Push(PILA, TOPE, MAX, DATO)
    Llamar a Pila_llena(TOPE, MAX, BAND)
    Si (BAND = VERDADERO) entonces
        Escribir "Desbordamiento, Pila llena"
    Sino
        Hacer TOPE <- TOPE + 1
        Hacer PILA[TOPE] <- DATO

int main(){
    cout << "hola mundo"


    //crear pila de 8 espacios
    crear_pila(8);
    push(4);
    push(2);
    push(1);
    push(4);
    push(3);

    //recorrer array de los datos
    ver_pila();

    //pop
    remover(1);

    ver_pila();

    return 0
}