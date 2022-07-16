/*
** main.c:
**
** The test/driver program for the homework.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/


#include <stdio.h>
#include "hw5_lib.h"


void test_operate_polynomials () 
{
	double a3, a2, a1 , a0 , b3, b2,  b1, b0;
	char op;
	printf("Please enter the first 3rd degree polynomial's coefficients.\n(3,a),...,(0,d): ");
	scan_3polynomial(&a3,&a2,&a1,&a0);	/* Taking the coefficients properly and return them in a proper way. */
	
	printf("\nPlease enter the second 3rd degree polynomial's coefficients.\n(3,a),...,(0,d): ");
	scan_3polynomial(&b3,&b2,&b1,&b0);	/* Taking the coefficients properly and return them in a proper way. */

	printf("\nPlease enter an operator(+,-,*): ");
	scan_operator(&op);	/* Taking the operator in a proper way. */

	operate_polynomials(&a3,&a2,&a1,&a0,&b3,&b2,&b1,&b0,op);

	if(op == '+' || op == '-'){
		printf("\nCoefficients of the result polynomial are:\n");
		printf("nx^3 ----> n = %f\n", a3);
		printf("nx^2 ----> n = %f\n", a2);
		printf("nx   ----> n = %f\n", a1);
		printf("n    ----> n = %f\n\n", a0);
	}
	else if(op == '*' || op == 'x'){
		printf("\nCoefficients of the result polynomial are:\n");
		printf("nx^6 ----> n = %f\n", a3);
		printf("nx^5 ----> n = %f\n", a2);
		printf("nx^4 ----> n = %f\n", a1);
		printf("nx^3 ----> n = %f\n", a0);
		printf("nx^2 ----> n = %f\n", b3);
		printf("nx   ----> n = %f\n", b2);
		printf("n    ----> n = %f\n\n", b1);		
	}
}


void test_four_d_vectors ()
{
	double mean_a0=0.0, mean_a1=0.0, mean_a2=0.0, mean_a3=0.0, longest_distance=0.0;
	int N=5;
	four_d_vectors (&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, N);
	printf("Mean a0: %f\nMean a1: %f\nMean a2: %f\nMean a3: %f\nThe longest distance between two points: %f\n\n\n", mean_a0, mean_a1, mean_a2, mean_a3, longest_distance);
}


void test_dhondt_method ()
{
	int partyA=0, partyB=0, partyC=0, partyD=0, partyE=0, numberOfSeats=0;
	dhondt_method (&partyA, &partyB, &partyC, &partyD, &partyE, numberOfSeats);
	printf("Party A: %d seat(s).\nParty B: %d seat(s).\nParty C: %d seat(s).\nParty D: %d seat(s).\nParty E: %d seat(s).\n\n\n", partyA, partyB, partyC, partyD, partyE);
}


void test_order_2d_points_cc ()
{
	double x1=0.0, y1=0.0, x2=0.0, y2=0.0, x3=0.0, y3=0.0;
	order_2d_points_cc (&x1, &y1, &x2, &y2, &x3, &y3);
	printf("Counter-Clockwise Order: (%f,%f) - (%f,%f) - (%f,%f)\n\n\n", x1, y1, x2, y2, x3, y3);
}


void test_number_encrypt ()
{
	unsigned char number=0;
	number_encrypt (&number);
	printf("Encrypted number: %d\n\n\n", number);
}


/*
** main function for testing the functions...
**
*/
int main(void) {
	test_operate_polynomials ();
	test_four_d_vectors ();
	test_dhondt_method ();
	test_order_2d_points_cc ();
	test_number_encrypt ();
	return (0);
} /* end main */
