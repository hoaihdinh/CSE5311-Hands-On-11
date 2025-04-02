#pragma once

struct AVLTreeNode {
    int key;
    int data;
    AVLTreeNode *left;
    AVLTreeNode *right;
    AVLTreeNode *parent;
    int height;
};

class AVLTree {
    private:
        AVLTreeNode *root;
    
        AVLTreeNode* search_node(int key);
        AVLTreeNode* get_min_node(AVLTreeNode *node);
        AVLTreeNode* get_max_node(AVLTreeNode *node);
        AVLTreeNode* get_predecessor_node(AVLTreeNode *node);
        AVLTreeNode* get_successor_node(AVLTreeNode *node);
        void rec_print_in_order(AVLTreeNode *node);
        void rec_delete_tree(AVLTreeNode *node);
        void transplant(AVLTreeNode *node1, AVLTreeNode *node2);
        
    public:
        AVLTree();
        ~AVLTree();

        int  search(int key);
        void insert(int data);
        void insert(int key, int data);
        void remove(int key);
        int  get_min();
        int  get_max();
        int  get_predecessor(int key);
        int  get_successor(int key);
        void print_in_order();
};