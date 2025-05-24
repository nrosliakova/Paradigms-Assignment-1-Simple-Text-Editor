#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
	char value = NULL;
	node* next = NULL;
} node;

//node* resize(node* ptr, int new_size);
node* resize();
void append(const char text[]);
void print_text();
void clean_buffer();

int arraysize = 4;
node* p_first_chars;
node* last_char;
int line_counter = 1;

int main() {

	p_first_chars = (node*)calloc(arraysize, sizeof(node));
	for (int i = 0; i < arraysize; i++) {
		node n;
		p_first_chars[i] = n;
	}

	//---
	last_char = p_first_chars;
	printf("Hello User!\n");
	char command;

	while (1) {
		printf("Choose the command (press 'h' for help) : ");
		scanf_s(" %c", &command, 1);
		printf("\n");

		switch (command) {
			case 'h': // Help 
				printf(
					"1 - Append text symbols to the end\n" // done
					"2 - Start the new line\n"
					"3 - Use files to saving the information\n"
					"4 - Use files to loading the information\n"
					"5 - Print the current text to console\n" // done
					"6 - Insert the text by line and symbol index\n"
					"7 - Search\n"
					"e - Exit\n" // done
				);
				break;
			case '1': // Append text symbols to the end 
			{
				//printf("The command 1 is not implemented\n");
				char text[100];
				printf("Write text to append (up to 100 characters):\n\n");
				//clean_buffer();
				while (getchar() != '\n');
				fgets(text, sizeof(char)*100, stdin);
				int len = strlen(text);
				if (len > 0 && text[len - 1] == '\n') {
					text[len - 1] = '\0';
				}
				text[len] = '\0';
				//len -= 1;
				append(text);
				printf("\n");
				printf("Done! Text to append:\n%s\n", text);
				break;
			}
			case '2': // Start the new line
				//printf("The command 2 is not implemented\n");
				//append("\n");
				line_counter++;
				printf("Done!\n");
				break;
			case '3': // Use files to saving the information
				printf("The command 3 is not implemented\n");
				break;
			case '4': // Use files to loading the information
				printf("The command 4 is not implemented\n");
				break;
			case '5': // Print the current text to console 
				//printf("The command 5 is not implemented\n");
				//print_text();
				//---------
				printf("Your text:\n\n");
				for (int i = 0; i < line_counter; i++) {

					node cur_char = p_first_chars[i];
					while (cur_char.value != NULL) {
						printf("%c", cur_char.value);
						if (cur_char.next != NULL)
							cur_char = *cur_char.next;
						else break;
					}


					printf("\n");
				}
				//---------
				printf("\n");

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
		//while (getchar() != '\n');
		//getchar();
		clean_buffer();
		system("cls");
		//while (getchar() != '\n');
	}
	
	
	return 0;
}

//node* resize(node* ptr) {
node* resize() {
	//node* ptr2 = (node* )realloc(ptr, arraysize * sizeof(node*));
	node* ptr2 = (node* )realloc(p_first_chars, arraysize * sizeof(node*));
	return ptr2;
}

void append(const char text[]) {
	int len = strlen(text);
	node* nodes = (node*)calloc(len + 1, sizeof(node));
	bool execute_if = true;
	for (int i = 0; i < len; i++) {
		node* cur_node_p;
		if (last_char->value != NULL && i == 0 && execute_if) {
			last_char->next = &nodes[i];
			cur_node_p = last_char;
			i--;
			execute_if = false;
			continue;
		}
		cur_node_p = &nodes[i];
		cur_node_p->value = text[i];

		node* node_next_p = &nodes[i + 1];
		cur_node_p->next = (i != len - 1) ? node_next_p : NULL;
		last_char = cur_node_p;
		if (p_first_chars[line_counter - 1].value == NULL && i == 0)
			p_first_chars[line_counter - 1] = *cur_node_p;
	}
}

void print_text() {
	for (int i = 0; i < line_counter; i++) {
		//node cur_char = p_first_chars[i];
		//do {
		//	printf("%c", cur_char.value);
		//	cur_char = *cur_char.next;
		//} while (cur_char.value != NULL);

		node cur_char = *p_first_chars[i].next;
		while (cur_char.value != NULL) {
			printf("%c", cur_char.value);
			if (cur_char.next != NULL) 
				cur_char = *cur_char.next;
			else break;
		}


		printf("\n");
	}
}

void clean_buffer() {
	while (getchar() != '\n');
	getchar();

}