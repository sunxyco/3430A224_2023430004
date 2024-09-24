#include <fstream>
#include <iostream>
using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};

// Crear un nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->info = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}


class Arbol {
private:
    Node* root = nullptr;

    // Metodo recursivo privado para insertar un nodo en el arbol binario de busqueda
    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            // Crear un nuevo nodo si se encuentra una posicion vacia
            cout << "Se a ingresado el nodo ~ " << data << "\n";
            return createNode(data);
        }

        if (data < node->info) {
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            node->right = insertNode(node->right, data);
        } else {
            cout << "El nodo ya se encuentra en el árbol: " << data << endl;
        }

        return node;
    }

    // Metodo recursivo privado para buscar un nodo
    bool buscar_2(Node* root, int buscar) { 
        if (root == nullptr) {
            return false; 
        } else if (root->info == buscar) { 
            return true; 
        } else if (buscar < root->info) { 
            return buscar_2(root->left, buscar); 
        } else {
            return buscar_2(root->right, buscar); 
        }
    }

    // Metodo recursivo privado para eliminar un nodo
    Node* deleteNode(Node* root, int key) { 
        if (root == nullptr) {
            //cout << "Se a eliminado el nodo ~ " << key << "\n";
            return root; 
        } 

        if (key < root->info) { 
            root->left = deleteNode (root->left, key);
        } else if (key > root->info) { 
            root->right = deleteNode(root->right, key);
        } else { 
            if (root->left == nullptr) { 
                Node* temp = root->right;
                delete root; 
                return temp; 
            } else if (root->right == nullptr) {
                Node* temp = root->left; 
                delete root;
                return temp; 
            } 

            Node* temp = root->right;
            while (temp->left != nullptr) { 
                temp = temp->left; 
            } 

            root->info = temp->info; 
            root->right = deleteNode(root->right, temp->info); 
        } 

        return root;
    }

    // Metodo recursivo privado para imprimir el arbol en preorden
    void printPreOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->info << " ";
        printPreOrden(node->left);
        printPreOrden(node->right);
    }

    // Metodo recursivo privado para imprimir el arbol en inorden
    void printInOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printInOrden(node->left);
        cout << node->info << " ";
        printInOrden(node->right);
    }

    // Metodo recursivo privado para imprimir el arbol en postorden
    void printPostOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printPostOrden(node->left);
        printPostOrden(node->right);
        cout << node->info << " ";
    }

    // Metodo recursivo privado para recorrer el arbol
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                string cadena = to_string(node->info) + "i"; 
                fp << "\"" << cadena << "\" [shape=point];" << endl;
                fp << node->info << "->\"" << cadena << "\";" << endl;
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = to_string(node->info) + "d"; 
                fp << "\"" << cadena << "\" [shape=point];" << endl;
                fp << node->info << "->\"" << cadena << "\";" << endl;
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }

public:
    Arbol() : root(nullptr) {}

    // Metodo publico para insertar un nodo
    void insert(int data) {
        root = insertNode(root, data);
    }

    // Metodo publico para buscar un nodo
    void buscar_1(int numero_buscar) {
        if (buscar_2(root, numero_buscar)) {
            cout << "\nSe encontró el numero ~ " << numero_buscar << "\n";
        } else {
            cout << "\nNo se ha encontrado el numero ~ " << numero_buscar << "\n";
        }
    }

    // Metodo publico para eliminar un nodo
    void eliminar_elemento(int numero_eliminar) {
        if (buscar_2(root, numero_eliminar)) {
            cout << "\nEliminando elemento\n";
            root = deleteNode(root, numero_eliminar);
            cout << "Elemento eliminado ~ " << numero_eliminar << "\n";
        } else {
            cout << "\nNo se ha encontrado el elemento\n";
        }
    }

    // Metodo publico para imprimir el arbol en preorden
    void printPreOrden() const {
        printPreOrden(root);
        cout << endl;
    }

    // Metodo publico para imprimir el arbol en inorden
    void printInOrden() const {
        printInOrden(root);
        cout << endl;
    }

    // Metodo publico para imprimir el arbol en postorden
    void printPostOrden() const {
        printPostOrden(root);
        cout << endl;
    }

    // Metodo publico para generar y mostrar la visualizacion del arbol
    void visualize(int sistema_usuario) {
        ofstream fp("mi_arbol.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo mi_arbol.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=pink];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;
        fp.close();

        system("dot -Tpng -o mi_arbol.png mi_arbol.txt");
        
        if (sistema_usuario == 1) {
            cout << "Diagrama~\n";
            system("start mi_arbol.png");
        } else if (sistema_usuario == 2) {
            system("eog mi_arbol.png");
            cout << "Diagrama~\n";
        } else {
            cout << "No a sido posible generar la imagen\n";
        }
    }
};



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
        }
        catch (const invalid_argument& e) {
            cout << "Entrada inválida, por favor ingresa un número entero válido.\n";
        }
        catch (const out_of_range& e) {
            cout << "Número fuera de rango, intenta de nuevo.\n";
        }
    }

    return numero;  // Devuelve el número entero validado
}

int main() {

    Arbol arbolBinario;

    int opcion = 11;
    int valor;
    int nuevoValor;

    while (opcion != 0) {

        cout << "\nMenu:\n1. Insertar numero\n2. Eliminar numero\n3. Modificar elemenot\n4. Mostrar Contenido del arbol, PreOrden, InOrden, PosrOrden\n5. Generar imagen Grafo\n6. Ingresar valores por defecto ~ [120, 87, 140, 43, 99, 130, 22, 65, 93, 135, 56]\n0. Salir\n\n";

        opcion = obtenerNumeroValido("> ");

        //menu
        switch (opcion) {
            case 1:
                // Insertar número
                valor = obtenerNumeroValido("Ingresa un número entero: ");
                arbolBinario.insert(valor);

                break;
            case 2:
                // Eliminar número
                valor = obtenerNumeroValido("Ingresa un número entero para eliminar: ");
                arbolBinario.eliminar_elemento(valor);

                break;
            case 3:
                // 3) Modificar un elemento buscado (eliminar valor viejo e insertar el nuevo valor).
                // Modificar numero ~ se quiere crear un nodo y eliminar otro ~ insertar/eliminar
                valor = obtenerNumeroValido("Ingresa el numero del nodo que quiere modificar: ");
                nuevoValor = obtenerNumeroValido("Ingresa el nuevo numero: ");

                arbolBinario.eliminar_elemento(valor);
                arbolBinario.insert(nuevoValor);

                break;
            case 4:
                // Mostrar contenido del grafo            
                cout << "\nContenido del Arbol~\n\n";
                // Imprimir el arbolBinario en preorden
                cout << "Recorrido en PreOrden: ";
                arbolBinario.printPreOrden();
                cout << "Recorrido en InOrden: ";
                arbolBinario.printInOrden();
                cout << "Recorrido en PostOrden: ";
                arbolBinario.printPostOrden();

                cout << "\n\n";
                break;
            case 5:{
                // Mostrar vizualizacion del grafo
                cout << "    Ingrese su sitema operativo\n    1. Windows\n    2. Linux\n\n";
                int sub_ingreso = 0;

                while (sub_ingreso != 1 && sub_ingreso != 2) {
                    sub_ingreso = obtenerNumeroValido(">");

                    if (sub_ingreso != 1 && sub_ingreso != 2) {
                        cout << "    Opción no válida. Por favor ingrese nuevamente su opcion\n";
                    }
                }
                
                //1 - Windows / 2 - Linux
                arbolBinario.visualize(sub_ingreso);

                break;
                }
            case 0:
                //salir
                cout << "Se a cerrado el programa";
                
                break;
            case 6: {
                //ingresar valores por defecto

                // Insertar numeros en el arbolBinario usando el metodo insert
                int mis_ints[11] = {120, 87, 140, 43, 99, 130, 22, 65, 93, 135, 56};
                
                // Recorrer el arreglo e insertar los
                for (int i = 0; i < 11; i++) {
                    arbolBinario.insert(mis_ints[i]);
                }
                cout << "\n\nSe ingresaron los valores\n\n";

                break;
            }

            default:
                cout << "\n~ " << opcion << " ~ No es una opcion valida, porfavor intentelo nuevamente\n\n";

                break;
        }
    }
}