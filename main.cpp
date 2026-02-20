#include <cstdio>
#include <cstdlib>
#include <cstring>
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
    // Valid:
    //   argc == 1  -> read from stdin (keyboard or redirected)
    //   argc == 2  -> read from filename
    // Invalid:
    //   argc > 2   -> error
    if (argc > 2) {
        printUsage();
        return 1;
    }

    FILE* in = stdin;
    const char* baseName = "out";   // default for keyboard or redirection

    if (argc == 2) {
        baseName = argv[1];
        in = fopen(argv[1], "r");
        if (!in) {
            cerr << "Error: Cannot open file '" << argv[1] << "'\n";
            return 1;
        }
    }

    // Build tree from input source (file or stdin)
    node_t* root = buildTree(in);

    // Close only if we opened a file (not stdin)
    if (in != stdin) {
        fclose(in);
    }

    // Traversals write baseName.levelorder / .preorder / .postorder
    traverseLevelOrder(root, baseName);
    traversePreOrder(root, baseName);
    traversePostOrder(root, baseName);

    return 0;
}
