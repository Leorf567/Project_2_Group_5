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
    std::string country;
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

void breadthfirstSearch(Node* root, int level, vector<vector<Billionaire>>& result, string searchCountry) {
    if (root == nullptr) {
        return;
    }
    while ((int)result.size() <= level) {
        result.push_back({});
    }
    if (root->data.country == searchCountry) {
        result[level].push_back(root->data);
    }
    breadthfirstSearch(root->left, level + 1, result, searchCountry);
    breadthfirstSearch(root->right, level + 1, result, searchCountry);
}

vector<vector<Billionaire>> breadthfirstSearch(Node* root, string searchCountry) {
    vector<vector<Billionaire>> result;
    breadthfirstSearch(root, 0, result, searchCountry);
    return result;
}

void depthfirstSearch(Node* root, string searchCountry, vector<Billionaire>& result) {
    if (root == nullptr) {
        return;
    }
    if (root->data.country == searchCountry) {
        result.push_back(root->data);
    }
    depthfirstSearch(root->left, searchCountry, result);
    depthfirstSearch(root->right, searchCountry, result);
}

vector<Billionaire> depthfirstSearch(Node* root, string searchCountry) {
    vector<Billionaire> result;
    depthfirstSearch(root, searchCountry, result);
    return result;
}
