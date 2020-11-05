#include "file_handler.h"
#include "file_handler.h"

file_handler::file_handler(const string& filename)
{
    this->filename = filename;
}

void file_handler::write_to_file(vector<car>& data, string& fName)
{
    ofstream fout(fName);

    for (int i = 0; i < data.size(); i++) 
    {
        fout << data.at(i).number<<' '<<data.at(i).brand<<' '<< data.at(i).owner << ' ' << data.at(i).stolen << ' ';

        if (i != data.size() - 1) 
        {
            fout << endl;
        }
    }

    fout.close();
}

void file_handler::get_from_file(vector<car>& data)
{
    ifstream fin;
    fin.open(filename);

    if (fin.is_open())
    {
        data.clear();
        car p;
        string number;

        while (fin.good())
        {
            getline(fin, number, ' ');
            if (number.empty() || number == "\n")
            {
                break;
            }
            else if (!data.empty())
            {
                number.erase(0, 1);
            }
            p.number = number;
            getline(fin, p.brand, ' ');
            getline(fin, p.owner, ' ');
            getline(fin, p.stolen, ' ');
            data.push_back(p);
        }
    }
    else
    {
        cout << "Could not open the file " << filename << endl;
    }

    fin.close();
}

void file_handler::write_test()
{
    vector<car> data;
    car p1 = car("H292YS", "Toyota", "Roman", "Yes");
    car p2 = car("B929WS", "BMW", "Steve", "No");
    car p3 = car("M727AR", "Ferrari", "Barbara", "Yes");
    car p4 = car("F800FD", "Lambargini", "Bob", "No");
    car p5 = car("K200RM", "Mercedes", "Alex", "Yes");
    data.push_back(p1);
    data.push_back(p2);
    data.push_back(p3);
    data.push_back(p4);
    data.push_back(p5);
    write_to_file(data, filename);
}



bool file_handler::delete_element(string Number) 
{
    vector<car> data;
    get_from_file(data);
    int size = data.size();
    for (int i = 0; i < size; ++i)
    {
        if (Number == data[i].number) 
        {
            for (int j = i; j < data.size() - 1; j++) 
            {
                data[j] = data[j + 1];
            }
            data.pop_back();
            i--;
            size--;
        }
    }
    write_to_file(data, filename);
    return size == data.size();
}

void file_handler::print_stolen()
{
    vector<car> data;
    get_from_file(data);

    if (data.empty()) 
    {
        cout << "File is empty" << endl;
        return;
    }

    int size = data.size();
    for (int i = 0; i < size; ++i)
    {
        if (data[i].stolen == "Yes")
        {
            data[i].print();
        }
    }
}

bool file_handler::check_stolen(const string& Number)
{
    vector<car> data;
    get_from_file(data);

    if (data.empty()) 
    {
        cout << "File is empty" << endl;
        return false;
    }

    int size = data.size();
    for (int i = 0; i < size; ++i)
    {
        if (data[i].number == Number)
        {
            if (data[i].stolen == "Yes")
                return true;
            else
                return false;
        }
    }
    cout << "This car wasn't found, check the number you entered" << endl;
    return false;
}

void file_handler::print() 
{
    vector<car> data;
    get_from_file(data);

    if (data.empty()) 
    {
        cout << "File is empty" << endl;
    }
    cout << "File contents" << endl;
    for (int i = 0; i < data.size(); i++)
    {
        data[i].print();
    }
}