#include <iostream>
#include "Document.h"
#include "SearchEngine.h"

using namespace std;

int main()
{
    Document doc;
    SearchEngine search;

    doc.insertLine(1, "I love programming.");
    doc.insertLine(2, "I enjoy programming.");
    doc.insertLine(3, "I am learning C++ programming.");

    cout << "========== DOCUMENT ==========\n";
    doc.display();

    cout << "\nTEST 1: SEARCH EXISTING WORD\n";
    search.searchText(doc, "programming");

    cout << "\nTEST 2: SEARCH NON-EXISTING WORD\n";
    search.searchText(doc, "Python");

    cout << "\nTEST 3: SEARCH EMPTY WORD\n";
    search.searchText(doc, "");

    return 0;
}