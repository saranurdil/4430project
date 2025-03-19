#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Node type options
typedef enum {
    NODE_INTEGER, 
    NODE_ADD,
    NODE_SUBTRACT,
    NODE_MULTIPLY,
    NODE_DIVIDE
} NodeType;

// Node struct
typedef struct ASTNode {
    NodeType type;
    int value; // Equals to zero for non-integer type nodes
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

ASTNode* expression();
ASTNode* expression_suffix(ASTNode* left);
ASTNode* term();
ASTNode* term_suffix(ASTNode* left);
ASTNode* factor();

char current_token[100];
char current_token_type[100];

// Function that creates new nodes for a tree
ASTNode* create_node(NodeType type, int value, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode)); 
    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}

// Function to get the next token from the lexer output
void get_next_token() {
    if(scanf("%90[^,],%90s", current_token, current_token_type) != 2) {
        strcpy(current_token, "");
        strcpy(current_token_type, "");
    }
}

// GRAMMAR: <expression> -> <term> <expression_suffix>
ASTNode* expression() {
    ASTNode* term_node = term();
    return expression_suffix(term_node);
}

// GRAMMAR: <term> -> <factor> <term_suffix>
ASTNode* term() {
    ASTNode* factor_node = factor();
    return term_suffix(factor_node);
}

// GRAMMAR: <factor> -> ( <expression> ) | <integer>
ASTNode* factor() {
    // Check if current token is "(" -> call expression()
    if (strcmp(current_token_type, "left_paren") == 0) {
        get_next_token();  // Move to the next token (which should be an expression)
        ASTNode* inner_expr = expression();  // Call expression

        if (strcmp(current_token_type, "right_paren") != 0) {
            printf("Error: Expected ')' but found '%s'\n", current_token);
            exit(1);
        }
        get_next_token();

        return inner_expr;
    } 
    else if (strcmp(current_token_type, "integer") == 0) {
        int value = atoi(current_token);
        ASTNode* node = create_node(NODE_INTEGER, value, NULL, NULL);
        get_next_token();
        return node;
    } 
    else {
        printf("Error: Unexpected token '%s' of type '%s'\n", current_token, current_token_type);
        exit(1);
    }
}

// GRAMMAR: <term_suffix> -> * <factor> <term_suffix> | / <factor> <term_suffix> | ε
ASTNode* term_suffix(ASTNode* left) {
    // Check if current token is * or /
    if (strcmp(current_token_type, "multiply_operator") == 0 || strcmp(current_token_type, "divide_operator") == 0) {
        char operator_type[100]; 
        strcpy(operator_type, current_token_type);  

        get_next_token();  

        ASTNode* factor_node = factor();
        ASTNode* new_node = (strcmp(operator_type, "multiply_operator") == 0) ?
                            create_node(NODE_MULTIPLY, 0, left, factor_node) :
                            create_node(NODE_DIVIDE, 0, left, factor_node);

        return term_suffix(new_node);
    }
    return left;
}

// GRAMMAR: <expression_suffix> -> + <term> <expression_suffix> | - <term> <expression_suffix> | ε
ASTNode* expression_suffix(ASTNode* left) {
    // Check if current token is + or -
    if (strcmp(current_token_type, "add_operator") == 0 || strcmp(current_token_type, "subtract_operator") == 0) {
        char operator_type[100]; 
        strcpy(operator_type, current_token_type);  

        get_next_token();  

        ASTNode* right = expression();  

        // Build AST tree
        ASTNode* new_node = (strcmp(operator_type, "add_operator") == 0) ?
                            create_node(NODE_ADD, 0, left, right) :
                            create_node(NODE_SUBTRACT, 0, left, right);

        return new_node;  
    }
    return left;
}

// Function to print the AST
void print_tree(ASTNode* node, int indent) {

    // If the tree is empty
    if (node == NULL) {
        printf("Empty tree.\n");
        return;
    }

    for (int i = 0; i < indent; i++) printf("\t");
    
    switch (node->type) {
        case NODE_INTEGER:
            printf("%d (int)\n", node->value);
            break;
        case NODE_ADD:
            printf("+ (Add)\n");
            print_tree(node->left, indent + 1);
            print_tree(node->right, indent + 1);
            break;
        case NODE_SUBTRACT:
            printf("- (Subtract)\n");
            print_tree(node->left, indent + 1);
            print_tree(node->right, indent + 1);
            break;
        case NODE_MULTIPLY:
            printf("* (Multiply)\n");
            print_tree(node->left, indent + 1);
            print_tree(node->right, indent + 1);
            break;
        case NODE_DIVIDE:
            printf("/ (Divide)\n");
            print_tree(node->left, indent + 1);
            print_tree(node->right, indent + 1);
            break;
    }
}

// Main function
int main() {
    get_next_token();
    ASTNode* root = expression();
    print_tree(root, 0);
    return 0;
}