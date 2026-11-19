
#include "FileManager.h"
#include <fstream>

using namespace std;

// GET FILE PATH
string FileManager::getFilePath(const string& filename)
{
    // Create Documents folder if it doesn't exist
    filesystem::create_directories("Documents");

    string name = filename;

    // Automatically add .txt extension
    if (filesystem::path(name).extension() != ".txt")
    {
        name += ".txt";
    }

    return (filesystem::path("Documents") / name).string();
}

// SAVE FILE
bool FileManager::saveFile(
    const Document& doc,
    const string& filename)
{
    string path = getFilePath(filename);

    ofstream outFile(path);

    if (!outFile)
    {
        cout << "Error: Unable to save file!\n";
        return false;
    }

    for (int i = 1; i <= doc.getLineCount(); i++)
    {
        outFile << doc.getLine(i) << endl;
    }

    outFile.close();

    cout << "File saved successfully!\n";

    return true;
}

// OPEN FILE
bool FileManager::openFile(
    Document& doc,
    const string& filename)
{
    string path = getFilePath(filename);

    ifstream inFile(path);

    if (!inFile)
    {
        cout << "Error: File does not exist!\n";
        return false;
    }

    Document temp;
    string line;

    while (getline(inFile, line))
    {
        if (!temp.insertLine(temp.getLineCount() + 1, line))
        {
            cout << "Error: Unable to load document!\n";
            return false;
        }
    }

    inFile.close();

    doc = temp;

    cout << "File opened successfully!\n";

    return true;
}

// SAVE AS
bool FileManager::saveAs(
    const Document& doc,
    const string& filename)
{
    return saveFile(doc, filename);
}

// LIST ALL SAVED FILES
void FileManager::listFiles()
{
    filesystem::create_directories("Documents");

    cout << "\n========== SAVED DOCUMENTS ==========\n";

    bool found = false;

    for (const auto& entry :
         filesystem::directory_iterator("Documents"))
    {
        if (entry.is_regular_file() &&
            entry.path().extension() == ".txt")
        {
            cout << "- "
                 << entry.path().filename().string()
                 << endl;

            found = true;
        }
    }

    if (!found)
    {
        cout << "No saved documents found.\n";
    }

    cout << "=====================================\n";
}
