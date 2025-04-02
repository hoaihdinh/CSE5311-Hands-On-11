#pragma once

enum NodeColor {
    black, red
};

struct RedBlackNode {
    int key;
    int data;
    NodeColor color;
    RedBlackNode *left;
    RedBlackNode *right;
    RedBlackNode *parent;
};

class RedBlackTree {
    private:
        RedBlackNode *root;
    
        RedBlackNode* search_node(int key);
        RedBlackNode* get_min_node(RedBlackNode *node);
        RedBlackNode* get_max_node(RedBlackNode *node);
        RedBlackNode* get_predecessor_node(RedBlackNode *node);
        RedBlackNode* get_successor_node(RedBlackNode *node);
        void rec_print_in_order(RedBlackNode *node);
        void rec_delete_tree(RedBlackNode *node);
        void transplant(RedBlackNode *node1, RedBlackNode *node2);
        void left_rotate(RedBlackNode *node);
        void right_rotate(RedBlackNode *node);
        void red_black_tree_fixup(RedBlackNode *node);

    public:
        RedBlackTree();
        ~RedBlackTree();

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