#pragma once

struct BinaryTreeNode {
    int key;
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;
    BinaryTreeNode *parent;
};

class BinarySearchTree {
    private:
        BinaryTreeNode *root;
    
        BinaryTreeNode* search_node(int key);
        BinaryTreeNode* get_min_node(BinaryTreeNode *node);
        BinaryTreeNode* get_max_node(BinaryTreeNode *node);
        BinaryTreeNode* get_predecessor_node(BinaryTreeNode *node);
        BinaryTreeNode* get_successor_node(BinaryTreeNode *node);
        void rec_print_in_order(BinaryTreeNode *node);
        void rec_delete_tree(BinaryTreeNode *node);
        void transplant(BinaryTreeNode *node1, BinaryTreeNode *node2);
        
    public:
        BinarySearchTree();
        ~BinarySearchTree();

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