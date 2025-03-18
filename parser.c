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


//function that creates new nodes for a tree
ASTNode* create_node(NodeType type, int value, ASTNode* left, ASTNode* right){

    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode)); //allocate memory for the node
    node->type = type; //set node type (i.e integer, add, subtract, etc)
    node->value = value; //set node value (i.e 15, +, /, -, etc)
    node->left = left; //set node's left child
    node->right = right; //set node's right child

    return node;
}



