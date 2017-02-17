#include "singly_linked_list.h"
#include <iostream>

using namespace std;

class student
{
private:
	string name;
	int score;
public:
	student()
		:name("None"), score(0) {}
	student(int score, string s = "None")
		:name(s), score(score) {}
	bool operator<(const student & t) const;
	bool operator!=(const student & t)const;
	friend std::ostream & operator<<(std::ostream & os, const student & t);
};

int main(void)
{
	SLinkedList<int> num;
	SLinkedList<student> students;
	cout << "add 5,7,0 to list" << endl;
	num.Add(5);
	num.Add(7);
	num.Add(0);
	cout << "print list\n";
	num.PrintSLList();
	cout << endl;
	cout << "test Iterator in list" << endl;

	SLinkedList<int>::Iterator it = num.begin();
	for(;it != num.end();++it)
		cout << *it << endl;

	cout << "The first num in list is " << num.Front() << endl;

	cout << "remove num 5\n";
	if (num.Remove(5))
	{
		num.PrintSLList();
		cout << endl;
	}
	else
	{
		cout << "cannot find num 5 in list\n";
		num.PrintSLList();
		cout << endl;
	}
	cout << "remove num 10" << endl;
	if (num.Remove(10))
	{
		num.PrintSLList();
		cout << endl;
	}
	else
	{
		cout << "cannot find num 10 in list\n";
		num.PrintSLList();
		cout << endl;
	}

	if (num.IsEmpty())
	{
		cout << "list is empty" << endl;
	}
	else
	{
		cout << "list is not empty" << endl;
	}

	cout << "Add item(name: Tom socre: 80)" << endl;
	students.Add(student(80, "Tom"));
	cout << "Add item(name: John score 80)" << endl;
	students.Add(student(80, "John"));
	cout << "Add item(name: Alex score 96)" << endl;
	students.Add(student(96, "Alex"));
	cout << "Add item(name: Tim score: 75)" << endl;
	students.Add(student(75, "Tim"));
	cout << "Print list: " << endl;
	students.PrintSLList();

	cout << "Test Iterator in list" << endl;
	SLinkedList<student>::Iterator st = students.begin();
	for(;st != students.end();++st)
		cout << *st << endl;

	cout << "The first elem is: " << students.Front() << endl;

	cout << "remove item(name: Tom socre: 80)\n";
	if (students.Remove(student(80,"Tom")))
	{
		students.PrintSLList();
		cout << endl;
	}
	else
	{
		cout << "cannot find item(name: Tom socre: 80) in list\n";
		students.PrintSLList();
		cout << endl;
	}
	cout << "remove item(name: TTom socre: 80)" << endl;
	if (students.Remove(student(80,"TTom")))
	{
		students.PrintSLList();
		cout << endl;
	}
	else
	{
		cout << "cannot find item(name: TTom socre: 80) in list\n";
		students.PrintSLList();
		cout << endl;
	}

	if (students.IsEmpty())
	{
		cout << "list is empty" << endl;
	}
	else
	{
		cout << "list is not empty" << endl;
	}

	cout << "Done!" << endl;
	return 0;
}

bool student::operator<(const student & t) const
{
	if (this->score < t.score)
		return true;
	else
		return false;
}

bool student::operator!=(const student & t) const
{
	if (this->score != t.score || this->name != t.name)
		return true;
	else
		return false;
}

std::ostream & operator<<(std::ostream & os, const student & t)
{
	os << "name: " << t.name << "  " << "score: " << t.score;
	return os;
}
