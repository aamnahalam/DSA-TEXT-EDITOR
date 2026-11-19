
#include "UndoManager.h"

UndoManager::UndoManager()
{
}

// Save current document before editing
void UndoManager::saveState(Document& document)
{
    undoStack.push(document);

    // New edit clears old redo history
    redoStack.clear();
}

// Undo operation
bool UndoManager::undo(Document& document)
{
    if (undoStack.isEmpty())
    {
        return false;
    }

    redoStack.push(document);

    document = undoStack.peek();

    undoStack.pop();

    return true;
}

// Redo operation
bool UndoManager::redo(Document& document)
{
    if (redoStack.isEmpty())
    {
        return false;
    }

    undoStack.push(document);

    document = redoStack.peek();

    redoStack.pop();

    return true;
}

// Check whether Undo is possible
bool UndoManager::canUndo()
{
    return !undoStack.isEmpty();
}

// Check whether Redo is possible
bool UndoManager::canRedo()
{
    return !redoStack.isEmpty();
}

// Clear Undo and Redo history
void UndoManager::clearHistory()
{
    undoStack.clear();
    redoStack.clear();
}