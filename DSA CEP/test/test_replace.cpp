#include <iostream>
#include "Document.h"
#include "SearchEngine.h"

using namespace std;

int main()
{
    Document doc;
    SearchEngine search;

    doc.insertLine(1, "I love Java.");
    doc.insertLine(2, "Java is interesting.");
    doc.insertLine(3, "I am learning Java.");

    cout << "========== ORIGINAL DOCUMENT ==========\n";
    doc.display();

    // TEST 1: REPLACE ONE
    cout << "\nTEST 1: REPLACE ONE\n";

    if (search.replaceOne(doc, "Java", "C++"))
        cout << "One occurrence replaced successfully.\n";
    else
        cout << "Text not found.\n";

    doc.display();

    // TEST 2: REPLACE ALL
    cout << "\nTEST 2: REPLACE ALL\n";

    int count = search.replaceAll(doc, "Java", "Python");

    cout << "Total replacements: " << count << endl;

    doc.display();

    // TEST 3: WORD NOT FOUND
    cout << "\nTEST 3: WORD NOT FOUND\n";

    count = search.replaceAll(doc, "HTML", "CSS");

    cout << "Total replacements: " << count << endl;

    // TEST 4: EMPTY SEARCH
    cout << "\nTEST 4: EMPTY SEARCH\n";

    count = search.replaceAll(doc, "", "C++");

    cout << "Total replacements: " << count << endl;

    // TEST 5: DELETE MATCH BY REPLACING WITH EMPTY TEXT
    cout << "\nTEST 5: REPLACE WITH EMPTY TEXT\n";

    count = search.replaceAll(doc, "Python", "");

    cout << "Total replacements: " << count << endl;

    doc.display();

    return 0;
}