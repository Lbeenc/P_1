#include <cstdio>
#include <iostream>

#include "node.h"
#include "buildTree.h"
#include "traversals.h"

using namespace std;

static void printUsage() {
    cerr << "Fatal: Improper usage\n";
    cerr << "Usage: P1 [filename]\n";
}

int main(int argc, char* argv[]) {
    const int MIN_ARGS = 1;
    const int MAX_ARGS = 2;

    FILE* inFile = stdin;
    const char* baseName = "out"; // required for keyboard input OR stdin redirection

    // improper usage
    if (argc < MIN_ARGS || argc > MAX_ARGS) {
        printUsage();
        return 1;
    }

    // P1 filename -> read from filename and baseName is filename
    if (argc == MAX_ARGS) {
        baseName = argv[1];
        inFile = fopen(argv[1], "r");
        if (inFile == nullptr) {
            cerr << "Error: Cannot open file '" << argv[1] << "'\n";
            return 1;
        }
    }

    node_t* root = buildTree(inFile);

    if (inFile != stdin) {
        fclose(inFile);
    }

    traverseLevelOrder(root, baseName);
    traversePreOrder(root, baseName);
    traversePostOrder(root, baseName);

    return 0;
}
