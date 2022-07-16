/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/


#include <stdio.h>
#include "hw1_io.h"

					/*(P(x) = (a0x^3 + a1x^2 + a2x^1 + a3x^0) */
void write_polynomial3(double a0, double a1, double a2, double a3)
{

	/* this function can be written shortly but in this way, it can be used for printing
	different polynoms with very simple changes(changing array's size, j's value and num_of_coeff's value) */


    int num_of_coeff;
    double coeffs[10];			/* array of coefficents declared.*/
    int i,j;					/* i and j will be used in for loop */ /*"j" is used for printing exponent of each x. */

    coeffs[0] = a0;
    coeffs[1] = a1;
    coeffs[2] = a2;
    coeffs[3] = a3;
										
	num_of_coeff = 4;
	

	for(i = 0,j = num_of_coeff - 1; i < num_of_coeff; i++,j--){
		/* loop for printing the polynomial function's coefficients one by one.*/
		
													
		if(i == num_of_coeff - 1){
			/* condition prevents printing "x^0". */

			if(coeffs[i] > 0){						
				printf("+%g", coeffs[i]);
			}
			else if(coeffs[i] < 0){
				/* condition prevents printing "-+". */
				printf("%g", coeffs[i]);
			}

			break;									/* loop must be terminated after that condition. */
		}

		if(coeffs[i] > 0){
			/* includes conditions for coefficients which are positive. */

			if(coeffs[i] != 1){
				/* includes conditions for positive coefficients except for "1". */

				if(j == 1){
					/* condition prevents printing "x^1" instead of "x". */
					printf("+%gx", coeffs[i]);
				}

				else{

					if(i == 0){
						/* if first coefficent is positive prevents printing "+" before number. */
						printf("%gx^%d", coeffs[i],j);
					}
					else{
						printf("+%gx^%d", coeffs[i],j);
					}
						
				}

			}

			else{	/* condition prevents printing "+1.0x" instead of "x". */
			
				if(j == 1){
					/* condition prevents printing "x^1" instead of "x". */
					printf("+x");
				}

				else{

					if(i == 0){
						/* if first coefficent is positive prevents printing "+" before number. */
						printf("x^%d", j);
					}
					else{
						printf("+x^%d", j);
					}
					
				}
				
			}

		}


		else if(coeffs[i] < 0){
			/* includes conditions for coefficients which are negative. */ 

			if(coeffs[i] != -1){
				/* includes conditions for negative coefficients except for "-1". */

				if(j == 1){
					/* condition prevents printing "x^1" instead of "x".*/
					printf("%gx", coeffs[i]);
				}
				else{
					printf("%gx^%d", coeffs[i],j);
				}
				
			}
			else{	/* condition prevents printing "-1.0x" instead of "-x". */
				
				if(j == 1){
					printf("-x");
				}
				else{
					printf("-x^%d", j);
				}
				
			}
		}
	}
	printf("\n");
}

					/*(P(x) = (a0x^4 + a1x^3 + a2x^2 + a3x^1 + a4x^0) */
void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{

	/* this function can be written shortly but in this way, it can be used for printing
	different polynoms with very simple changes(changing array's size, j's value and num_of_coeff's value) */

	int num_of_coeff;			
    double coeffs[10];				/* array of coefficents declared.*/
	int i,j;						/* i and j will be used in for loop */ /*"j" is used for printing exponent of each x. */

    coeffs[0] = a0;
    coeffs[1] = a1;
    coeffs[2] = a2;
    coeffs[3] = a3;
    coeffs[4] = a4;

    num_of_coeff = 5;

	for(i = 0,j = num_of_coeff - 1; i < num_of_coeff; i++,j--){
		/* loop for printing the polynomial function's coefficients one by one. */		

		if(i == num_of_coeff - 1){
			/* condition prevents printing "x^0".*/

			if(coeffs[i] > 0){
				printf("+%g", coeffs[i]);
			}
			else if(coeffs[i] < 0){
				/* prevents printing "-+".*/
				printf("%g", coeffs[i]);
			}

			break;										/* loop must be terminated after that condition. */
		}

		if(coeffs[i] > 0){
			/* includes conditions for coefficients which are positive.*/

			if(coeffs[i] != 1){
				/* includes conditions for positive coefficients except for "1". */

				if(j == 1){
					/* condition prevents printing "x^1" instead of "x". */
					printf("+%gx", coeffs[i]);
				}
				else{

					if(i == 0){
						/* if first coefficent is positive prevents printing "+" before number. */
						printf("%gx^%d", coeffs[i],j);
					}
					else{
						printf("+%gx^%d", coeffs[i],j);
					}
					
				}


			}

			else{	/* condition prevents printing "1.0x" instead of "x". */				

				if(j == 1){								
					printf("+x");
				}
				else{

					if(i == 0){
						/* if first coefficent is positive prevents printing "+" before number. */
						printf("x^%d", j);
					}
					else{
						printf("+x^%d", j);
					}
					
				}
				
			}

		}


		else if(coeffs[i] < 0){
			/* includes conditions for coefficients which are negative. */

			if(coeffs[i] != -1){	
				/* includes conditions for negative coefficients except for "-1". */

				if(j == 1){								
					/* condition prevents printing "x^1" instead of "x". */
					printf("%gx", coeffs[i]);		
				}
				else{
					printf("%gx^%d", coeffs[i],j);
				}
				
			}

			else{	/* condition prevents printing "-1.0x" instead of "-x". */

				if(j == 1){
					printf("-x");
				}
				else{
					printf("-x^%d", j);
				}
				
			}

		}

	}
	printf("\n");
}
