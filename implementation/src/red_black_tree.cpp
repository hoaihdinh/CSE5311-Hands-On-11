#include <iostream>

#include "red_black_tree.hpp"

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

RedBlackTree::~RedBlackTree() {
    rec_delete_tree(root);
}

RedBlackNode* RedBlackTree::search_node(int key) {
    RedBlackNode *tmp = root;
    while(tmp != nullptr && tmp->key != key) {
        tmp = (tmp->key > key) ? tmp->left : tmp->right;
    }

    if(tmp != nullptr && tmp->key == key) {
        return tmp;
    }

    return nullptr;
}

RedBlackNode* RedBlackTree::get_min_node(RedBlackNode *node) {
    if(node == nullptr) {
        return nullptr;
    }

    while(node->left != nullptr) {
        node = node->left;
    }

    return node;
}

RedBlackNode* RedBlackTree::get_max_node(RedBlackNode *node) {
    if(node == nullptr) {
        return nullptr;
    }

    while(node->right != nullptr) {
        node = node->right;
    }

    return node;
}

RedBlackNode* RedBlackTree::get_predecessor_node(RedBlackNode *node) {
    if(node == nullptr) {
        return nullptr;
    }

    // Attempt to get the largest value in the left subtree
    RedBlackNode *tmp = get_max_node(node->left);
    
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

RedBlackNode* RedBlackTree::get_successor_node(RedBlackNode *node) {
    if(node == nullptr) {
        return nullptr;
    }

    // Attempt to get the smallest value in the right subtree
    RedBlackNode *tmp = get_min_node(node->right);
    
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

void RedBlackTree::rec_print_in_order(RedBlackNode *node) {
    if(node->left != nullptr) { 
        rec_print_in_order(node->left);
    }

    std::cout << node->data << " ";

    if(node->right != nullptr) {
        rec_print_in_order(node->right);
    }
}

void RedBlackTree::rec_delete_tree(RedBlackNode *node) {
    if(node->left != nullptr) { 
        rec_delete_tree(node->left);
    }

    delete node;

    if(node->right != nullptr) {
        rec_delete_tree(node->right);
    }
}

void RedBlackTree::transplant(RedBlackNode *node1, RedBlackNode *node2) {
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

void RedBlackTree::left_rotate(RedBlackNode *node) {
    if(node == nullptr) {
        return;
    }

    // target will take node's place in the rotation process
    // - target's left will contain node (and by extention node's subtrees)
    // - node's right will take target's left subtree
    // - target's right will remain as is
    RedBlackNode *target = node->right;
    node->right = target->left;

    if(target->left != nullptr) {
        target->left->parent = node;
    }

    target->parent = node->parent;

    transplant(node, target);

    target->left = node;
    node->parent = target;
}

void RedBlackTree::right_rotate(RedBlackNode *node) {
    if(node == nullptr) {
        return;
    }

    // target will take node's place in the rotation process
    // - target's right will contain node (and by extention node's subtrees)
    // - node's left will take target's right subtree
    // - target's left will remain as is
    RedBlackNode *target = node->left;
    node->left = target->right;

    if(target->right != nullptr) {
        target->right->parent = node;
    }

    target->parent = node->parent;

    transplant(node, target);

    target->right = node;
    node->parent = target;
}

void RedBlackTree::red_black_tree_fixup(RedBlackNode *node) {
    while(node->parent->color == NodeColor::red) {
        if(node->parent== node->parent->parent->left) {
            RedBlackNode *tmp = node->parent->parent->right;

            if(tmp->color == NodeColor::red) {
                node->parent->color = NodeColor::black;
                tmp->color = NodeColor::black;
                node->parent->parent->color = NodeColor::red;
                node = node->parent->parent;
            } else if (node == node->parent->right) {
                node = node->parent;
                left_rotate(node);
            }
        }
    }
}

void RedBlackTree::insert(int data) {
    insert(data, data);
}

void RedBlackTree::insert(int key, int data) {
    RedBlackNode *new_node = new RedBlackNode;
    new_node->key   = key;
    new_node->data  = data;
    new_node->left  = new_node->right = nullptr;
    new_node->color = NodeColor::red;

    if(root != nullptr) {
        RedBlackNode *tmp = root;
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
        root->color = NodeColor::black;
    }

    red_black_tree_fixup(new_node);
}

int RedBlackTree::search(int key) {
    RedBlackNode *node = search_node(key);
    if(node != nullptr) {
        return node->data;
    }
    return -1;
}

void RedBlackTree::remove(int key) {
    RedBlackNode *nodeToRemove = search_node(key);

    if(nodeToRemove == nullptr) {
        return;
    }

    if(nodeToRemove->left == nullptr) {
        transplant(nodeToRemove, nodeToRemove->right);
    } else if (nodeToRemove->right == nullptr) {
        transplant(nodeToRemove, nodeToRemove->left);
    } else {
        RedBlackNode *nodeToReplace = get_min_node(nodeToRemove->right);

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

int RedBlackTree::get_max() {
    if(root != nullptr) {
        return get_max_node(root)->data;
    }

    return -1;
}

int RedBlackTree::get_min() {
    if(root != nullptr) {
        return get_min_node(root)->data;
    }

    return -1;
}

int RedBlackTree::get_predecessor(int key) {
    RedBlackNode *node = search_node(key);
    if(node != nullptr) {
        RedBlackNode *predecessor_node = get_predecessor_node(node);

        return (predecessor_node != nullptr) ? predecessor_node->data : -1;
    }
    return -1;
}

int RedBlackTree::get_successor(int key) {
    RedBlackNode *node = search_node(key);
    if(node != nullptr) {
        RedBlackNode *successor_node = get_successor_node(node);

        return (successor_node != nullptr) ? successor_node->data : -1;
    }
    return node->data;
}

void RedBlackTree::print_in_order() {
    std::cout << "Printing Red-Black Tree inorder: ";
    rec_print_in_order(root);
    std::cout << std::endl;
}