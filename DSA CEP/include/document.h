
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

using namespace std;

class Document
{
private:
    string* lines;
    int capacity;
    int lineCount;

        // Bookmark storage
    int* bookmarks;
    int bookmarkCount;
    int bookmarkCapacity;

    void resize();
    void resizeBookmarks();
public:

    // Constructor
    Document();

 // Copy Constructor
Document(const Document& other)
{
    lineCount = other.lineCount;
    capacity = other.capacity;

    lines = new string[capacity];

    for (int i = 0; i < lineCount; i++)
    {
        lines[i] = other.lines[i];
    }

    bookmarkCount = other.bookmarkCount;
    bookmarkCapacity = other.bookmarkCapacity;

    bookmarks = new int[bookmarkCapacity];

    for (int i = 0; i < bookmarkCount; i++)
    {
        bookmarks[i] = other.bookmarks[i];
    }
}

// Copy Assignment Operator
Document& operator=(const Document& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] lines;
    delete[] bookmarks;

    lineCount = other.lineCount;
    capacity = other.capacity;

    lines = new string[capacity];

    for (int i = 0; i < lineCount; i++)
    {
        lines[i] = other.lines[i];
    }

    bookmarkCount = other.bookmarkCount;
    bookmarkCapacity = other.bookmarkCapacity;

    bookmarks = new int[bookmarkCapacity];

    for (int i = 0; i < bookmarkCount; i++)
    {
        bookmarks[i] = other.bookmarks[i];
    }

    return *this;
}

    // Destructor
    ~Document();

    bool insertLine(int position, string text);

    bool editLine(int lineNumber, string newText,
                  string& oldText);

      bool convertCase(int lineNumber, int choice,
                 string& convertedText) const;

    bool deleteLine(int lineNumber, string& deletedText);

    bool insertText(int lineNumber, int column, string text);

    bool deleteText(int lineNumber, int startColumn,
                    int length, string& deletedText);

    bool deleteCharacter(int lineNumber, int column,
                         string& deletedText);

    bool deleteWord(int lineNumber, int column,
                    string& deletedText);

    bool deleteRange(int lineNumber, int startColumn,
                     int length, string& deletedText);

void display(
    const string& searchWord = "",
    int selectedLine = -1,
    int selectedPosition = -1,
    bool caseSensitive = true
);

    string getLine(int lineNumber) const;

    int getLineCount() const;

    int getCharacterCount() const;

    int getWordCount() const;

int getCharacterCountWithoutSpaces() const;

void analyzeWordFrequency() const;

void findDuplicateLines() const;

// Bookmark functions
int toggleBookmark(int lineNumber);

void displayBookmarks() const;

    void clear();
};

#endif
