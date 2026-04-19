# TextEditor

A lightweight console-based text editor written in C++17, featuring full undo/redo 
history, file I/O, and text search and replace. Built as a foundation for a future 
GUI version using Dear ImGui.

## Features

- Load and save plain text files
- Add, edit, and delete lines by index
- Undo and redo for all editing operations (Add, Delete, Edit, Replace)
- Search for lines containing a given substring
- Replace first occurrence in a specific line, or all occurrences across the file
- Input handling with std::numeric_limits to prevent stream corruption

## Project Structure

- `src/Editor.h` — class interface and private data structures (Action, ActionType)
- `src/Editor.cpp` — implementation of all editor operations
- `src/TextEditor.cpp` — console UI and entry point

## Building

The project was developed with Visual Studio 2022 on Windows. Open the `.sln` file 
or compile manually with any C++17-compatible compiler:

    g++ -std=c++17 src/Editor.cpp src/TextEditor.cpp -o TextEditor

## Known Limitations

- `replaceAll` records each modified line as a separate undo action; undoing a 
  replace-all requires pressing undo once per affected line.
- No syntax highlighting or cursor navigation (planned for the ImGui UI phase).

## Roadmap

- [ ] Dear ImGui graphical interface
- [ ] Multi-file tabs
- [ ] Atomic undo for replaceAll
- [ ] Search with match highlighting

## License

MIT — see [LICENSE](LICENSE) for details.
