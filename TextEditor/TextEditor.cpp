#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	char value = NULL;
	node* next = NULL;
} node;

node* resize(node* ptr, int new_size);

int arraysize = 4;
node last_char;

int main() {
	//---
	node* p_first_chars;
	node* p_last_chars;

	p_first_chars = (node*)calloc(arraysize, sizeof(node));
	//p_last_chars = (node*)calloc(arraysize, sizeof(node));

	//---
	printf("'%c'\n", last_char.value);
	printf("Hello User!\n");
	char command;

	while (1) {
		printf("Choose the command (press 'h' for help) : ");
		scanf_s(" %c", &command, 1);
		printf("\n");

		switch (command) {
			case 'h': // Help 
				printf(
					"1 - Append text symbols to the end\n"
					"2 - Start the new line\n"
					"3 - Use files to saving the information\n"
					"4 - Use files to loading the information\n"
					"5 - Print the current text to console\n"
					"6 - Insert the text by line and symbol index\n"
					"7 - Search (please note that text can be found more than once)\n"
					"e - Exit\n"
				);
				break;
			case '1': // Append text symbols to the end 
				printf("The command 1 is not implemented\n");
				break;
			case '2': // Start the new line
				printf("The command 2 is not implemented\n");
				break;
			case '3': // Use files to saving the information
				printf("The command 3 is not implemented\n");
				break;
			case '4': // Use files to loading the information
				printf("The command 4 is not implemented\n");
				break;
			case '5': // Print the current text to console 
				printf("The command 5 is not implemented\n");
				break;
			case '6': // Insert the text by line and symbol index
				printf("The command 6 is not implemented\n");
				break;
			case '7': // Search (please note that text can be found more than once)
				printf("The command 7 is not implemented\n");
				break;
			case 'e':
				return 0;
			default:
				printf("Error! The command '%c' does not exist.\n", command);
		}
		printf("\nPress enter to continue. ");
		while (getchar() != '\n');
		getchar();
		system("cls");
		while (getchar() != '\n');
	}
	
	
	return 0;
}

node* resize(node* ptr, int new_size) {
	node* ptr2 = (node* )realloc(ptr, new_size);
	return ptr2;
}