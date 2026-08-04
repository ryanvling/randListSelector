// Random List Item Selector
//
// Command-line tool that, when queried, pseudo-randomly selects & outputs an
// item from a list defined an input .txt file.
//
// Last Updated: 4 Aug 2026

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef const char *const ConstString;

typedef struct {
	ConstString chars;
	int32_t length;
} ConstStringWithLength;

const uint8_t INPUT_LIMIT = 255;

// Messages
ConstString MSG_INTRO =
	"Please enter the pathname of a .txt file, '?' to see the list of commands,"
	" or 'end' to exit the program:\n";
ConstString MSG_PROMPT = "> ";
ConstString MSG_HELP =
	"============================== HELP GUIDE ==============================\n"
	"Available commands:\n"
	" - ?: Show this help message\n"
	" - r: Output another random prompt\n"
	" - n: Input a new list\n"
	" - end: Exit the program\n\n";
ConstString MSG_NEW_FILE = "Please enter the pathname of a .txt file:\n";
ConstString MSG_ERROR_INVALID =
	"This query is not a valid file pathname or recognised command. Enter '?' "
	"for further help.\n";
ConstString MSG_ERROR_NO_FILE =
	"No file has been input yet. Please enter a .txt file pathname 1st.\n";
ConstString MSG_EXIT = "Bye! (>wo)/\n";

// Commands
ConstStringWithLength CMD_HELP = {"?", 1};
ConstStringWithLength CMD_RAND = {"r", 1};
ConstStringWithLength CMD_NEW = {"n", 1};
ConstStringWithLength CMD_EXIT = {"end", 3};

////////////////////////////////////////////////////////////////////////////////

bool getList(char *input, char **list);
bool readFile(char *input, FILE *listFile);
char *fileToString(FILE *listFile, uint64_t contentLength);
void getItems(char *listContents, uint64_t contentLength, char **list);

void randomSelect(size_t maxIdx, char**list);

////////////////////////////////////////////////////////////////////////////////

int main(void) {
	char *input = malloc(INPUT_LIMIT + 1 * sizeof(char));
	bool listIsInput = false;
	char **list = NULL;
	size_t maxIdx = 0;
	size_t randIdx = 0;
	bool exit = false;

	printf("%s", MSG_INTRO);
	srand((unsigned int)time(NULL));
	
	while (exit == false) {
		printf("%s", MSG_PROMPT);
		fgets(input, INPUT_LIMIT + 1, stdin);

		// Process user input
		if (strncmp(input, CMD_HELP.chars, CMD_HELP.length) == 0) {
			printf("%s", MSG_HELP);
		} else if (strncmp(input, CMD_RAND.chars, CMD_RAND.length) == 0) {
			if (listIsInput) {
				randomSelect(maxIdx, list);
			} else {
				printf("%s", MSG_ERROR_NO_FILE);
			}
		} else if (strncmp(input, CMD_NEW.chars, CMD_NEW.length) == 0) {
			// TODO - clear current list
			printf("%s%s", MSG_NEW_FILE, MSG_PROMPT);
		} else if (strncmp(input, CMD_EXIT.chars, CMD_EXIT.length) == 0) {
			printf("%s", MSG_EXIT);
			exit = true;
		} else {
			listIsInput = getList(input, list);
		}
	}

	return 0;
}

// Get the indexed list from the list file
bool getList(char *input, char **list) {
	FILE *listFile = NULL;

	if (readFile(input, listFile) == false) {
		printf("%s", MSG_ERROR_INVALID);
		return false;
	}
	
	// TODO - get contentLength
	// char *listContents = fileToString(listFile, contentLength);
	// getItems(listContents, contentLength, list);

	return true;
}

// Reads the file given by the input pathname
// Returns true if the file was successfully read, & false otherwise
bool readFile(char *input, FILE *listFile) {
	bool valid = true;
	// TODO - check for file type
	listFile = fopen(input, "r");

	if (listFile == NULL) {
		fprintf(stderr, "Unable to open file: %s\n", input);
		valid = false;
	}

	return valid;
}

// Read contents of the list file to a string
char *fileToString(FILE *listFile, uint64_t contentLength) {
	char *listContents = NULL; // TODO
	uint8_t inputByte;
	int contentsIdx = 0;

	while(contentsIdx < contentLength) {
		inputByte = fgetc(listFile);
		listContents[contentsIdx] = inputByte;
		++contentsIdx;
	}

	return listContents;
}

// Read each list item into an array
void getItems(char *listContents, uint64_t contentLength, char **list) {
	// TODO
}

// Pseudo-randomly selects an index from 0 to maxIdx (inclusive), then outputs
// the list item at that index
void randomSelect(size_t maxIdx, char **list) {
	size_t randIdx = rand() % maxIdx; // TODO - adjust for skew
	printf("%s\n", list[randIdx]);
}
