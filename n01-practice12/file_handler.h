#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "car.h"
using namespace std;
class file_handler
{
public:
	explicit file_handler(const string& filename);

	bool delete_element(string Number);

	void print_stolen();

	void print();

	bool check_stolen(const string& number);

	void write_test();

private:
	string filename;

	void write_to_file(vector<car>& data_vector, string& filename);

	void get_from_file(vector<car>& data_vector);
};

