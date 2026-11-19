# DSA Text Editor

> A feature-rich, console-based text editor in C++17, built from scratch on custom data structures.

![C++](https://img.shields.io/badge/C%2B%2B-17-blue) ![Platform](https://img.shields.io/badge/platform-Windows-lightgrey) ![Status](https://img.shields.io/badge/status-complete-brightgreen)



## 1. Overview

**DSA Text Editor** is a menu-driven terminal application for creating, editing, searching, analysing and saving plain-text documents. It was developed as a **Data Structures & Algorithms Complex Engineering Problem (DSA CEP)**. Instead of using ready-made containers such as `std::vector` or `std::stack`, the core of the editor (document buffer, undo/redo, search history, recent files) is implemented manually with raw dynamic memory, so the data-structure logic is fully visible in the code.

The program has a colourful ANSI interface, a dark/light theme, a cursor-based line editor, undo/redo, search & replace, bookmarks, word-frequency analysis, duplicate-line detection, typing statistics and optional auto-save.


## 2. Key Features

| Category | Features |
|---|---|
| Document management | Create new document, open existing file, Save, Save As, list all saved documents, recent-files list (last 5), unsaved-changes protection (Save / Don't Save / Cancel). |
| Editing | Insert line at any position, edit line, delete line, insert text at a column, delete text range, **interactive cursor-based line editing** (arrow keys, Home, End, Delete, Backspace). |
| Case conversion | UPPERCASE, lowercase, Title Case and Sentence case for any line. |
| Search & Replace | Case-sensitive search with highlighted matches, Next / Previous result navigation, Replace one, Replace all. |
| Undo / Redo | Unlimited (memory-bound) multi-level undo and redo using two stacks of document snapshots. |
| Analysis tools | Word-frequency analyser, duplicate-line finder, line/word/character counts (with and without spaces). |
| Bookmarks | Toggle a bookmark on any line and view all bookmarked lines. |
| History | Search history – the last 10 searches, stored in a circular queue. |
| Productivity | Auto-save toggle, typing statistics (characters/words typed, deletions, total typing time, fastest speed). |
| User interface | Welcome screen, categorised dashboard with 30 options, dark/light theme, coloured output, status bar (file name + SAVED / UNSAVED / NEW state). |


## 3. Data Structures & Algorithms Used

This is the heart of the project. Each structure below is hand-written – no STL containers are used for the core logic.

| Data structure | Where it is used | Details |
|---|---|---|
| Dynamic array (resizable) | `Document` – lines (`string*`) and bookmarks (`int*`) | Starts with capacity 5 and doubles when full (amortised O(1) append). Insertion/deletion in the middle shifts elements: O(n). |
| Generic Stack<T> (template) | `UndoManager` – undoStack and redoStack | Array-based stack, push/pop/peek in O(1), automatic capacity doubling, `Stack<Document>` instantiation. |
| Circular queue (fixed array) | `SearchHistory` | Capacity 10; *front* and *count* with modulo arithmetic; oldest entry is overwritten when full. O(1) add. |
| Most-recently-used list | `RecentFiles` | Fixed array of 5; reopened files move to the front; duplicates removed. |
| Linear / naive string search | `SearchEngine` | Scans every line with character-by-character matching (optionally case-insensitive); O(N·M) overall. |
| Snapshot-based undo/redo | `UndoManager` + `Document` | A deep copy of the document is pushed before every change; a new edit clears the redo stack. |
| Rule of Three | `Document` | Custom copy constructor, copy-assignment operator and destructor so deep copies are memory-safe. |


## 4. System Architecture

The project follows a layered, object-oriented design with a clear separation of responsibilities:

```
  main.cpp
     |
  TextEditor  ........ UI layer (menus, input, theme, auto-save, recent files)
     |
  EditorController ... Application logic (coordinates everything, statistics)
     |
     +-- Document ...... Text buffer + editing, bookmarks, analysis
     +-- UndoManager ... Undo/Redo  -->  Stack<Document> x2
     +-- SearchEngine .. Search / replace / next / previous
     +-- FileManager ... Load / save files in the Documents/ folder
     +-- SearchHistory . Circular queue of last 10 searches
```

| Class | Responsibility |
|---|---|
| **TextEditor** | Console UI: welcome screen, dashboard menu, input validation, theme, auto-save, recent files. Owns an *EditorController* and *RecentFiles*. |
| **EditorController** | Facade between UI and logic. Wraps every edit with undo-snapshots, tracks typing statistics and search-navigation state. |
| **Document** | In-memory text buffer. All line/text operations, case conversion, counts, bookmarks, word frequency, duplicate detection and coloured display. |
| **UndoManager** | Keeps undo and redo stacks of *Document* snapshots. |
| **Stack<T>** | Generic, array-based stack template. |
| **SearchEngine** | Stateless search / replace / find-next / find-previous algorithms operating on a *Document*. |
| **FileManager** | Reads and writes `.txt` files in the `Documents/` folder; lists saved files. |
| **SearchHistory** | Circular queue storing the 10 most recent search words. |
| **RecentFiles** | Fixed-size MRU list of the 5 most recently used files. |
| **Colours.h** | ANSI colour/format macros (`RED`, `BOLD`, …). |


### UML class diagram

The full UML class diagram (attributes, methods, visibility, multiplicity, composition and dependency arrows) is included in the repository as `docs/UML_Class_Diagram.png`; the editable StarUML source is `docs/DSA_CEP_UML.mdj`.

![UML Class Diagram](docs/UML_Class_Diagram.png)

**Relationships:** *TextEditor* ◆→ *EditorController*, *RecentFiles* (composition); *EditorController* ◆→ *Document*, *UndoManager*, *SearchEngine*, *FileManager*, *SearchHistory* (composition); *UndoManager* ◆→ 2 × *Stack<Document>* (composition); *SearchEngine*, *FileManager*, *UndoManager* ┈→ *Document* (dependency).


## 5. Project Structure

```
DSA CEP/
|-- main.cpp                 Program entry point
|-- include/                 Header files
|   |-- TextEditor.h         UI layer
|   |-- EditorController.h   Application logic
|   |-- document.h           Text buffer
|   |-- UndoManager.h        Undo / redo
|   |-- Stack.h              Generic stack template
|   |-- SearchEngine.h       Search & replace
|   |-- SearchHistory.h      Circular queue of searches
|   |-- RecentFiles.h        Recently used files
|   |-- FileManager.h        File I/O
|   `-- Colours.h            ANSI colour macros
|-- src/                     Implementations (.cpp for each header)
|-- test/                    Test programs
|-- Documents/               Saved user documents (.txt) - created automatically
|-- build/                   Compiled output
|-- docs/                    UML diagram and screenshots
`-- README.md
```


## 6. Requirements

- **Operating system:** Windows (the interactive editor uses `<conio.h>` / `_getch()`).
- **Compiler:** GCC / MinGW-w64 (g++) with **C++17** support (uses `<filesystem>`).
- **Terminal:** One that supports ANSI escape codes (Windows Terminal, VS Code terminal, Windows 10+ console).
- **Optional:** Visual Studio Code with the C/C++ extension (a build task is already provided in `.vscode/tasks.json`).


## 7. Build & Run


### Using the command line

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude main.cpp src/TextEditor.cpp src/EditorController.cpp ^
    src/document.cpp src/UndoManager.cpp src/SearchEngine.cpp src/FileManager.cpp ^
    src/SearchHistory.cpp src/RecentFiles.cpp -o build/Debug/TextEditor.exe

build\Debug\TextEditor.exe
```


### Using VS Code

- Open the project folder in VS Code.
- Press **Ctrl + Shift + B** to run the default build task.
- Run `build/Debug/TextEditor.exe` from the project root so the `Documents/` folder is created in the right place.

> **Note:** Run the program from the project root folder. Saved files are stored in a `Documents/` folder relative to the current working directory. The headers include `"Document.h"` while the file is named `document.h`; this works on Windows (case-insensitive) but on Linux/macOS rename the file to `Document.h`.


## 8. How to Use

When the program starts, a welcome screen is shown. Press **ENTER** to open the main dashboard, type the option number and press ENTER. The bottom bar always shows the current **FILE** and its **STATUS** (NEW DOCUMENT / UNSAVED CHANGES / SAVED).

| # | Option | Description |
|---|---|---|
| 01 | Create New Document | Starts an empty document (asks to save pending changes first). |
| 02 | Open Existing File | Loads a saved `.txt` file from `Documents/`. |
| 03 | Insert New Line | Inserts a new line at a chosen position. |
| 04 | Edit Existing Line | Opens the interactive cursor-based editor for a line. |
| 05 | Delete Line | Removes a line. |
| 06 | Insert Text | Inserts text at a given line and column. |
| 07 | Delete Text | Deletes a number of characters starting at a column. |
| 08 | Text Case Converter | UPPERCASE, lowercase, Title Case or Sentence case. |
| 09 | Search Text | Finds and highlights all matches of a word. |
| 10 | Replace One Occurrence | Replaces the current / first match. |
| 11 | Replace All Occurrences | Replaces every match and reports the count. |
| 12 / 13 | Next / Previous Search Result | Jumps between matches of the last search. |
| 14 / 15 | Undo / Redo | Reverts or re-applies the last change. |
| 16 | Display Document | Prints the numbered document. |
| 17 / 18 | Display / Clear Search History | Shows or clears the last 10 searches. |
| 19 / 20 | Save / Save As | Saves under the current or a new name (`.txt` added automatically). |
| 21 | Word Frequency Analyzer | Counts how often each word appears. |
| 22 | Find Duplicate Lines | Lists identical lines. |
| 23 / 24 | Toggle / View Bookmarks | Marks lines and lists the bookmarked ones. |
| 25 | Recent Files | Shows the last 5 files; pick one to open. |
| 26 | View All Saved Documents | Lists every file in `Documents/`. |
| 27 | Change Theme | Switches between dark and light mode. |
| 28 | Toggle Auto-Save | Automatically saves after each modification when ON. |
| 29 | View Typing Statistics | Characters/words typed, deletions, typing time, fastest speed. |
| 30 | Exit Editor | Quits (prompts to save unsaved changes). |


### Interactive line editor – keyboard controls

| Key | Action |
|---|---|
| ← / → | Move cursor left / right |
| Home / End | Jump to start / end of the line |
| Backspace / Delete | Delete character before / under the cursor |
| Any printable key | Insert character at the cursor |
| Enter | Save the edited line |
| Esc | Cancel editing and keep the original line |


### Unsaved-changes prompt

Before creating a new document, opening a file or exiting with unsaved work you are asked: **Save (S)**, **Don't Save (D)** or **Cancel (C)**.


## 9. File Storage

- All documents are stored as plain `.txt` files inside the `Documents/` folder (created automatically).
- The `.txt` extension is added automatically if you omit it.
- Search history and recent files live in memory only and reset when the program closes.


## 10. Testing

The `test/` folder and `src/EditorControllerSearchTest.cpp` contain console test programs covering the document buffer, colour output, undo/redo, search & replace, navigation, file handling and an integration/overall test. Compile a test together with the needed `src/*.cpp` files, for example:

```bash
g++ -std=c++17 -Iinclude test/test_document.cpp src/document.cpp -o build/test_document.exe
build\test_document.exe
```


## 11. Complexity Summary

| Operation | Time complexity |
|---|---|
| Append a line (amortised) | O(1) |
| Insert / delete line in the middle | O(n) |
| Stack push / pop / peek | O(1) (amortised for push) |
| Save state for undo | O(n) – deep copy of the document |
| Search / replace all | O(N·M) – N characters, M pattern length |
| Add to search history / recent files | O(1) / O(k), k ≤ 5 |


## 12. Known Limitations

- Windows only because of `conio.h`.
- Undo stores a full copy of the document for each change, which uses more memory on very large files.
- Text files only; no rich formatting.
- Search history and recent files are not persisted between runs.


## 13. Future Improvements

- Replace snapshot undo with a command (delta) pattern to save memory.
- Use efficient string-matching (KMP / Boyer-Moore) in the search engine.
- Persist search history, recent files and settings in a config file.
- Cross-platform keyboard handling (ncurses) for Linux/macOS.
- Line-range selection, copy / cut / paste, and syntax highlighting.


## 14. Authors

| Name | Roll No. | Role |
1. Syeda Aamnah Alam
2. Hiba Zia
3. Hafsa Saad

**Course:** Data Structures & Algorithms (CEP)  |  **Institution:** [ NED UNIVERSITY ]  |  **Supervisor:** [ Sir Shahab Tahzeeb ]  |  **Year:** 2026


## 15. License

This project was created for educational purposes. You may add a license of your choice (for example MIT) in a `LICENSE` file.
