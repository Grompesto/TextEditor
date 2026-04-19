#include "Editor.h"
#include <iostream>
#include <limits>

int main()
{
	Editor editor;
	std::string filename = "C:\\Users\\zlaya\\Downloads\\test.txt";

	editor.loadFromFile(filename);

	int choice;
	while (true)
	{
		std::cout << "\n1. Show text\n2. Add line\n3. Delete line\n4. Edit line\n5. Save\n6. Exit\n7. Undo\n8. Redo\n9. Find\n10. Replace in line\n11. Replace all\n";
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (choice == 1)
		{
			editor.print();
		}
		else if (choice == 2)
		{
			std::string line;
			std::cout << "Enter line to add: ";
			std::getline(std::cin, line);
			editor.addLine(line);
		}
		else if (choice == 3)
		{
			size_t index;
			std::cout << "Enter line index to delete: ";
			std::cin >> index;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			editor.deleteLine(index);
		}
		else if (choice == 4)
		{
			size_t index;
			std::cout << "Enter line index to edit: ";
			std::cin >> index;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::string line;
			std::cout << "Enter new line: ";
			std::getline(std::cin, line);

			editor.editLine(index, line);
		}
		else if (choice == 5)
		{
			editor.saveToFile(filename);
		}
		else if (choice == 6)
		{
			break;
		}
		else if (choice == 7)
		{
			editor.undo();
		}
		else if (choice == 8)
		{
			editor.redo();
		}
		else if (choice == 9)
		{
			std::string query;
			std::cout << "Enter text to find: ";
			std::getline(std::cin, query);

			auto results = editor.find(query);

			for (auto index : results)
			{
				std::cout << index << ": " << editor.getLine(index) << std::endl;
			}
		}
		else if (choice == 10)
		{
			size_t index;
			std::cout << "Enter line index to replace in: ";
			std::cin >> index;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::string from, to;
			std::cout << "Enter text to replace: ";
			std::getline(std::cin, from);
			std::cout << "Enter replacement text: ";
			std::getline(std::cin, to);

			editor.replaceInLine(index, from, to);
		}
		else if (choice == 11)
		{
			std::string from, to;
			std::cout << "Enter text to replace: ";
			std::getline(std::cin, from);
			std::cout << "Enter replacement text: ";
			std::getline(std::cin, to);
			editor.replaceAll(from, to);
		}
	}
	return 0;
}
