/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Burak Kocausta
** 
*/

#include <stdio.h>
#include "hw5_lib.h"
#include <math.h>

/*-------------------------------------------- PART I --------------------------------------------*/
void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
	/* Selecting the operation according to entered op. */
	if(op == '+'){ /* 4 coefficient is needed for result in addition. a3,a2,a1,a0 is used for storing the results. */
		*a3 += *b3;		 *a2 += *b2;	 *a1 += *b1;	 *a0 += *b0;
	}
	else if(op == '-'){/* 4 coefficient is needed for result in substraction. a3,a2,a1,a0 is used for storing the results. */
		*a3 -= *b3;		*a2 -= *b2;		 *a1 -= *b1;	 *a0 -= *b0;
	}
	else if(op == '*'){ /* 7 coefficient is needed for returning result for multiplication. Coefficients used except for b0. */
		multiply_polynomials(a3,a2,a1,a0,b3,b2,b1,*b0);
	}
	else if(op == 'x'){ /* In case if user enters x for multiplying process. */
		multiply_polynomials(a3,a2,a1,a0,b3,b2,b1,*b0);
	}
}/* End of function. */
/*----------------------------------------------------------------------------------------*/

/*-------------------------------------------- PART II --------------------------------------------*/
void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	int i;			/* i will be used in while loop for counting. */
	double d0, d1, d2, d3, euclidian_distance,n0,n1,n2,n3;	/* n is used for user inputs.*/
															/* d is used to represent difference and also used for
															holding the entered input before calculation. */

	*mean_a0=0; *mean_a1=0; *mean_a2=0; *mean_a3=0;			/* 0 should be assigned before process. */

	i = 1;

	scan_4d_vectors(&n0, &n1, &n2, &n3);					/* Taking the vector inputs in a proper way. */

	if(n0 != -1 || n1 != -1 || n2 != -1 || n3 != -1){		/* If user enters -1 -1 -1 -1 process must end. */

		/* Add components which is in same dimension, and assign result to mean variables. */
		*mean_a0 += n0;		*mean_a1 += n1;		*mean_a2 += n2;		*mean_a3 += n3; 

		while(i < N){	/* If N vectors are inputted stop the iteration. */

			/* Holding the user inputs data for calculating difference. */
			d0 = n0;	d1 = n1;	d2 = n2;	d3 = n3;

			scan_4d_vectors(&n0, &n1, &n2, &n3);	/* Taking the vector inputs in a proper way. */
		
			if(n0 == -1 && n1 == -1 && n2 == -1 && n3 == -1) /* If user enters -1 -1 -1 -1 process must end. */
				break;
			
			else{
				/* Add components which is in same dimension, and assign result to mean variables. */
				*mean_a0 += n0;		*mean_a1 += n1;		*mean_a2 += n2;		*mean_a3 += n3; 

				/* Calculate the differences for calculation of euclidian distance between two consecutive vectors. */
				d0 = d0 - n0;	 d1 = d1 - n1;	 d2 = d2 - n2;	 d3 = d3 - n3;

				distance_between_4d_points(d0, d1, d2, d3, &euclidian_distance); /* Calculating the euclidian distance. */

				if(*longest_distance < euclidian_distance)	/* If calculated distance is the maximum, then store it. */
					*longest_distance = euclidian_distance;

				i++;			/* Increment the counter. */
			}
		}/* End of the iteration. */
	}
	/*Calculating the mean values. */
	*mean_a0 = *mean_a0/i;	*mean_a1 = *mean_a1/i;	*mean_a2 = *mean_a2/i;	*mean_a3 = *mean_a3/i;

}/* End of function. */
/*----------------------------------------------------------------------------------------*/
void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{/* Calculating the euclidian distance.*/

    *euclidian_distance = d0*d0 + d1*d1 + d2*d2 + d3*d3;
    *euclidian_distance = sqrt(*euclidian_distance);
}/* End of function. */
/*----------------------------------------------------------------------------------------*/

/*-------------------------------------------- PART III --------------------------------------------*/
void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
	int i,sa,sb,sc,sd,se;					/* sa,..,se is used for counting the total seats for each party. */
	int max;								
	int tempa, tempb, tempc, tempd, tempe;	/* temp variables is used for storing the party's first values. */

	sa = 0;		sb = 0;		sc = 0;		sd = 0;		se = 0; /* sa, ... ,se is seat numbers of each party. */

	scan_5_votes(partyA,partyB,partyC,partyD,partyE,&numberOfSeats);
	tempa = *partyA;	 tempb = *partyB;	 tempc = *partyC;	tempd = *partyD;	tempe = *partyE;
	
	for(i = 0; i < numberOfSeats; i++){ /* loop iterates till all seats are distributed. */

		max  = find_max(*partyA,*partyB,*partyC, *partyD, *partyE); /* Finding the maximum vote. */

		/* Finding the which party has maximum votes. */
		/* After finding max, calculate the next value of that party and give party a seat. */
		if(max == *partyA){
			*partyA = tempa / (sa + 2);
			(sa)++;
		}

		else if(max == *partyB){
			*partyB = tempb / (sb + 2); 
			(sb)++;
		}

		else if(max == *partyC){
			*partyC = tempc / (sc + 2);
			(sc)++;
		}

		else if(max == *partyD){
			*partyD = tempd / (sd + 2);
			(sd)++;
		}

		else{
			*partyE = tempe / (se + 2);
			(se)++;
		}	
	} /* End of the iteration. */

	/* Seat numbers are returned.*/
	*partyA = sa;
	*partyB = sb;
	*partyC = sc;
	*partyD = sd;
	*partyE = se;
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
/*-------------------------------------------- PART III --------------------------------------------*/
void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{	
	/* Taking the components from the user properly, and preventing possible errors.*/
	printf("Please enter three 2d point's each component one by one.\n");
	scan_double_num(x1,1,1);		scan_double_num(y1,2,1);	discard();
	scan_double_num(x2,3,2);		scan_double_num(y2,4,2);	discard();
	scan_double_num(x3,5,3);		scan_double_num(y3,6,3);	discard();

	/* After 3 ordering process, they will be ordered properly. */
	order_2_point(x1,y1,x2,y2);
	order_2_point(x1,y1,x3,y3);	
	order_2_point(x2,y2,x3,y3);
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
/*-------------------------------------------- PART IV --------------------------------------------*/
void number_encrypt (unsigned char* number)
{
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';

	scan_uchar(number);

	/* Determining the components according to the given number. */
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);

	/* Determine a new number according to the components. */
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);

}/* End of function. */


void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	/* Getting components according to the number .*/
	assign_bits(b0, &number);
	assign_bits(b1, &number);
	assign_bits(b2, &number);
	assign_bits(b3, &number);
	assign_bits(b4, &number);
	assign_bits(b5, &number);
	assign_bits(b6, &number);
	assign_bits(b7, &number);
	/* Components are determined. */
}/* End of function. */


void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
	
	*number = 0;
	/* Constructing a new number with components. */
	*number += b0 * 128;
	*number += b1 * 64;
	*number += b6 * 32;
	*number += b7 * 16;
	*number += b4 * 8;
	*number += b5 * 4;
	*number += b2 * 2 + b3 * 1;
	/* New number is constructed and returned. */
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
/*------------------------------------------------HELPER FUNCTIONS------------------------------------------------*/
void scan_3polynomial(double *a3, double *a2, double *a1, double *a0){ /* Function takes a proper input for 3rd degree polynomial.*/

	int i,flag3,flag2,flag1,flag0;		/* Flags are used for checking if the user entered all 3 2 1 0 degree's coefficients.*/
	double degree;

		flag3 = 0;	 flag2 = 0;	 flag1 = 0;	 flag0 = 0;
	do{	/* If user enters wrong input ask the user for input till valid input is entered. */
		i = 0;

		while(i < 4){

			scan_coefficient(&degree);		/* Degree is taken from the user properly. */

			/* Taking the proper coefficient according to the degrees value.*/
			if(degree == 3){
		 		scan_coefficient(a3);
		 		flag3 = 1;
			}
			else if(degree == 2){
		 		scan_coefficient(a2);
		 		flag2 = 1;
			}
			else if(degree == 1){
				scan_coefficient(a1);
				flag1 = 1;
			}
			else if(degree == 0){
		 		scan_coefficient(a0);
		 		flag0 = 1;
			}
			i++;
		}

		/* Checking if the user entered proper input. */
		if(flag3 != 1 || flag2 != 1 || flag1 != 1 || flag0 != 1){
			
			discard();	/* Discard the unnecessary inputs. */
			/* Ask for input again. */
			printf("Degrees and coefficients are not properly inputted!\nPlease enter them in proper format: ");
		}

	}while(flag3 != 1 || flag2 != 1 || flag1 != 1 || flag0 != 1);

	discard();		/* Discard the unnecessary inputs. */
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
void scan_coefficient(double *a){ /* Function takes a coefficient input with characters. */
	char ch;	
	int status;		/* status is for checking the scanf's returned value. */

	status = 0;
	
	do{
		status = scanf("%lf", a);
		if(status == 0){ /* If status equals to 0, so input is stuck on the buffer.*/
			scanf("%c", &ch);	/* Taking the stucked char in buffer. */
		}

	}while(status != 1);	/* Do the iteration till status is equal to 1. */
}/* End of function. */
/*----------------------------------------------------------------------------------------*/		
void scan_operator(char *op){	/* Function takes a proper operator which are +,-,*,x */
	scanf("%c", op);

	while(*op != '+' && *op != '-' && *op != '*' && *op != 'x'){		

		if(*op != '\n'){
			discard();
			printf("Invalid operator is entered! Please enter a proper operator(+,-,*): ");
		}		
		scanf("%c", op);
	}
	discard();					/* Discard the unnecessary inputs. */
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
void discard(){					/* This loop discards unnecessary inputs. */	
	
	char ch;

	do{

		scanf("%c", &ch);
	}while(ch != '\n');
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
void multiply_polynomials (double* a3, double* a2, double* a1, double* a0, double* b3,
double* b2, double* b1, double b0){ /* This function multiplies 3rd degree polynoms */

	double c6,c5,c4,c3,c2,c1,c0; /* c6 is 6th degree c5 5th degree .... */
								 /* max degree will be 6 */
	/* calculating the coefficients */
	c6 = *a3 * *b3;												
	c5 = (*a3 * *b2) + (*b3 * *a2);										
	c4 = (*a3 * *b1) + (*b3 * *a1) + (*a2 * *b2);
	c3 = (*a2 * *b1) + (*a1 * *b2) + (*a3 * b0) + (*b3 * *a0);
	c2 = (*a1 * *b1) + (*a2 * b0) + (*b2 * *a0);
	c1 = (*a1 * b0) + (*b1 * *a0);
	c0 = (b0 * *a0);
	/* calculating the coefficients */

	/* Returning the new polynoms's coefficients. */
	*a3 = c6;	*a2 = c5;	*a1 = c4;	*a0 = c3;	*b3 = c2;	*b2 = c1;	*b1 = c0;   

}/* End of function */
/*----------------------------------------------------------------------------------------*/
void scan_4d_vectors(double* n0, double* n1, double* n2, double* n3){
/* Function takes a proper input during scanning 4d vector.*/
	int status;

	printf("Enter 4d Vector's components. Exit with -1 -1 -1 -1\n n0 n1 n2 n3: ");
	status = scanf("%lf %lf %lf %lf", n0, n1, n2, n3);
	while(status != 4){
		discard();
		printf("Invalid input entered! Please enter them properly.\nEnter 4d Vector's components: ");
		status = scanf("%lf %lf %lf %lf", n0, n1, n2, n3);
	}

	discard();
	printf("\n");
}/* End of function */
/*----------------------------------------------------------------------------------------*/
void scan_5_votes(int *a, int *b, int *c, int *d, int *e,int *seat){
	/* Function is asks user for total votes and number of seats for parties and returns them.*/
	printf("Please enter total votes for party A: ");		scan_positive_int(a);
	printf("Please enter total votes for party B: ");		scan_positive_int(b);
	printf("Please enter total votes for party C: ");		scan_positive_int(c);
	printf("Please enter total votes for party D: ");		scan_positive_int(d);
	printf("Please enter total votes for party E: ");		scan_positive_int(e);
	printf("Please enter total number of seats: ");			scan_positive_int(seat);
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
void scan_positive_int(int *num){	/* Function scans nonnegative integers.*/
	int status;

	status = scanf("%d", num);

	while(status != 1 || (*num < 0)){/* This loop asks user for new input till proper input is entered. */
		discard();
		printf("Invalid input entered! Please enter it properly: ");
		status = scanf("%d", num);
	}

	discard();
	printf("\n");
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
int find_max(int a, int b, int c, int d, int e){
	int max;
	max = 0;
										/* Finding the maximum value without using arrays. */
	if(a >= b)
		max = a;										

	else if(b > a)
		max = b;

	if(c >= max)
		max = c;

	if(d >= max)
		max = d;

	if(e >= max)
		max = e;

	return max;	
}/* End of function */
/*----------------------------------------------------------------------------------------*/
void scan_double_num(double *x, int i, int j){		/* Function scans a double number with wanted format.*/
	int status;										/* Second parameter(i) decides x component or y component is asked. */	
	char ch;										/* Third parameter(j) decides which x or which y is asked. */ 

	if(i % 2 == 1)			
		ch = 'x';
	else
		ch = 'y';

	printf("\n%c%d = ",ch,j);
	status = scanf("%lf", x);
	/* This loop asks user for input till input is entered properly. */
	while(status != 1){					/* Checking the scanf's returned value. */

		discard();
		printf("Invalid input! Please enter the proper input again\n %c%d = ",ch,j);	/* Warn and ask for input again. */
		status = scanf("%lf", x);
	}
}/* End of function */
/*----------------------------------------------------------------------------------------*/	
void order_2_point(double *x1,double *y1, double *x2, double *y2){	/* 2 point is ordered counter-clockwise with this function.*/ 

	int reg1,reg2;

	reg1 = find_region(*x1, *y1);		/* Determining the region's of points. */
	reg2 = find_region(*x2, *y2);

	if(reg1 < reg2) return;				/* If they are not in the same region the quickly function can order points. */
	else if(reg2 < reg1){				
		swap_points(x1,y1,x2,y2);		/* If the second point's region is smaller than swap the points. */
		return;
	}
	else{									/* If they are in the same region than order them with slope. */
		order_w_slope(x1,y1,x2,y2,reg1);
	}
}/* End of function */
/*----------------------------------------------------------------------------------------*/
int find_region(double x, double y){		/* Function determines the region of given point in x-y coordinate system. */
	int reg;

	if(x > 0 && y >= 0) reg = 1;
	else if(x <= 0 && y > 0) reg = 2;
	else if(x < 0 && y <= 0) reg = 3;
	else if(x >= 0 && y < 0) reg = 4;

	else reg = 0;

	return reg;	
}/* End of function */
/*----------------------------------------------------------------------------------------*/
void swap_points(double *x1, double *y1, double *x2, double *y2){	/* Function swaps value of 2 points and returns them. */
	double temp;

	temp = *x1;
	*x1 = *x2;
	*x2 = temp;

	temp = *y1;
	*y1 = *y2;
	*y2 = temp;
}/* End of function */
/*----------------------------------------------------------------------------------------*/
void order_w_slope(double *x1, double *y1, double *x2, double *y2, int reg){
	/* This function takes two points which are in the same region, and compare their slope. After comparing process
	they are ordered. */

	double tx1,tx2,ty1,ty2,slope1,slope2; /*tx and ty variables are temp value which used in determining the order. */

	tx1 = *x1;		tx2 = *x2;		ty1 = *y1;		ty2 = *y2;

	/* Checking if any of the component has a negative value. */
	if(tx1 < 0) tx1 *= -1;
	if(tx2 < 0) tx2 *= -1;
	if(ty1 < 0) ty1 *= -1;
	if(ty2 < 0) ty2 *= -1;

	if(tx1 == 0 && tx2 == 0){		/* If x values are 0, then slope can't be calculated.*/
		
		if(ty1 <= ty2)
			return;
		else{
			swap_points(x1,y1,x2,y2);
			return;
		}
	}
	else{

		if(reg == 1 || reg == 3){		/* Comparing the slopes according to the regions, and ordering them. */

			slope1 = ty1 / tx1;			/* Calculating the slopes. */
			slope2 = ty2 / tx2;

			if(slope1 < slope2){        
				return;
			}
			else if(slope1 > slope2){
				swap_points(x1, y1, x2, y2);
			}
			else{						/* If slopes are equal, then distance to origin(0,0) is determine the order. */
				if(tx1 < tx2)
					return;
				else
					swap_points(x1,y1,x2,y2);
			}
		}

		else if(reg == 2 || reg == 4){	/* Comparing the slopes according to the regions, and ordering them. */

			if(tx1 == 0)
				return;
			else if(tx2 == 0){
				swap_points(x1,y1,x2,y2);
				return;
			}
			else{

				slope1 = ty1 / tx1;			/* Calculating the slopes. */
				slope2 = ty2 / tx2;

				if(slope1 > slope2){        
					return;
				}
				else if(slope1 < slope2){
					swap_points(x1, y1, x2, y2);
				}
				else{						/* If slopes are equal, then distance to origin(0,0) is determine the order. */

					if(ty1 < ty2)
						return;
					else
						swap_points(x1,y1,x2,y2);
				}
			}	
		}
	}			
}/* End of function. */
/*----------------------------------------------------------------------------------------*/
void scan_uchar(unsigned char *number){ /* Function takes proper input from user. */
	int num,status;

	printf("Please enter a number between 0-255: ");	/* Asking user for input. */
	status = scanf("%d", &num);

	while(status != 1){				/* Checking the scanf's returned value. */
		discard();
		printf("Invalid input is entered!\nPlease enter a proper input: ");		/* Warn the user and ask for input again.*/
		status = scanf("%d", &num);
	}
	*number = (unsigned char)num;					/* Cast the taken input and return. */

}/* End of function. */
/*----------------------------------------------------------------------------------------*/
void assign_bits(char *b, unsigned char* num){		/* If the input can be divided by two function assignes 0 to bit.
													If not function assignes 1 to that bit, and returns the number's 
													divided by two version. */
	if(*num % 2 == 0) *b = 0;
	else *b = 1;
	*num /= 2;
}/* End of function */