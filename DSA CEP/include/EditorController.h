
#ifndef EDITORCONTROLLER_H
#define EDITORCONTROLLER_H

#include "Document.h"
#include "UndoManager.h"
#include "SearchEngine.h"
#include "FileManager.h"
#include "SearchHistory.h"
#include <chrono>

class EditorController
{
private:

    Document document;
    UndoManager history;
    SearchEngine searchEngine;
FileManager fileManager;
SearchHistory searchHistory;
bool currentSearchCaseSensitive;


// Typing Statistics
long long totalCharactersTyped;
long long totalWordsTyped;

long long totalCharactersDeleted;
long long totalLinesDeleted;

double totalTypingTime;
double fastestTypingSpeed;

// Typing session tracking
chrono::steady_clock::time_point typingStartTime;
bool typingSessionActive;

// Search Navigation State
string currentSearchWord;
int currentSearchLine;
int currentSearchPosition;
bool searchStarted;

void resetSearchNavigation();

public:

    // Insert and Edit
    bool insertLine(int position, string text);

    bool editLine(int lineNumber, string newText);

    bool convertLineCase(int lineNumber, int choice);

    bool deleteLine(int lineNumber);

    bool insertText(int lineNumber, int column, string text);

    bool deleteText(int lineNumber, int column, int length);

    bool interactiveEditLine(int lineNumber, bool cursorAtEnd);

    // Undo and Redo
    bool undo();

    bool redo();

    // Search
    void searchText(const string& searchWord);

    // Replace
    bool replaceOne(const string& searchWord,
                    const string& replacementText);

    int replaceAll(const string& searchWord,
                   const string& replacementText);

    // Display
    void display();
    
    // Document Information
int getLineCount() const;

int getCharacterCount() const;

int getWordCount() const;

int getCharacterCountWithoutSpaces() const;

void displayWordFrequency() const;

void displayDuplicateLines() const;

// Bookmarks

int toggleBookmark(int lineNumber);

void displayBookmarks() const;

string getLine(int lineNumber) const;

    // File Management

bool saveFile(const string& filename);

bool openFile(const string& filename);

bool saveAs(const string& filename);

// Display all saved documents

void displaySavedFiles();

void displaySearchHistory();

void clearSearchHistory();

// Typing Statistics

bool interactiveEditInProgress;

void displayTypingStatistics() const;

// Helper functions

void recordTypedText(const string& text);

void recordDeletedCharacters(long long count);

void recordTypingTime(double seconds);

// Search Navigation

bool nextSearch();

bool previousSearch();

EditorController();

void newDocument();

};

#endif
