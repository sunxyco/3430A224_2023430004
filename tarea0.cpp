#include <iostream>
using namespace std;

//Estructura
struct Node { 
    int data;
    Node* left;
    Node* right;
};

//Nuevo nodo
Node* createNode(int data) {
    Node* newNode = new Node;
    newNode->data = data;
    //Caso inicial de hijos
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Pre-order traversal: Root -> Left -> Right
void preOrderTraversal(Node* root) {
    if (root == nullptr) { 
        return;
    }
    std::cout << root->data << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
} 

Node* insert(Node* root, int data) { 
    if (root == NULL) { 
        root = createNode(data); 
    }   
    else if (data <= root->data) { 
        root->left = insert(root->left, data); }
    else { 
        root->right = insert(root->right, data);
    }
    return root; 
}

int main(){
    cout << "holamundo";
    //int nodo_principal;
    Node* nodo_principal = createNode(8);

    insert(nodo_principal, 2);
    insert(nodo_principal, 12);
    insert(nodo_principal, 123);
    insert(nodo_principal, 41234);
    insert(nodo_principal, 123);
    insert(nodo_principal, 23);
    insert(nodo_principal, 1423);
    insert(nodo_principal, 11111);

    preOrderTraversal(nodo_principal);
}


/*
bool search(Node* root, int data) {
    if (root == NULL) {
        return false;
    }
    else if (root->data == data) {
        return true;
    }
    else if (data <= root->data) {
        return search(root->left, data);
    }
    else {
        return search(root->right, data);
    }
}

Node* deleteNode(Node* root, int key) { 
    if (root == NULL) { 
        return root;
    }

    if (key < root->data) { 
        root->left = deleteNode(root->left, key); 
    } else if (key > root->data) {
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
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Pre-order traversal: Root -> Left -> Right
void preOrderTraversal(Treeliode* root) {
    if (root == nullptr) { 
        return;
    }
    std::cout << root->data << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
} 

// In-order traversal: Left -> Root -> Right
void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return; 
    }
    inOrderTraversal(root->left);
    std::cout << root->data << " ";
    inOrderTraversal(root->right);
}

// Post-order traversal: Left -> Right -> Root
void postOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return; 
    }
    postOrderTraversal (root->left);
    postOrderTraversal(root->right); 
    std::cout << root->data << " ";
}*/