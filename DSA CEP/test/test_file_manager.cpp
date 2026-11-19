
#include <iostream>
#include "FileManager.h"

using namespace std;

int main()
{
    Document doc;
    FileManager fileManager;

    // TEST 1: CREATE DOCUMENT
    cout << "\n========== TEST 1: CREATE DOCUMENT ==========" << endl;

    doc.insertLine(1, "Welcome to NED University");
    doc.insertLine(2, "Computer Systems Engineering");
    doc.insertLine(3, "DSA Text Editor Project");

    doc.display();

    // TEST 2: SAVE FILE
    cout << "\n========== TEST 2: SAVE FILE ==========" << endl;

    if (fileManager.saveFile(doc, "mydocument.txt"))
    {
        cout << "Save test passed!" << endl;
    }
    else
    {
        cout << "Save test failed!" << endl;
        return 1;
    }

    // TEST 3: OPEN FILE
    cout << "\n========== TEST 3: OPEN FILE ==========" << endl;

    Document newDoc;

    if (fileManager.openFile(newDoc, "mydocument.txt"))
    {
        cout << "Open test passed!" << endl;
    }
    else
    {
        cout << "Open test failed!" << endl;
        return 1;
    }

    newDoc.display();

    // TEST 4: VERIFY DOCUMENT CONTENTS
    cout << "\n========== TEST 4: VERIFY CONTENTS ==========" << endl;

    bool correct = true;

    if (newDoc.getLineCount() != 3)
        correct = false;

    if (newDoc.getLine(1) != "Welcome to NED University")
        correct = false;

    if (newDoc.getLine(2) != "Computer Systems Engineering")
        correct = false;

    if (newDoc.getLine(3) != "DSA Text Editor Project")
        correct = false;

    if (correct)
        cout << "All document contents verified successfully!" << endl;
    else
        cout << "Document verification failed!" << endl;

    // TEST 5: SAVE AS
    cout << "\n========== TEST 5: SAVE AS ==========" << endl;

    if (fileManager.saveAs(newDoc, "backup.txt"))
    {
        cout << "Save As test passed!" << endl;
    }
    else
    {
        cout << "Save As test failed!" << endl;
        return 1;
    }

    cout << "\n========== FILE MANAGEMENT TESTS COMPLETED ==========" << endl;

    return 0;
}
