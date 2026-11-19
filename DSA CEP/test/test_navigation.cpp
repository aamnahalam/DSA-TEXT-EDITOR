
#include <iostream>
#include "EditorController.h"

using namespace std;

int main()
{
    EditorController editor;

    editor.insertLine(1, "Computer engineering is interesting.");
    editor.insertLine(2, "I study Computer systems.");
    editor.insertLine(3, "Computer programming is important.");
    editor.insertLine(4, "Computer networks are useful.");

    cout << "\n========== INITIAL SEARCH ==========\n";

    editor.searchText("Computer");

    cout << "\n========== NEXT SEARCH ==========\n";

    editor.nextSearch();

    editor.nextSearch();

    editor.nextSearch();

    editor.nextSearch();

    cout << "\n========== PREVIOUS SEARCH ==========\n";

    editor.previousSearch();

    editor.previousSearch();

    return 0;
}
