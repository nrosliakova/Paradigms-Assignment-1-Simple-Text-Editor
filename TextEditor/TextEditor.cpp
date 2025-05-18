#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char value = NULL;
	node* next = NULL;
} node;

int main() {

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
				printf("The command is not implemented\n");
				break;
			case '2': // Start the new line
				printf("The command is not implemented\n");
				break;
			case '3': // Use files to saving the information
				printf("The command is not implemented\n");
				break;
			case '4': // Use files to loading the information
				printf("The command is not implemented\n");
				break;
			case '5': // Print the current text to console 
				printf("The command is not implemented\n");
				break;
			case '6': // Insert the text by line and symbol index
				printf("The command is not implemented\n");
				break;
			case '7': // Search (please note that text can be found more than once)
				printf("The command is not implemented\n");
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
	}
	
	
	return 0;
}

