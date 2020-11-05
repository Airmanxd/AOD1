#include <iostream>
#include "file_handler.h"
int main()
{
    string number;
    file_handler handler = file_handler("test.txt");
    handler.write_test();
    handler.print();
    cout << "Stolen cars" << endl;
    handler.print_stolen();
    cout << "Check if a car is stolen (enter the number of the car you want to check): ";
    cin >> number;
    if (handler.check_stolen(number))
        cout << "Stolen" << endl;
    else
        cout << "Not stolen :)" << endl;
    handler.delete_element(number);
    cout << "Data without the checked car" << endl;
    handler.print();
}