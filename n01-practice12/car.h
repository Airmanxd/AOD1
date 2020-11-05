#pragma once
#include <string>
using namespace std;
class car
{
public:
	string number, brand, owner, stolen;
	car();
	car(string number, string brand, string owner, string stolen);
	void print();
};

