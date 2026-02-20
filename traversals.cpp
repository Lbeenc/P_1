#include "traversals.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;

static void printNodeLine(ofstream& out, node_t* n, int depth) {
    const int INDENT_SPACES = 4;

    out << string(depth * INDENT_SPACES, ' ');
    out << depth << " " << n->key;

    for (size_t i = 0; i < n->items.size(); i++) {
        out << " " << n->items[i];
    }
    out << "\n";
}

static string makeName(const char base[], const char* suffix) {
    return string(base) + suffix;
}

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
        auto cur = q.front();
        q.pop();

        printNodeLine(out, cur.first, cur.second);

        if (cur.first->left)  q.push({cur.first->left, cur.second + 1});
        if (cur.first->right) q.push({cur.first->right, cur.second + 1});
    }
}

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
