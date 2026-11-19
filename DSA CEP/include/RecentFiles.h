#ifndef RECENTFILES_H
#define RECENTFILES_H

#include <iostream>
#include <string>

using namespace std;

class RecentFiles
{
private:
    static const int MAX_FILES = 5;
    string files[MAX_FILES];
    int count;

public:
    RecentFiles();

    void addFile(const string& filename);
    int getCount() const;
    string getFile(int index) const;
};

#endif