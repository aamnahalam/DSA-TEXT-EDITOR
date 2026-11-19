
#include <iostream>
#include "Document.h"
using namespace std;

int main()
{
    Document original;

    original.insertLine(1, "Hello World");
    original.insertLine(2, "Welcome to NED");

    cout << "Original Document:" << endl;
    original.display();

    // Create a deep copy
    Document copy = original;

    copy.insertLine(3, "DSA Project");

    cout << "\nCopied Document:" << endl;
    copy.display();

    cout << "\nOriginal Document After Copy Modification:" << endl;
    original.display();

    // Test assignment operator
    Document assigned;
    assigned = original;

    cout << "\nAssigned Document:" << endl;
    assigned.display();

    return 0;
}
