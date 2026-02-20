#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

struct node_t {
    int key;                         // ASCII code of first character
    std::vector<std::string> items;  // strings in input order for this key
    node_t* left;
    node_t* right;

    explicit node_t(int k) : key(k), left(nullptr), right(nullptr) {}
};

#endif
