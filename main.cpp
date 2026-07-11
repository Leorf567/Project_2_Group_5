#include <iostream>
#include <vector>
#include <string>
#include "billionaire.h"

using namespace std;

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
    if (b.country < root->data.country) {
        root->left = insert(root->left, b);
    } else {
        root->right = insert(root->right, b);
    }
    return root;
}

double wealthToGdpPercent(const Billionaire& b) {
    if (b.gdp <= 0) {
        return 0.0;
    }
    return (b.netWorth * 1000000000.0 / b.gdp) * 100.0;
}

void printInOrder(Node* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << root->data.name << " - " << root->data.company << " (" << root->data.sector
         << ") - $" << root->data.netWorth << "B - rank " << root->data.rank
         << " - age " << root->data.age << " - " << root->data.year
         << " - " << wealthToGdpPercent(root->data) << "% of " << root->data.country << "'s GDP\n";
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


void compareGdpImpact(Node* root, const string& countryName) {
    vector<Billionaire> res = depthfirstSearch(root, countryName);
    if (res.empty()) return;

    Billionaire maxB = res[0];
    for (const auto& b : res) {
        if (wealthToGdpPercent(b) > wealthToGdpPercent(maxB)) {
            maxB = b;
        }
    }
    cout << " - " << countryName << ": " << maxB.name << " owns "
         << wealthToGdpPercent(maxB) << "% of the national GDP ($" << maxB.netWorth << "B)\n";
}


int main() {
    cout << "--- LOADING REAL DATASET ---\n";
    vector<Billionaire> database = loadBillionaireData("billionaires_flat.txt");

    if (database.empty()) {
        cout << "Error: Database is empty. Could not load file.\n";
        return 1;
    }

    Node* root = nullptr;
    for (const auto& b : database) {
        root = insert(root, b);
    }
    cout << "Successfully inserted " << database.size() << " records into the Binary Search Tree!\n";

    Billionaire targetTest = database[0];
    string targetCountry = targetTest.country;
    cout << "\n--- RUNNING BFS TEST FOR COUNTRY: " << targetCountry << " ---\n";

    vector<vector<Billionaire>> bfsResult = breadthfirstSearch(root, targetCountry);
    for (int i = 0; i <= 2; ++i) {
        cout << "\nLevel " << i << " Results:\n";
        if (i >= bfsResult.size() || bfsResult[i].empty()) {
            cout << " - No matching records found at this level.\n";
        } else {
            for (const auto& b : bfsResult[i]) {
                cout << " - Found: " << b.name << " | Net Worth: $" << b.netWorth
                     << "B | Company: " << b.company
                     << " | " << wealthToGdpPercent(b) << "% of GDP\n";
            }
        }
    }
    cout << "\n--- WEALTH TO GDP COMPARISON (DEVELOPED VS DEVELOPING) ---\n";

    cout << "[Developed Nations (US & Europe)]\n";
    compareGdpImpact(root, "United States");
    compareGdpImpact(root, "United Kingdom");

    cout << "\n[Developing Nations]\n";
    compareGdpImpact(root, "Mexico");
    compareGdpImpact(root, "Nigeria");

    return 0;
}