/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Burak Kocausta
** 
*/

#include <stdio.h>
#include "hw8_lib.h"


#define WORDSIZE 30

/* 
*	Function is a recursive function which reads one line at a time on input.txt and deletes wanted word from that line,
*	It prints edited line to output.txt file. 
*/ 
void delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words)
{	

	char line[1600];			/* Array of chars is declared to store line. */

	if(fgets(line,1500,infid) == NULL)		/* If line does not read or end of file is reached, return. */
		return;

	else{
		
		check_words(line,words_to_delete,number_of_words);	/* Editing line in a wanted way. */
		
		fprintf(outfid,"%s",line);							/* Printing the line to the output.txt.*/
		delete_words(infid,outfid,words_to_delete,number_of_words);	/* Call function again. */
	}
}/* End of Function. */
/* =================================================================================================== */

/* 	
*	Function opens two file which names are given from the user, and calls the recursive function for editing.
*/ 
void clean_file(char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
	FILE* infid;
	FILE* outfid;

	infid = fopen(infile,"r");				/* Opening input file. */

	if(infid == NULL){						/* If there is an error, return. */
		printf("ERROR! There is no file such %s.\n\n" ,infile);
		return;
	}

	outfid = fopen(outfile,"w");			/* Opening output file. */

	if(outfid == NULL){						/* If there is an error, return. */
		printf("An error is occured. EXITING...\n\n");
		return;
	}

	delete_words (infid, outfid, words_to_delete, number_of_words);		/* Call the recursive funtion. */
	
	fclose(infid);		/* Closing files. */															
	fclose(outfid);
}/* End of Function. */
/* =================================================================================================== */

	/* 
	*	Function is a recursive function which is maze game for 2 players.
	*   It takes move input from user and displays maze after each move.	
	*   If one of the player reaches the target, game ends.
	*   Function returns 0 if game is ended without nobody win.
	*/
int maze_move(cell_type maze[][8], cell_type player, move_type move)
{
	int i,j,ans,flag;					/* ans will be returned. flag is for checking if, move is valid or not.*/
	i = 0;		j = 0;		ans = 0;
	
	/* Displaying the maze. */
	printf("===========================================\n\n");
	printf("WALL -> =    PLAYER 1 -> 1     PLAYER 2 -> 2      TARGET -> T\n\n");
	print_8x8_maze(maze,8,8);		/* Function prints maze. */

	if(!scan_move(&move,&player)){	/* Taking the direction from user. */

		printf("\n\nGAME OVER! Player %d exitted.\n\n",player-2);
		ans = 0;					/* If user exits return 0; */
	}	

	else{

		find_current_loc(maze,player,&i,&j);	/* Function finds current location of given player. */
	
		switch(move){		/* Selecting the movement. */
			case move_left: 	flag = move_to_left(maze,i,j);
								break;
			case move_right:	flag = move_to_right(maze,i,j);
							 	break; 
			case move_up: 		flag = move_to_up(maze,i,j);
								break;
			case move_down:		flag = move_to_down(maze,i,j);
								break;
			default:			flag = 0;
							break;
		}/* End of Selecting. */
		if(flag == 0){			/* If given move is invalid or cannot be done print message and call function again. */	
			printf("\nINVALID MOVEMENT PLEASE ENTER A VALID DIRECTION!\n\n");
			ans = maze_move(maze,player,move);
		}

		else if(flag == 2){		/* If one of the player wins the game print message and return 1. */
			printf("\n\nGAME OVER! PLAYER %d HAS WON!\n\n",player-2);
			ans = 1;
		}

		else if(player == cell_p1)	/* Change the player in each calling. */
			ans = maze_move(maze,cell_p2,move);
	
		else if(player == cell_p2)	/* Change the player in each calling. */
			ans = maze_move(maze,cell_p1,move);

	}
	
	return ans;			/* Returns 1 if one of the player is won. */
}/* End Of Function. */
/* =================================================================================================== */

/* 
*	Function calls a recursive function which displays towers_of_hanoi 
*   with suggested moves. 
*/
void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n)
{
   int total_disk,startp[8],auxp[8],endp[8],i,step;
   
   if(n > 7 || n < 1)				/* Function works for at most 7, at least 1. */
   		printf("Please enter a number between 1-7!\n");
   
   else{

   		total_disk = n;				/* Assigning n to total disk variable. */
		step = 1;					/* Before counting the steps assign 1 to step. */
		for(i = 1; i <= n; i++)		/* Assigning disks to start peg at first. */
			startp[i-1] = i;

		for(i = 0; i < n; i++){		/* Assigning 0 to auxiliary peg and end peg. */
			auxp[i] = 0;
			endp[i] = 0;
		}
		display_disk(startp,endp,auxp,total_disk,step);	/* Display the first step. */


		visualized_hanoi(start_peg,end_peg,aux_peg,n,startp,auxp,endp,total_disk,&step); /* Display the other steps. */	
   }
}/* End Of Function. */
/* =================================================================================================== */

/* *************************** HELPER FUNCTIONS *************************** */

					/* HELPER FUNCTIONS FOR THE PART 1 --- DELETING WORDS */

/* 
*	Function  is recursive function which deletes words which are in de words array from line string. 
*/
void check_words(char line[],char *words[WORDSIZE],int num){

	int length;			/* length variable is for length of word. */
	length = 0;

	if(num <= 0)		/* If number of word is 0, then there is no word, so return. */
		return;
	
	else{
		length = wordlen(words[num-1]);				/* Calculating the length of word and assign it. */
		if(length > 1)
			search_word(words[num-1],line,length);	/* Searching the word in line and deleting it. */

		check_words(line,words,num-1);				/* Call the function for other words in words array. */
	}
}/* End Of Function. */
/* =================================================================================================== */

/* 
*	Function calculates the length of a given string.
*/	
int wordlen(char *str){

	if(str[0] == '\0')			/* Return 0 if end of the line is reached. */
		return 0;

	else
		return 1 + wordlen(&str[1]);	/* Counting the length of word. */
}/* End Of Function. */
/* =================================================================================================== */

/* 
*	Function is a recursive function which searches given word in a string finds and deletes it. 
*/ 		
void search_word(char *word, char line[],int length){
	char temp_str[30];	/* Creating a temp_str for assigning extracted a word from line. */

	if(line[0] == '\0')	/* If end of the line is reached, return. */
		return;

	else if(line[length] == ' ' || line[length] == '.' || line[length] == '\n'){									
		extract_word(line,length,temp_str);			/* Extract lines inital word in a given length */
		if(compare_words(temp_str,word) == 1){		/* If it is same with the wanted words, remove it. */

			remove_word(line,length);				/* Removes the word from line. */
			search_word(word,&line[1],length);		/* Call the function again. */
		}	
		else
			search_word(word,&line[1],length);		/* If word is not found, call function again. */
	}
	else
		search_word(word,&line[1],length);		/* If word is not found, call function again. */
		
}/* End Of Function. */
/* =================================================================================================== */
	
/* 
*	Function is a recursive function which extracts a word from a line's initial character for given length.
*	Ex: line --> extract_word, length --> 4  then output will be  -->  extr 
*/
char* extract_word(char *line,int length,char *word){
	
	char temp_str[30];	/* temp_str is used for temporary storage for charaters. */

	if(length <= 0)			/* If length is equal or below 0, assign null character. */ 
		word[0] = '\0';

	else					/* Concatinate word with characters for every returning process. */
		sprintf(word,"%c%s",line[0],extract_word(&line[1],length-1,temp_str));
	
	return word;			/* Return the extracted word. */
}/* End Of Function. */
/* =================================================================================================== */

/* 	
*	Function is a recursive funtion which compares 2 word.
*	If they are same returns 1. Otherwise returns 0.
*/
int compare_words(char *word1,char *word2){

	if(word1[0] == '\0')							/* If null character is reached, return 1. */
		return 1;

	else if(word1[0] == word2[0])					/* If characters are equal call function for others. */
		return compare_words(&word1[1], &word2[1]);

	else											/* If characters are not equal, return 0. */
		return 0;
}/* End Of Function. */
/* =================================================================================================== */

/* 
*	Function is a recursive function which removes chars from given line's initial with given length
*/		
void remove_word(char *line,int length){
											
	if(line[length] != '\0'){				/* If null char is not reached. Do the process. */

		line[0] = line[length+1];			/* Sliding the characters. */
		remove_word(&line[1],length);		/* Call function again. */
	}
}/* End Of Function. */
/* =================================================================================================== */


							/* HELPER FUNCTIONS FOR THE PART 2 --- MAZE GAME */
/*
*	Function scans the movement from user.
*	If player is invalid, scans it again.
*	If user wants to exit returns 0, otherwise returns 1
*/
int scan_move(move_type *move,cell_type *player){

	int temp;	/* temp is used for scanning. */
	int retval;

	if(*player != cell_p1 && *player != cell_p2){
		printf("\n\nWhich player is making the move :(PLAYER1 -> 1  PLAYER2 -> 2): ");
		scanf("%d" ,&temp);
		*player = temp + 2;
	}
	/* Asking the user for input. */
	printf("\n\n%d. player's move(0:left, 1:right, 2:up, 3:down, 4: exit) -> ",*player-2);
	scanf("%d", &temp);
	if(temp == 4) retval = 0;

	else{
		*move = temp;
		retval = 1;
	}

	return retval;
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function is a recursive funciton which finds current location of player and returns coordinates.
*/
int find_current_loc(cell_type maze[][8],cell_type player,int* i,int* j){
	int ans;

	if(*j >= 8){			/* Rows border is reached, than go to next row. */
		(*j) = 0; 
		(*i)++;
	}
		
	if((*i) >= 8)			/* If last row is reached return. */
		ans = 0;	

	else if(maze[*i][*j] == player)	/* If player's location is found return coordinates. */
		ans = 1;
	
	else{
		(*j)++;										/* Go to the next column */
		ans = find_current_loc(maze,player,i,j);	/* If player is not found, call function again */
	}
	
	return ans;			/* Returns 1 if it is found, otherwise 0. */
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function is a recursive function which displays maze which is 8x8.	
*/	
void print_8x8_maze(cell_type maze[][8], int row, int column){
	int i,j;

	i = 8 - row;			
	j = 8 - column;

	if(j > 7 && i > 7)	return;				/* If borders are reached return. */
		
	else if(j > 7){							/* If last column is reached,go to the next row's first column. */

		column = 8;
		row--;
		printf("\n");
		print_8x8_maze(maze,row,column);	/* Call function again. */
	}

	else{

		switch(maze[i][j]){		/* Selecting the value which will be printed. */

			case cell_p1:		printf(" 1");	break;
				
			case cell_p2:		printf(" 2");	break;
				
			case cell_wall:		printf(" =");	break;
				
			case cell_target: 	printf(" T");	break;
	
			case cell_free: 	printf("  ");	break;
		}
		column--;							/* Go to the next column. */
		print_8x8_maze(maze,row,column);	/* Call function again. */
	}
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function moves player to the left in the maze.
*	If target is reached, it returns 2.
*	If invalid movement is intented to be done, return 0.
*	If movement done with success, return 1.
*/
int move_to_left(cell_type maze[][8],int i,int j){
	int retval;		
	cell_type temp;		/* temp is used for swap operation. */

	if(j == 0)			/* If player is on the leftest side move cannot be done. */
		retval = 0;
	else{				

		switch(maze[i][j-1]){					/* Selecting the operation. */
			case cell_wall: 	retval = 0;
								break;
			case cell_target: 	retval = 2;
							  	break;
			case cell_free:		temp = maze[i][j];
								maze[i][j] = maze[i][j-1];
								maze[i][j-1] = temp;
								retval = 1;
								break;
			default: 			retval = 0;
								break;
		}
	}
	return retval;					/* return checked value */
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function moves player to the right in the maze.
*	If target is reached, it returns 2.
*	If invalid movement is intented to be done, return 0.
*	If movement done with success, return 1.
*/

int move_to_right(cell_type maze[][8],int i,int j){
	int retval;
	cell_type temp;			/* temp is used for swap operation. */

	if(j == 7)				/* If player is on the rightest side move cannot be done. */
		retval = 0;
	else{

		switch(maze[i][j+1]){					/* Selecting the operation. */
			case cell_wall: 	retval = 0;
								break;
			case cell_target: 	retval = 2;
							  	break;
			case cell_free:		temp = maze[i][j];
								maze[i][j] = maze[i][j+1];
								maze[i][j+1] = temp;
								retval = 1;
								break;
			default: 			retval = 0;
								break;
		}
	}
	return retval;				/* return checked value */
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function moves player to the above in the maze.
*	If target is reached, it returns 2.
*	If invalid movement is intented to be done, return 0.
*	If movement done with success, return 1.
*/
int move_to_up(cell_type maze[][8],int i,int j){
	int retval;
	cell_type temp;				/* temp is used for swap operation. */

	if(i == 0)					/* If player is on the top, move cannot be done. */
		retval = 0;
	else{

		switch(maze[i-1][j]){						/* Selecting the operation. */
			case cell_wall: 	retval = 0;
								break;
			case cell_target: 	retval = 2;
							  	break;
			case cell_free:		temp = maze[i][j];
								maze[i][j] = maze[i-1][j];
								maze[i-1][j] = temp;
								retval = 1;
								break;
			default: 			retval = 0;
								break;
		}
	}
	return retval;				/* return checked value */
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function moves player to the below in the maze.
*	If target is reached, it returns 2.
*	If invalid movement is intented to be done, return 0.
*	If movement done with success, return 1.
*/
int move_to_down(cell_type maze[][8],int i,int j){
	int retval;
	cell_type temp;				/* temp is used for swap operation. */

	if(i == 7)					/* If player is on the top, move cannot be done. */
		retval = 0;
	else{

		switch(maze[i+1][j]){						/* Selecting the operation. */
			case cell_wall: 	retval = 0;
								break;
			case cell_target: 	retval = 2;
							  	break;
			case cell_free:		temp = maze[i][j];
								maze[i][j] = maze[i+1][j];
								maze[i+1][j] = temp;
								retval = 1;
								break;
			default: 			retval = 0;
								break;
		}
	}
	return retval;				/* return checked value */
}/* End Of Function. */
/* =================================================================================================== */

					/* HELPER FUNCTIONS FOR THE PART 3 --- TOWERS OF HANOI */

/* 
*	Function is a recursive function which visualize towers of hanoi in a suggested algorithm. 
*/
void visualized_hanoi(char start_peg, char end_peg, char aux_peg, int n,int *startp,int *auxp,int *endp,int total_disk,int* step){
					  

	if(n == 1){
		(*step)++;															/* Incrementing step. */
    	insert_disk(startp,endp,auxp,n,start_peg,end_peg,total_disk);		/* Inserts disk start peg to end peg. */
    	display_disk(startp,endp,auxp,total_disk,*step);					/* Prints the step */
    }

    else{
    	/* Using end peg as an auxiliary peg. */
    	visualized_hanoi(start_peg,aux_peg,end_peg,n-1,startp,auxp,endp,total_disk,step); /* Call function again. */	

    	(*step)++;				  /* Incrementing the step before displaying operation. */	
    	insert_disk(startp,endp,auxp,n,start_peg,end_peg,total_disk);		/* Inserts disk start peg to end peg. */
    	display_disk(startp,endp,auxp,total_disk,*step);

    	/* Using start peg as an auxiliary peg. */
    	visualized_hanoi(aux_peg,end_peg,start_peg,n-1,startp,auxp,endp,total_disk,step);   	
    }
}/* End Of Function. */
/* =================================================================================================== */

/* 
*	Function inserts disks peg1 to peg2, according to the peg's name. 
*/
void insert_disk(int *startp,int *endp,int *auxp,int n,char peg1,char peg2,int total_disk){

	/* Pop and push functions are used for inserting, array is thought as a stack. */

	if((peg1 == 'S' || peg1 == '0' || peg1 == 's') && (peg2 == 'E' || peg2 == '2' || peg2 == 'e')){
		pop(startp,n);
		push(endp,n,total_disk);
	}
	else if((peg1 == 'S' || peg1 == '0' || peg1 == 's') && (peg2 == 'A' || peg2 == '1' || peg2 == 'a')){
		pop(startp,n);
		push(auxp,n,total_disk);
	}
	else if((peg2 == 'S' || peg2 == '0' || peg2 == 's') && (peg1 == 'A' || peg1 == '1' || peg1 == 'a')){
		pop(auxp,n);
		push(startp,n,total_disk);
	}
	else if((peg2 == 'S' || peg2 == '0' || peg2 == 's') && (peg1 == 'E' || peg1 == '2' || peg1 == 'e')){
		pop(endp,n);
		push(startp,n,total_disk);
	}
	else if((peg1 == 'E' || peg1 == '2' || peg1 == 'e') && (peg2 == 'A' || peg2 == '1' || peg2 == 'a')){
		pop(endp,n);
		push(auxp,n,total_disk);
	}
	else if((peg2 == 'E' || peg2 == '2' || peg2 == 'e') && (peg1 == 'A' || peg1 == '1' || peg1 == 'a')){
		pop(auxp,n);
		push(endp,n,total_disk);
	}
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function pulls a number in an array as a stack.
*	First index is thought as top of the stack.
*	Assigning 0 means pulling number.	
*	Using loops on part 3 is allowed so for loop is used.
*/
void pop(int *stack,int n){
	int i;

	for(i = 0; i < 8; i++){	
		if(stack[i] == n){		
			stack[i] = 0;		/* Assign 0 to that number. */
			break;				/* No need to look for others. */
		}
	}
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function pushes a number in an array as a stack.
*	First index is thought as top of the stack.
*	Assigning 0 means pulling number.	
*	Using loops on part 3 is allowed so for loop is used.
*/	
void push(int *stack,int n,int total_disk){
	int i;

	for(i = total_disk - 1; i >= 0; i--){
		if(stack[i] == 0){
			stack[i] = n;			/* Assign the num of that part. */
			break;					/* No need to look for others. */
		}
	}
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function displays disks on each peg properly.
*	Using loops on part 3 is allowed, so that for loop is used.
*/
void display_disk(int *startp,int *endp,int *auxp, int total_disk,int step){
	int i;
	display_head(total_disk,step);			/* Printing the head part first. */	

	for(i = 0; i < total_disk; i++){	/* Loop first prints stars above the number, than prints number with stars.*/
		
												/* Printing stars according to the disk size. */
		print_above_num(startp[i],total_disk);	
		print_above_num(auxp[i],total_disk);
		print_above_num(endp[i],total_disk);	
	
		printf("\n");							/* Go to the other line. */
		
		print_num_line(startp[i],total_disk);	/* Printing the disk part, which is consist of star and number. */
		print_num_line(auxp[i],total_disk);
		print_num_line(endp[i],total_disk);

		printf("\n");							/* Go to the other part. */
	}/* End Of Iteration. */	

	/* Printing the last line. */	
	print_above_num(startp[total_disk-1],total_disk);
	print_above_num(auxp[total_disk-1],total_disk);
	print_above_num(endp[total_disk-1],total_disk);

	printf("\n\n");	
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function displays head of the hanoi towers.
*/
void display_head(int total_disk,int step){
	
	int k;				/* k is unique number for printing properly. */		

	k = total_disk*2+3;	/* Calculating the unique number. */

	print_line(4*k+4,'=');		printf("\n");			/* Printing first line. */


	/* printing second and third line. */
	printf("=");	print_line(2*k-4,' ');		printf("STEP %-3d ",step);	print_line(2*k-3,' ');	printf("=\n");
		
	print_line(4*k+4,'=');		printf("\n\n");		
	
	/* Printing the name of pegs properly. */
	print_line(total_disk+1,' ');		printf("S");
	print_line(k+4,' ');				printf("A");
	print_line(k+4,' ');				printf("E\n\n\n");	

}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function prints stars which are at above at number.
*/	
void print_above_num(int num,int total_disk){

		if(num != 0){							/* Checking if it is 0. */
			print_line(total_disk - num,' ');	/* Print proper amount of spaces. */
			print_stars(num);					/* Print proper amount of stars. */
			print_line(total_disk - num,' ');	/* Print spaces again. */
			print_line(5,' '); 
		}
		
		else{	/* If it is 0 just print spaces properly. */
			print_line(total_disk*2+3,' ');
			print_line(5,' ');
		}
}/* End Of Function. */
/* =================================================================================================== */

/*
*	Function prints stars and numbers properly.
*/
void print_num_line(int num,int total_disk){
	if(num != 0){
		print_line(total_disk - num,' ');
		print_disk(num);
		print_line(total_disk - num,' ');
		print_line(5,' ');
	}
	else{
		print_line(total_disk*2+3,' ');
		print_line(5,' ');
	}
}/* End Of Function. */
/* =================================================================================================== */
void print_disk(int n){		/* Printing number line with stars. */
	int i;
	
	printf("*");
	for(i = 0; i < n; i++)	printf(" ");
		
	printf("%d",n);
	for(i = 0; i < n; i++)	printf(" ");
		
	printf("*");
}/* End Of Function. */
/* =================================================================================================== */
void print_stars(int n){	/* Printing stars unique amount of time. */
	int i;

	n = n * 2 + 3;
	for(i = 0; i < n; i++) printf("*");

}/* End Of Function. */
/* =================================================================================================== */
void print_line(int num,char ch){	/* Function prints given character, wanted time. */
	int i;

	for(i = 0; i < num;i++) printf("%c",ch);
}/* End Of Function. */