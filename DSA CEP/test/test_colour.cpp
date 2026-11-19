
#include <iostream>
#include "Colours.h"

using namespace std;

int main()
{
    cout << CYAN << BOLD;
    cout << "====================================\n";
    cout << "          NOVA TEXT EDITOR          \n";
    cout << "====================================\n";

    cout << RESET;

    cout << GREEN << "SUCCESS: Document saved!\n";
    cout << YELLOW << "WARNING: Unsaved changes!\n";
    cout << RED << "ERROR: File not found!\n";
    cout << MAGENTA << "UNDO: Previous action restored!\n";
    cout << BLUE << "REDO: Action performed again!\n";

    cout << RESET;

    return 0;
}
