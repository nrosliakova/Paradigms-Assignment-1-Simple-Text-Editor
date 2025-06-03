
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <tuple>
using namespace std;

typedef struct node{
	char value = NULL;
	node* next = NULL;
} node;

typedef struct coordinates{
	int line = NULL;
	int index = NULL;
} coordinates;

class TextEditor {
	int arraysize = 4;

	node** p_first_chars;
	node* last_char;
	int line_counter = 0;
	stack<char*> before;
	stack<char*> after; 
	int chars_counter = 0;
	coordinates cursor;

	public:
		//char copied_text[100];
		//char user_input[100];
		char* copied_text;
		char* user_input;

		TextEditor() {
			p_first_chars = (node**)calloc(arraysize, sizeof(node));
			/*for (int i = 0; i < arraysize; i++) {
				p_first_chars[i] = NULL;
			}*/

			last_char = p_first_chars[0];
			char* text = get_text();
			before.push(text);
			set_cursor(0, 0);
		}

		~TextEditor() {
			free_stacks();
			delete p_first_chars;
			p_first_chars = NULL;
			last_char = NULL;
		}
		
		/*void get_input(const char question[]) {
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
		}*/
		void set_cursor(int line, int index) {
			if (find_char(line, index) == NULL && find_char(line, index - 1) == NULL) return;
			cursor.line = line;
			cursor.index = index;
		}
		void get_input(const char question[]) {
			int text_max_length = 4;
			char* text = (char*)malloc(text_max_length * sizeof(char));
			printf("%s", question);
			//clean_buffer();
			while (getchar() != '\n');

			char cur_char = getchar();
			int i = 0;
			while (cur_char != '\n') {
				if (i == text_max_length) {
					text_max_length *= 2;
					text = resize(text, text_max_length);
				}
				text[i] = cur_char;
				cur_char = getchar();
				i++;
			}
			text[i] = '\0';
			//strcpy_s(user_input, text);
			user_input = text;
			//delete text;
			//text = NULL;
		}

		char* get_text() {
			if (chars_counter == 0) {
				char* text = (char*)malloc(sizeof(char));
				text[0] = '\0';
				return text;
			}
			//char* text = (char*)malloc((chars_counter + 1) * sizeof(char)); // maybe chars_counter + 1 ?
			char* text = (char*)calloc(chars_counter + 1, sizeof(char)); // maybe chars_counter + 1 ?
			
			node cur_char = *p_first_chars[0];
			int i = 0;
			while (cur_char.value != NULL) {
				text[i] = cur_char.value;
				i++;
				if (cur_char.next != NULL)
					cur_char = *cur_char.next;
				else break;
			}
			text[i] = '\0';
			return text;
		}

		//void append(char* text) {
		void append(char* text = NULL) {
			//char* text = user_input;
			if (text == NULL) text = user_input;
			int len = strlen(text);
			if (len == 0) return;
			chars_counter += len;
			//int nodes_max_count = 4;
			//node* nodes = (node*)calloc(nodes_max_count, sizeof(node));
			node* nodes = (node*)calloc(len + 1, sizeof(node));
			if (last_char != NULL && last_char->value != NULL) {
				last_char->next = &nodes[0];
			}

			//int i = 0;
			node* cur_node_p;
			//while(text[i] !='\0'){
			for (int i = 0; i < len; i++) {
				/*if (i == nodes_max_count - 1) {
					nodes_max_count *= 2;
					nodes = resize(nodes, nodes_max_count);
					last_char->next = &nodes[i];
				}*/
				cur_node_p = &nodes[i];
				cur_node_p->value = text[i];

				node* node_next_p = &nodes[i + 1];
				//cur_node_p->next = (i != len - 1) ? node_next_p : NULL;
				cur_node_p->next = node_next_p;
				//if (p_first_chars[line_counter] == NULL || p_first_chars[line_counter]->value == NULL)
				if (p_first_chars[line_counter] == NULL)
					p_first_chars[line_counter] = cur_node_p;

				last_char = cur_node_p;
				//i++;
			}
			//last_char->next->value = NULL;
			last_char->next = NULL;
		}

		void add_to_stack() {
			char* text = get_text();
			before.push(text);

			while (after.size() != 0) {
				char* t = after.top();
				delete t;
				after.pop();
			}		
		}

		void new_line() {
			append((char*)"\n");
			line_counter++;
			if (line_counter >= arraysize)
				p_first_chars = resize();
			p_first_chars[line_counter] = NULL;

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

		//node* insert(node* nd) {
		//node* insert() {
		//void insert() {
		//	int len = strlen(user_input);
		//	chars_counter += len;
		//	node* nodes = (node*)calloc(len + 1, sizeof(node));
		//	node* last_node = find_char(cursor.line, cursor.index - 1);
		//	node* node_after_insert = last_node->next;
		//	last_node->next = &nodes[0];
		// 
		//	for (int i = 0; i < len; i++) {
		//		node* cur_node_p;
		//		cur_node_p = &nodes[i];
		//		cur_node_p->value = user_input[i];
		// 
		//		node* node_next_p = &nodes[i + 1];
		//		cur_node_p->next = (i != len - 1) ? node_next_p : NULL;
		// 
		//		last_node = cur_node_p;
		//	}
		//	last_node->next = node_after_insert;
		//	//return nd;
		//}
		void insert(char* text = NULL) { // ÇÀÃÀËÜÍÀ
			if (text == NULL) text = user_input;
			int len = strlen(text);
			chars_counter += len;
			node* nodes = (node*)calloc(len + 1, sizeof(node));
			node* last_node;
			node* node_before_insert;
			node* node_after_insert;
			if (cursor.index == 0) {
				last_node = p_first_chars[cursor.line];
				node_after_insert = p_first_chars[cursor.line];
				p_first_chars[cursor.line] = &nodes[0];
			}
			else {
				last_node = find_char(cursor.line, cursor.index - 1);
				if (last_node == NULL) return;
				node_after_insert = last_node->next;
				last_node->next = &nodes[0];
			}

			for (int i = 0; i < len; i++) {
				node* cur_node_p;
				cur_node_p = &nodes[i];
				cur_node_p->value = text[i];

				node* node_next_p = &nodes[i + 1];
				cur_node_p->next = (i != len - 1) ? node_next_p : NULL;

				last_node = cur_node_p;
			}
			last_node->next = node_after_insert;
			//return nd;
		}

		//void insert(int num_line) {
		//	int len = strlen(user_input);
		//	chars_counter += len;
		//	node* nodes = (node*)calloc(len + 1, sizeof(node));
		//	node* last_node = p_first_chars[num_line];
		//	node* node_after_insert = p_first_chars[num_line];
		//	p_first_chars[num_line] = &nodes[0];
		// 
		//	for (int i = 0; i < len; i++) {
		//		node* cur_node_p;
		//		cur_node_p = &nodes[i];
		//		cur_node_p->value = user_input[i];
		// 
		//		node* node_next_p = &nodes[i + 1];
		//		cur_node_p->next = (i != len - 1) ? node_next_p : NULL;
		// 
		//		last_node = cur_node_p;
		//	}
		//	last_node->next = node_after_insert;
		//}

		void replace() {
			int num_of_symb = strlen(user_input);
			delete_(num_of_symb);
			insert();
			/*if (num_line == 0) {
				delete_(num_line, num_of_symb);
				insert(num_line);
			}
			else {
				node* nd_before = find_char(num_line, num_char - 1);
				delete_(nd_before, num_of_symb);
				insert(nd_before);
			}*/
		}

		//void delete_(node* node_before, int num_of_symb) {
		//	node* cur_node_p = node_before->next;
		//	for (int i = 0; i < num_of_symb; i++) {
		//		if (cur_node_p == NULL) break;
		//		cur_node_p = cur_node_p->next;
		//		chars_counter--;
		//	}
		//	node_before->next = cur_node_p;
		//	//return node_before;
		//}
		void delete_(int num_of_symb) { // ÇÀÃÀËÜÍÀ
			node* node_before_del = find_char(cursor.line, cursor.index - 1);
			node* cur_node_p = (cursor.index == 0) ? p_first_chars[cursor.line] : node_before_del->next;
			for (int i = 0; i < num_of_symb; i++) {
				if (cur_node_p == NULL) break;
				cur_node_p = cur_node_p->next;
				chars_counter--;
			}
			if(cursor.index == 0) p_first_chars[cursor.line] = cur_node_p;
			else node_before_del->next = cur_node_p;
			//return p_first_chars[num_line];
		}
		//void delete_(int num_line, int num_of_symb) {
		//	if (num_line > line_counter) {
		//		printf("Error, this line does not exist yet. ");
		//		return;
		//	}
		//	node* cur_node_p = p_first_chars[num_line];
		// 
		//	for (int i = 0; i < num_of_symb; i++) {
		//		if (cur_node_p == NULL) break;
		//		cur_node_p = cur_node_p->next;
		//		chars_counter--;
		//	}
		//	p_first_chars[num_line] = cur_node_p;
		//	//return p_first_chars[num_line];
		//}

		void delete_all() {
			delete p_first_chars;
			p_first_chars = (node**)calloc(arraysize, sizeof(node));
			/*for (int i = 0; i < arraysize; i++) {
				p_first_chars[i] = NULL;
			}*/
			last_char = p_first_chars[0];
			set_cursor(0, 0);
		}

		//tuple<node*, int> copy(node* first_node, int num_of_symb) {
		//tuple<node*, int> copy(int line_num, int char_num, int num_of_symb) {
		tuple<node*, int> copy(int num_of_symb) {
			//char text[100];
			//int text_max_length = 4;
			node* cur_node_p = find_char(cursor.line, cursor.index);
			if (cur_node_p == NULL) {
				cur_node_p = NULL;
				return make_tuple(cur_node_p, 0);
			}
			char* text = (char*)malloc((num_of_symb + 1) * sizeof(char));
			//node* cur_node_p = first_node;
			text[num_of_symb] = '\0';
			int i;
			for (i = 0; i < num_of_symb; i++) {
				if (cur_node_p == NULL) {
					text[i] = '\0';
					break;
				}
				text[i] = cur_node_p->value;
				cur_node_p = cur_node_p->next;
			}
			//strcpy_s(copied_text, text);			
			copied_text = text;	
			//return cur_node_p;
			return make_tuple(cur_node_p, i);
		}

		//void cut(node* node_before, int num_of_symb) {
		//void cut(int line_num, int char_num, int num_of_symb) {
		void cut(int num_of_symb) {
			node* last_node;
			//tie(last_node, num_of_symb) = copy(node_before->next, num_of_symb);
			//tie(last_node, num_of_symb) = copy(line_num, char_num, num_of_symb);
			tie(last_node, num_of_symb) = copy(num_of_symb);
			if (last_node == NULL) return;
			if(cursor.index == 0)
				p_first_chars[cursor.line] = last_node;
			else {
				node* node_before = find_char(cursor.line, cursor.index - 1);
				node_before->next = last_node;
			}
			chars_counter -= num_of_symb;
			//return node_before;
		}

		//node* cut(int num_line, int num_of_symb) {
		//	if (num_line > line_counter) {
		//		printf("Error, this line does not exist yet. ");
		//		return NULL;
		//	}
		//	char text[100];
		//	node* cur_node_p = p_first_chars[num_line];
		//	text[num_of_symb] = '\0';
		//	for (int i = 0; i < num_of_symb; i++) {
		//		if (cur_node_p == NULL) {
		//			text[i] = '\0';
		//			break;
		//		}
		//		text[i] = cur_node_p->value;
		//		cur_node_p = cur_node_p->next;
		//		chars_counter--;
		//	}
		//	strcpy_s(copied_text, text);
		//	p_first_chars[num_line] = cur_node_p;
		//	return p_first_chars[num_line];
		//}

		void paste() {			
			//user_input = copied_text;
			insert(copied_text);
			/*if(num_line != 0)
				insert(find_char(num_line, num_char));
			else 
				insert(num_line);*/
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
					if (cur_line_num > line_counter) return; // add
					cur_char_num = 0;
					if (cur_char.next != NULL) cur_char = *cur_char.next;
					continue;
				}
				if (cur_char.value == user_input[i]) {
					if (i == 0) {
						coord.index = cur_char_num;
						coord.line = cur_line_num;
					}
					i++;
				}
				else if (cur_char.value == user_input[0])
					i = 1;
				else i = 0;

				if (i == len_) {
					if (el_counter + 1 > coord_arr_size) {
						coord_arr_size *= 2;
						//coord_arr = resize_coordinates(coord_arr, coord_arr_size);
						coord_arr = resize(coord_arr, coord_arr_size);
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
				//delete coord_arr;
				//coord_arr = NULL;
			}
			printf("\nText is present in positions (%d results): \n\n", el_counter);
			printf("\tline\tchar\n");
			for (int j = 0; j < el_counter; j++) {
				printf("\t%d\t%d\n", coord_arr[j].line, coord_arr[j].index);
			}
			delete coord_arr;
			coord_arr = NULL;
		}

		void print_text() {
			if (p_first_chars[0] == NULL) {
				printf("No text has been added yet.");
				return;
			}
			printf("Your text:\n\n");
			node* cur_char = p_first_chars[0];
			while (cur_char != NULL) {
				printf("%c", cur_char->value);
				//if (cur_char->next != NULL)
				cur_char = cur_char->next;
				//else break;
			}
		}

		void load_from_file() {
			FILE* fptr;
			char* fname;
			//strcpy_s(fname, user_input);
			fname = user_input;
			if (fopen_s(&fptr, fname, "r") != 0) {
				printf("Error: can not open file %s\n", fname);
				return;
			}
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

		void save_to_file() {
			FILE* fptr;
			char* fname;
			fname = user_input;
			if (fopen_s(&fptr, fname, "w") != 0) {
				printf("Error: can not open file %s\n", fname);
				return;
			}
			node cur_char = *p_first_chars[0];
			while (cur_char.value != NULL) {
				fprintf(fptr, "%c", cur_char.value);
				if (cur_char.next != NULL)
					cur_char = *cur_char.next;
				else break;
			}
			printf("\n");
			printf("Text has been saved successfully!\n");
			fclose(fptr);
			fptr = NULL;
		}

		void undo() {
			if (before.size() == 1) return;

			char* text = before.top();
			before.pop();
			after.push(text);
			text = before.top();
			delete_all();
			append(text);
		}

		void redo() {
			if (after.empty()) return;

			char* text = after.top();
			after.pop();
			before.push(text);

			delete_all();
			append(text);
		}

		void clean_buffer() {
			while (getchar() != '\n');
			getchar();

		}
				
	private:
		void free_stacks() {
			while (!before.empty()) {
				char* t = before.top();
				before.pop();
			}
			while (!after.empty()) {
				char* t = after.top();
				after.pop();
			}
		}
		node** resize() {
			arraysize *= 2;
			node** ptr2 = (node**)realloc(p_first_chars, arraysize * sizeof(node));
			return ptr2;
		}

		//char* resize(char* ptr, int new_size) {
		//	arraysize *= 2;
		//	char* ptr2 = (char*)realloc(ptr, new_size * sizeof(char));
		//	return ptr2;
		//}
		template <typename T>
		T* resize(T* ptr, int new_size) {
			//arraysize *= 2;
			T* ptr2 = (T*)realloc(ptr, new_size * sizeof(T));
			return ptr2;
		}
		//coordinates* resize_coordinates(coordinates* ptr, int new_size) {
		//	coordinates* ptr2 = (coordinates*)realloc(ptr, new_size * sizeof(coordinates));
		//	return ptr2;
		//}
		
};

int main() {
	printf("Hello User!\n");
	int command;
	TextEditor text_editor;

	while (1) {
		printf("Choose the command (press '0' for help) : ");
		int res = scanf_s("%d", &command);

		if (res != 1) {
			printf("\nError! Command must be an integer.\n");
			goto Clear_system;
		}
		printf("\n");

		switch (command) {
			case 0: // Help 
			{
				printf(
					" 1 - Append text to the end\n" // done 
					" 2 - Start new line\n" // done 
					" 3 - Save to file\n" // done
					" 4 - Load from file\n" // done
					" 5 - Print current text\n" // done
					" 6 - Insert\n" // done
					" 7 - Search\n" // done
					" 8 - Delete\n" // done
					" 9 - Undo\n" // done
					"10 - Redo\n" // done
					"11 - Cut\n" // done
					"12 - Paste\n" // done
					"13 - Copy\n" // done
					"14 - Replace\n" // done
					"14 - Set cursor\n" 
					"-1 - Exit\n" 
				);
				break;
			}
			case 1: // Append text symbols to the end 
			{
				text_editor.get_input("Write text to append:\n\n");
				//text_editor.append(text_editor.user_input);
				text_editor.append();
				printf("\n");
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
				text_editor.get_input("Enter the file name for saving: ");
				//FILE * fptr;
				//fopen_s(&fptr, "C:\\Dev\\KSE\\1 year\\Principles and Paradigms\\Assignments\\Simple Text Editor\\TextEditorResult.txt", "w");
				//text_editor.save_to_file(fptr);
				text_editor.save_to_file();
				//fclose(fptr);
				//free(fptr);
				//fptr = NULL;

				//printf("Text has been saved successfully!\n");
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
				//int line_num;
				//int char_num;
				//printf("Insert\nChoose line and index: ");
				//scanf_s("%d %d", &line_num, &char_num);
				//printf("\n");

				//node* node_where_insert = text_editor.find_char(line_num, char_num);
				//if (node_where_insert == NULL) break;

				text_editor.get_input("Enter text to insert:\n\n");
				text_editor.insert();

				//if (char_num == 0)
				//	text_editor.insert(line_num);
				//else 
				//	text_editor.insert(node_where_insert);
				
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
				//int line_num;
				//int char_num;
				//int num_of_symb;
				//printf("Delete\nChoose line, index and number of symbols: ");
				//scanf_s("%d %d %d", &line_num, &char_num, &num_of_symb);
				//printf("\n");
				int num_of_symb;
				printf("Delete\nInput number of symbols: ");
				//scanf_s("%d", &num_of_symb);
				cin >> num_of_symb;
				printf("\n");
				text_editor.delete_(num_of_symb);
								
				//if (char_num != 0) {
				//	node* node_before_del = text_editor.find_char(line_num, char_num - 1);
				//	if (node_before_del == NULL) break;
				//	text_editor.delete_(node_before_del, num_of_symb);
				//}
				//else text_editor.delete_(char_num, num_of_symb);

				break;
			}
			case 9: // Undo
			{
				text_editor.undo();
				printf("Done!\n");
				break;
			}
			case 10: // Redo
			{
				text_editor.redo();
				printf("Done!\n");				
				break;
			}
			case 11: // Cut
			{
				//int line_num;
				//int char_num;
				//int num_of_symb;
				//printf("Cut\nChoose line, index and number of symbols: ");
				//scanf_s("%d %d %d", &line_num, &char_num, &num_of_symb);
				//printf("\n");
				int num_of_symb;
				printf("Cut\nInput number of symbols: ");
				//scanf_s("%d", &num_of_symb);
				cin >> num_of_symb;
				printf("\n");
				text_editor.cut(num_of_symb);

				//if (char_num != 0) {
				//	node* node_before_cut = text_editor.find_char(line_num, char_num - 1);
				//	if (node_before_cut == NULL) break;
				//	text_editor.cut(node_before_cut, num_of_symb);
				//}
				//else text_editor.cut(char_num, num_of_symb);

				break;
			}
			case 12: // Paste
			{
				//int line_num;
				//int char_num;
				//printf("Paste\nChoose line and index: ");
				//scanf_s("%d %d", &line_num, &char_num);
				//printf("\n");

				//text_editor.paste(line_num, char_num);
				text_editor.paste();
				printf("Text is pasted successfully!\n");

				break;
			}
			case 13: // Copy 
			{
				//int line_num;
				//int char_num;
				//int num_of_symb;
				//printf("Copy\nChoose line, index and number of symbols: ");
				//scanf_s("%d %d %d", &line_num, &char_num, &num_of_symb);
				//printf("\n");

				int num_of_symb;
				printf("Copy\nInput number of symbols: ");
				//scanf_s("%d", &num_of_symb);
				cin >> num_of_symb;
				printf("\n");
				text_editor.copy(num_of_symb);

				//node* node_to_copy = text_editor.find_char(line_num, char_num);
				//if (node_to_copy == NULL) break;

				//text_editor.copy(node_to_copy, num_of_symb);
				printf("Text is copied successfully!\n");
				
				break;
			}
			case 14: // Insert with replacement 
			{
				//int line_num;
				//int char_num;
				//printf("Replace\nChoose line and index: ");
				//scanf_s("%d %d", &line_num, &char_num);
				//printf("\n");

				//node* node_start_replacement = text_editor.find_char(line_num, char_num);
				//if (node_start_replacement == NULL) break;

				//text_editor.get_input("Enter text to replace (up to 100 characters):\n\n");
				//text_editor.replace(line_num, char_num);
				text_editor.get_input("Enter text to replace:\n\n");
				text_editor.replace();

				break;
			}
			case 15: // Set cursor
				int line_num;
				int char_num;
				printf("Set cursor\nChoose line and index: ");
				scanf_s("%d %d", &line_num, &char_num);
				printf("\n");
				text_editor.set_cursor(line_num, char_num);
				//printf("Done!\n");
				break;
			case -1:
				return 0;
			default:
				printf("Error! The command '%d' does not exist.\n", command);
				break;
		}
		if (command == 1 || command == 2 || command == 6 || command == 8 || command == 11 || command == 12 || command == 14)
			text_editor.add_to_stack();
		Clear_system:
		printf("\nPress enter to continue... ");
		text_editor.clean_buffer();
		system("cls");

	}
	
	
	return 0;
}