#include <string>
#include <iostream>
#include <vector>

using namespace std;

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

void breadthfirstSearch(Node* root, int level, vector<vector<Billionaire>>& result, int searchWorth) {
    if (root == nullptr) {
        return;
    }
    if (result[level].empty()) {
        result[level].push_back({});
    }
    if (root->data.netWorth == searchWorth) {
        result[level].push_back({});
    }
    breadthfirstSearch(root->left, level + 1, result, searchWorth);
    breadthfirstSearch(root->right, level + 1, result, searchWorth);
}

vector<vector<Billionaire>> breadthfirstSearch(Node* root, int level, int searchWorth) {
    vector<vector<Billionaire>> result;
    breadthfirstSearch(root, 0, result, searchWorth);
    return result;
}


void depthfirstSearch(Node* root, int searchWorth, vector<Billionaire>& result) {
    if (root == nullptr) {
        return;
    }
    if (searchWorth == root->data.netWorth) {
        result.push_back(root->data);
    }
    depthfirstSearch(root->left, searchWorth, result);
    depthfirstSearch(root->right, searchWorth, result);
}

vector<Billionaire> depthfirstSearch(Node* root, int searchWorth) {
    vector<Billionaire> result;
    depthfirstSearch(root, searchWorth, result);
    return result;
}