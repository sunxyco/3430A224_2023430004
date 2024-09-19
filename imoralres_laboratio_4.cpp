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
            return createNode(data);
        }

        if (data < node->info) {
            // Insertar en el subarbol izquierdo
            node->left = insertNode(node->left, data);
        } else if (data > node->info) {
            // Insertar en el subarbol derecho
            node->right = insertNode(node->right, data);
        } else {
            // El dato ya esta en el arbol
            cout << "El nodo ya se encuentra en el árbol: " << data << endl;
        }

        return node;
    }

    // Metodo recursivo privado para imprimir el arbol en preorden
    void printPreOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->info << " "; // Imprimir el dato del nodo actual
        printPreOrden(node->left);  // Recorrer el subarbol izquierdo
        printPreOrden(node->right); // Recorrer el subarbol derecho
    }

    // In-orden traversal: Left -> Root -> Right
    void printInOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printInOrden(node->left);
        cout << node->info << " ";
        printInOrden(node->right);
    }

    void printPostOrden(Node* node) const {
        if (node == nullptr) {
            return;
        }
        printPostOrden(node->left);
        printPostOrden(node->right);
        cout << node->info << " ";
    }

public:
    Arbol() : root(nullptr) {}

    // Metodo publico para insertar un nodo en el arbol
    void insert(int data) {
        root = insertNode(root, data);
    }

    // Metodo publico para imprimir el arbol en preorden
    void printPreOrden() const {
        printPreOrden(root);
        cout << endl;
    }

    void printInOrden() const {
        printInOrden(root);
        cout << endl;
    }

    void printPostOrden() const {
    printPostOrden(root);
    cout << endl;
    }

    // Otros metodos publicos y privados (si es necesario)
    
    //eliminar (root, elemento_eliminar)
    Node* deleteNode(Node* root, int key) { 

        if (root == NULL) {
            return root; 
        } 

        if (key < root->info) { 
            root->left = deleteNode (root->left, key);
        } else if (key > root->info) { 
            root->right = deleteNode(root->right, key);
        } else { 
            if (root->left == NULL) { 
                Node* temp = root->right;
                delete root; 
                return temp; 
            } else if (root->right == NULL) {
                Node* temp = root->left; 
                delete root;
                return temp; 
            } 

            Node* temp = root->right;
            while (temp->left != NULL) { 
                temp = temp->left; 
            } 

            root->info = temp->info; 
            root->right = deleteNode(root->right, temp->info); 
        } 

        return root;
    }


    //buscar
    //busca en el arbol y se retorna true si existe (root, elemento_buscar)
    bool buscar_2(Node* root, int buscar) { 
        if (root == NULL) {
            return false; 
        } 
        else if (root->info == buscar) { 
            return true; 
        }
        else if (buscar <= root->info) { 
            return buscar_2(root->left, buscar); 
        } else {
            return buscar_2(root->right, buscar); 
        }
    }

    void buscar_1(int numero_buscar) {
        if ( buscar_2(root, numero_buscar) ) {
            cout << "\nSe encontró el numero ~ " << numero_buscar << "\n";
        } else {
            cout << "\nNo se a encontrado el numero ~ " << numero_buscar << "\n";
        }
    }

    void eliminar_elemento(int numero_elimnar) {
        if ( buscar_2(root, numero_elimnar) ) {
            cout << "\nEliminando elemento\n";
            deleteNode(root, numero_elimnar);
            cout << "\nElemento eliminado\n";
        } else {
            cout << "\nNo se a encontrado el elemento\n";
        }
    }

    // Recorrer el arbol en preorden y escribir en el archivo
    void recorrer(Node* node, ofstream& fp) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                fp << node->info << "->" << node->left->info << ";" << endl;
            } else {
                string cadena = to_string(node->info) + "i"; // Convertir a string primero
                fp << "\"" << cadena << "\" [shape=point];" << endl; // Comillas alrededor del nombre del nodo ~ sino, se generan ambiguedades con el graphviz
                fp << node->info << "->\"" << cadena << "\";" << endl; // Comillas alrededor de la referencia
            }

            if (node->right != nullptr) {
                fp << node->info << "->" << node->right->info << ";" << endl;
            } else {
                string cadena = to_string(node->info) + "d"; // Convertir a string primero
                fp << "\"" << cadena << "\" [shape=point];" << endl; // Comillas alrededor del nombre del nodo ~ sino, se generan ambiguedades con el graphviz
                fp << node->info << "->\"" << cadena << "\";" << endl; // Comillas alrededor de la referencia
            }

            recorrer(node->left, fp);
            recorrer(node->right, fp);
        }
    }
    
    // Generar y mostrar la visualizacion del arbol
    void visualize() {
        ofstream fp("mi_arbol.txt");

        if (!fp.is_open()) {
            cerr << "Error al abrir el archivo mi_arbol.txt" << endl;
            return;
        }

        fp << "digraph G {" << endl;
        fp << "node [style=filled fillcolor=yellow];" << endl;

        recorrer(root, fp);

        fp << "}" << endl;

        fp.close();

        // Generar y mostrar la imagen del arbol
        system("dot -Tpng -o mi_arbol.png mi_arbol.txt");
        system("start mi_arbol.png");
    }

};

int main() {
    Arbol arbol;

    // Insertar numeros en el arbol usando el metodo insert
    int mis_ints[11] = {120, 87, 140, 43, 99, 130, 22, 65, 93, 135, 56};
    
    // Recorrer el arreglo e insertar los
    for (int i = 0; i < 11; i++) {
        arbol.insert(mis_ints[i]);
    }
    
    // Imprimir el arbol en preorden
    cout << "Recorrido en preorden: ";
    arbol.printPreOrden();
    cout << "Recorrido en InOrden: ";
    arbol.printInOrden();
    cout << "Recorrido en PostOrden: ";
    arbol.printPostOrden();

    arbol.visualize();

    arbol.buscar_1(130);
    arbol.buscar_1(129);

    arbol.eliminar_elemento(99);
    
    string hola;
    hola = "holamundo";
    cin >> hola;
    
    arbol.visualize();
    return 0;
}