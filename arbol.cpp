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

    return 0;
}