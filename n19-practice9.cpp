#include <iostream>
using namespace std;
 
class q
{
public:
    int arrival = 0;
    q* next = NULL;
    q* last = NULL;
    int size = 0;
    int departure = 0;
    q()
    {
        last = this;
    }
    void add(int s, int l)
    {
        q* tmp = new q();
        tmp->arrival = s;
        tmp->departure = l;
        last->next = tmp;
        last = tmp;
        size++;
    }
    void del()
    {
        size--;
        q* temp = this->next;
        this->next = temp->next;
        delete temp;
    }
};
 
int main()
{
    int entry, c = 0, dep = 0, last_entry = 0;
    float average = 0;
    q* qu = new q();
    cout << "Enter the data below (-1 to end) ";
    cin >> entry;
    c++;
    dep = entry + 10;
    last_entry = entry;
    cin >> entry;
    while (entry != -1)
    {
        c++;
        while (qu->next != NULL && qu->next->departure < entry)
            qu->del();
 
        if (qu->size < 5)
        {
            if (entry < dep)
            {
                dep += 10;
                qu->add(entry, dep);
                average += dep - entry - 10;
            }
            else
            {
                dep = entry + 10;
            }
        }
        last_entry = entry;
        cin >> entry;
        while (entry < last_entry)
        {
            cout << "Error! Time only moves forward";
            return 0;
        }
    }
    average /= c;
    cout << "Average waiting time for the day was: " << average;
}