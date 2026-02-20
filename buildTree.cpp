#include "buildTree.h"

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

static bool isAllowedChar(unsigned char c) {
    const int SPECIAL_MIN = 33;
    const int SPECIAL_MAX = 47;

    if (isalnum(c)) return true;
    if (c >= SPECIAL_MIN && c <= SPECIAL_MAX) return true;
    return false;
}

static void abortBadChar(char bad, const string& token) {
    cerr << "Error: Invalid character '" << bad << "' encountered in token: " << token << "\n";
    exit(1);
}

static void validateToken(const string& token) {
    for (unsigned char c : token) {
        if (!isAllowedChar(c)) {
            abortBadChar(static_cast<char>(c), token);
        }
    }
}

static node_t* insertToken(node_t* root, const string& token) {
    const int k = static_cast<unsigned char>(token[0]);

    if (root == nullptr) {
        node_t* n = new node_t(k);
        n->items.push_back(token);
        return n;
    }

    if (k < root->key) {
        root->left = insertToken(root->left, token);
    } else if (k > root->key) {
        root->right = insertToken(root->right, token);
    } else {
        root->items.push_back(token); // preserve input order
    }

    return root;
}

node_t* buildTree(FILE* in) {
    if (!in) {
        cerr << "Error: Null input stream.\n";
        exit(1);
    }

    node_t* root = nullptr;
    bool sawAny = false;

    const int BUF_SIZE = 1024;
    const int MAX_SCAN = 1023; // keep room for null terminator
    char buf[BUF_SIZE];

    while (fscanf(in, "%1023s", buf) == 1) { // MAX_SCAN matches format
        sawAny = true;

        string token(buf);
        if (token.empty()) continue;

        validateToken(token);
        root = insertToken(root, token);
    }

    if (!sawAny) {
        cerr << "Error: Missing data.\n";
        exit(1);
    }

    return root;
}
