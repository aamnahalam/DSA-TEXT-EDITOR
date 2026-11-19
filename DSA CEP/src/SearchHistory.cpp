
#include "SearchHistory.h"

// Constructor
SearchHistory::SearchHistory()
{
    front = 0;
    count = 0;
}

// Add a new search
void SearchHistory::addSearch(const string& searchWord)
{
    if (searchWord.empty())
    {
        return;
    }

    int rear;

    if (count == MAX_SIZE)
    {
        // Queue is full: remove oldest search
        searches[front] = searchWord;

        front = (front + 1) % MAX_SIZE;
    }
    else
    {
        rear = (front + count) % MAX_SIZE;

        searches[rear] = searchWord;

        count++;
    }
}

// Display search history
void SearchHistory::displayHistory() const
{
    cout << "\n========== SEARCH HISTORY ==========\n";

    if (count == 0)
    {
        cout << "No search history available.\n";
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            int index = (front + i) % MAX_SIZE;

            cout << i + 1 << ". " << searches[index] << endl;
        }
    }

    cout << "====================================\n";
}

// Clear search history
void SearchHistory::clearHistory()
{
    front = 0;
    count = 0;

    cout << "Search history cleared successfully.\n";
}
