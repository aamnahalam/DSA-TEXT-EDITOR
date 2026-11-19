
#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "Document.h"
#include <string>
using namespace std;

class SearchEngine
{
public:
    void searchText(
        const Document& doc,
        const string& searchWord,
        bool caseSensitive = true
    ) const;

    bool replaceOne(
        Document& doc,
        const string& searchWord,
        const string& replacementText,
        bool caseSensitive = true
    ) const;

    bool replaceOne(
        Document& doc,
        const string& searchWord,
        const string& replacementText,
        int lineNumber,
        int position,
        bool caseSensitive = true
    ) const;

    int replaceAll(
        Document& doc,
        const string& searchWord,
        const string& replacementText,
        bool caseSensitive = true
    ) const;

    bool findNext(
        const Document& doc,
        const string& searchWord,
        int& currentLine,
        int& currentPosition,
        bool caseSensitive = true
    ) const;

    bool findPrevious(
        const Document& doc,
        const string& searchWord,
        int& currentLine,
        int& currentPosition,
        bool caseSensitive = true
    ) const;
};

#endif
