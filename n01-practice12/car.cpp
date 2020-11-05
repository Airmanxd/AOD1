#include "car.h"
#include <string>
#include <iostream>
using namespace std;
car::car(string number, string brand, string owner, string stolen)
{
	this->number = number;
	this->brand = brand;
	this->owner = owner;
	this->stolen = stolen;
}

car::car() = default;

void car::print()
{
	cout << "Number: " << this->number << endl
		<< "Brand: " << this->brand << endl
		<< "Owner: " << this->owner << endl
		<< "Stolen: " << this->stolen << endl << "-----------------------" << endl;
}

