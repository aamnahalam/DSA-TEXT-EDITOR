
#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{
    Stack<int> s(5);

    cout << "Pushing elements into Stack..." << endl;

    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top element: " << s.peek() << endl;

    cout << "Stack size: " << s.getSize() << endl;

    cout << "\nRemoving top element..." << endl;

    s.pop();

    cout << "New top element: " << s.peek() << endl;

    cout << "Stack size: " << s.getSize() << endl;

    cout << "\nRemoving all elements..." << endl;

    s.pop();
    s.pop();

    cout << "Is stack empty? ";

    if (s.isEmpty())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}
