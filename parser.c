#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//node type options
typedef enum {
    NODE_INTEGER, 
    NODE_ADD,
    NODE_SUBTRACT,
    NODE_MULTIPLY,
    NODE_DIVIDE
} NodeType;

//Node struct
typedef struct ASTNode {
    NodeType type;
    int value; //equals to zero for non-integer type nodes
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;



