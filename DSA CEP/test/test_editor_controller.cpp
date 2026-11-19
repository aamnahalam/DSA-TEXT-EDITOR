#include <iostream>
#include "EditorController.h"
using namespace std;

int main()
{
    EditorController editor;

    cout << "INSERTING LINES:" << endl;

    editor.insertLine(1, "Hello World");
    editor.insertLine(2, "Welcome to NED");

    editor.display();

    cout << "\nEDITING LINE:" << endl;

    editor.editLine(1, "Hello Students");

    editor.display();

    cout << "\nUNDO:" << endl;

    editor.undo();
    editor.display();

    cout << "\nREDO:" << endl;

    editor.redo();
    editor.display();

    cout << "\nDELETING LINE:" << endl;

    editor.deleteLine(2);
    editor.display();

    cout << "\nUNDO DELETE:" << endl;

    editor.undo();
    editor.display();

    return 0;
}