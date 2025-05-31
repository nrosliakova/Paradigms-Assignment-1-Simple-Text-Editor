//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//-- c++
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct node{
	char value = NULL;
	node* next = NULL;
} node;

typedef struct coordinates{
	int line_num = NULL;
	int char_num = NULL;
} coordinates;

class TextEditor {
	int arraysize = 4;
	node** p_first_chars;
	//node* p_last_chars;
	node* last_char;
	int line_counter = 0;

	public:
		char copied_text[100];
		char user_input[100];
		TextEditor() {
			p_first_chars = (node**)calloc(arraysize, sizeof(node));
			for (int i = 0; i < arraysize; i++) {
				p_first_chars[i] = NULL;
			}

			last_char = p_first_chars[0];
		}
		~TextEditor() {
			/*node* cur_char = p_first_chars[0];
			while (cur_char != NULL) {
				node* next_char = cur_char->next;
				free(cur_char);
				cur_char = next_char;
			}
			free(p_first_chars);
			p_first_chars = NULL;
			free(last_char);
			last_char = NULL;*/
		}
		//----------------------FUNCTIONS--------------------------------------------
		
		void get_input(const char question[]) {
			char text[100];
			printf("%s", question);
			while (getchar() != '\n');
			fgets(text, sizeof(char) * 100, stdin);
			int len = strlen(text);
			if (len > 0 && text[len - 1] == '\n') {
				text[len - 1] = '\0';
			}
			text[len] = '\0';
			strcpy_s(user_input, text);
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

		void new_line() {
			append("\n");
			line_counter++;
			if (line_counter > arraysize)
				p_first_chars = resize();
		}

		node* find_char(int line_num, int char_num) {
			if (line_num > line_counter) {
				printf("Error, this line does not exist yet. ");
				return NULL;
			}
			node* nod = p_first_chars[line_num];
			bool error_occurred = false;
			for (int i = 1; i <= char_num; i++) {
				if (nod->next == NULL) {
					printf("Error, this character number does not exist yet. Last character number is %d.", i);
					return NULL;
				}
				nod = nod->next;
			}
			return nod;
		}

		node* insert(node* nd) {
			int len = strlen(user_input);
			node* nodes = (node*)calloc(len + 1, sizeof(node));
			node* prev_node = nd;
			node* node_after_insert = nd->next;
			prev_node->next = &nodes[0];

			for (int i = 0; i < len; i++) {
				node* cur_node_p;
				cur_node_p = &nodes[i];
				cur_node_p->value = user_input[i];

				node* node_next_p = &nodes[i + 1];
				cur_node_p->next = (i != len - 1) ? node_next_p : NULL;

				prev_node = cur_node_p;
			}
			prev_node->next = node_after_insert;
			return nd;
		}

		void insert(int num_line) {
			int len = strlen(user_input);
			node* nodes = (node*)calloc(len + 1, sizeof(node));
			node* last_node = p_first_chars[num_line];
			node* node_after_insert = p_first_chars[num_line];
			p_first_chars[num_line] = &nodes[0];

			for (int i = 0; i < len; i++) {
				node* cur_node_p;
				cur_node_p = &nodes[i];
				cur_node_p->value = user_input[i];

				node* node_next_p = &nodes[i + 1];
				cur_node_p->next = (i != len - 1) ? node_next_p : NULL;

				last_node = cur_node_p;
			}
			last_node->next = node_after_insert;
		}

		node* replace(node* nd) {
			int len = strlen(user_input);
			node* cur_node_p = nd;

			for (int i = 0; i < len; i++) {
				cur_node_p->value = user_input[i];
				cur_node_p = cur_node_p->next;
			}
			return nd;
		}

		node* delete_(node* node_before, int num_of_symb) {
			node* cur_node_p = node_before->next;

			for (int i = 0; i < num_of_symb; i++) {
				cur_node_p = cur_node_p->next;
			}
			node_before->next = cur_node_p;
			return node_before;
		}

		node* delete_(int num_line, int num_of_symb) {
			if (num_line > line_counter) {
				printf("Error, this line does not exist yet. ");
				return NULL;
			}
			node* cur_node_p = p_first_chars[num_line];

			for (int i = 0; i < num_of_symb; i++) {
				if (cur_node_p == NULL) break;
				cur_node_p = cur_node_p->next;
			}
			p_first_chars[num_line] = cur_node_p;
			return p_first_chars[num_line];
		}

		void copy(node* nd, int num_of_symb) {
			char text[100];
			//node* node_before = nd;
			//node* cur_node_p = node_before->next;
			node* cur_node_p = nd;
			text[num_of_symb] = '\0';

			for (int i = 0; i < num_of_symb; i++) {
				if (cur_node_p == NULL) {
					text[i] = '\0';
					break;
				}
				text[i] = cur_node_p->value;
				cur_node_p = cur_node_p->next;
			}
			strcpy_s(copied_text, text);			
		}

		node* cut(node* node_before, int num_of_symb) {
			char text[100];
			//node* node_before = nd;
			node* cur_node_p = node_before->next;
			text[num_of_symb] = '\0';
			for (int i = 0; i < num_of_symb; i++) {
				if (cur_node_p == NULL) {
					text[i] = '\0';
					break;
				}
				text[i] = cur_node_p->value;
				cur_node_p = cur_node_p->next;
			}

			strcpy_s(copied_text, text);
			node_before->next = cur_node_p;
			return node_before;
		}

		node* cut(int num_line, int num_of_symb) {
			if (num_line > line_counter) {
				printf("Error, this line does not exist yet. ");
				return NULL;
			}
			char text[100];
			//node* node_before = nd;
			node* cur_node_p = p_first_chars[num_line];
			text[num_of_symb] = '\0';
			for (int i = 0; i < num_of_symb; i++) {
				if (cur_node_p == NULL) {
					text[i] = '\0';
					break;
				}
				text[i] = cur_node_p->value;
				cur_node_p = cur_node_p->next;
			}

			strcpy_s(copied_text, text);
			//node_before->next = cur_node_p;
			p_first_chars[num_line] = cur_node_p;
			return p_first_chars[num_line];
		}

		void paste(int num_line, int num_char) {
			if (num_line > line_counter) {
				printf("Error, this line does not exist yet. ");
				return;
			}
			strcpy_s(user_input, copied_text);
			if(num_line != 0)
				insert(find_char(num_line, num_char));
			else 
				insert(num_line);
		}

		void search() {
			node cur_char = *p_first_chars[0];
			int coord_arr_size = 4;
			coordinates* coord_arr = (coordinates*)calloc(coord_arr_size, sizeof(coordinates));
			int el_counter = 0;
			int len_ = strlen(user_input);
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
				if (cur_char.value == user_input[i]) {
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
			printf("\nText is present in positions (%d results): \n\n", el_counter);
			printf("\tline\tchar\n");
			for (int j = 0; j < el_counter; j++) {
				printf("\t%d\t%d\n", coord_arr[j].line_num, coord_arr[j].char_num);
			}
		}

		void print_text() {
			if (p_first_chars[0] == NULL) {
				printf("No text has been added yet.");
				return;
			}
			printf("Your text:\n\n");
			node cur_char = *p_first_chars[0];
			while (cur_char.value != NULL) {
				printf("%c", cur_char.value);
				if (cur_char.next != NULL)
					cur_char = *cur_char.next;
				else break;
			}
		}

		void load_from_file() {
			FILE* fptr;
			char fname[100];
			strcpy_s(fname, user_input);
			if (fopen_s(&fptr, fname, "r") != 0) {
				printf("Error: can not open file %s\n", fname);
			}
			else {
				char text[100];
				while (fgets(text, 100, fptr) != NULL) {
					new_line();

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
				fptr = NULL;
			}
		}

		void print_text_in_file(FILE* fptr) {
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

		
	private:
		node** resize() {
			arraysize *= 2;
			node** ptr2 = (node**)realloc(p_first_chars, arraysize * sizeof(node));
			return ptr2;
		}
		coordinates* resize_coordinates(coordinates* ptr, int new_size) {
			coordinates* ptr2 = (coordinates*)realloc(ptr, new_size * sizeof(coordinates));
			return ptr2;
		}
		
};

int main() {
	printf("Hello User!\n");
	int command;
	//char command;
	TextEditor text_editor;

	while (1) {
		printf("Choose the command (press '0' for help) : ");
		//scanf_s(" %c", &command, 2);
		cin >> command;
		printf("\n");

		switch (command) {
			case 0: // Help 
			{
				printf(
					" 1 - Append text symbols to the end\n" // done
					" 2 - Start the new line\n" // done
					" 3 - Use files to saving the information\n" // done
					" 4 - Use files to loading the information\n" // done
					" 5 - Print the current text to console\n" // done
					" 6 - Insert the text by line and symbol index\n" // done
					" 7 - Search\n" // done
					" 8 - Delete\n" // done
					" 9 - Undo\n" 
					"10 - Redo\n" 
					"11 - Cut\n" // done
					"12 - Paste\n" // done
					"13 - Copy\n" // done
					"14 - Insert with replacement\n" // done
					"-1 - Exit\n" 
				);
				break;
			}
			case 1: // Append text symbols to the end 
			{
				text_editor.get_input("Write text to append (up to 100 characters):\n\n");
				text_editor.append(text_editor.user_input);
				printf("\n");
				//printf("Done! Text to append:\n%s\n", text);
				printf("Done! Text to append:\n%s\n", text_editor.user_input);
				break;
			}
			case 2: // Start the new line
			{
				text_editor.new_line();
				printf("New line has been added!\n");
				break;
			}
			case 3: // Use files to saving the information
			{
				FILE * fptr;
				fopen_s(&fptr, "C:\\Dev\\KSE\\1 year\\Principles and Paradigms\\Assignments\\Simple Text Editor\\TextEditorResult.txt", "w");
				text_editor.print_text_in_file(fptr);
				fclose(fptr);
				free(fptr);
				fptr = NULL;

				printf("Text has been saved successfully!\n");
				break;
			}
			case 4: // Use files to loading the information
			{
				text_editor.get_input("Enter the file name for loading: ");
				text_editor.load_from_file();
				break;
			}
			case 5: // Print the current text to console 
			{
				text_editor.print_text();
				printf("\n\n");
				break;				
			}
			case 6: // Insert the text by line and symbol index
			{
				int line_num;
				int char_num;
				printf("Insert\nChoose line and index: ");
				scanf_s("%d %d", &line_num, &char_num);
				printf("\n");

				node* node_where_insert = text_editor.find_char(line_num, char_num);
				if (node_where_insert == NULL) break;

				text_editor.get_input("Enter text to insert (up to 100 characters):\n\n");

				if (char_num == 0)
					text_editor.insert(line_num);
				else 
					text_editor.insert(node_where_insert);
				
				break;
			}
			case 7: // Search (please note that text can be found more than once)
			{
				text_editor.get_input("Enter text to search: ");
				text_editor.search();
				break;
			}
			case 8: // Delete
			{
				int line_num;
				int char_num;
				int num_of_symb;
				printf("Delete\nChoose line, index and number of symbols: ");
				scanf_s("%d %d %d", &line_num, &char_num, &num_of_symb);
				printf("\n");
								
				if (char_num != 0) {
					node* node_before_del = text_editor.find_char(line_num, char_num - 1);
					if (node_before_del == NULL) break;
					text_editor.delete_(node_before_del, num_of_symb);
				}
				else text_editor.delete_(char_num, num_of_symb);

				//printf("Done!\n");

				break;
			}
			case 9: // Undo
			{
				printf("The command 9 is not implemented\n");
				break;
			}
			case 10: // Redo
			{
				printf("The command 10 is not implemented\n");
				break;
			}
			case 11: // Cut
			{
				int line_num;
				int char_num;
				int num_of_symb;
				printf("Cut\nChoose line, index and number of symbols: ");
				scanf_s("%d %d %d", &line_num, &char_num, &num_of_symb);
				printf("\n");

				if (char_num != 0) {
					node* node_before_cut = text_editor.find_char(line_num, char_num - 1);
					if (node_before_cut == NULL) break;
					text_editor.cut(node_before_cut, num_of_symb);
				}
				else text_editor.cut(char_num, num_of_symb);

				break;
			}
			case 12: // Paste
			{
				int line_num;
				int char_num;
				printf("Paste\nChoose line and index: ");
				scanf_s("%d %d", &line_num, &char_num);
				printf("\n");

				text_editor.paste(line_num, char_num);
				printf("Done!\n");

				break;
			}
			case 13: // Copy 
			{
				int line_num;
				int char_num;
				int num_of_symb;
				printf("Copy\nChoose line, index and number of symbols: ");
				scanf_s("%d %d %d", &line_num, &char_num, &num_of_symb);
				printf("\n");

				node* node_to_copy = text_editor.find_char(line_num, char_num);
				if (node_to_copy == NULL) break;

				text_editor.copy(node_to_copy, num_of_symb);
				printf("Done!\n");
				
				break;
			}
			case 14: // Insert with replacement 
			{
				int line_num;
				int char_num;
				printf("Replace\nChoose line and index: ");
				scanf_s("%d %d", &line_num, &char_num);
				printf("\n");

				node* node_start_replacement = text_editor.find_char(line_num, char_num);
				if (node_start_replacement == NULL) break;

				text_editor.get_input("Enter text to replace (up to 100 characters):\n\n");
				text_editor.replace(node_start_replacement);

				break;
			}
			case -1:
				return 0;
			default:
				printf("Error! The command '%d' does not exist.\n", command);
				break;
		}
		printf("\nPress enter to continue... ");
		while (getchar() != '\n');
		getchar();
		//text_editor.clean_buffer();
		system("cls");
		//while (getchar() != '\n');
	}
	
	
	return 0;
}