<h1>Functions</h1>

1- Deletes given word from given text. All functions are recursive, and done without using string.h library.  
- void clean_file(char* infile, char * outfile, char* words_to_delete[30], int number_of_words);  

2- A maze game for 2 players, first player who reaches the target wins. All methods are written recursively.  
- int maze_move(cell_type maze[][8], cell_type player, move_type move);  

3- Visualizes towers of hanoi solution for n pegs.  
- void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n);  