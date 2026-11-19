
#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include "Document.h"
#include "Stack.h"

class UndoManager
{
private:

    Stack<Document> undoStack;
    Stack<Document> redoStack;

public:

    UndoManager();

    void saveState(Document& document);

    bool undo(Document& document);

    bool redo(Document& document);

    bool canUndo();

    bool canRedo();

    void clearHistory();
};

#endif
