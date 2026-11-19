
#include "Document.h"

int main()
{
    Document doc;

    string oldText;
    string deletedText;

    cout << "TEST 1: INSERT LINES\n";

    doc.insertLine(1, "Hello World");
    doc.insertLine(2, "Welcome to NED");
    doc.insertLine(3, "DSA Project");

    doc.display();

    cout << "\nTEST 2: INSERT TEXT\n";

    doc.insertText(1, 7, "C++ ");

    doc.display();

    cout << "\nTEST 3: EDIT LINE\n";

    doc.editLine(2, "Computer Systems Engineering", oldText);

    cout << "Old line: " << oldText << endl;

    doc.display();

    cout << "\nTEST 4: DELETE TEXT\n";

    doc.deleteText(1, 1, 5, deletedText);

    cout << "Deleted text: " << deletedText << endl;

    doc.display();

    cout << "\nTEST 5: DELETE LINE\n";

    doc.deleteLine(3, deletedText);

    cout << "Deleted line: " << deletedText << endl;

    doc.display();

    cout << "\nTEST 6: DOCUMENT STATISTICS\n";

    cout << "Total lines: " << doc.getLineCount() << endl;

    cout << "Total characters: "
         << doc.getCharacterCount() << endl;

    cout << "\nTEST 7: INVALID LINE NUMBER\n";

    if (!doc.deleteLine(10, deletedText))
    {
        cout << "Invalid line number detected successfully.\n";
    }
    
     cout << "\nTEST 8: DYNAMIC ARRAY RESIZING\n";

doc.insertLine(3, "Fourth line");
doc.insertLine(4, "Fifth line");
doc.insertLine(5, "Sixth line");

doc.display();

 cout << "\nTEST 9: DELETE CHARACTER\n";

    doc.insertLine(3, "COMPUTER");

    if (doc.deleteCharacter(3, 4, deletedText))
    {
        cout << "Deleted character: " << deletedText << endl;
    }

    doc.display();


    cout << "\nTEST 10: DELETE WORD\n";

    doc.insertLine(4, "I love Computer Engineering");

    if (doc.deleteWord(4, 9, deletedText))
    {
        cout << "Deleted word: " << deletedText << endl;
    }

    doc.display();


    cout << "\nTEST 11: DELETE RANGE\n";

    doc.insertLine(5, "ABCDEFGHIJ");

    if (doc.deleteRange(5, 3, 5, deletedText))
    {
        cout << "Deleted range: " << deletedText << endl;
    }

    doc.display();

    cout << "\nALL TESTS COMPLETED.\n";

    return 0;
}
