
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <filesystem>

#include "Document.h"

using namespace std;
class FileManager
{
private:

    // Get the complete storage path
    string getFilePath(const string& filename);

public:

    // Save document
    bool saveFile(const Document& doc, const string& filename);

    // Open existing document
    bool openFile(Document& doc, const string& filename);

    // Save document with a new filename
    bool saveAs(const Document& doc, const string& filename);

    // Display all saved documents
    void listFiles();

};

#endif
