
#include <iostream> 
#include "linkedlist.hpp"

// Driver Code 
int main() 
{ 
    Linkedlist list; 
    // Inserting nodes 
    list.insert(1); 
    list.insert(2); 
    list.insert(3); 
    list.insert(4); 
    list.insert(5); 
    list.insert(6); 
    list.insert(7); 
    list.insert(8); 
    list.insert(9); 
    list.insert(10); 
    list.insert(11); 
    list.insert(12); 
    list.insert(13); 
    list.insert(14); 
    list.insert(15); 
    list.insert(16); 
    list.insert(17); 
    list.insert(18); 
    list.insert(19); 

    Linkedlist::iterator it{};
    it = list;

    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';
    std::cout << (it++)->data << '\n';




    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';
    // std::cout << (++it)->data << '\n';


    return 0;
}
