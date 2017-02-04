#ifndef __CIRCULARLY_LINKED_LIST_H__

#include <iostream>
#include <string>
#define __CIRCULARLY_LINKED_LIST_H__

class CLListException
{
public:
	CLListException(const std::string& err)
		:errMsg(err) {}
	std::string GetError() { return errMsg; }
private:
	std::string errMsg;
};

class EmptyCLList : public CLListException
{
public:
	EmptyCLList(const std::string & err)
		:CLListException(err) {}
};

class OutOfMemory : public CLListException
{
public:
	OutOfMemory(const std::string & err)
		:CLListException(err) {}
};

template <typename E>
class CircleList;

template <typename E>
class CNode
{
private:
	E elem;
	CNode<E> * next;
	friend class CircleList<E>;
};

template <typename E>
class CircleList
{
public:
	CircleList();
	~CircleList();
	bool IsEmpty() const;
	const E& Front() const;  //element following cursor
	const E& Back() const;    //element at cursor
	void Advance();           //advance cursor
	void Add(const E& e) throw(OutOfMemory);     //add after cursor
	void Remove()throw(EmptyCLList);            //remove node after cursor
	void PrintCLList();
protected:
	void TraverseCLList(void (CircleList<E>::*func)(CNode<E> * cur));
	void PrintNode(CNode<E> * cur);
	void DeleteNode(CNode<E> * cur);
private:
	CNode<E> * cursor;
};

template <typename E>
CircleList<E>::CircleList()
	:cursor(nullptr) {}

template <typename E>
CircleList<E>::~CircleList()
{
	TraverseCLList(&CircleList<E>::DeleteNode);
	cursor = nullptr;
}

template <typename E>
bool CircleList<E>::IsEmpty()const
{
	return nullptr == cursor;
}

template <typename E>
const E& CircleList<E>::Front() const
{
	return cursor->next->elem;
}

template <typename E>
const E& CircleList<E>::Back() const
{
	return cursor->elem;
}

template <typename E>
void CircleList<E>::Advance()
{
	cursor = cursor->next;
}

template <typename E>
void CircleList<E>::Add(const E& e) throw(OutOfMemory)
{
	CNode<E> * t = new CNode<E>;
	if (nullptr == t)
		throw OutOfMemory("Fail to create CNode: out of memory");
	t->elem = e;
	if (nullptr == cursor)
	{
		t->next = t;
		cursor = t;
	}
	else
	{
		t->next = cursor->next;
		cursor->next = t;
	}
}

template <typename E>
void CircleList<E>::Remove() throw(EmptyCLList)
{
	CNode<E> * old = cursor->next;
	if (nullptr == cursor)
		throw EmptyCLList("The List is empty");
	if (old == cursor)
	{
		cursor = nullptr;
	}
	else
	{
		cursor->next = old->next;
	}
	delete old;
}

template <typename E>
void CircleList<E>::PrintCLList()
{
	TraverseCLList(&CircleList<E>::PrintNode);
}

template <typename E>
void CircleList<E>::TraverseCLList(void (CircleList<E>::*func)(CNode<E> * cur))
{
	CNode<E> * temp, *cur;
	if (nullptr == cursor)
		return;
	cur = cursor;
	do
	{
		temp = cur;
		cur = cur->next;
		(this->*func)(temp);
	} while (cur != cursor);
}

template <typename E>
void CircleList<E>::DeleteNode(CNode<E> * cur)
{
	delete cur;
}

template <typename E>
void CircleList<E>::PrintNode(CNode<E> * cur)
{
	std::cout << cur->elem << std::endl;
}

#endif // !__CIRCULARLY_LINKED_LIST_H__
