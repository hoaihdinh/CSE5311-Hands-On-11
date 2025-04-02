#include <iostream>

#include "binary_search_tree.hpp"
#include "red_black_tree.hpp"
#include "avl_tree.hpp"

int main() {

    BinarySearchTree *bst = new BinarySearchTree();

    int array[] = {12, 10, 20, 40, 33, 5, 0, 30};

    for(int i = 0; i < 8; i++) {
        std::cout<< "Inserting: " << array[i] << std::endl;
        bst->insert(array[i]);

    }

    std::cout << "Search 12: " << bst->search(12) << std::endl;
    std::cout << "Search 10: " << bst->search(10) << std::endl;
    std::cout << "Search 20: " << bst->search(20) << std::endl;
    std::cout << "Search 100: " << bst->search(100) << std::endl;


    bst->print_in_order();

    std::cout << "\nMax value: " << bst->get_max() << std::endl;
    std::cout << "Min value: " << bst->get_min() << std::endl;

    std::cout << "\nPredecessor of 12: " << bst->get_predecessor(12) << std::endl;
    std::cout << "Successor of 12: " << bst->get_successor(12) << std::endl;

    std::cout << "\nPredecessor of 10: " << bst->get_predecessor(10) << std::endl;
    std::cout << "Successor of 10: " << bst->get_successor(10) << std::endl;

    std::cout << "\nPredecessor of 20: " << bst->get_predecessor(20) << std::endl;
    std::cout << "Successor of 20: " << bst->get_successor(20) << std::endl;

    std::cout << "\nDeleting 12..." << std::endl;
    bst->remove(12);

    bst->print_in_order();

    std::cout << "\nPredecessor of 10: " << bst->get_predecessor(10) << std::endl;
    std::cout << "Successor of 10: " << bst->get_successor(10) << std::endl;

    std::cout << "\nPredecessor of 20: " <<bst->get_predecessor(20) << std::endl;
    std::cout << "Successor of 20: " << bst->get_successor(20) << std::endl;

    return 0;
}