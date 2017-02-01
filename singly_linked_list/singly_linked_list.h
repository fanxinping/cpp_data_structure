#pragma once
#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_
#include <string>
#include <iostream>

class SLListException
{
public:
	SLListException(const std::string& err)
		:errMsg(err) {}
	std::string GetError() { return errMsg; }
private:
	std::string errMsg;
};

class EmptySLList : public SLListException
{
public:
	EmptySLList(const std::string & err)
		:SLListException(err) {}
};

template <typename E>
class SLinkedList;

template <typename E>
class SNode
{
private:
	E elem;
	SNode<E> * next;
	friend class SLinkedList<E>;
};

template <typename E>
class SLinkedList
{
public:
	SLinkedList();
	~SLinkedList();
	bool IsEmpty() const;
	const E& Front() const;
	void Add(const E& elem);
	bool Remove(const E& elem) throw(EmptySLList);
	void PrintSLList();
private:
	SNode<E> * head;
	void PrintSNode(SNode<E> * cur);
	void DeleteSNode(SNode <E> * cur);
	void TraverseSLList(void(SLinkedList<E>::*func)(SNode<E> * cur));
};

//private methods for Class SLinkedList

/*print information of Node, need '<<' operation for Node*/
template <typename E>
void SLinkedList<E>::PrintSNode(SNode<E> * cur) 
{
	std::cout << cur->elem << endl;
}

template <typename E>
void SLinkedList<E>::DeleteSNode(SNode<E> * cur)
{
	delete cur;
}

template <typename E>
void SLinkedList<E>::TraverseSLList(void(SLinkedList<E>::*func)(SNode<E> * cur))
{
	//SLinkedList<E> T;
	SNode<E> * cur;
	SNode<E> * temp;
	cur = head;
	while (nullptr != cur)
	{
		temp = cur;
		cur = cur->next;
		(this->*func)(temp);
	}
}

//public methods for Class SLinkedList
template <typename E>
SLinkedList<E>::SLinkedList() :head(nullptr) {}

template <typename E>
SLinkedList<E>::~SLinkedList()
{
	TraverseSLList(&SLinkedList<E>::DeleteSNode);
	head = nullptr;
}

template <typename E>
bool SLinkedList<E>::IsEmpty() const
{
	return nullptr == head;
}

template <typename E>
const E& SLinkedList<E>::Front() const
{
	return head->elem;
}

/*add elem in ascending order, need operation '<' for elem*/
template <typename E>
void SLinkedList<E>::Add(const E& elem)
{
	SNode<E> * cur;
	SNode<E> * temp;
	SNode<E> ** link = &head;
	while ((cur = *link) != nullptr && cur->elem < elem)
	{
		link = &cur->next;
	}
	temp = new SNode<E>;
	temp->elem = elem;
	temp->next = cur;
	*link = temp;
}

/*remove elem in list, need operation '!=' for elem*/
template <typename E>
bool SLinkedList<E>::Remove(const E& elem) throw(EmptySLList)
{
	SNode<E> * cur;
	SNode<E> ** link = &head;
	if (nullptr == head)   //list is empty
		throw EmptySLList("The singly linked list is empty");
	while ((cur = *link) != nullptr && cur->elem != elem)
	{
		link = &cur->next;
	}
	if (nullptr == cur)
		return false;
	*link = cur->next;
	delete cur;
	return true;
}

template <typename E>
void SLinkedList<E>::PrintSLList()
{
	TraverseSLList(&SLinkedList<E>::PrintSNode);
}

#endif
