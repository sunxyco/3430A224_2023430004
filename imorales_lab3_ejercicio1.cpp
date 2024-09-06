#include <iostream>
#include <string>

struct Pila{
    int maximo;
    int tope;
    int mi_array[maximo];
    bool band;
};

void crear_pila(int max){

}

void push(int dato){

}

void pop(int dato){

}

void pila_vacia(tope, band){
    si tope == 0 {
        hacer band <- verdadero
    sino 
        hacer band <- falso
    }
}

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
    crear_pila(8) 
    
    return 0
}