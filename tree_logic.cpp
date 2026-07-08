#include <string>
#include <iostream>

struct Billionaire {
    std::string name;
    int rank;
    int year;
    std::string company;
    std::string sector;
    int age;
    double netWorth;
};

struct Node {
    Billionaire data;
    Node* left;
    Node* right;
};

Node* newNode(Billionaire b) {
    Node* n = new Node();
    n->data = b;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

Node* insert(Node* root, Billionaire b) {
    if (root == nullptr) {
        return newNode(b);
    }
    if (b.netWorth < root->data.netWorth) {
        root->left = insert(root->left, b);
    } else {
        root->right = insert(root->right, b);
    }
    return root;
}

void printInOrder(Node* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    std::cout << root->data.name << " - " << root->data.company << " (" << root->data.sector
              << ") - $" << root->data.netWorth << "B - rank " << root->data.rank
              << " - age " << root->data.age << " - " << root->data.year << "\n";
    printInOrder(root->right);
}
