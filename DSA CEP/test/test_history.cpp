
#include <iostream>
#include "EditorController.h"

using namespace std;

int main()
{
    EditorController editor;

    // Insert sample document
    editor.insertLine(1, "Computer systems engineering");
    editor.insertLine(2, "Computer programming");
    editor.insertLine(3, "Data structures and algorithms");

    // Perform searches
    editor.searchText("Computer");

    editor.searchText("engineering");

    editor.searchText("programming");

    editor.searchText("Data");

    // Display search history
    editor.displaySearchHistory();

    // Clear search history
    editor.clearSearchHistory();

    // Display history again
    editor.displaySearchHistory();

    return 0;
}
