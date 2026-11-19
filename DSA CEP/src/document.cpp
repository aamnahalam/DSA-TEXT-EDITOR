#include "Document.h"
#include "Colours.h"
#include <cctype>
#include <iomanip>
#include <iostream>

// Constructor
Document::Document()
{
    capacity = 5;
    lineCount = 0;

    lines = new string[capacity];

    // Initialize bookmark storage
    bookmarkCapacity = 5;
    bookmarkCount = 0;

    bookmarks = new int[bookmarkCapacity];
}
// Destructor
Document::~Document()
{
    delete[] lines;
    delete[] bookmarks;
}

// Resize the dynamic array
void Document::resize()
{
    int newCapacity = capacity * 2;

    string* newLines = new string[newCapacity];

    for (int i = 0; i < lineCount; i++)
    {
        newLines[i] = lines[i];
    }

    delete[] lines;

    lines = newLines;
    capacity = newCapacity;
}

// Resize bookmark dynamic array
void Document::resizeBookmarks()
{
    int newCapacity = bookmarkCapacity * 2;

    int* newBookmarks = new int[newCapacity];

    for (int i = 0; i < bookmarkCount; i++)
    {
        newBookmarks[i] = bookmarks[i];
    }

    delete[] bookmarks;

    bookmarks = newBookmarks;
    bookmarkCapacity = newCapacity;
}

// Insert a complete line
bool Document::insertLine(int position, string text)
{
    if (position < 1 || position > lineCount + 1)
    {
        return false;
    }

    if (lineCount == capacity)
    {
        resize();
    }

    int index = position - 1;

    // Shift lines towards the right
    for (int i = lineCount; i > index; i--)
    {
        lines[i] = lines[i - 1];
    }

    lines[index] = text;

    lineCount++;

    // Shift bookmarked line numbers down
for (int i = 0; i < bookmarkCount; i++)
{
    if (bookmarks[i] >= position)
    {
        bookmarks[i]++;
    }
}

    return true;
}

// Edit an existing line
bool Document::editLine(int lineNumber, string newText,
                        string& oldText)
{
    if (lineNumber < 1 || lineNumber > lineCount)
    {
        return false;
    }

    int index = lineNumber - 1;

    oldText = lines[index];

    lines[index] = newText;

    return true;
}
// Convert the case of a selected line
bool Document::convertCase(int lineNumber, int choice,
                           string& convertedText) const
{
    if (lineNumber < 1 || lineNumber > lineCount)
    {
        return false;
    }

    if (choice < 1 || choice > 4)
    {
        return false;
    }

    convertedText = lines[lineNumber - 1];

    bool newWord = true;
    bool newSentence = true;

    for (int i = 0; i < static_cast<int>(convertedText.length()); i++)
    {
        unsigned char ch =
            static_cast<unsigned char>(convertedText[i]);

        if (choice == 1) // UPPERCASE
        {
            convertedText[i] = toupper(ch);
        }
        else if (choice == 2) // lowercase
        {
            convertedText[i] = tolower(ch);
        }
        else if (choice == 3) // Title Case
        {
            if (isalpha(ch))
            {
                if (newWord)
                {
                    convertedText[i] = toupper(ch);
                    newWord = false;
                }
                else
                {
                    convertedText[i] = tolower(ch);
                }
            }
            else if (isspace(ch))
            {
                newWord = true;
            }
        }
        else if (choice == 4) // Sentence case
        {
            if (isalpha(ch))
            {
                if (newSentence)
                {
                    convertedText[i] = toupper(ch);
                    newSentence = false;
                }
                else
                {
                    convertedText[i] = tolower(ch);
                }
            }

            if (ch == '.' || ch == '!' || ch == '?')
            {
                newSentence = true;
            }
        }
    }

    return true;
}
// Delete a complete line
bool Document::deleteLine(int lineNumber, string& deletedText)
{
    if (lineNumber < 1 || lineNumber > lineCount)
    {
        return false;
    }

    int index = lineNumber - 1;

    deletedText = lines[index];

    // Shift remaining lines towards the left
    for (int i = index; i < lineCount - 1; i++)
    {
        lines[i] = lines[i + 1];
    }

    lineCount--;

// Update bookmark positions after deleting a line
int newBookmarkCount = 0;

for (int i = 0; i < bookmarkCount; i++)
{
    // Remove bookmark belonging to deleted line
    if (bookmarks[i] == lineNumber)
    {
        continue;
    }

    // Shift bookmarks above deleted line upwards
    if (bookmarks[i] > lineNumber)
    {
        bookmarks[i]--;
    }

    bookmarks[newBookmarkCount] = bookmarks[i];
    newBookmarkCount++;
}

bookmarkCount = newBookmarkCount;

return true;
}

// Insert text within an existing line
bool Document::insertText(int lineNumber, int column,
                          string text)
{
    if (lineNumber < 1 || lineNumber > lineCount)
    {
        return false;
    }

    int index = lineNumber - 1;
    int lineLength = static_cast<int>(lines[index].length());

    if (column < 1 || column > lineLength + 1)
    {
        return false;
    }

    string::size_type position =
        static_cast<string::size_type>(column - 1);

    lines[index].insert(position, text);

    return true;
}

// Delete text within an existing line
bool Document::deleteText(int lineNumber, int startColumn,
                          int length, string& deletedText)
{
    if (lineNumber < 1 || lineNumber > lineCount)
    {
        return false;
    }

    int index = lineNumber - 1;
    int lineLength = static_cast<int>(lines[index].length());

    if (startColumn < 1 || length <= 0)
    {
        return false;
    }

    int startIndex = startColumn - 1;

    if (startIndex >= lineLength)
    {
        return false;
    }

    if (length > lineLength - startIndex)
    {
        return false;
    }

    string::size_type position =
        static_cast<string::size_type>(startIndex);

    string::size_type deleteLength =
        static_cast<string::size_type>(length);

    deletedText = lines[index].substr(position, deleteLength);

    lines[index].erase(position, deleteLength);

    return true;
}
  
// Display document with search highlighting
void Document::display(
    const string& searchWord,
    int selectedLine,
    int selectedPosition,
 bool caseSensitive)
{
    cout << "\n";

    cout << BRIGHT_CYAN << BOLD;
    cout << "============================================================\n";
    cout << "                    DOCUMENT VIEW                          \n";
    cout << "============================================================\n";
    cout << RESET;

    // Display search information
    if (!searchWord.empty())
    {
        cout << BRIGHT_BLUE << BOLD;
        cout << "  SEARCH: " << searchWord << "\n";
        cout << RESET;

        cout << YELLOW << "  Yellow = Other matches";
        cout << RESET << "   ";

        cout << BRIGHT_GREEN << BOLD;
        cout << "Green = Selected match\n";
        cout << RESET;

        cout << "------------------------------------------------------------\n";
    }

    if (lineCount == 0)
    {
        cout << YELLOW;
        cout << "\n             Your document is currently empty.\n";
        cout << RESET;
    }
    else
    {
        cout << BRIGHT_BLUE << BOLD;
        cout << "  LINE     CONTENT\n";
        cout << "  ----------------------------------------------------------\n";
        cout << RESET;

        for (int i = 0; i < lineCount; i++)
        {
            // Display line number
            cout << BRIGHT_CYAN << BOLD;
            cout << "  " << setw(4) << right << i + 1;
            cout << "     ";
            cout << RESET;

            string currentLine = lines[i];

            cout << WHITE;

            int j = 0;

            while (j < static_cast<int>(currentLine.length()))
            {
                bool match = false;

                // Check whether search word matches at this position
                if (!searchWord.empty() &&
                    j + static_cast<int>(searchWord.length()) <=
                    static_cast<int>(currentLine.length()))
                {
                    bool same = true;

for (int k = 0; k < static_cast<int>(searchWord.length()); k++)
{
    char documentChar = currentLine[j + k];
    char searchChar = searchWord[k];

    if (!caseSensitive)
    {
        documentChar = static_cast<char>(
            tolower(static_cast<unsigned char>(documentChar))
        );

        searchChar = static_cast<char>(
            tolower(static_cast<unsigned char>(searchChar))
        );
    }

    if (documentChar != searchChar)
    {
        same = false;
        break;
    }
}

if (same)
{
    match = true;
}
                }

                if (match)
                {
                    // Check whether this is the currently selected match
                    if (i + 1 == selectedLine &&
                        j == selectedPosition)
                    {
                        cout << BRIGHT_GREEN << BOLD;
                    }
                    else
                    {
                        cout << BRIGHT_YELLOW << BOLD;
                    }

                    cout << currentLine.substr(j, searchWord.length());

                    cout << RESET << WHITE;

                    j += static_cast<int>(searchWord.length());
                }
                else
                {
                    cout << currentLine[j];
                    j++;
                }
            }

            cout << RESET << "\n";
        }
    }

    cout << BRIGHT_CYAN << BOLD;
    cout << "============================================================\n";
    cout << RESET;

    cout << "\n";
}

// Get a particular line
string Document::getLine(int lineNumber) const
{
    if (lineNumber < 1 || lineNumber > lineCount)
    {
        return "";
    }

    return lines[lineNumber - 1];
}

// Get number of lines
int Document::getLineCount() const
{
    return lineCount;
}

// Get total number of characters
int Document::getCharacterCount() const
{
    int total = 0;

    for (int i = 0; i < lineCount; i++)
    {
        total += static_cast<int>(lines[i].length());
    }

    return total;
}

// Get total characters excluding whitespace
int Document::getCharacterCountWithoutSpaces() const
{
    int total = 0;

    for (int i = 0; i < lineCount; i++)
    {
        for (int j = 0; j < static_cast<int>(lines[i].length()); j++)
        {
            if (!isspace(static_cast<unsigned char>(lines[i][j])))
            {
                total++;
            }
        }
    }

    return total;
}

// Get total number of words
int Document::getWordCount() const
{
    int total = 0;

    for (int i = 0; i < lineCount; i++)
    {
        bool insideWord = false;

        for (int j = 0; j < static_cast<int>(lines[i].length()); j++)
        {
            char ch = lines[i][j];

            if (!isspace(static_cast<unsigned char>(ch)))
            {
                if (!insideWord)
                {
                    total++;
                    insideWord = true;
                }
            }
            else
            {
                insideWord = false;
            }
        }
    }

    return total;
}


// Delete a single character
bool Document::deleteCharacter(int lineNumber, int column,
                               string& deletedText)
{
    return deleteText(lineNumber, column, 1, deletedText);
}

// Delete a complete word at a given position
bool Document::deleteWord(int lineNumber, int column,
                          string& deletedText)
{
    if (lineNumber < 1 || lineNumber > lineCount)
    {
        return false;
    }

    int index = lineNumber - 1;
    int lineLength = static_cast<int>(lines[index].length());

    if (column < 1 || column > lineLength)
    {
        return false;
    }

    int start = column - 1;
    int end = start;

    // Position must be inside a word
    if (isspace(static_cast<unsigned char>(
            lines[index][static_cast<string::size_type>(start)])))
    {
        return false;
    }

    // Find beginning of word
    while (start > 0 &&
           !isspace(static_cast<unsigned char>(
               lines[index][static_cast<string::size_type>(start - 1)])))
    {
        start--;
    }

    // Find end of word
    while (end < lineLength &&
           !isspace(static_cast<unsigned char>(
               lines[index][static_cast<string::size_type>(end)])))
    {
        end++;
    }

    int length = end - start;

    string::size_type position =
        static_cast<string::size_type>(start);

    string::size_type deleteLength =
        static_cast<string::size_type>(length);

    deletedText = lines[index].substr(position, deleteLength);

    lines[index].erase(position, deleteLength);

    return true;
}

// Delete a selected range of characters
bool Document::deleteRange(int lineNumber, int startColumn,
                           int length, string& deletedText)
{
    return deleteText(lineNumber, startColumn,
                      length, deletedText);
}

// Clear document
void Document::clear()
{
    lineCount = 0;
    bookmarkCount = 0;
}

// Analyze the frequency of words in the document
void Document::analyzeWordFrequency() const
{
    int totalCharacters = getCharacterCount();

    if (totalCharacters == 0)
    {
        cout << "\nDocument is empty. Nothing to analyze!\n";
        return;
    }

    // Dynamic arrays to store unique words and their frequencies
    string* words = new string[totalCharacters];
    int* frequencies = new int[totalCharacters];

    int uniqueWords = 0;
    int totalWords = 0;

    // Process every line
    for (int i = 0; i < lineCount; i++)
    {
        string currentWord = "";

        for (int j = 0; j <= (int)lines[i].length(); j++)
        {
            char ch = '\0';

            if (j < (int)lines[i].length())
            {
                ch = lines[i][j];
            }

            if (j < (int)lines[i].length() &&
                isalnum(static_cast<unsigned char>(ch)))
            {
                currentWord += static_cast<char>(
                    tolower(static_cast<unsigned char>(ch)));
            }
            else
            {
                // A complete word has been found
                if (!currentWord.empty())
                {
                    totalWords++;

                    int index = -1;

                    // Check whether the word already exists
                    for (int k = 0; k < uniqueWords; k++)
                    {
                        if (words[k] == currentWord)
                        {
                            index = k;
                            break;
                        }
                    }

                    if (index != -1)
                    {
                        frequencies[index]++;
                    }
                    else
                    {
                        words[uniqueWords] = currentWord;
                        frequencies[uniqueWords] = 1;
                        uniqueWords++;
                    }

                    currentWord = "";
                }
            }
        }
    }

    // Sort words by frequency (highest first)
    for (int i = 0; i < uniqueWords - 1; i++)
    {
        for (int j = 0; j < uniqueWords - i - 1; j++)
        {
            if (frequencies[j] < frequencies[j + 1])
            {
                int tempFrequency = frequencies[j];
                frequencies[j] = frequencies[j + 1];
                frequencies[j + 1] = tempFrequency;

                string tempWord = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tempWord;
            }
            else if (frequencies[j] == frequencies[j + 1] &&
                     words[j] > words[j + 1])
            {
                string tempWord = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tempWord;
            }
        }
    }

    // Display results
    cout << "\n";
    cout << BRIGHT_CYAN << BOLD;
    cout << "============================================================\n";
    cout << "                 WORD FREQUENCY ANALYSIS                   \n";
    cout << "============================================================\n";
    cout << RESET;

    cout << BRIGHT_BLUE << BOLD;
    cout << left << setw(30) << "WORD"
         << right << setw(15) << "FREQUENCY" << "\n";
    cout << "------------------------------------------------------------\n";
    cout << RESET;

    for (int i = 0; i < uniqueWords; i++)
    {
        cout << GREEN << left << setw(30) << words[i]
             << right << setw(15) << frequencies[i] << "\n";
    }

    cout << "------------------------------------------------------------\n";

    cout << BRIGHT_CYAN << BOLD;
    cout << "Total Words: " << totalWords << "\n";
    cout << "Unique Words: " << uniqueWords << "\n";
    cout << "============================================================\n";
    cout << RESET;

    // Release dynamic memory
    delete[] words;
    delete[] frequencies;
}
// Find duplicate lines in the document
void Document::findDuplicateLines() const
{
    bool duplicatesFound = false;

    cout << "\n";
    cout << BRIGHT_CYAN << BOLD;
    cout << "============================================================\n";
    cout << "                    DUPLICATE LINES                        \n";
    cout << "============================================================\n";
    cout << RESET;

    for (int i = 0; i < lineCount; i++)
    {
        // Ignore empty lines
        if (lines[i].empty())
        {
            continue;
        }

        // Check whether this line was already examined
        bool alreadyChecked = false;

        for (int j = 0; j < i; j++)
        {
            if (lines[i] == lines[j])
            {
                alreadyChecked = true;
                break;
            }
        }

        if (alreadyChecked)
        {
            continue;
        }

        // Count occurrences of the current line
        int count = 0;

        for (int j = 0; j < lineCount; j++)
        {
            if (lines[i] == lines[j])
            {
                count++;
            }
        }

        // Display only lines that occur more than once
        if (count > 1)
        {
            duplicatesFound = true;

            cout << "\n" << BRIGHT_YELLOW << BOLD;
            cout << "Duplicate: " << lines[i] << "\n";
            cout << RESET;

            cout << "Occurrences: " << count << "\n";
            cout << "Line numbers: ";

            for (int j = 0; j < lineCount; j++)
            {
                if (lines[i] == lines[j])
                {
                    cout << j + 1 << " ";
                }
            }

            cout << "\n";
            cout << "------------------------------------------------------------\n";
        }
    }

    if (!duplicatesFound)
    {
        cout << GREEN << "\nNo duplicate lines found!\n" << RESET;
    }

    cout << BRIGHT_CYAN;
    cout << "============================================================\n";
    cout << RESET;
}
// Add or remove a bookmark
// Returns 1 if added, 2 if removed, 0 if invalid
int Document::toggleBookmark(int lineNumber)
{
    if (lineNumber < 1 || lineNumber > lineCount)
    {
        return 0;
    }

    // Check whether line is already bookmarked
    for (int i = 0; i < bookmarkCount; i++)
    {
        if (bookmarks[i] == lineNumber)
        {
            // Remove existing bookmark
            for (int j = i; j < bookmarkCount - 1; j++)
            {
                bookmarks[j] = bookmarks[j + 1];
            }

            bookmarkCount--;

            return 2;
        }
    }

    // Increase capacity if necessary
    if (bookmarkCount == bookmarkCapacity)
    {
        resizeBookmarks();
    }

    // Add new bookmark
    bookmarks[bookmarkCount] = lineNumber;
    bookmarkCount++;

    return 1;
}


// Display all bookmarked lines
void Document::displayBookmarks() const
{
    cout << "\n";

    cout << BRIGHT_CYAN << BOLD;
    cout << "============================================================\n";
    cout << "                    BOOKMARKED LINES                       \n";
    cout << "============================================================\n";
    cout << RESET;

    if (bookmarkCount == 0)
    {
        cout << YELLOW << "\nNo bookmarked lines found!\n" << RESET;
    }
    else
    {
        cout << BRIGHT_BLUE << BOLD;
        cout << "  LINE     CONTENT\n";
        cout << "  ----------------------------------------------------------\n";
        cout << RESET;

        for (int i = 0; i < bookmarkCount; i++)
        {
            int lineNumber = bookmarks[i];

            cout << BRIGHT_GREEN << BOLD;
            cout << "  " << setw(4) << right << lineNumber;
            cout << "     ";
            cout << RESET;

            cout << WHITE << lines[lineNumber - 1] << RESET << "\n";
        }
    }

    cout << BRIGHT_CYAN;
    cout << "============================================================\n";
    cout << RESET;
}