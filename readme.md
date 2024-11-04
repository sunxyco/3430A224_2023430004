# Hashing con Resolución de Colisiones

Este programa implementa una tabla hash en C++ que permite el ingreso, almacenamiento y búsqueda de numeros con métodos de resolución de colisiones: (lineal, cuadrático y doble hash). Los números se almacenan en una tabla hash(arreglo), y si se produce una colisión, el programa intenta resolverla usando el método especificado por el usuario al momento de compilar el programa.

## Parámetros

1. **Metodo de resolucion de colisiones (`<Metodo>`)**: Una letra arbitraria que ayudara a seleccionar el metodo de resolucion de colisiones
• (L) Reasignación Prueba Lineal
• (c) Reasignación Prueba Cuadrática
• (D) Reasignación Doble Dirección Hash

## Ejemplo de Ejecución

Se deben recibir 1 parámetro obligatorio

./hash <Metodo({L/C/D})>

ejemplo~
./hash L