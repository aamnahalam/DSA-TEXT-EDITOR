#include <iostream>
#include "EditorController.h"

using namespace std;

int main()
{
    EditorController editor;

    editor.insertLine(1, "banana");
    editor.insertLine(2, "Computer engineering");
    editor.insertLine(3, "Computer programming");
    editor.insertLine(4, "Computer networks");

    cout << "\n========== TEST 1: INSERT DOCUMENT ==========\n";
    editor.display();

    cout << "\n========== TEST 2: SEARCH MULTIPLE OCCURRENCES ==========\n";
    editor.searchText("ana");

    cout << "\n========== TEST 3: NEXT SEARCH ==========\n";
    editor.nextSearch();

    cout << "\n========== TEST 4: PREVIOUS SEARCH ==========\n";
    editor.previousSearch();

    cout << "\n========== TEST 5: SEARCH NONEXISTENT WORD ==========\n";
    editor.searchText("Python");

    cout << "\n========== TEST 6: EDIT AFTER SEARCH ==========\n";
    editor.searchText("Computer");
    editor.editLine(2, "Updated engineering line");
    editor.nextSearch();

    cout << "\n========== TEST 7: FINAL DOCUMENT ==========\n";
    editor.display();

    return 0;
}