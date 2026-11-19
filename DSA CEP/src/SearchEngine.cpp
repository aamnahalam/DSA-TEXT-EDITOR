
#include "SearchEngine.h"
#include <iostream>
#include <cctype>
using namespace std;

// Compare two characters according to the selected search mode
static bool charactersMatch(char a, char b, bool caseSensitive)
{
    if (caseSensitive)
    {
        return a == b;
    }

    return tolower(static_cast<unsigned char>(a)) ==
           tolower(static_cast<unsigned char>(b));
}

// Check whether a search word matches at a particular position
static bool matchesAt(
    const string& line,
    const string& searchWord,
    int position,
    bool caseSensitive)
{
    if (position < 0 ||
        position + static_cast<int>(searchWord.length()) >
        static_cast<int>(line.length()))
    {
        return false;
    }

    for (int k = 0; k < static_cast<int>(searchWord.length()); k++)
    {
        if (!charactersMatch(line[position + k],
                             searchWord[k], caseSensitive))
        {
            return false;
        }
    }

    return true;
}

// Search for the first matching position from a given starting point
static int findMatch(
    const string& line,
    const string& searchWord,
    int startPosition,
    bool caseSensitive)
{
    for (int j = startPosition;
         j <= static_cast<int>(line.length()) -
              static_cast<int>(searchWord.length());
         j++)
    {
        if (matchesAt(line, searchWord, j, caseSensitive))
        {
            return j;
        }
    }

    return -1;
}


// Search Text
void SearchEngine::searchText(
    const Document& doc,
    const string& searchWord,
    bool caseSensitive) const
{
    if (searchWord.empty())
    {
        cout << "Error: Search word cannot be empty.\n";
        return;
    }

    int totalOccurrences = 0;

    cout << "\n========== SEARCH RESULTS ==========\n";

    for (int i = 1; i <= doc.getLineCount(); i++)
    {
        string currentLine = doc.getLine(i);

        for (int j = 0;
             j <= static_cast<int>(currentLine.length()) -
                  static_cast<int>(searchWord.length());
             j++)
        {
            if (matchesAt(currentLine, searchWord, j, caseSensitive))
            {
                totalOccurrences++;

                cout << "Found at Line: " << i
                     << ", Position: " << j + 1 << endl;
            }
        }
    }

    if (totalOccurrences == 0)
    {
        cout << "No matching text found.\n";
    }
    else
    {
        cout << "\nTotal occurrences: "
             << totalOccurrences << endl;
    }

    cout << "====================================\n";
}


// Find Next Occurrence
bool SearchEngine::findNext(
    const Document& doc,
    const string& searchWord,
    int& currentLine,
    int& currentPosition,
    bool caseSensitive) const
{
    if (searchWord.empty())
    {
        return false;
    }

    int totalLines = doc.getLineCount();

    if (totalLines == 0)
    {
        return false;
    }

    int startLine = currentLine;
    int startPosition = currentPosition;

    for (int i = 0; i < totalLines; i++)
    {
        int lineNumber = ((startLine - 1 + i) % totalLines) + 1;

        string line = doc.getLine(lineNumber);

        int start = 0;

        if (i == 0)
        {
            start = startPosition + 1;

            if (start < 0)
            {
                start = 0;
            }
        }

        int foundPosition = findMatch(
            line, searchWord, start, caseSensitive);

        if (foundPosition != -1)
        {
            currentLine = lineNumber;
            currentPosition = foundPosition;

            return true;
        }
    }

    return false;
}


// Replace First Occurrence
bool SearchEngine::replaceOne(
    Document& doc,
    const string& searchWord,
    const string& replacementText,
    bool caseSensitive) const
{
    if (searchWord.empty())
    {
        return false;
    }

    for (int i = 1; i <= doc.getLineCount(); i++)
    {
        string currentLine = doc.getLine(i);

        int position = findMatch(
            currentLine, searchWord, 0, caseSensitive);

        if (position != -1)
        {
            currentLine.replace(
                static_cast<size_t>(position),
                searchWord.length(),
                replacementText);

            string oldText;

            return doc.editLine(i, currentLine, oldText);
        }
    }

    return false;
}


// Replace Selected Occurrence
bool SearchEngine::replaceOne(
    Document& doc,
    const string& searchWord,
    const string& replacementText,
    int lineNumber,
    int position,
    bool caseSensitive) const
{
    if (searchWord.empty())
    {
        return false;
    }

    if (lineNumber < 1 || lineNumber > doc.getLineCount())
    {
        return false;
    }

    if (!matchesAt(
        doc.getLine(lineNumber),
        searchWord,
        position,
        caseSensitive))
    {
        return false;
    }

    string currentLine = doc.getLine(lineNumber);

    currentLine.replace(
        static_cast<size_t>(position),
        searchWord.length(),
        replacementText);

    string oldText;

    return doc.editLine(lineNumber, currentLine, oldText);
}


// Replace All Occurrences
int SearchEngine::replaceAll(
    Document& doc,
    const string& searchWord,
    const string& replacementText,
    bool caseSensitive) const
{
    if (searchWord.empty())
    {
        return 0;
    }

    int totalReplacements = 0;

    for (int i = 1; i <= doc.getLineCount(); i++)
    {
        string originalLine = doc.getLine(i);
        string newLine = "";

        int position = 0;
        int foundPosition;

        int lineReplacements = 0;

        while ((foundPosition = findMatch(
                    originalLine,
                    searchWord,
                    position,
                    caseSensitive)) != -1)
        {
            newLine += originalLine.substr(
                position, foundPosition - position);

            newLine += replacementText;

            position = foundPosition +
                       static_cast<int>(searchWord.length());

            lineReplacements++;
        }

        if (lineReplacements > 0)
        {
            newLine += originalLine.substr(position);

            string oldText;

            if (doc.editLine(i, newLine, oldText))
            {
                totalReplacements += lineReplacements;
            }
        }
    }

    return totalReplacements;
}


// Find Previous Occurrence
bool SearchEngine::findPrevious(
    const Document& doc,
    const string& searchWord,
    int& currentLine,
    int& currentPosition,
    bool caseSensitive) const
{
    if (searchWord.empty())
    {
        return false;
    }

    int totalLines = doc.getLineCount();

    if (totalLines == 0)
    {
        return false;
    }

    int startLine = currentLine;
    int startPosition = currentPosition;

    for (int i = 0; i < totalLines; i++)
    {
        int lineNumber = ((startLine - 1 - i + totalLines)
                          % totalLines) + 1;

        string line = doc.getLine(lineNumber);

        int start = static_cast<int>(line.length()) -
                    static_cast<int>(searchWord.length());

        if (i == 0)
        {
            start = startPosition - 1;
        }

        for (int j = start; j >= 0; j--)
        {
            if (matchesAt(line, searchWord, j, caseSensitive))
            {
                currentLine = lineNumber;
                currentPosition = j;

                return true;
            }
        }
    }

    return false;
}
