#include "RecentFiles.h"

RecentFiles::RecentFiles()
{
    count = 0;
}

void RecentFiles::addFile(const string& filename)
{
    if (filename.empty())
        return;

    // Remove the file if it already exists
    int position = -1;

    for (int i = 0; i < count; i++)
    {
        if (files[i] == filename)
        {
            position = i;
            break;
        }
    }

    if (position != -1)
    {
        for (int i = position; i < count - 1; i++)
        {
            files[i] = files[i + 1];
        }

        count--;
    }

    // Make room if the list is full
    if (count == MAX_FILES)
    {
        count--;
    }

    // Shift existing files one position down
    for (int i = count; i > 0; i--)
    {
        files[i] = files[i - 1];
    }

    files[0] = filename;
    count++;
}

int RecentFiles::getCount() const
{
    return count;
}

string RecentFiles::getFile(int index) const
{
    if (index < 0 || index >= count)
        return "";

    return files[index];
}