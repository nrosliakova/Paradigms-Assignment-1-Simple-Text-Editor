#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
	char value = NULL;
	node* next = NULL;
} node;

typedef struct coordinates{
	int line_num = NULL;
	int char_num = NULL;
} coordinates;

//node* resize(node* ptr, int new_size);
node** resize();
coordinates* resize_coordinates(coordinates* ptr, int new_size);
void append(const char text[]);
node* insert(const char text[], node* nd);
coordinates* search(const char text[]);
void print_text();
void print_text_in_file(FILE* fptr);
void clean_buffer();

int arraysize = 4;
node** p_first_chars;
//node* p_last_chars;
node* last_char;
int line_counter = 0;

int main() {

	p_first_chars = (node**)calloc(arraysize, sizeof(node));
	for (int i = 0; i < arraysize; i++) {
		//node* n;
		p_first_chars[i] = NULL;
	}

	//---
	last_char = p_first_chars[0];
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
					"2 - Start the new line\n" // done
					"3 - Use files to saving the information\n" // done
					"4 - Use files to loading the information\n" // done
					"5 - Print the current text to console\n" // done
					"6 - Insert the text by line and symbol index\n" // done
					"7 - Search\n" // done
					"e - Exit\n" // done
				);
				break;
			case '1': // Append text symbols to the end 
			{
				char text[100];
				printf("Write text to append (up to 100 characters):\n\n");
				while (getchar() != '\n');
				fgets(text, sizeof(char)*100, stdin);
				int len = strlen(text);
				if (len > 0 && text[len - 1] == '\n') {
					text[len - 1] = '\0';
				}
				text[len] = '\0';
				append(text);
				printf("\n");
				printf("Done! Text to append:\n%s\n", text);
				break;
			}
			case '2': // Start the new line
				append("\n");
				line_counter++;
				if (line_counter > arraysize)
					p_first_chars = resize();
				printf("Done!\n");
				break;
			case '3': // Use files to saving the information
				FILE * fptr;
				fopen_s(&fptr, "C:\\Dev\\KSE\\1 year\\Principles and Paradigms\\Assignments\\Simple Text Editor\\TextEditorResult.txt", "w");
				print_text_in_file(fptr);
				fclose(fptr);

				printf("Text has been saved successfully!\n");
				break;
			case '4': // Use files to loading the information
			{
				char fname[100];
				printf(" Enter the file name for loading: ");
				//clean_buffer();
				while (getchar() != '\n');
				fgets(fname, sizeof(char) * 100, stdin);
				int fname_len = strlen(fname);
				if (fname_len > 0 && fname[fname_len - 1] == '\n') {
					fname[fname_len - 1] = '\0';
				}
				fname[fname_len] = '\0';

				FILE* fptr;
				if (fopen_s(&fptr, fname, "r") != 0) {
					printf("Error: can not open file %s\n", fname);
				}
				else {
					
					char text[100];
					while (fgets(text, 100, fptr) != NULL) {
						append("\n");
						line_counter++;

						int len = strlen(text);
						if (len > 0 && text[len - 1] == '\n') {
							text[len - 1] = '\0';
						}
						text[len] = '\0';

						append(text);

					}


					printf("\n");
					printf("Text has been loaded successfully!\n");
					fclose(fptr);
				}
				break;
			}
			case '5': // Print the current text to console 
			{
				printf("Your text:\n\n");
				print_text();
				printf("\n\n");

				break;
			}
				
			case '6': // Insert the text by line and symbol index
			{
				int line_num;
				int char_num;
				printf(" Choose line and index: ");
				scanf_s("%d %d", &line_num, &char_num);
				printf("\n");

				if (line_num > line_counter) {
					printf("Error, this line does not exist yet. ");
					break;
				}
				node* node_before_insert = p_first_chars[line_num];
				bool error_occurred = false;
				for (int i = 1; i <= char_num; i++) {
					if (node_before_insert->next == NULL) {
						printf("Error, this character number does not exist yet. Last character number is %d.", i);
						error_occurred = true;
						break;
					}
					node_before_insert = node_before_insert->next;
				}
				if (error_occurred) break;

				char text[100];
				printf("Enter text to insert (up to 100 characters):\n\n");
				while (getchar() != '\n');
				fgets(text, sizeof(char) * 100, stdin);
				int len = strlen(text);
				if (len > 0 && text[len - 1] == '\n') {
					text[len - 1] = '\0';
				}
				text[len] = '\0';
				node_before_insert = insert(text, node_before_insert);

				break;
			}
			case '7': // Search (please note that text can be found more than once)
			{
				char text[100];
				printf("Enter text to search: ");
				while (getchar() != '\n');
				fgets(text, sizeof(char) * 100, stdin);
				int len = strlen(text);
				if (len > 0 && text[len - 1] == '\n') {
					text[len - 1] = '\0';
				}
				text[len] = '\0';
	
				//-----------------------------------------------------------------
				node cur_char = *p_first_chars[0];
				int coord_arr_size = 4;
				coordinates* coord_arr = (coordinates*)calloc(coord_arr_size, sizeof(coordinates));
				int el_counter = 0;
				int len_ = strlen(text);
				int i = 0;
				int cur_line_num = 0;
				int cur_char_num = 0;
				coordinates coord;

				while (cur_char.value != NULL) {
					if (cur_char.value == '\n') {
						cur_line_num++;
						cur_char_num = 0;
						if (cur_char.next != NULL) cur_char = *cur_char.next;
						continue;
					}
					if (cur_char.value == text[i]) {
						if (i == 0) {
							coord.char_num = cur_char_num;
							coord.line_num = cur_line_num;
						}
						i++;
					}
					else i = 0;

					if (i == len_) {
						if (el_counter + 1 > coord_arr_size) {
							coord_arr_size *= 2;
							coord_arr = resize_coordinates(coord_arr, coord_arr_size);
						}
						coord_arr[el_counter] = coord;
						el_counter++;
						i = 0;
					}
					if (cur_char.next != NULL) {
						cur_char = *cur_char.next;
						cur_char_num++;
					}
					else break;
				}
				//-----------------------------------------------------------------
				printf("\nText is present in positions (%d results): \n\n", el_counter);
				printf("\tline\tchar\n");
				for(int j = 0; j < el_counter; j++){
					printf("\t%d\t%d\n", coord_arr[j].line_num, coord_arr[j].char_num);
				}
				break;
			}
			case 'e':
				return 0;
			default:
				printf("Error! The command '%c' does not exist.\n", command);
		}
		printf("\nPress enter to continue... ");
		//while (getchar() != '\n');
		//getchar();
		clean_buffer();
		system("cls");
		//while (getchar() != '\n');
	}
	
	
	return 0;
}

node** resize() {
	arraysize *= 2;
	node** ptr2 = (node** )realloc(p_first_chars, arraysize * sizeof(node));
	return ptr2;
}
coordinates* resize_coordinates(coordinates* ptr, int new_size) {
	arraysize *= 2;
	coordinates* ptr2 = (coordinates* )realloc(ptr, new_size * sizeof(coordinates));
	return ptr2;
}

void append(const char text[]) {
	int len = strlen(text);
	node* nodes = (node*)calloc(len + 1, sizeof(node));
	if (last_char != NULL && last_char->value != NULL) {
		last_char->next = &nodes[0];
	}

	for (int i = 0; i < len; i++) {
		node* cur_node_p;
		cur_node_p = &nodes[i];
		cur_node_p->value = text[i];

		node* node_next_p = &nodes[i + 1];
		cur_node_p->next = (i != len - 1) ? node_next_p : NULL;
		if (p_first_chars[line_counter] == NULL || p_first_chars[line_counter]->value == NULL)
			p_first_chars[line_counter] = cur_node_p;
				

		last_char = cur_node_p;
	}
}
node* insert(const char text[], node* nd) {
	int len = strlen(text);
	node* nodes = (node*)calloc(len + 1, sizeof(node));
	node* prev_node = nd;
	node* node_after_insert = nd->next;
	prev_node->next = &nodes[0];	

	for (int i = 0; i < len; i++) {
		node* cur_node_p;
		cur_node_p = &nodes[i];
		cur_node_p->value = text[i];

		node* node_next_p = &nodes[i + 1];
		cur_node_p->next = (i != len - 1) ? node_next_p : NULL;			

		prev_node = cur_node_p;
	}
	prev_node->next = node_after_insert;
	return nd;
}

void print_text() {
	node cur_char = *p_first_chars[0];
	while (cur_char.value != NULL) {
		printf("%c", cur_char.value);
		if (cur_char.next != NULL)
			cur_char = *cur_char.next;
		else break;
	}
}
void print_text_in_file(FILE * fptr) {
	node cur_char = *p_first_chars[0];
	while (cur_char.value != NULL) {
		//printf("%c", cur_char.value);
		fprintf(fptr, "%c", cur_char.value);
		if (cur_char.next != NULL)
			cur_char = *cur_char.next;
		else break;
	}
}

void clean_buffer() {
	while (getchar() != '\n');
	getchar();

}