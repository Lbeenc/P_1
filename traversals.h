#ifndef TRAVERSALS_H
#define TRAVERSALS_H

#include "node.h"

void traverseLevelOrder(node_t* root, const char basefilename[]);
void traversePreOrder(node_t* root, const char basefilename[]);
void traversePostOrder(node_t* root, const char basefilename[]);

#endif
