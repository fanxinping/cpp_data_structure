#pragma once
#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <iostream>
#include <string>

class DLListException
{
public:
	DLListException(const std::string& err)
		:errMsg(err) {}
	std::string GetError() { return errMsg; }
private:
	std::string errMsg;
};

class EmptyDLList : public DLListException
{
public:
	EmptyDLList(const std::string & err)
		:DLListException(err) {}
};

class OutOfMemory : public DLListException
{
public:
	OutOfMemory(const std::string & err)
		:DLListException(err) {}
};

template <typename E>
class DLinkedList;

template <typename E>
class DNode
{
private:
	E elem;
	DNode<E> * prev;
	DNode<E> * next;
	friend class DLinkedList<E>;
};

template <typename E>
class DLinkedList
{
public:
	DLinkedList();
	~DLinkedList();
	bool IsEmpty() const;
	const E& Front() const;
	const E& Back() const;
	void Add(const E& e) throw(OutOfMemory);
	bool Remove(const E& e) throw(EmptyDLList);
	void PrintDLList();
protected:
	void DeleteNode(DNode<E> * cur);
	void PrintNode(DNode<E> * cur);
	void TraverseDLList(void (DLinkedList<E>::*func)(DNode<E> * cur));
private:
	DNode<E> * header;
	DNode<E> * tailer;
};

template <typename E>
DLinkedList<E>::DLinkedList()
{
	header = new DNode<E>;
	tailer = new DNode<E>;
	header->next = tailer;
	tailer->prev = header;
}

template <typename E>
DLinkedList<E>::~DLinkedList()
{
	TraverseDLList(&DLinkedList<E>::DeleteNode);
	delete header;
	delete tailer;
}

template <typename E>
bool DLinkedList<E>::IsEmpty() const
{
	return header->next == tailer;
}

template <typename E>
const E& DLinkedList<E>::Front() const
{
	return header->next->elem;
}

template <typename E>
const E& DLinkedList<E>::Back() const
{
	return tailer->prev->elem;
}

/*add elem to list, need operation '<' for elem*/
template <typename E>
void DLinkedList<E>::Add(const E& e) throw(OutOfMemory)
{
	DNode<E> * cur, *t;
	DNode<E> ** link;
	link = &header->next;
	while ((cur = *link) != tailer && cur->elem < e)
	{
		link = &cur->next;
	}
	t = new DNode<E>;
	if (nullptr == t)
		throw OutOfMemory("Fail to create DNode: out of Memory");
	t->elem = e;
	t->next = cur;
	t->prev = cur->prev;
	*link = t;
	cur->prev = t;
}

/*remove elem form list, need operation '!=' for elem*/
template <typename E>
bool DLinkedList<E>::Remove(const E& e) throw(EmptyDLList)
{
	DNode<E> * cur, *t;
	DNode<E> ** link;
	if (header->next == tailer)
		throw EmptyDLList("The Doubly Linked list is empty");
	link = &header->next;
	while ((cur = *link) != tailer && cur->elem != e)
		link = &cur->next;
	if (cur == tailer)
		return false;
	t = cur;
	*link = cur->next;
	cur->next->prev = cur->prev;
	delete t;
	return true;
}

/*print information of list, need operation '<<' for elem*/
template <typename E>
void DLinkedList<E>::PrintDLList()
{
	TraverseDLList(&DLinkedList<E>::PrintNode);
}

template <typename E>
void DLinkedList<E>::DeleteNode(DNode<E> * cur)
{
	delete cur;
}

/*print information of node, need operation '<<' for elem*/
template <typename E>
void DLinkedList<E>::PrintNode(DNode<E> * cur)
{
	std::cout << cur->elem << std::endl;
}

template <typename E>
void DLinkedList<E>::TraverseDLList(void (DLinkedList<E>::*func)(DNode<E> * cur))
{
	DNode<E> * cur;
	DNode<E> * temp;
	cur = header->next;
	while (cur != tailer)
	{
		temp = cur;
		cur = cur->next;
		(this->*func)(temp);
	}
}
 
#endif