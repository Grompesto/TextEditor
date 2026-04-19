#include "Editor.h"
#include <iostream>
#include <fstream>

//Functions for editor operations
void Editor::loadFromFile(const std::string& filename) // Load text from file into editor
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "Error opening file: " << filename << std::endl;
		return;
	}

	lines.clear();
	clearRedo();
	while (!undoStack.empty()) undoStack.pop();
	
	std::string line;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}
}

void Editor::print() const // Print the current text in the editor with line numbers
{
	for (size_t i = 0; i < lines.size(); ++i)
	{
		std::cout << i << ':' << lines[i] << std::endl;
	}
}

void Editor::addLine(const std::string& line) // Add a new line to the end of the text and record the action for undo/redo
{
	lines.push_back(line);

	Action action;
	action.type = ActionType::Add;
	action.index = lines.size() - 1;
	action.newText = line;

	undoStack.push(action);
	
	clearRedo();
}

void Editor::saveToFile(const std::string& filename) // Save the current text in the editor to a file
{
	std::ofstream file(filename);

	if(!file.is_open())
	{
		std::cout << "Error opening file: " << filename << std::endl;
		return;
	}

	for (const auto& l : lines)
	{
		file << l << '\n';
	}
}

void Editor::deleteLine(size_t index) // Delete a line at a specific index and record the action for undo/redo
{
	if (index >= lines.size())
	{
		std::cout << "Invalid index\n";
		return;
	}
	
	Action action;
	action.type = ActionType::Delete;
	action.index = index;
	action.oldText = lines[index];

	lines.erase(lines.begin() + index);

	undoStack.push(action);

	clearRedo();
}

void Editor::editLine(size_t index, const std::string& newLine) // Edit a line at a specific index and record the action for undo/redo
{
	if (index >= lines.size())
	{
		std::cout << "Invalid index\n";
		return;
	}
	
	Action action;
	action.type = ActionType::Edit;
	action.index = index;
	action.oldText = lines[index];
	action.newText = newLine;

	lines[index] = newLine;

	undoStack.push(action);
	
	clearRedo();
}

void Editor::undo() // Undo the last action performed in the editor and record it for redo
{
	if (undoStack.empty())
	{
		std::cout << "Nothing to undo\n";
		return;
	}
		
	Action action = undoStack.top();
	undoStack.pop();

	if (action.type == ActionType::Add)
	{
		if (action.index <= lines.size())
		{
			lines.erase(lines.begin() + action.index);
		}
	}
	else if (action.type == ActionType::Delete)
	{
		if (action.index <= lines.size())
		{
			lines.insert(lines.begin() + action.index, action.oldText);
		}
	}
	else if (action.type == ActionType::Edit)
	{
		if (action.index <= lines.size())
		{
			lines[action.index] = action.oldText;
		}
	}
	else if (action.type == ActionType::Replace)
	{
		if (action.index <= lines.size())
		{
			lines[action.index] = action.oldText;
		}
	}

	redoStack.push(action);
}

void Editor::redo() // Redo the last undone action in the editor and record it for undo
{
	if (redoStack.empty())
	{
		std::cout << "Nothing to redo\n";
		return;
	}

	Action action = redoStack.top();
	redoStack.pop();

	if (action.type == ActionType::Add) 
	{
		if (action.index <= lines.size())
		{
			lines.insert(lines.begin() + action.index, action.newText);
		}
	}
	else if (action.type == ActionType::Delete) 
	{
		if (action.index <= lines.size())
		{
			lines.erase(lines.begin() + action.index);
		}
	}
	else if (action.type == ActionType::Edit) 
	{
		if (action.index <= lines.size())
		{
			lines[action.index] = action.newText;
		}
	}
	else if (action.type == ActionType::Replace)
	{
		if (action.index <= lines.size())
		{
			lines[action.index] = action.newText;
		}
	}

	undoStack.push(action);
}

std::vector<size_t> Editor::find(const std::string& query) const // Find all lines that contain a specific query string and return their indices
{
	std::vector<size_t> result;

	for (size_t i = 0; i < lines.size(); ++i)
	{
		if (lines[i].find(query) != std::string::npos)
		{
			result.push_back(i);
		}
	}
	return result;
}

void Editor::replaceInLine(size_t index, const std::string& from, const std::string& to) // Replace the first occurrence of a specific substring in a line at a specific index with another substring
{
	if (index >= lines.size()) return;

	std::string oldLine = lines[index];

	size_t pos = lines[index].find(from);
	if (pos == std::string::npos) return;

	lines[index].replace(pos, from.length(), to);

	Action action;
	action.type = ActionType::Replace;
	action.index = index;
	action.oldText = oldLine;
	action.newText = lines[index];

	undoStack.push(action);
	clearRedo();
}

void Editor::replaceAll(const std::string& from, const std::string& to) // Replace all occurrences of a specific substring in all lines with another substring
{
	if (from.empty()) return;
	
	for (size_t i = 0; i < lines.size(); ++i)
	{
		std::string oldLine = lines[i];

		size_t pos = 0;
		bool changed = false;

		while ((pos = lines[i].find(from,pos)) != std::string::npos)
		{
			lines[i].replace(pos, from.length(), to);
			pos += to.length();
			changed = true;
		}

		if (changed)
		{
			Action action;
			action.type = ActionType::Replace;
			action.index = i;
			action.oldText = oldLine;
			action.newText = lines[i];

			undoStack.push(action);
		}
	}

	clearRedo();
}

const std::string& Editor::getLine(size_t index) const // Get the line at a specific index in the editor
{
	if (index >= lines.size())
	{
		throw std::out_of_range("Invalid index");
	}
	return lines[index];
}

void Editor::clearRedo() // Clear the redo stack to prevent redoing actions after a new action has been performed
{
	while (!redoStack.empty()) redoStack.pop();
}