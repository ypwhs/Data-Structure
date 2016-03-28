#include <iostream>
#include <cstdio>

using namespace std;

class Node{
public:
    int data;
    Node * left, *right;
    Node(int v){
        data = v;
        left = NULL;
        right = NULL;
    }
};

class Tree{
public:
    Node * root;
    Tree(){
        root = NULL;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    Node * insert(Node * node, int data) {
        if (node==NULL) {
            node = new Node(data);
        } else {
            if (data <= node->data) {
                node->left = insert(node->left, data); 
            }
            else { 
                node->right = insert(node->right, data); 
            }
        }
        return node;
    }

    bool lookup(int data){
        return lookup(root, data);
    }

    bool lookup(Node * node, int data){
        if (node==NULL) {
            return(false);
        }

        if (data==node->data) {
            return(true);
        } 
        else if (data < node->data) {
            return(lookup(node->left, data));
        } 
        else { 
            return(lookup(node->right, data));
        } 
    }

    void printTree() {
        printTree(root, 0);
        printf("\n");
    }

    void printTree(Node * node, int depth) { 
        if (node == NULL) return;
        // left, node itself, right 
        printTree(node->left, depth+1);
        printf("depth = %d\tvalue = %d\n", depth, node->data);
        // printf("data = %d\n", node->data);
        printTree(node->right, depth+1);
    }
};

int main()
{
    Tree tree;
    int values[] = {25 , 1 , 19 , 58 , 126 , 27 , 7 , 74 , 54 , 50 , 51 , 87 , 57 , 88 , 117 , 75};
    for (int i = 0; i < 16; ++i)
    {
        tree.insert(values[i]);
    }
    tree.printTree();
    return 0;
}
