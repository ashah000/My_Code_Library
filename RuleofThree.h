#pragma once

#include <iostream>
using namespace std;

/*
if a class defines one (or more) of the following, it should explicitly define all three, which are:

destructor
copy constructor
copy assignment operator

*/
class RuleofThree
{
private:
	int *ptr;

public:
	RuleofThree()
	{
		cout << "In Defualt Constructor" << endl;
		ptr = new int[10];
		for (int i = 0; i < 10; i++)
		{
			ptr[i] = i + 2;
		}
	}

	~RuleofThree()
	{
		cout << "In Destructor" << endl;
		delete[] ptr;
	}

	RuleofThree(const RuleofThree & obj)
	{
		cout << "Copy Constructor Called" << endl;
		ptr = new int[10]; // Deep Copy
		for (int i = 0; i < 10; i++)
		{
			this->ptr[i] = obj.ptr[i];
		}
	}

	RuleofThree(RuleofThree && obj)
	{
		ptr = obj.ptr;
		obj.ptr = nullptr;
	}

	RuleofThree & operator = (const RuleofThree & obj)
	{
		cout << "Assignment operator called " << endl;
		ptr = new int[10];
		for (int i = 0; i < 10; i++)
		{
			this->ptr[i] = obj.ptr[i];
		}
		return *this;
	}
};