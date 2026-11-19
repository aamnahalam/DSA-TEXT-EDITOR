
#include <iostream>
#include "EditorController.h"

using namespace std;

int main()
{
    EditorController editor;

    cout << "\n========== TEST 1: INSERT DOCUMENT ==========" << endl;

    editor.insertLine(1, "Welcome to NED University");
    editor.insertLine(2, "Computer Systems Engineering");
    editor.insertLine(3, "DSA Text Editor Project");

    editor.display();

    cout << "\n========== TEST 2: SAVE FILE ==========" << endl;

    if (editor.saveFile("editor_document.txt"))
        cout << "Save test passed!" << endl;
    else
        cout << "Save test failed!" << endl;

    cout << "\n========== TEST 3: EDIT DOCUMENT ==========" << endl;

    editor.editLine(1, "Welcome to our Text Editor");

    editor.display();

    cout << "\n========== TEST 4: OPEN SAVED FILE ==========" << endl;

    if (editor.openFile("editor_document.txt"))
        cout << "Open test passed!" << endl;
    else
        cout << "Open test failed!" << endl;

    editor.display();

    cout << "\n========== TEST 5: VERIFY UNDO HISTORY ==========" << endl;

    if (editor.undo())
        cout << "Undo was possible!" << endl;
    else
        cout << "Undo history is correctly cleared!" << endl;

    cout << "\n========== TEST 6: SAVE AS ==========" << endl;

    if (editor.saveAs("editor_backup.txt"))
        cout << "Save As test passed!" << endl;
    else
        cout << "Save As test failed!" << endl;

    cout << "\n========== FILE INTEGRATION TESTS COMPLETED ==========" << endl;

    return 0;
}
