
#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
    Stack<int> s(3);

    cout << "Initial Capacity: "
         << s.getCapacity() << endl;

    cout << "\nPushing elements..." << endl;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Capacity after 3 elements: "
         << s.getCapacity() << endl;

    s.push(40);

    cout << "Capacity after 4 elements: "
         << s.getCapacity() << endl;

    s.push(50);
    s.push(60);
    s.push(70);

    cout << "Capacity after 7 elements: "
         << s.getCapacity() << endl;

    cout << "\nTop Element: " << s.peek() << endl;

    cout << "Total Elements: " << s.getSize() << endl;

    cout << "\nTesting Pop..." << endl;

    s.pop();

    cout << "New Top Element: " << s.peek() << endl;

    cout << "Total Elements: " << s.getSize() << endl;

    return 0;
}
