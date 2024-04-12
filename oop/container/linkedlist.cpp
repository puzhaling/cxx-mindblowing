#include "linkedlist.hpp"
#include "utils.hpp"

Linkedlist::iterator next(Linkedlist::iterator& it) 
{
	return ++it;
}

void Linkedlist::clear()
{
	if (this->head == nullptr)
	{
		return;
	}
	
	Node* curr{ this->head };
	Node* prev{ nullptr };

	while (curr != nullptr) 
	{	
		prev = curr;
		curr = curr->next;
		delete(prev);
	}
}

Linkedlist::Linkedlist(const Linkedlist& l)
{
	if (l.empty())
	{
		return;
	}

	Node* curr1{ this->head };
	Node* curr2{ l.head };

	curr1 = new Node(curr2->data);

	while (curr2->next != nullptr)
	{
		curr1->next = new Node(curr2->next->data);
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
	curr1->next = nullptr;
}

Linkedlist::~Linkedlist() 
{
	this->clear();
}

size_type Linkedlist::size() const
{
	if (this->head == nullptr) 
	{
		return 0;
	}
	
	Node* temp{ this->head };
	size_type count{};
	
	while (temp != nullptr)
	{
		temp = temp->next;
		count++;	
	}

	return count;
}

// prefix increment
Linkedlist::iterator Linkedlist::iterator::operator++()     
{ 	
	if (this->m_node->next)
	{
		Node* current{ this->m_node->next };
		while (current->next)
		{
			if (is_prime(current->data)) 
			{
				this->m_node = current;
				return *this;
			}
			else 
			{
				current = current->next;
			}
		}
		if (is_prime(current->data))
		{
			this->m_node = current;
			return *this;
		}
		return iterator{ Node{} };
	}
	return iterator{ Node{} };
}

Linkedlist& Linkedlist::operator=(Linkedlist& l)
{
	// l1 becomes copy of l2
	this->clear();

	if (l.empty())
	{
		return *this;
	}

	Node* curr1{ this->head };
	Node* curr2{ l.head };

	curr1 = new Node(curr2->data);

	while (curr2->next != nullptr) 
	{
		curr1->next = new Node(curr2->next->data);
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
	curr1->next = nullptr;

	return *this;
}

bool Linkedlist::operator==(const Linkedlist& l)
{
	if (this->size() != l.size())
	{
		return false;
	}

	Node* temp1{ this->head };
	Node* temp2{ l.head };

	while (temp1 != nullptr || temp2 != nullptr) 
	{
		if (temp1->data != temp2->data) 
		{
			return false;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}

	return temp1 == nullptr && temp2 == nullptr;
}

bool Linkedlist::operator!=(const Linkedlist& l) 
{
	return !(*this == l);
}

void Linkedlist::swap(const Linkedlist& l)
{
	if (l.empty())
	{
		return;
	}

	Node* curr1{ this->head };
	Node* curr2{ l.head };

	while (curr1 != nullptr && curr2 != nullptr) 
	{
		curr1->data = curr2->data;
		curr1 = curr1->next;
		curr2 = curr2->next;
	}
}

void Linkedlist::delete_node(int nodeOffset) 
{ 
    Node *temp1 = head, *temp2 = NULL; 
    int ListLen = 0; 
  
    if (head == NULL) { 
        std::cout << "List empty." << std::endl; 
        return; 
    } 
  
    while (temp1 != NULL) { 
        temp1 = temp1->next; 
        ListLen++; 
    } 

    if (ListLen < nodeOffset) { 
        std::cout << "Index out of range"
             << std::endl; 
        return; 
    } 
  
    temp1 = head; 
  
    if (nodeOffset == 1) {
        head = head->next; 
        delete temp1; 
        return; 
    } 

    while (nodeOffset-- > 1) { 
        temp2 = temp1; 
        temp1 = temp1->next; 
    } 
  
    temp2->next = temp1->next; 
  
    delete temp1; 
} 
  
void Linkedlist::insert(int data) 
{  
    Node* newNode = new Node(data); 
  
    if (head == NULL) { 
        head = newNode; 
        return; 
    } 
  
    Node* temp = head; 
    while (temp->next != NULL) { 
        temp = temp->next; 
    } 
  
    temp->next = newNode; 
} 
  

void Linkedlist::print() const
{ 
    Node* temp = head; 
  
    if (head == NULL) { 
        std::cout << "List empty" << std::endl; 
        return; 
    } 
  
    while (temp != NULL) { 
        std::cout << temp->data << " "; 
        temp = temp->next; 
    } 
} 

bool Linkedlist::empty() const
{
    return head == nullptr;
}

size_type Linkedlist::max_size() const 
{
	return 100;
}

void swap(Linkedlist& l1, Linkedlist& l2)
{
	Node* h1{ l1.get_head() };
	Node* h2{ l2.get_head() };

	Node* temp{ h1 };
	h1 = h2;
	h2 = temp;
}