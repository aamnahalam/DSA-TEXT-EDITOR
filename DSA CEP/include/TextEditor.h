#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <iostream>
#include <string>
#include "EditorController.h"
#include "RecentFiles.h"

using namespace std;

class TextEditor
{
private:

    EditorController editor;
RecentFiles recentFiles;
    string currentFilename;
    bool isModified;
 bool lightMode;
 bool autoSaveEnabled;

    int readNumber(string message);
    string readText(string message);

    void showMenu();
    void showWelcomeScreen();
    void changeTheme();
    void applyTheme();

    // Unsaved changes protection
    bool saveChanges();
    bool confirmSaveChanges();

    void autoSaveIfEnabled();
void toggleAutoSave();

    void createNewDocument();
    void openDocument();
    void insertLine();
    void editLine();
    void convertTextCase();
    void wordFrequencyAnalyzer();
    void duplicateLineFinder();
    void bookmarkLine();
void showBookmarks();
    void deleteLine();
    void insertText();
    void deleteText();
    void searchText();
    void replaceOne();
    void replaceAll();
    void navigateNext();
    void navigatePrevious();
    void undo();
    void redo();
    void displayDocument();
    void saveDocument();
    void saveAsDocument();
    void searchHistory();
void showRecentFiles();
void showSavedDocuments();
public:

    TextEditor();
    void run();
};

#endif