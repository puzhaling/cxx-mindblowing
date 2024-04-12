#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <cstdint>
#include <iterator>

struct Node
{ 
    int data{}; 
    Node* next{}; 
}; 

class Linkedlist 
{ 
public:
	class  iterator; 

public: 
    Linkedlist() : head{} {}
    Linkedlist(const Linkedlist&);
	~Linkedlist(); 

  	Node*& get_head() { return this->head; }

    void insert(int data); 
    void print() const; 
    void delete_node(int nodeOffset); 
	void clear();
	void swap(const Linkedlist&);
	
    bool empty() const;
    
   	size_type max_size() const;
   	size_type size() const;

   	bool operator==(const Linkedlist&);
   	bool operator!=(const Linkedlist&);
   	Linkedlist& operator=(Linkedlist&);

private:
	Node* head;

}; 

class Linkedlist::iterator 
{
public:
    using value_type        = int;
    using pointer           = value_type*;
    using reference         = value_type&;
    using difference_type   = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

public:
    iterator() = default;
    iterator(Node node) 	   : m_node{ new Node{ node.data } } {} 
    iterator(Node* node) 	   : m_node{ node 			       } {} 
    iterator(iterator& it) 	   : m_node{ it.m_node             } {}
    iterator(Linkedlist& list) : m_node{ list.get_head()       } {}

    iterator operator++();

    // postfix increment
    iterator operator++(int)
    { 	
        if (m_node->next)
        {
            iterator old{ *this };
            m_node = m_node->next;
            return old;
        }
        else
        {
            return m_node;
        }
    }
    reference   operator*()  { return m_node->data; }
    pointer	    operator->() { return m_node; }

private:
    Node* get_node() { return m_node; }
    Node* m_node;

};

void swap(Linkedlist& l1, Linkedlist& l2);

#endif
