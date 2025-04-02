#include <iostream>

#include "binary_search_tree.hpp"

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    rec_delete_tree(root);
}

BinaryTreeNode* BinarySearchTree::search_node(int key) {
    BinaryTreeNode *tmp = root;
    while(tmp != nullptr && tmp->key != key) {
        tmp = (tmp->key > key) ? tmp->left : tmp->right;
    }

    if(tmp != nullptr && tmp->key == key) {
        return tmp;
    }

    return nullptr;
}

BinaryTreeNode* BinarySearchTree::get_min_node(BinaryTreeNode *node) {
    if(node == nullptr) {
        return nullptr;
    }

    while(node->left != nullptr) {
        node = node->left;
    }

    return node;
}

BinaryTreeNode* BinarySearchTree::get_max_node(BinaryTreeNode *node) {
    if(node == nullptr) {
        return nullptr;
    }

    while(node->right != nullptr) {
        node = node->right;
    }

    return node;
}

BinaryTreeNode* BinarySearchTree::get_predecessor_node(BinaryTreeNode *node) {
    if(node == nullptr) {
        return nullptr;
    }

    // Attempt to get the largest value in the left subtree
    BinaryTreeNode *tmp = get_max_node(node->left);
    
    // If tmp is nullptr, then node does not have a right subtree
    // therefore, the next value will be a parent node
    if(tmp == nullptr) {
        tmp = node->parent;

        // If tmp's left child is the current node, then the node is
        // smaller than tmp, however it will be larger than tmp's parent
        // So the predecessor must be higher up in the tree
        while(tmp != nullptr && tmp->left == node) {
            node = tmp;
            tmp = tmp->parent;
        }
        
        // By the end of the while loop, tmp will be the proper predecessor to the original input node
    }

    return tmp;
}

BinaryTreeNode* BinarySearchTree::get_successor_node(BinaryTreeNode *node) {
    if(node == nullptr) {
        return nullptr;
    }

    // Attempt to get the smallest value in the right subtree
    BinaryTreeNode *tmp = get_min_node(node->right);
    
    // If tmp is nullptr, then node does not have a right subtree
    // therefore, the next value will be a parent node
    if(tmp == nullptr) {
        tmp = node->parent;

        // If tmp's right child is the current node, then the node is
        // larger than tmp, however it will be less than tmp's parent
        // So the successor must be higher up in the tree
        while(tmp != nullptr && tmp->right == node) {
            node = tmp;
            tmp = tmp->parent;
        }
        
        // By the end of the while loop, tmp will be the proper successor to the original input node
    }

    return tmp;
}

void BinarySearchTree::rec_print_in_order(BinaryTreeNode *node) {
    if(node->left != nullptr) { 
        rec_print_in_order(node->left);
    }

    std::cout << node->data << " ";

    if(node->right != nullptr) {
        rec_print_in_order(node->right);
    }
}

void BinarySearchTree::rec_delete_tree(BinaryTreeNode *node) {
    if(node->left != nullptr) { 
        rec_delete_tree(node->left);
    }

    delete node;

    if(node->right != nullptr) {
        rec_delete_tree(node->right);
    }
}

void BinarySearchTree::transplant(BinaryTreeNode *node1, BinaryTreeNode *node2) {
    if(node1->parent == nullptr) {
        root = node2;
    } else if(node1 == node1->parent->left) {
        node1->parent->left = node2;
    } else { // node1->parent->right == node1
        node1->parent->right = node2;
    }

    if(node2 != nullptr) {
        node2->parent = node1->parent;
    }
}

void BinarySearchTree::insert(int data) {
    insert(data, data);
}

void BinarySearchTree::insert(int key, int data) {
    BinaryTreeNode *new_node = new BinaryTreeNode;
    new_node->key  = key;
    new_node->data = data;
    new_node->left = new_node->right = nullptr;

    if(root != nullptr) {
        BinaryTreeNode *tmp = root;
        while((tmp->left != nullptr && tmp->key > key) || (tmp->right != nullptr && tmp->key <= key)) {
            tmp = (tmp->key > key) ? tmp->left : tmp->right;
        }

        new_node->parent = tmp;
        if(tmp->key > key) {
            tmp->left = new_node;
        } else {
            tmp->right = new_node;
        }
    } else {
        new_node->parent = nullptr;
        root = new_node;
    }
}

int BinarySearchTree::search(int key) {
    BinaryTreeNode *node = search_node(key);
    if(node != nullptr) {
        return node->data;
    }
    return -1;
}

void BinarySearchTree::remove(int key) {
    BinaryTreeNode *nodeToRemove = search_node(key);

    if(nodeToRemove == nullptr) {
        return;
    }

    if(nodeToRemove->left == nullptr) {
        transplant(nodeToRemove, nodeToRemove->right);
    } else if (nodeToRemove->right == nullptr) {
        transplant(nodeToRemove, nodeToRemove->left);
    } else {
        BinaryTreeNode *nodeToReplace = get_min_node(nodeToRemove->right);

        if(nodeToReplace->parent != nodeToRemove) {
            transplant(nodeToReplace, nodeToReplace->right);
            nodeToReplace->right = nodeToRemove->right;
            nodeToReplace->right->parent = nodeToReplace;
        }

        transplant(nodeToRemove, nodeToReplace);
        nodeToReplace->left = nodeToRemove->left;
        nodeToReplace->left->parent = nodeToReplace;
    }

}

int BinarySearchTree::get_max() {
    if(root != nullptr) {
        return get_max_node(root)->data;
    }

    return -1;
}

int BinarySearchTree::get_min() {
    if(root != nullptr) {
        return get_min_node(root)->data;
    }

    return -1;
}

int BinarySearchTree::get_predecessor(int key) {
    BinaryTreeNode *node = search_node(key);
    if(node != nullptr) {
        BinaryTreeNode *predecessor_node = get_predecessor_node(node);

        return (predecessor_node != nullptr) ? predecessor_node->data : -1;
    }
    return -1;
}

int BinarySearchTree::get_successor(int key) {
    BinaryTreeNode *node = search_node(key);
    if(node != nullptr) {
        BinaryTreeNode *successor_node = get_successor_node(node);

        return (successor_node != nullptr) ? successor_node->data : -1;
    }
    return node->data;
}

void BinarySearchTree::print_in_order() {
    std::cout << "Printing BST inorder: ";
    rec_print_in_order(root);
    std::cout << std::endl;
}