#include "buildTree.h"

#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

static bool isAllowedChar(unsigned char c) {
    // Allowed:
    // - letters/digits (isalnum)
    // - special ASCII 33..47:  ! " # $ % & ' ( ) * + , - . /
    if (isalnum(c)) return true;
    if (c >= 33 && c <= 47) return true;
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
    int k = static_cast<unsigned char>(token[0]);

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
        // same key -> append in input order
        root->items.push_back(token);
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

    // Read whitespace-separated "strings" of unknown count
    char buf[1024];
    while (fscanf(in, "%1023s", buf) == 1) {
        sawAny = true;
        string token(buf);

        // Validate all chars and also ensure token not empty
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
