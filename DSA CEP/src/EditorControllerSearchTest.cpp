
#include <iostream>
#include "EditorController.h"

using namespace std;

int main()
{
    EditorController editor;

    // INSERTING LINES
    cout << "\nINSERTING LINES:" << endl;

    editor.insertLine(1, "Hello World");
    editor.insertLine(2, "Welcome to NED");

    editor.display();

    // EDITING LINE
    cout << "\nEDITING LINE:" << endl;

    editor.editLine(1, "Hello Students");

    editor.display();

    // UNDO
    cout << "\nUNDO:" << endl;

    editor.undo();
    editor.display();

    // REDO
    cout << "\nREDO:" << endl;

    editor.redo();
    editor.display();

    // DELETING LINE
    cout << "\nDELETING LINE:" << endl;

    editor.deleteLine(2);
    editor.display();

    // UNDO DELETE
    cout << "\nUNDO DELETE:" << endl;

    editor.undo();
    editor.display();

    // SEARCH TEST
    cout << "\nSEARCH TEST:" << endl;

    editor.insertLine(3, "Hello again Hello");

    editor.searchText("Hello");

    // REPLACE ONE TEST
    cout << "\nREPLACE ONE TEST:" << endl;

    if (editor.replaceOne("Hello", "Hi"))
    {
        cout << "First occurrence replaced successfully!" << endl;
    }
    else
    {
        cout << "Text not found!" << endl;
    }

    editor.display();

    // REPLACE ALL TEST
    cout << "\nREPLACE ALL TEST:" << endl;

    int count = editor.replaceAll("Hello", "Hi");

    cout << "Total replacements: " << count << endl;

    editor.display();

    // UNDO REPLACE ALL
    cout << "\nUNDO REPLACE ALL:" << endl;

    editor.undo();
    editor.display();

    // REDO REPLACE ALL
    cout << "\nREDO REPLACE ALL:" << endl;

    editor.redo();
    editor.display();

    cout << "\n========== ALL TESTS COMPLETED ==========" << endl;

    return 0;
}
