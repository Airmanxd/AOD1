#include <iostream>
using namespace std;

int HashFunctionHorner(const string& s, int table_size, const int key)
{
    int hash_result = 0;
    for (int i = 0; s[i] != 0; ++i)
    {
        hash_result = (key * hash_result + s[i]) % table_size;
    }
    hash_result = (hash_result * 2 + 1) % table_size;
    return hash_result;
}
int hash1(const string& s, int table_size)
{
    return HashFunctionHorner(s, table_size, table_size - 1);
}
int hash2(const string& s, int table_size)
{
    return HashFunctionHorner(s, table_size, table_size + 1);
}

class HashTable
{
    static const int default_size = 8;
    constexpr static const double rehash_size = 0.75;
    struct Node
    {
        string name, phone;
        bool state;
        Node(const string& name_, const string& phone_) : name(name_), phone(phone_), state(true) {}
    };
    Node** arr;
    int size;
    int buffer_size;
    int size_all_non_nullptr;

    void resize()
    {
        int past_buffer_size = buffer_size;
        buffer_size *= 2;
        size_all_non_nullptr = 0;
        size = 0;
        Node** arr2 = new Node * [buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr2[i] = nullptr;
        swap(arr, arr2);
        for (int i = 0; i < past_buffer_size; ++i)
        {
            if (arr2[i] && arr2[i]->state)
                add(arr2[i]->name, arr2[i]->phone);
        }
        for (int i = 0; i < past_buffer_size; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

    void rehash()
    {
        size_all_non_nullptr = 0;
        size = 0;
        Node** arr2 = new Node * [buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr2[i] = nullptr;
        swap(arr, arr2);
        for (int i = 0; i < buffer_size; ++i)
        {
            if (arr2[i] && arr2[i]->state)
                add(arr2[i]->name, arr2[i]->phone);
        }
        for (int i = 0; i < buffer_size; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

public:
    HashTable()
    {
        buffer_size = default_size;
        size = 0;
        size_all_non_nullptr = 0;
        arr = new Node * [buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr[i] = nullptr;
    }
    ~HashTable()
    {
        for (int i = 0; i < buffer_size; ++i)
            if (arr[i])
                delete arr[i];
        delete[] arr;
    }
    bool add(const string& name, const string& phone)
    {
        if (size + 1 > int(rehash_size * buffer_size))
            resize();
        else if (size_all_non_nullptr > 2 * size)
            rehash();
        int h1 = hash1(name, buffer_size);
        int h2 = hash2(name, buffer_size);
        int i = 0;
        int first_deleted = -1;
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->name == name && arr[h1]->state)
                return false;
            if (!arr[h1]->state && first_deleted == -1)
                first_deleted = h1;
            h1 = (h1 + h2) % buffer_size;
            ++i;
        }
        if (first_deleted == -1)
        {
            arr[h1] = new Node(name, phone);
            ++size_all_non_nullptr;
        }
        else
        {
            arr[first_deleted]->name = name;
            arr[first_deleted]->phone = phone;
            arr[first_deleted]->state = true;
        }
        ++size;
        return true;
    }
    bool remove(const string& name)
    {
        int h1 = hash1(name, buffer_size);
        int h2 = hash2(name, buffer_size);
        int i = 0;
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->name == name && arr[h1]->state)
            {
                arr[h1]->state = false;
                --size;
                return true;
            }
            h1 = (h1 + h2) % buffer_size;
            ++i;
        }
        return false;
    }
    bool find(const string& name)
    {
        int h1 = hash1(name, buffer_size);
        int h2 = hash2(name, buffer_size);
        int i = 0;
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->name == name && arr[h1]->state)
            {
                cout << "value: "<< arr[h1]->name << " state: "<< arr[h1]->state;
                return true;

            }
            h1 = (h1 + h2) % buffer_size;
            ++i;
        }
        return false;
    }
    void print()
    {
        for (int i = 0; i < buffer_size; i++)
        {
            if (arr[i] != nullptr && arr[i]->state)
                cout << i + 1 << ": " << arr[i]->name << ": " << arr[i]->phone << endl;
        }
    }
};

int main()
{
    HashTable* table = new HashTable();
    string name, phone, data;
    cout << "Enter the name: ";
    cin >> name;
    while (name != "END")
    {
        cout << "Enter the phone: ";
        cin >> phone;
        data = name + ": " + phone;
        table->add(name, phone);
        table->print();
        cout << "Enter the name (END to end the input, REMOVE to remove a person from the table): ";
        cin >> name;
        if (name == "REMOVE")
        {
            cin >> name;
            table->remove(name);
            table->print();
            cout << "Enter the name (END to end the input): ";
        }
    }

}

