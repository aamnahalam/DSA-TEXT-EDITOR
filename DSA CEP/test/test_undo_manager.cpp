
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

    // Save state before editing
    manager.saveState(document);

    // Edit document
    document.editLine(1, "Hello Students", oldText);

    cout << "\nAFTER EDIT:" << endl;
    document.display();

    // Test Undo
    cout << "\nPERFORMING UNDO..." << endl;

    if (manager.undo(document))
        document.display();
    else
        cout << "Nothing to undo!" << endl;

    // Test Redo
    cout << "\nPERFORMING REDO..." << endl;

    if (manager.redo(document))
        document.display();
    else
        cout << "Nothing to redo!" << endl;

    // Test Undo availability
    cout << "\nCan Undo? "
         << (manager.canUndo() ? "Yes" : "No") << endl;

    cout << "Can Redo? "
         << (manager.canRedo() ? "Yes" : "No") << endl;

    return 0;
}
