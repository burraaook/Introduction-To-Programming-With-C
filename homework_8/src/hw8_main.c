/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
** 
*/


#include <stdio.h>
#include "hw8_lib.h"


void test_clean_file () 
{
	char infile[] = "input.txt";		/* Assigning file names. */
	char outfile[] = "output.txt";		
										/* Sample words */	
	char *words_to_delete[30] = {"apple","orange","knock","words","knight"};

	/* number_of_word is total number of words in words_to_delete array. */
	
	int number_of_words = 5;			/* Please enter number of words properly. */

	clean_file(infile,outfile,words_to_delete,number_of_words);	/* Calling function.*/
}


void test_maze_move ()
{
	move_type move;			/* Declaration of enumerated type. */
	
	/* Creating a sample maze. */

	cell_type maze[8][8] =
	{
		{cell_wall,  cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall},
		{cell_wall,  cell_free,cell_p2,  cell_free,cell_wall,cell_free,cell_free,cell_wall},
		{cell_wall,  cell_free,cell_wall,cell_free,cell_wall,cell_free,cell_free,cell_wall},
		{cell_wall,  cell_free,cell_wall,cell_free,cell_wall,cell_free,cell_free,cell_wall},
		{cell_wall, cell_p1,   cell_wall,cell_free,cell_free,cell_wall,cell_free,cell_wall},
		{cell_wall,  cell_free,cell_wall,cell_wall,cell_free,cell_free,cell_free,cell_wall},
		{cell_wall,cell_free,cell_free,cell_free,cell_free,cell_wall,cell_target,cell_wall},
		{cell_wall,  cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall}
	};
	move = 0;
	/* 
	*	maze_move function is a recursive function which does all the job.
	*	(asking for direction, checking movements validity, performing movement etc..)
	*/
	maze_move(maze,cell_p1,move);	
}


void test_towers_of_hanoi ()
{
	char start_peg,end_peg,aux_peg;
	int n;

	/*	
	*	start_peg 	<--	   '0','S','s'
	*	end_peg 	<--	   '2','E','e'
	*	aux_peg 	<--	   '1','A','a'
	*/

	/* Assigning characters for representing each peg. */
	/* n is equal to number of disk. */
	start_peg = '0';	end_peg = '2';		aux_peg = '1';
	n = 5;
	towers_of_hanoi(start_peg, end_peg, aux_peg,n);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_clean_file ();
	test_maze_move ();
	test_towers_of_hanoi ();
	return (0);
} /* end main */
