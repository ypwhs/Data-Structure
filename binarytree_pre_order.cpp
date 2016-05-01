#include <iostream>
#include <cstdio>
#include <queue>

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

    void preorder(){
        preorder(root, 0);
        printf("\n");
    }

    void preorder(Node * node, int depth){
        if (node == NULL) return;
        printf("depth = %d\tvalue = %d\n", depth, node->data);
        preorder(node->left, depth+1);
        preorder(node->right, depth+1);
    }

    void inorder(){
        inorder(root, 0);
        printf("\n");
    }

    void inorder(Node * node, int depth){
        if (node == NULL) return;
        inorder(node->left, depth+1);
        printf("depth = %d\tvalue = %d\n", depth, node->data);
        inorder(node->right, depth+1);
    }

    void postorder(){
        postorder(root, 0);
        printf("\n");
    }

    void postorder(Node * node, int depth){
        if (node == NULL) return;
        postorder(node->left, depth+1);
        postorder(node->right, depth+1);
        printf("depth = %d\tvalue = %d\n", depth, node->data);
    }

    void levelorder(){
        levelorder(root);
        printf("\n");
    }

    void levelorder(Node * node){
        queue<Node *> s;
        Node * p;
        int depth = -1;
        s.push(NULL);
        s.push(node);
        while(s.size()){
            if(s.front() == NULL){
                depth ++;
                s.pop();
                if(s.size())s.push(NULL);
                else break;
            }
            p = s.front();
            s.pop();
            printf("depth = %d\tvalue = %d\n", depth, p->data);
            if(p->left != NULL)
                s.push(p->left);
            if(p->right != NULL)
                s.push(p->right);
        }
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
    printf("In order\n");
    tree.inorder();
    printf("Level order\n");
    tree.levelorder();
    return 0;
}
