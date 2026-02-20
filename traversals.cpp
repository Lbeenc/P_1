#include "traversals.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

static void printNodeLine(ofstream& out, node_t* n, int depth) {
    // indent = 4 * depth spaces
    out << string(depth * 4, ' ');
    out << depth << " " << n->key;

    // print list items separated by single spaces
    for (size_t i = 0; i < n->items.size(); i++) {
        out << " " << n->items[i];
    }
    out << "\n";
}

static string makeName(const char base[], const char* suffix) {
    return string(base) + suffix;
}

// -------- Level Order (BFS) --------
void traverseLevelOrder(node_t* root, const char basefilename[]) {
    ofstream out(makeName(basefilename, ".levelorder"));
    if (!out) {
        cerr << "Error: Cannot open output file for levelorder.\n";
        exit(1);
    }
    if (!root) return;

    queue<pair<node_t*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto [cur, depth] = q.front();
        q.pop();

        printNodeLine(out, cur, depth);

        if (cur->left)  q.push({cur->left, depth + 1});
        if (cur->right) q.push({cur->right, depth + 1});
    }
}

// -------- Pre Order (Root, Left, Right) --------
static void preOrderRec(node_t* n, int depth, ofstream& out) {
    if (!n) return;
    printNodeLine(out, n, depth);
    preOrderRec(n->left, depth + 1, out);
    preOrderRec(n->right, depth + 1, out);
}

void traversePreOrder(node_t* root, const char basefilename[]) {
    ofstream out(makeName(basefilename, ".preorder"));
    if (!out) {
        cerr << "Error: Cannot open output file for preorder.\n";
        exit(1);
    }
    preOrderRec(root, 0, out);
}

// -------- Post Order (Left, Right, Root) --------
static void postOrderRec(node_t* n, int depth, ofstream& out) {
    if (!n) return;
    postOrderRec(n->left, depth + 1, out);
    postOrderRec(n->right, depth + 1, out);
    printNodeLine(out, n, depth);
}

void traversePostOrder(node_t* root, const char basefilename[]) {
    ofstream out(makeName(basefilename, ".postorder"));
    if (!out) {
        cerr << "Error: Cannot open output file for postorder.\n";
        exit(1);
    }
    postOrderRec(root, 0, out);
}
