#include "EditorController.h"
#include <conio.h>
#include <iomanip>

// Constructor
EditorController::EditorController()
{
    currentSearchLine = 1;
    currentSearchPosition = -1;
    searchStarted = false;
    currentSearchCaseSensitive = true;

    // Initialize Typing Statistics
    totalCharactersTyped = 0;
    totalWordsTyped = 0;
    totalCharactersDeleted = 0;
    totalLinesDeleted = 0;

    totalTypingTime = 0.0;
    fastestTypingSpeed = 0.0;

    interactiveEditInProgress = false;
}
// Record inserted text
void EditorController::recordTypedText(const string& text)
{
    totalCharactersTyped += text.length();

    bool insideWord = false;

    for (char ch : text)
    {
        if (ch != ' ' && ch != '\t' && ch != '\n')
        {
            if (!insideWord)
            {
                totalWordsTyped++;
                insideWord = true;
            }
        }
        else
        {
            insideWord = false;
        }
    }
}

// Record deleted characters
void EditorController::recordDeletedCharacters(long long count)
{
    if (count > 0)
    {
        totalCharactersDeleted += count;
    }
}

// Record typing time
void EditorController::recordTypingTime(double seconds)
{
    if (seconds > 0)
    {
        totalTypingTime += seconds;
    }
}

// Reset Search Navigation
void EditorController::resetSearchNavigation()
{
    currentSearchWord = "";
    currentSearchLine = 1;
    currentSearchPosition = -1;
    searchStarted = false;
    
}


// Edit Line


bool EditorController::editLine(int lineNumber, string newText)
{
    Document previous = document;

    string oldText;

    bool success = document.editLine(lineNumber, newText, oldText);

    if (success)
    {
        history.saveState(previous);

        // Count typed text only if this is not interactive editing

        if (!interactiveEditInProgress)
        {
            recordTypedText(newText);
        }

        resetSearchNavigation();
    }

    return success;
}

// Convert the case of a line

bool EditorController::convertLineCase(int lineNumber, int choice)
{
    string convertedText;

    if (!document.convertCase(lineNumber, choice, convertedText))
    {
        return false;
    }

    return editLine(lineNumber, convertedText);
}
string EditorController::getLine(int lineNumber) const
{
    return document.getLine(lineNumber);
}

// Interactive Cursor-Based Editing


bool EditorController::interactiveEditLine(
    int lineNumber, bool cursorAtEnd)
{
    if (lineNumber < 1 || lineNumber > document.getLineCount())
    {
        cout << "\nInvalid line number.\n";
        return false;
    }

    string originalLine = document.getLine(lineNumber);
    string editedLine = originalLine;

    long long sessionCharacters = 0;
    long long sessionWords = 0;

    bool wordStarted = false;

    auto sessionStart = chrono::steady_clock::now();

    int cursor = cursorAtEnd
        ? static_cast<int>(editedLine.length())
        : 0;

    interactiveEditInProgress = true;

    cout << "\n========================================\n";
    cout << "          INTERACTIVE EDITOR\n";
    cout << "========================================\n";

    cout << "\nArrow Keys : Move Cursor";
    cout << "\nHome       : Beginning of Line";
    cout << "\nEnd        : End of Line";
    cout << "\nBackspace  : Delete Previous Character";
    cout << "\nDelete     : Delete Next Character";
    cout << "\nEnter      : Save Changes";
    cout << "\nEsc        : Cancel Changes\n";

    cout << "\nLine " << lineNumber << ":\n";

    while (true)
    {
        cout << "\r\033[2K";
        cout << " > " << editedLine;

        cout << "\r\033[" << (4 + cursor) << "G";
        cout.flush();

        int key = _getch();

        // Special keys
        if (key == 0 || key == 224)
        {
            int specialKey = _getch();

            switch (specialKey)
            {
                case 75: // Left Arrow
                    if (cursor > 0)
                        cursor--;
                    break;

                case 77: // Right Arrow
                    if (cursor < static_cast<int>(editedLine.length()))
                        cursor++;
                    break;

                case 71: // Home
                    cursor = 0;
                    break;

                case 79: // End
                    cursor = static_cast<int>(editedLine.length());
                    break;

                case 83: // Delete
                    if (cursor < static_cast<int>(editedLine.length()))
                    {
                        editedLine.erase(
                            static_cast<string::size_type>(cursor), 1);

                        recordDeletedCharacters(1);
                    }
                    break;
            }
        }

        // Backspace
        else if (key == 8)
        {
            if (cursor > 0)
            {
                editedLine.erase(
                    static_cast<string::size_type>(cursor - 1), 1);

                cursor--;

                recordDeletedCharacters(1);
            }
        }

        // Enter: Save changes
        else if (key == 13)
        {
            auto sessionEnd = chrono::steady_clock::now();

            double sessionTime =
                chrono::duration<double>(
                    sessionEnd - sessionStart).count();

            totalCharactersTyped += sessionCharacters;
            totalWordsTyped += sessionWords;

            recordTypingTime(sessionTime);

           if (sessionTime > 0 && sessionCharacters > 0)
{
    double sessionWPM =
        (sessionCharacters / 5.0) * 60.0 / sessionTime;

    if (sessionWPM > fastestTypingSpeed)
    {
        fastestTypingSpeed = sessionWPM;
    }
}

            cout << "\n\nEditing completed.\n";

if (editedLine == originalLine)
{
    interactiveEditInProgress = false;
    cout << "No changes were made.\n";
    return true;
}

bool success = editLine(lineNumber, editedLine);

interactiveEditInProgress = false;

return success;
        }

        // Escape: Cancel editing
        else if (key == 27)
        {
            interactiveEditInProgress = false;

            cout << "\n\nEditing cancelled.\n";
            return false;
        }

        // Printable characters
        else if (key >= 32 && key <= 126)
        {
            char typedCharacter = static_cast<char>(key);

            editedLine.insert(
                static_cast<string::size_type>(cursor),
                1,
                typedCharacter);

            cursor++;

            sessionCharacters++;

            if (typedCharacter != ' ' &&
                typedCharacter != '\t')
            {
                if (!wordStarted)
                {
                    sessionWords++;
                    wordStarted = true;
                }
            }
            else
            {
                wordStarted = false;
            }
        }
    }
}



// Delete Line

bool EditorController::deleteLine(int lineNumber)
{
    Document previous = document;

    string deletedText;

    bool success = document.deleteLine(lineNumber, deletedText);

    if (success)
    {
        history.saveState(previous);

        totalLinesDeleted++;
        recordDeletedCharacters(deletedText.length());

        resetSearchNavigation();
    }

    return success;
}



// Insert Line
bool EditorController::insertLine(int position, string text)
{
    Document previous = document;

    bool success = document.insertLine(position, text);

    if (success)
    {
        history.saveState(previous);

        recordTypedText(text);

        resetSearchNavigation();
    }

    return success;
}


// Insert Text
bool EditorController::insertText(int lineNumber, int column, string text)
{
    Document previous = document;

    bool success = document.insertText(lineNumber, column, text);

    if (success)
    {
        history.saveState(previous);

        recordTypedText(text);

        resetSearchNavigation();
    }

    return success;
}



// Delete Text
bool EditorController::deleteText(int lineNumber, int column, int length)
{
    Document previous = document;

    string deletedText;

    bool success = document.deleteText(
        lineNumber, column, length, deletedText);

    if (success)
    {
        history.saveState(previous);

        recordDeletedCharacters(deletedText.length());

        resetSearchNavigation();
    }

    return success;
}



bool EditorController::undo()
{
    bool success = history.undo(document);

    if (success)
    {
        resetSearchNavigation();
    }

    return success;
}

bool EditorController::redo()
{
    bool success = history.redo(document);

    if (success)
    {
        resetSearchNavigation();
    }

    return success;
}

// Display document
void EditorController::display()
{
    if (searchStarted)
    {
        document.display(
    currentSearchWord,
    currentSearchLine,
    currentSearchPosition,
    currentSearchCaseSensitive
);
    }
    else
    {
        document.display();
    }
}

//search text
// Search Text
void EditorController::searchText(const string& searchWord)
{
    if (searchWord.empty())
    {
        searchEngine.searchText(document, searchWord,currentSearchCaseSensitive);
        return;
    }
    int choice;

cout << "\n========== SEARCH MODE ==========\n";
cout << "1. Case-sensitive\n";
cout << "2. Case-insensitive\n";
cout << "Enter your choice: ";
cin >> choice;

while (choice != 1 && choice != 2)
{
    cout << "Invalid choice! Enter 1 or 2: ";
    cin >> choice;
}

currentSearchCaseSensitive = (choice == 1);

    searchHistory.addSearch(searchWord);

    currentSearchWord = searchWord;

    currentSearchLine = 1;
    currentSearchPosition = -1;

    searchStarted = true;

    searchEngine.searchText(document, searchWord);

    // Select the first occurrence and refresh the document
    nextSearch();
}

// Display word frequency analysis
void EditorController::displayWordFrequency() const
{
    document.analyzeWordFrequency();
}

// Display duplicate lines
void EditorController::displayDuplicateLines() const
{
    document.findDuplicateLines();
}

// Toggle bookmark on a selected line
int EditorController::toggleBookmark(int lineNumber)
{
    return document.toggleBookmark(lineNumber);
}


// Display bookmarked lines
void EditorController::displayBookmarks() const
{
    document.displayBookmarks();
}



// Replace One
bool EditorController::replaceOne(
    const string& searchWord,
    const string& replacementText)
{
    if (searchWord.empty())
    {
        cout << "\nSearch word cannot be empty.\n";
        return false;
    }

    // Select search mode
    int choice;

    cout << "\n========== REPLACEMENT MODE ==========\n";
    cout << "1. Case-sensitive\n";
    cout << "2. Case-insensitive\n";
    cout << "Enter your choice: ";
    cin >> choice;

    while (choice != 1 && choice != 2)
    {
        cout << "Invalid choice! Enter 1 or 2: ";
        cin >> choice;
    }

    currentSearchCaseSensitive = (choice == 1);

    Document previous = document;

    // Start a fresh replacement operation
    resetSearchNavigation();

    bool success = searchEngine.replaceOne(
        document,
        searchWord,
        replacementText,
        currentSearchCaseSensitive
    );

    if (success)
    {
        history.saveState(previous);
        recordTypedText(replacementText);

        cout << "\nFirst matching occurrence replaced successfully.\n";
    }
    else
    {
        cout << "\nNo matching occurrence found to replace.\n";
    }

    return success;
}

// Replace All
int EditorController::replaceAll(
    const string& searchWord,
    const string& replacementText)
{
    if (searchWord.empty())
    {
        cout << "\nSearch word cannot be empty.\n";
        return 0;
    }

    // Select search mode
    int choice;

    cout << "\n========== REPLACEMENT MODE ==========\n";
    cout << "1. Case-sensitive\n";
    cout << "2. Case-insensitive\n";
    cout << "Enter your choice: ";
    cin >> choice;

    while (choice != 1 && choice != 2)
    {
        cout << "Invalid choice! Enter 1 or 2: ";
        cin >> choice;
    }

    currentSearchCaseSensitive = (choice == 1);

    Document previous = document;

    int count = searchEngine.replaceAll(
        document,
        searchWord,
        replacementText,
        currentSearchCaseSensitive
    );

    if (count > 0)
    {
        history.saveState(previous);
        recordTypedText(replacementText);

        cout << "\nReplace All completed successfully.\n";
        cout << "Total replacements: " << count << endl;
    }
    else
    {
        cout << "\nNo matching occurrences found.\n";
    }

    resetSearchNavigation();

    return count;
}


// SAVE FILE
bool EditorController::saveFile(const string& filename)
{
    return fileManager.saveFile(document, filename);
}

// OPEN FILE
bool EditorController::openFile(const string& filename)
{
    bool success = fileManager.openFile(document, filename);

    if (success)
    {
        history.clearHistory();

        resetSearchNavigation();
    }

    return success;
}

// SAVE AS
bool EditorController::saveAs(const string& filename)
{
    return fileManager.saveAs(document, filename);
}
// DISPLAY SAVED DOCUMENTS
void EditorController::displaySavedFiles()
{
    fileManager.listFiles();
}

// Display Search History
void EditorController::displaySearchHistory()
{
    searchHistory.displayHistory();
}

// Clear Search History
void EditorController::clearSearchHistory()
{
    searchHistory.clearHistory();
}
// Next Search
// Next Search
bool EditorController::nextSearch()
{
    if (!searchStarted)
    {
        cout << "Please perform a search first.\n";
        return false;
    }


bool found = searchEngine.findNext(
    document,
    currentSearchWord,
    currentSearchLine,
    currentSearchPosition,
    currentSearchCaseSensitive
);
    if (found)
    {
        cout << "\nNext occurrence found at Line: "
             << currentSearchLine
             << ", Position: "
             << currentSearchPosition + 1 << endl;
    }
    else
    {
        cout << "\nNo matching occurrence found.\n";
    }

    // Refresh document with the selected occurrence highlighted
    display();

    return found;
}


// Previous Search
bool EditorController::previousSearch()
{
    if (!searchStarted)
    {
        cout << "Please perform a search first.\n";
        return false;
    }


bool found = searchEngine.findPrevious(
    document,
    currentSearchWord,
    currentSearchLine,
    currentSearchPosition,
    currentSearchCaseSensitive
);

    if (found)
    {
        cout << "\nPrevious occurrence found at Line: "
             << currentSearchLine
             << ", Position: "
             << currentSearchPosition + 1 << endl;
    }
    else
    {
        cout << "\nNo matching occurrence found.\n";
    }

    // Refresh document with the selected occurrence highlighted
    display();

    return found;
}

// Create New Document
void EditorController::newDocument()
{
    document.clear();
    history.clearHistory();
    resetSearchNavigation();
}
// Get Document Line Count
int EditorController::getLineCount() const
{
    return document.getLineCount();
}

// Get Document Character Count
int EditorController::getCharacterCount() const
{
    return document.getCharacterCount();
}
// Get Document Word Count
int EditorController::getWordCount() const
{
    return document.getWordCount();
}

// Get Document Character Count Without Spaces
int EditorController::getCharacterCountWithoutSpaces() const
{
    return document.getCharacterCountWithoutSpaces();
}

// Display Typing Statistics
void EditorController::displayTypingStatistics() const
{
    double averageWPM = 0.0;

    if (totalTypingTime > 0)
    {
        averageWPM =
            (totalWordsTyped / 5.0) * 60.0 / totalTypingTime;
    }

    cout << "\n";
    cout << "====================================================\n";
    cout << "                 TYPING STATISTICS                 \n";
    cout << "====================================================\n";

    cout << "\n  Total Characters Typed : "
         << totalCharactersTyped;

    cout << "\n  Total Words Typed      : "
         << totalWordsTyped;

    cout << "\n  Characters Deleted    : "
         << totalCharactersDeleted;

    cout << "\n  Lines Deleted         : "
         << totalLinesDeleted;

         int minutes = static_cast<int>(totalTypingTime) / 60;
double seconds = totalTypingTime - (minutes * 60);

cout << "  \n Total Typing Time     : "
     << minutes << " minutes, "
     << fixed << setprecision(2) << seconds
     << " seconds\n";

    cout << "\n  Average Typing Speed  : "
         << averageWPM << " WPM";

    cout << "\n  Fastest Typing Speed  : "
         << fastestTypingSpeed << " WPM";

    cout << "\n\n====================================================\n";
}
