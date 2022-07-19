/*
** hw8_lib.h:
**
** The header file declaring library functions.
**
** Author: Burak Kocausta
** 
*/

typedef enum {cell_wall,cell_free,cell_target,cell_p1,cell_p2}cell_type;

typedef enum {move_left,move_right,move_up,move_down}move_type;

void clean_file(char* infile, char * outfile, char* words_to_delete[30], int number_of_words);


int maze_move(cell_type maze[][8], cell_type player, move_type move);


void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n);


#define WORDSIZE 30

				/* HELPER FUNCTIONS FOR FIRST PART */				/* Helper functions are explained on their definiton. */

void check_words(char line[],char *words[WORDSIZE],int num);
int wordlen(char *str);
void search_word(char *word, char line[],int length);
char* extract_word(char *line,int length,char *word);
int compare_words(char *word1,char *word2);
void remove_word(char *line,int length);
/* ==================================== */

				/* HELPER FUNCTIONS FOR SECOND PART */

int scan_move(move_type *move,cell_type *player);
int find_current_loc(cell_type maze[][8], cell_type player, int* i, int* j);
void print_8x8_maze(cell_type maze[][8], int row, int column);
int move_to_left(cell_type maze[][8], int i,int j);
int move_to_right(cell_type maze[][8], int i, int j);
int move_to_up(cell_type maze[][8], int i, int j);
int move_to_down(cell_type maze[][8], int i, int j);
/* ==================================== */

				/* HELPER FUNCTIONS FOR THIRD PART */

void insert_disk(int *startp,int *endp,int *auxp,int n,char peg1,char peg2,int total_disk);
void display_disk(int *startp,int *endp,int *auxp,int total_disk,int step);
void display_head(int total_disk,int step);
void print_above_num(int num,int total_disk);
void visualized_hanoi(char start_peg, char end_peg, char aux_peg, int n,int *startp,int *auxp,int *endp,int total_disk,int* step);				  
void pop(int *stack,int n);
void push(int *stack,int n,int total_disk);
void print_disk(int n);
void print_stars(int n);
void print_line(int num,char ch);
void print_num_line(int num,int total_disk);
/* ==================================== */
