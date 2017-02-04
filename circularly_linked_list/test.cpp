#include "circularly_linked_list.h"
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
	CircleList<int> num;
	CircleList<student> students;
	cout << "add 5,7,0 to list" << endl;
	num.Add(5);
	num.Add(7);
	num.Add(0);
	cout << "print list\n";
	num.PrintCLList();
	cout << endl;
	cout << "The num following cursor in list is " << num.Front() << endl;
	cout << "The num at cursor list is " << num.Back() << endl;

	cout << "Advance cursor" << endl;
	cout << "print list" << endl;
	num.PrintCLList();

	cout << "remove num" << endl;
	num.Remove();
	num.PrintCLList();
	cout << endl;

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
	students.PrintCLList();

	cout << "The element following cursor is: " << students.Front() << endl;
	cout << "The element at cursor is: " << students.Back() << endl;

	cout << "Advance cursor" << endl;
	students.Advance();
	students.PrintCLList();

	cout << "remove item\n";
	students.Remove();
	students.PrintCLList();
	cout << endl;


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
