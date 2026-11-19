#include "TextEditor.h"
#include "Colours.h"
#include <sstream>
#include <chrono>

// Constructor
TextEditor::TextEditor()
{
    isModified = false;
     lightMode = false;
     autoSaveEnabled = false;
}

// Colorful Welcome Screen
void TextEditor::showWelcomeScreen()
{
    applyTheme();

    // Clear terminal
    cout << "\033[2J\033[H";
cout << BRIGHT_CYAN << BOLD;

cout << "\n\n";
cout << "====================================================\n";
cout << "                                                    \n";
cout << "                      D S A                         \n";
cout << "                                                    \n";
cout << "                  TEXT   EDITOR                        \n";
cout << "                                                    \n";
cout << "====================================================\n";

cout << RESET;

    cout << "\n";

    cout << BRIGHT_MAGENTA << BOLD;
    cout << "          YOUR PERSONAL WRITING SPACE\n";
    cout << RESET;

    cout << "\n";

    cout << CYAN;
    cout << "       Create. Edit. Search. Save. Explore.\n";
    cout << RESET;

    cout << "\n";

    cout << GREEN;
    cout << "       * Undo and Redo Support\n";
    cout << "       * Advanced Search and Replace\n";
    cout << "       * Document Management\n";
    cout << "       * Search History\n";
    cout << RESET;

    cout << "\n";

    cout << YELLOW << BOLD;
    cout << "          Press ENTER to launch editor...";
    cout << RESET;

    string enter;
    getline(cin, enter);

    // Clear screen before opening main menu
    // Apply selected theme and clear screen

applyTheme();
    cout << "\033[2J\033[H";
}
// Change between Dark Mode and Light Mode
// Apply the selected terminal theme
void TextEditor::applyTheme()
{
    if (lightMode)
    {
        // Light Mode: White background, black default text
        cout << "\033]11;#FFFFFF\007";
        cout << "\033]10;#000000\007";
    }
    else
    {
        // Dark Mode: Black background, white default text
        cout << "\033]11;#000000\007";
        cout << "\033]10;#FFFFFF\007";
    }
}

// Change between Dark Mode and Light Mode
void TextEditor::changeTheme()
{
    lightMode = !lightMode;

    applyTheme();

    // Clear screen so the new background becomes visible
    cout << "\033[2J\033[H";

    if (lightMode)
    {
        cout << GREEN << BOLD;
        cout << "Light Mode activated successfully!\n";
    }
    else
    {
        cout << BRIGHT_CYAN << BOLD;
        cout << "Dark Mode activated successfully!\n";
    }

    cout << RESET;
}
// Read an integer safely
int TextEditor::readNumber(string message)
{
    string input;
    int number;
    char extra;

    while (true)
    {
        cout << message;
        getline(cin, input);

        stringstream ss(input);

        if (ss >> number && !(ss >> extra))
        {
            return number;
        }

        cout << "Invalid input! Enter a number.\n";
    }
}

// Read text
string TextEditor::readText(string message)
{
    string text;

    cout << message;
    getline(cin, text);

    return text;
}

// Display Menu

void TextEditor::showMenu()
{
    cout << "\n";

    // Main Header
    cout << BRIGHT_CYAN << BOLD;
    cout << "====================================================\n";
    cout << "                 DSA TEXT EDITOR                   \n";
    cout << "====================================================\n";
    cout << RESET;

    cout << CYAN << BOLD;
    cout << "                 MAIN DASHBOARD                     \n";
    cout << RESET;

    // Document Management
    cout << "\n";
    cout << BRIGHT_GREEN << BOLD;
    cout << "  DOCUMENT MANAGEMENT\n";
    cout << RESET;

    cout << GREEN;
    cout << "  [01] Create New Document\n";
    cout << "  [02] Open Existing File\n";
    cout << "  [19] Save Document\n";
    cout << "  [20] Save As\n";
    cout << RESET;

    // Editing Tools
    cout << "\n";
    cout << BRIGHT_MAGENTA << BOLD;
    cout << "  EDITING TOOLS\n";
    cout << RESET;

    cout << MAGENTA;
    cout << "  [03] Insert New Line\n";
    cout << "  [04] Edit Existing Line\n";
    cout << "  [05] Delete Line\n";
    cout << "  [06] Insert Text\n";
    cout << "  [07] Delete Text\n";
    cout << "  [08] Text Case Converter\n";
    cout << RESET;

    // Search Tools
    cout << "\n";
    cout << BRIGHT_YELLOW << BOLD;
    cout << "  SEARCH & REPLACE TOOLS\n";
    cout << RESET;

    cout << YELLOW;
    cout << "  [09] Search Text\n";
    cout << "  [10] Replace One Occurrence\n";
    cout << "  [11] Replace All Occurrences\n";
    cout << "  [12] Next Search Result\n";
    cout << "  [13] Previous Search Result\n";
    cout << "  [17] Display Search History\n";
    cout << "  [18] Clear Search History\n";
    cout << RESET;

    // History and Display
    cout << "\n";
    cout << BRIGHT_BLUE << BOLD;
    cout << "  HISTORY & DOCUMENT VIEW\n";
    cout << RESET;

    cout << BLUE;
    cout << "  [14] Undo\n";
    cout << "  [15] Redo\n";
    cout << "  [16] Display Document\n";
    cout << RESET;

    // Document Analysis
cout << "\n";
cout << BRIGHT_GREEN << BOLD;
cout << "  DOCUMENT ANALYSIS\n";
cout << RESET;

cout << GREEN;
cout << "  [21] Word Frequency Analyzer\n";
cout << RESET;

cout << GREEN;
cout << "  [22] Find Duplicate Lines\n";
cout << RESET;

// Bookmarks
cout << "\n";
cout << BRIGHT_GREEN << BOLD;
cout << "  BOOKMARKS\n";
cout << RESET;

cout << GREEN;
cout << "  [23] Toggle Bookmark\n";
cout << "  [24] View Bookmarks\n";
cout << RESET;

    // Exit
    cout << "\n";
    cout << BRIGHT_RED << BOLD;
cout << "  [25] Recent Files\n";
cout << "  [26] View All Saved Documents\n";
cout << "  [27] Change Theme (Dark / Light)\n";

cout << "  [28] Toggle Auto-Save ("
     << (autoSaveEnabled ? "ON" : "OFF") << ")\n";

     cout << "  [29] View Typing Statistics\n";
     cout << "  [30] Exit Editor\n";
    cout << RESET;

    // Footer
    cout << "\n";
    cout << CYAN;
    cout << "====================================================\n";
    cout << RESET;

    // Current document information
    cout << WHITE << BOLD;
    cout << "  FILE: ";
    cout << RESET;

    if (currentFilename.empty())
    {
        cout << YELLOW << "Untitled";
    }
    else
    {
        cout << GREEN << currentFilename;
    }

    cout << RESET;

    cout << "   |   ";

    cout << WHITE << BOLD << "STATUS: " << RESET;

   if (currentFilename.empty() && !isModified)
{
    cout << BRIGHT_CYAN << "NEW DOCUMENT";
}
else if (isModified)
{
    cout << BRIGHT_YELLOW << "UNSAVED CHANGES";
}
else
{
    cout << BRIGHT_GREEN << "SAVED";
}
// document statistics
    cout << RESET << "\n";

 
     cout << RESET;
    cout << CYAN;
    cout << "====================================================\n";
    cout << RESET;
}


// Save changes to the current file
bool TextEditor::saveChanges()
{
    if (currentFilename.empty())
    {
        string filename = readText(
            "No filename assigned. Enter filename to save: ");

        if (filename.empty())
        {
            cout << "Filename cannot be empty!\n";
            return false;
        }

     if (editor.saveAs(filename))
{
    currentFilename = filename;
    isModified = false;

    recentFiles.addFile(filename);

    cout << "Document saved successfully!\n";
    return true;
}

        return false;
    }

   if (editor.saveFile(currentFilename))
{
    isModified = false;
    recentFiles.addFile(currentFilename);
    return true;
}

    return false;
}
// Automatically save the document when Auto-Save is enabled
void TextEditor::autoSaveIfEnabled()
{
    if (!autoSaveEnabled || !isModified)
    {
        return;
    }

    if (currentFilename.empty())
    {
        cout << YELLOW
             << "Auto-Save is ON, but this document has no filename.\n"
             << "Please use Save or Save As first.\n"
             << RESET;
        return;
    }

    if (editor.saveFile(currentFilename))
    {
        isModified = false;
        recentFiles.addFile(currentFilename);

        cout << GREEN
             << "Auto-Save: Document saved successfully!\n"
             << RESET;
    }
    else
    {
        cout << RED
             << "Auto-Save failed! Your changes are still unsaved.\n"
             << RESET;
    }
}

// Turn Auto-Save ON or OFF
void TextEditor::toggleAutoSave()
{
    autoSaveEnabled = !autoSaveEnabled;

    if (autoSaveEnabled)
    {
        cout << GREEN << BOLD
             << "\nAuto-Save ENABLED successfully!\n"
             << RESET;

        // Save immediately if there are already unsaved changes
        autoSaveIfEnabled();
    }
    else
    {
        cout << YELLOW << BOLD
             << "\nAuto-Save DISABLED successfully!\n"
             << RESET;
    }
}

// Ask what to do with unsaved changes
bool TextEditor::confirmSaveChanges()
{
    if (!isModified)
    {
        return true;
    }

    while (true)
    {
        string choice = readText(
            "\nYou have unsaved changes.\n"
            "Save (S), Don't Save (D), or Cancel (C)? ");

        if (choice == "s" || choice == "S")
        {
            return saveChanges();
        }
        else if (choice == "d" || choice == "D")
        {
            return true;
        }
        else if (choice == "c" || choice == "C")
        {
            cout << "Operation cancelled.\n";
            return false;
        }

        cout << "Invalid choice! Enter S, D, or C.\n";
    }
}

// Create New Document
void TextEditor::createNewDocument()
{
    if (!confirmSaveChanges())
    {
        return;
    }

    string confirm = readText(
        "\nCreate a new document? (y/n): ");

    if (confirm == "y" || confirm == "Y")
    {
        editor.newDocument();

        currentFilename = "";
        isModified = false;

        cout << "New document created successfully!\n";
    }
    else
    {
        cout << "Operation cancelled.\n";
    }
}

// Open Existing File
void TextEditor::openDocument()
{
    if (!confirmSaveChanges())
    {
        return;
    }

    string filename = readText("Enter filename to open: ");

    if (filename.empty())
    {
        cout << "Filename cannot be empty!\n";
        return;
    }

if (editor.openFile(filename))
{
    currentFilename = filename;
    isModified = false;
    recentFiles.addFile(filename);
}
}

// Insert Line

// Insert Line
void TextEditor::insertLine()
{
    displayDocument();

    int position = readNumber("Enter line position: ");

    cout << "Enter text: ";

    auto startTime = chrono::steady_clock::now();

    string text;
    getline(cin, text);

    auto endTime = chrono::steady_clock::now();

    double typingTime = chrono::duration<double>(
        endTime - startTime
    ).count();

    editor.recordTypingTime(typingTime);

    if (editor.insertLine(position, text))
    {
        isModified = true;
        autoSaveIfEnabled();

        cout << "Line inserted successfully!\n";
    }
    else
    {
        cout << "Invalid line position!\n";
    }
}


void TextEditor::editLine()
{
    // Display the document before editing
    displayDocument();

    int line = readNumber("\nEnter line number to edit: ");

    if (editor.interactiveEditLine(line, true))
    {
        isModified = true;
        autoSaveIfEnabled();

        cout << "\nLine edited successfully!\n";
    }
    else
    {
        cout << "\nEditing cancelled or invalid line number!\n";
    }
}

// Text Case Converter
void TextEditor::convertTextCase()
{
    displayDocument();

    int line = readNumber("Enter line number: ");

    cout << "\n";
    cout << "1. UPPERCASE\n";
    cout << "2. lowercase\n";
    cout << "3. Title Case\n";
    cout << "4. Sentence case\n";

    int choice = readNumber("Choose conversion: ");

    if (editor.convertLineCase(line, choice))
    {
        isModified = true;
        autoSaveIfEnabled();

        cout << "\nText converted successfully!\n";
        cout << "Converted text: " << editor.getLine(line) << "\n";
    }
    else
    {
        cout << "\nInvalid line number or conversion choice!\n";
    }
}
// Word Frequency Analyzer
void TextEditor::wordFrequencyAnalyzer()
{
    editor.displayWordFrequency();
}
// Duplicate Line Finder
void TextEditor::duplicateLineFinder()
{
    editor.displayDuplicateLines();
}

// Add or remove bookmark
void TextEditor::bookmarkLine()
{
    if (editor.getLineCount() == 0)
    {
        cout << "\nDocument is empty. No lines to bookmark!\n";
        return;
    }

    displayDocument();

    int lineNumber = readNumber(
        "Enter line number to bookmark or remove bookmark: ");

    int result = editor.toggleBookmark(lineNumber);

    if (result == 1)
    {
        cout << GREEN << "\nBookmark added successfully!\n" << RESET;
    }
    else if (result == 2)
    {
        cout << YELLOW << "\nBookmark removed successfully!\n" << RESET;
    }
    else
    {
        cout << RED << "\nInvalid line number!\n" << RESET;
    }
}


// Display all bookmarks
void TextEditor::showBookmarks()
{
    editor.displayBookmarks();
}

// Delete Line
void TextEditor::deleteLine()
{
    displayDocument();
    int line = readNumber("Enter line number: ");

    if (editor.deleteLine(line))
    {
        isModified = true;
        autoSaveIfEnabled();

        cout << "Line deleted successfully!\n";
    }
    else
    {
        cout << "Invalid line number!\n";
    }
}
 // Insert Text
void TextEditor::insertText()
{ 
    displayDocument();
    int line = readNumber("Enter line number: ");

    if (editor.interactiveEditLine(line, true))
    {
        isModified = true;
        autoSaveIfEnabled();

        cout << "\nEditing completed successfully!\n";
    }
}

// Delete Text
void TextEditor::deleteText()
{
    displayDocument();

    int line = readNumber("Enter line number: ");

    if (editor.interactiveEditLine(line, false))
    {
        isModified = true;
        autoSaveIfEnabled();

        cout << "\nEditing completed successfully!\n";
    }
}




// Search Text
void TextEditor::searchText()
{
    displayDocument();
    string word = readText("Enter word to search: ");

    if (word.empty())
    {
        cout << "Search word cannot be empty!\n";
        return;
    }

    editor.searchText(word);
}


// Replace One
void TextEditor::replaceOne()
{
    string word = readText("Enter word to find: ");

    if (word.empty())
    {
        cout << "Search word cannot be empty!\n";
        return;
    }

    cout << "Enter replacement: ";

    auto startTime = chrono::steady_clock::now();

    string replacement;
    getline(cin, replacement);

    auto endTime = chrono::steady_clock::now();

    double typingTime = chrono::duration<double>(
        endTime - startTime
    ).count();

    editor.recordTypingTime(typingTime);

    if (editor.replaceOne(word, replacement))
    {
        isModified = true;
        autoSaveIfEnabled();

        cout << "First occurrence replaced successfully!\n";
    }
    else
    {
        cout << "No matching occurrence found!\n";
    }
}


// Replace All

void TextEditor::replaceAll()
{
    string word = readText("Enter word to find: ");

    if (word.empty())
    {
        cout << "Search word cannot be empty!\n";
        return;
    }

    cout << "Enter replacement: ";

    auto startTime = chrono::steady_clock::now();

    string replacement;
    getline(cin, replacement);

    auto endTime = chrono::steady_clock::now();

    double typingTime = chrono::duration<double>(
        endTime - startTime
    ).count();

    editor.recordTypingTime(typingTime);

    int count = editor.replaceAll(word, replacement);

    if (count > 0)
    {
        isModified = true;
        autoSaveIfEnabled();
    }

    cout << count << " occurrence(s) replaced.\n";
}

// Next Search
void TextEditor::navigateNext()
{
    editor.nextSearch();
}

// Previous Search
void TextEditor::navigatePrevious()
{
    editor.previousSearch();
}

// Undo
void TextEditor::undo()
{
    if (editor.undo())
    {
        isModified = true;
        autoSaveIfEnabled();

        cout << "Undo successful!\n";
    }
    else
    {
        cout << "Nothing to undo!\n";
    }
}

// Redo
void TextEditor::redo()
{
    if (editor.redo())
    {
        isModified = true;
        autoSaveIfEnabled();
        
        cout << "Redo successful!\n";
    }
    else
    {
        cout << "Nothing to redo!\n";
    }
}


// Display Document
void TextEditor::displayDocument()
{
    editor.display();

    cout << "\n";
    cout << GREEN;
    cout << "------------------------------------------------------------\n";
    cout << "                  DOCUMENT STATISTICS\n";
    cout << "  Total Lines: " << editor.getLineCount() << "\n";
    cout << "  Total Words: " << editor.getWordCount() << "\n";
    cout << "  Total Characters: " << editor.getCharacterCount() << "\n";
    cout << "  Characters (Without Spaces): "
         << editor.getCharacterCountWithoutSpaces() << "\n";
    cout << "============================================================\n";
    cout << RESET;
}

// Search History
void TextEditor::searchHistory()
{
    editor.displaySearchHistory();
}

// Save Document
void TextEditor::saveDocument()
{
    if (saveChanges())
    {
        cout << "Document saved successfully!\n";
    }
}

// Save As
void TextEditor::saveAsDocument()
{
    string filename = readText("Enter new filename: ");

    if (filename.empty())
    {
        cout << "Filename cannot be empty!\n";
        return;
    }

    if (editor.saveAs(filename))
    {
        currentFilename = filename;
        isModified = false;
        recentFiles.addFile(filename);
    }
}

void TextEditor::showRecentFiles()
{
    if (recentFiles.getCount() == 0)
    {
        cout << "\nNo recent files available!\n";
        return;
    }

    cout << "\n========== RECENT FILES ==========\n";

    for (int i = 0; i < recentFiles.getCount(); i++)
    {
        cout << i + 1 << ". "
             << recentFiles.getFile(i) << endl;
    }

    cout << "==================================\n";

    int choice = readNumber(
        "Enter file number to open (0 to go back): ");

    if (choice == 0)
        return;

    if (choice < 1 || choice > recentFiles.getCount())
    {
        cout << "Invalid selection!\n";
        return;
    }

    if (!confirmSaveChanges())
        return;

    string filename = recentFiles.getFile(choice - 1);

    if (editor.openFile(filename))
    {
        currentFilename = filename;
        isModified = false;
        recentFiles.addFile(filename);

        cout << "Recent file opened successfully!\n";
    }
}

// DISPLAY ALL SAVED DOCUMENTS
void TextEditor::showSavedDocuments()
{
    cout << "\n";

    cout << BRIGHT_CYAN << BOLD;
    cout << "========== ALL SAVED DOCUMENTS ==========\n";
    cout << RESET;

    // Display every file in the Documents folder
    editor.displaySavedFiles();

    cout << "\n";

    // Allow the user to open a document
    string choice = readText(
        "Do you want to open a document? (y/n): ");

    if (choice == "y" || choice == "Y")
    {
        openDocument();
    }
    else
    {
        cout << "Returning to dashboard...\n";
    }
}

// Run Editor
void TextEditor::run()
{
    int choice;

    showWelcomeScreen();

    while (true)
    {
        // Clear screen before displaying dashboard
        cout << "\033[2J\033[H";

        showMenu();

        choice = readNumber(
            "\033[96m\033[1m  >> Enter your choice: \033[0m");

        switch (choice)
        {
            case 1:
                createNewDocument();
                break;

            case 2:
                openDocument();
                break;

            case 3:
                insertLine();
                break;

            case 4:
                editLine();
                break;

            case 5:
                deleteLine();
                break;

            case 6:
                insertText();
                break;

            case 7:
                deleteText();
                break;

                case 8:
    convertTextCase();
    break;

            case 9:
                searchText();
                break;

            case 10:
                replaceOne();
                break;

            case 11:
                replaceAll();
                break;

            case 12:
                navigateNext();
                break;

            case 13:
                navigatePrevious();
                break;

            case 14:
                undo();
                break;

            case 15:
                redo();
                break;

            case 16:
                displayDocument();
                break;

            case 17:
                searchHistory();
                break;

            case 18:
                editor.clearSearchHistory();
                cout << "Search history cleared!\n";
                break;

            case 19:
                saveDocument();
                break;

            case 20:
                saveAsDocument();
                break;

                case 21:
    wordFrequencyAnalyzer();
    break;

    case 22:
    duplicateLineFinder();
    break;

    case 23:
    bookmarkLine();
    break;

case 24:
    showBookmarks();
    break;

case 25:
    showRecentFiles();
    break;

case 26:
    showSavedDocuments();
    break;

case 27:
    changeTheme();
    break;

    case 28:
    toggleAutoSave();
    break;

    case 29:
    editor.displayTypingStatistics();
    break;

case 30:
    if (confirmSaveChanges())
    {
        cout << "\nExiting DSA Text Editor. Goodbye!\n";
        return;
    }
    break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

        // Wait before returning to dashboard
        cout << "\n";
        cout << BRIGHT_CYAN << BOLD;
        cout << "Press ENTER to return to the dashboard...";
        cout << RESET;

        string pause;
        getline(cin, pause);
    }
}
