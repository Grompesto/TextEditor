#pragma once

#include <vector>
#include <string>
#include <stack>

class Editor {
private: 
	enum class ActionType
	{
		Add,
		Delete,
		Edit,
		Replace
	};
	
	struct Action
	{
		ActionType type;
		size_t index;
		std::string oldText;
		std::string newText;
	};
	
	std::vector<std::string> lines;
	std::stack<Action> undoStack;
	std::stack<Action> redoStack;
	void clearRedo();
	
public:
	
	// I/O
	void loadFromFile(const std::string& filename);
	void saveToFile(const std::string& filename);
	
	// display
	void print() const;
	const std::string& getLine(size_t index) const;
	
	// editing
	void addLine(const std::string& line);
	void deleteLine(size_t index);
	void editLine(size_t index, const std::string& newLine);
	void replaceInLine(size_t index, const std::string& from, const std::string& to);
	void replaceAll(const std::string& from, const std::string& to);
	
	// search
	std::vector<size_t> find(const std::string& query) const;
	
	// history
	void undo();
	void redo();

};