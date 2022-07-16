#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 4 					/* N determines the 2D array's dimension.*/ /* N must be bigger than 0. */  

typedef enum{left,right,up,down,quit_game}towards;	/* Enumerating directions for user. */

void create_puzzle(int puzzle[][N]);				/* Functions are explained on their definitions. */
void print_puzzle(int puzzle[][N]);
int movement(towards direction, int loc_x, int loc_y, int puzzle[][N]);
bool is_it_solved(int puzzle[][N]);
/* Helper Functions */
void scan_direction(towards *direction,int *loc_x, int *loc_y);
void print_line(int num);
void find_blank(int *b_loc_x, int *b_loc_y, int puzzle[][N]);
void move_left(int blank_x,int blank_y,int loc_x,int loc_y,int puzzle[][N]);
void move_right(int blank_x,int blank_y,int loc_x,int loc_y,int puzzle[][N]);
void move_up(int blank_x,int blank_y,int loc_x,int loc_y,int puzzle[][N]);
void move_down(int blank_x,int blank_y,int loc_x,int loc_y,int puzzle[][N]);
void swap(int *num1, int *num2);
/* Helper Functions */

int main(){

	int puzzle[N][N];				/* Declaration of 2d array. */
	int loc_x,loc_y,flag;			/* loc_x and loc_y are the inputs which will be taken from user. */
	towards direction;				/* Flag is for checking the movement function's returning value. */

	create_puzzle(puzzle);			/* Function creates a proper puzzle with 2D array. */

	do{		/* Loop continues till user gives up or puzzle solved. */
		print_puzzle(puzzle);										/* Print puzzle in every iteration. */
		scan_direction(&direction,&loc_x,&loc_y);					/* Taking the inputs from user. */
		flag = movement(direction,loc_x, loc_y,puzzle);				/* Perform the desired movement. */

		/* If user wants to exit, end the loop.*/
		if(direction == quit_game){
		 printf("\n\nGame over! You exited. Quitting ...\n\n");
		 break;
		}

		/* If desired movement cannot be performed, inform the user.*/
		else if (flag == 0) printf("\n\n This move cannot be done ! \n\n");	

	}while(!is_it_solved(puzzle));

	if(is_it_solved(puzzle)){				/* Giving feedback and printing the puzzle's last version. */
		printf("\n\nPuzzle is solved. Congratulations!!\n ");
		print_puzzle(puzzle);
	}
	
	return 0;
}	/* End of main. */
/*---------------------------------------------------------------------------------------*/
void create_puzzle(int puzzle[][N]){	/* Function creates NxN puzzle. */

	int i,j,k,temp_index1,temp_index2;	/* temp indexes are used during generating random number. */

	k = N*N - 1;						/* N*N - 1 will be the maximum number assigning it to k.*/
	for(i = 0; i < N; i++){				/* Assigning all numbers in a decreasing order. */
		for(j = 0; j < N; j++){
			puzzle[i][j] = k;
			k--;
		}
	}

	k = 0;				/* k is used again but this time it is used for counting. */
	do{					/* loop is iterates till unsolved puzzle is generated. */

		for(i = 0; i < N; i++){		/* Nested loop for assigning numbers. */

			for(j = 0; j < N; j++){

				temp_index1 = rand() % N;			/* Generating a new indexes. */
				temp_index2 = rand() % N;
				swap(&puzzle[i][j],&puzzle[temp_index1][temp_index2]);	/* Swap them with current i,j values. */
			}	
		}
		k++;
	}while((is_it_solved(puzzle)) && k < 10);	/* k is a counter and it is used for preventing the infinite loop. */
}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
void print_puzzle(int puzzle[][N]){	/* Function prints the puzzle properly. */
	
	int i,j;						/* i and j used for counting. */				

	printf("-------------------------------------------\n\n");
	print_line(N);			/* Prints '*' proper times. */
	printf("\n");
	
	for(i = 0; i < N; i++){	/* Loop prints numbers in a table properly. */
		
		printf("* ");
		for(j = 0; j < N; j++){

			if(puzzle[i][j] != 0) printf(" %-2d *",puzzle[i][j]);
			
			else printf("    *");						
		}
		printf("\n");
		print_line(N);
		printf("\n");
	}
	printf("\n\n\n");
}/* End of Function.*/
/*---------------------------------------------------------------------------------------*/
void print_line(int num){	/* Function is created for printing stars at above and below properly. */
	int i;

	for(i = 0; i < 5*num+2; i++){		/* Number of stars are always must be equal to 5*num + 2. */
		printf("*");
	}
}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
void scan_direction(towards *direction,int *loc_x, int *loc_y){

	/* Taking the inputs from user and returning them. */
	int temp;

	printf("Please enter the location:(start count from 0)\nRow: ");
	scanf("%d", loc_y);
	printf("Column: ");
	scanf("%d", loc_x);

	printf("Please enter the direction you want to move\n(left --> 0, right --> 1, up --> 2, down --> 3, exit --> 4): >>> ");
	scanf("%d", &temp);
	*direction = temp;	
}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
int movement(towards direction, int loc_x, int loc_y,int puzzle[][N]){	/* Function performs the desired movement by the user. */
																		/* If desired movement cannot be performed than returns
																		a proper value. */
	int flag,b_loc_x,b_loc_y;		/* flag will be returned value. */
									/* b_loc_x and b_loc_y are blank's locations.*/

	find_blank(&b_loc_x,&b_loc_y, puzzle);	/* Finding the blank's location. */
											/* Blank's location is used for sliding and checking preconditions. */
	flag = 1;								/* 1 is assigned to flag. */

	/* Preconditions before selecting the route. */
	if(loc_x > N-1 || loc_x < 0) flag = 0;	
	else if(loc_y > N-1 || loc_y < 0) flag = 0;

	else{

		switch(direction){		/* Selecting according to the direction input. */

			case right:
				/* Preconditions for moving right before performing the movement.*/
				if(b_loc_y != loc_y) flag = 0; 		/* blank must be on the same row with chosen number. */
				else if(loc_x >= b_loc_x) flag = 0;	/* blank must be on the right side of chosen number.*/

				else move_right(b_loc_x, b_loc_y, loc_x, loc_y, puzzle);	/* Sliding to the right. */	

				break;

			case left:
				/* Preconditions for moving left before performing the movement.*/
				if(b_loc_y != loc_y) flag = 0;		/* blank must be on the same row with chosen number. */
				else if(loc_x <= b_loc_x) flag = 0;	/* blank must be on the left side of chosen number.*/

				else move_left(b_loc_x, b_loc_y, loc_x, loc_y, puzzle);		/* Sliding to the left. */

				break;

			case down:
				/* Preconditions for moving down before performing the movement.*/
				if(b_loc_x != loc_x) flag = 0;		/* blank must be on the same column with chosen number. */
				else if(loc_y >= b_loc_y) flag = 0;	/* blank must be on the below of chosen number.*/

				else move_down(b_loc_x, b_loc_y, loc_x, loc_y, puzzle);		/* Sliding to the down. */

				break;

			case up:
				/* Preconditions for moving down before performing the movement.*/
				if(b_loc_x != loc_x) flag = 0;		/* blank must be on the same column with chosen number. */
				else if(loc_y <= b_loc_y) flag = 0;	/* blank must be on the above of chosen number.*/

				else move_up(b_loc_x, b_loc_y, loc_x, loc_y, puzzle);		/* Sliding to the up. */

				break;

			case quit_game:
				break;

			default:
				printf("\n\nInvalid Direction!!\n\n");
				break;
		}/* End of switch. */
	}
	
	return flag;		/* Returns 1 if movement performed, 0 if movement can not be performed. */
}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
void find_blank(int *b_loc_x,int *b_loc_y,int puzzle[][N]){		/* Function finds blank's location(on x and y axis)
																and returns it.*/
																
	int i,j,flag;		/* i and j is used for counting. Flag is used for breaking loop when blank is found. */

	flag = 1;

	for(i = 0; i < N && flag == 1; i++){		/* Loop iterates till blank is found. */
		for(j = 0; j < N; j++){

			if(puzzle[i][j] == 0){		/* If blank(zero) is found then return locations and exit from the loop. */
				*b_loc_y = i;
				*b_loc_x = j;			
				flag = 0;
				break;
			}
		}
	}
}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
void move_right(int blank_x,int blank_y,int loc_x,int loc_y,int puzzle[][N]){	/* Function slides number to right. */
				
	int i,j;

	swap(&puzzle[blank_y][blank_x], &puzzle[loc_y][loc_x]);		/* Swapping blank and chosen number. */

	/* This loop puts chosen number to the leftest side before blank.*/
	for(i = 1,j = 0; i < blank_x - loc_x; i++,j++)
		swap(&puzzle[blank_y][blank_x - i], &puzzle[blank_y][blank_x-j]);		

}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
void move_left(int blank_x,int blank_y,int loc_x,int loc_y,int puzzle[][N]){	/* Function slides number to left. */
				
	int i,j;

	swap(&puzzle[blank_y][blank_x],&puzzle[loc_y][loc_x]);		/* Swapping blank and chosen number. */

	/* This loop puts chosen number to the rightest side before blank.*/
	for(i = 1, j = 0; i < loc_x - blank_x; i++, j++)
		swap(&puzzle[blank_y][blank_x + i], &puzzle[blank_y][blank_x+j]);

}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
void move_down(int blank_x,int blank_y,int loc_x,int loc_y,int puzzle[][N]){	/* Function slides number to down. */

	int i,j;

	swap(&puzzle[blank_y][blank_x], &puzzle[loc_y][loc_x]);		/* Swapping blank and chosen number. */

	/* This loop puts chosen number to the top before blank.*/
	for(i = 1, j = 0; i < blank_y - loc_y; i++, j++)
		swap(&puzzle[blank_y-i][blank_x], &puzzle[blank_y - j][blank_x]);
	
}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
void move_up(int blank_x,int blank_y,int loc_x,int loc_y,int puzzle[][N]){

	int i,j;	

	swap(&puzzle[blank_y][blank_x], &puzzle[loc_y][loc_x]);		/* Swapping blank and chosen number. */

	/* This loop puts chosen number to the bottom before blank.*/
	for(i = 1, j = 0; i < loc_y - blank_y; i++, j++)
		swap(&puzzle[blank_y + i][blank_x], &puzzle[blank_y + j][blank_x]);

}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
bool is_it_solved(int puzzle[][N]){	/* Function checks if the puzzle is solved or not. */

	int i,j,k;							/* k is used for checking numbers. */
	bool flag;							/* flag will be returned as a boolean value. */

	flag = true;
	k = 1;

	for(i = 0; i < N && flag == true; i++){
		for(j = 0; j < N; j++){
			
			if((i != N-1) || (j != N-1)){			/* No need to check (N-1)x(N-1) location. It must be blank. */ 

				if(puzzle[i][j] != k){
					
					flag = false;					
					break;
				}			
			}

			k++;									/* Increment k. */
		}	
	}
	return flag;						/* returning the result. */
}/* End of Function. */
/*---------------------------------------------------------------------------------------*/
void swap(int *num1, int *num2){		/* Function swaps two variables values. */
	int temp;

	temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}/* End of Function. */