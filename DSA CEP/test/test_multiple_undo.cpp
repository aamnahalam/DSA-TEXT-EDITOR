
#include <iostream>
#include "Document.h"
#include "UndoManager.h"
using namespace std;

int main()
{
    Document document;
    UndoManager manager;

    string oldText;

    // Initial document
    document.insertLine(1, "Hello World");
    document.insertLine(2, "Welcome to NED");

    cout << "INITIAL DOCUMENT:" << endl;
    document.display();

    // First edit
    manager.saveState(document);
    document.editLine(1, "Hello Students", oldText);

    // Second edit
    manager.saveState(document);
    document.editLine(2, "Welcome to Programming", oldText);

    cout << "\nAFTER TWO EDITS:" << endl;
    document.display();

    // First Undo
    cout << "\nFIRST UNDO:" << endl;
    manager.undo(document);
    document.display();

    // Second Undo
    cout << "\nSECOND UNDO:" << endl;
    manager.undo(document);
    document.display();

    // Redo
    cout << "\nFIRST REDO:" << endl;
    manager.redo(document);
    document.display();

    // New edit after Undo and Redo
    cout << "\nNEW EDIT AFTER REDO:" << endl;

    manager.saveState(document);
    document.editLine(2, "New Text", oldText);
    document.display();

    // Check whether old Redo history was cleared
    cout << "\nCAN REDO? ";

    if (manager.canRedo())
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    // Undo the new edit
    cout << "\nUNDO NEW EDIT:" << endl;
    manager.undo(document);
    document.display();

    return 0;
}
