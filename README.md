## Ejemplo de Entrada

Este proyecto implementa un sistema de gestión para un puerto utilizando estructuras de datos basadas en pilas, donde se almacenan y manipulan contenedores en un número determinado de pilas.

## Características

1. **Gestión de Pilas**: El programa permite crear múltiples pilas de contenedores con capacidad limitada, ambas delimitadas por el usuario.
2. **Manipulación Dinámica de Contenedores**:
   - Agregar contenedores aleatorios a las pilas.
   - Eliminar un contenedor específico, reubicando otros contenedores en pilas con espacio disponible si es necesario.
3. **Estructura de Datos Dinámica**: Uso de punteros para manejar pilas de forma dinámica.

## Estructuras

- **Pila**: Representa una pila que puede almacenar una cantidad fija de contenedores.
- **Puerto**: Un puerto que contiene un número variable de pilas y maneja la adición y eliminación de contenedores.

### Funciones de la estructura `Pila`
- `push`: Agrega un contenedor a la pila si hay espacio disponible.
- `pop`: Elimina el último contenedor de la pila.
- `mostrar`: Muestra el contenido de la pila.

### Funciones de la estructura `Puerto`
- `agregar_elementos_aleatorios`: Agrega contenedores a las pilas de manera aleatoria y sin repetición.
- `eliminar_contenedor`: Busca un contenedor específico y lo elimina, reubicando otros contenedores si es necesario.
- `mostrar_puerto`: Muestra el contenido de todas las pilas en el puerto.

## Cómo usar el programa

1. Al iniciar el programa, se pide ingresar el número de pilas y la capacidad de cada una.
2. Se generan contenedores aleatorios en las pilas.
3. El usuario puede interactuar ingresando el nombre de un contenedor para eliminarlo del puerto.
4. El programa reubica los contenedores si es necesario y muestra el estado actual del puerto después de cada operación de reubicación.

## Ejemplo de Entrada

```bash
Ingrese numero de Pilas
> 3
Ingrese Capacidad de las Pilas
> 5
Ingrese El NOMBRE de el contenedor que desea eliminar ~ ('1/EMP1')
Salir ~ (salir)
> 2/EMP3