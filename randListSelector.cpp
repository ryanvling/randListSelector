// Random List Item Selector
//
// Command-line tool that, when queried, pseudo-randomly selects & outputs an
// item from a list defined in an input .txt file.
//
// Last Updated: 12 Oct 2026

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Messages
const std::string MSG_INTRO {
	"Please enter the pathname of a .txt file, '?' to see the list of commands,"
	" or 'end' to exit the program:\n"
};
const std::string MSG_PROMPT {"> "};
const std::string MSG_HELP {
	"============================== HELP GUIDE ==============================\n"
	"Available commands:\n"
	" - ?: Show this help message\n"
	" - r: Output another random prompt\n"
	" - n: Input a new list\n"
	" - end: Exit the program\n\n"
};
const std::string MSG_NEW_FILE {"Please enter the pathname of a .txt file:\n"};
const std::string MSG_ERROR_INVALID {
	"This query is not a valid file pathname or recognised command. Enter '?' "
	"for further help.\n"
};
const std::string MSG_ERROR_NO_FILE {
	"No file has been input yet. Please enter a .txt file pathname first.\n"
};
const std::string MSG_EXIT {"Bye! (>wo)/\n"};

// Commands
const std::string CMD_HELP {"?"};
const std::string CMD_RAND {"r"};
const std::string CMD_NEW {"n"};
const std::string CMD_EXIT {"end"};

////////////////////////////////////////////////////////////////////////////////

bool getList(std::string input, std::vector<std::string> list);
void randomSelect(size_t maxIdx, std::vector<std::string> list);

////////////////////////////////////////////////////////////////////////////////

int main() {
	std::string input {};
	bool listIsInput {false};
	std::vector<std::string> list {};
	size_t maxIdx {0};
	size_t randIdx {0};
	bool exit {false};

	std::cout << MSG_INTRO;
	srand((unsigned)time(0));
	
	while (exit == false) {
		std::cout << MSG_PROMPT;
		std::cin >> input;

		// Process user input
		if (input.compare(CMD_HELP) == 0) {
			std::cout << MSG_HELP;
		} else if (input.compare(CMD_RAND) == 0) {
			if (listIsInput) {
				randomSelect(maxIdx, list);
			} else {
				std::cout << MSG_ERROR_NO_FILE;
			}
		} else if (input.compare(CMD_NEW) == 0) {
			// TODO - clear current list
			std::cout << MSG_NEW_FILE << MSG_PROMPT;
		} else if (input.compare(CMD_EXIT) == 0) {
			std::cout << MSG_EXIT;
			exit = true;
		} else {
			listIsInput = getList(input, list);
		}
	}

	return 0;
}

// Get the indexed list from the list file
bool getList(std::string input, std::vector<std::string> list) {
	std::ifstream listFile {input};

	if (!listFile) { // TODO - handle error
		std::cout << MSG_ERROR_INVALID;
		return false;
	}

	std::string line;
	while (std::getline(listFile, line)) {
		list.emplace_back(line);
	}

	return true;
}

// Pseudo-randomly selects an index from 0 to maxIdx (inclusive), then outputs
// the list item at that index
void randomSelect(size_t maxIdx, std::vector<std::string> list) {
	size_t randIdx {rand() % maxIdx}; // TODO - adjust for skew
	std::cout << list.at(randIdx) << '\n';
}
