
#ifndef SEARCHHISTORY_H
#define SEARCHHISTORY_H

#include <iostream>
#include <string>
using namespace std;

class SearchHistory
{
private:
    static const int MAX_SIZE = 10;

    string searches[MAX_SIZE];

    int front;
    int count;

public:
    SearchHistory();

    void addSearch(const string& searchWord);

    void displayHistory() const;

    void clearHistory();
};

#endif
