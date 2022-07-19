/*
** hw1_lib.c:
**
** The source file implementing library functions.
**
** Author: Burak Kocausta
** 
*/

#include <stdio.h>
#include "hw1_lib.h"

				/* (P(x) = (a0x^3 + a1x^2 + a2x^1 + a3x^0)(xs = xstart, xe = xend, delta = step size) */
double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{

	/*-------------------------------------------------------------------   */
	/* Integral estimation is done according to "TRAPEZOIDAL RULE". 		**
	** The area under a curve is calculated by dividing the total			**
	** area into trapezoids according to step size. 						**						
	**-------------------------------------------------------------------   */

	double coeffs[10];			/* array of coefficents declared. */

    double num;					/* total number of trapezoids. */
    double sum,temp,temp2;		/* temp and temp2 are each trapezoid's starting and ending points. */	
	int i,flag;					/* 'i' will be used in for loop */ /* flag will be used in case xs > xe */ 

    coeffs[0] = a0;
    coeffs[1] = a1;
    coeffs[2] = a2;
    coeffs[3] = a3;
    flag = 0;

    if(xe < xs){				/* in case if xstart > xend */

    	temp = xe;
    	xe = xs;
    	xs = temp;
    	flag++;
    }

    num = (xe-xs) / delta;
    sum = 0.0, temp = xs,temp2 = xs;

	for(i = 0; i < num; i++){

		temp = temp + delta;
		sum = sum + tpzd_area(temp2, third_degree_pol(coeffs, temp2), temp, third_degree_pol(coeffs, temp));
		temp2 = temp2 + delta;
	} 

	if(flag != 0)
		return -sum;
	return sum;
}

				/* (P(x) = (a0x^4 + a1x^3 + a2x^2 + a3x^1 + a4x^0)(xs = xstart, xe = xend, delta = step size) */
double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{
	/*-------------------------------------------------------------------   */
	/* Integral estimation is done according to "TRAPEZOIDAL RULE". 		**
	** The area under a curve is calculated by dividing the total			**
	** area into trapezoids according to step size. 						**						
	**-------------------------------------------------------------------   */


	double coeffs[10];		/*  array of coefficents declared. */
		   

    double num;					/*  total number of trapezoids */
    double sum,temp,temp2;		/*  temp and temp2 are each trapezoid's starting and ending points.  */
	int i,flag;					/* 'i' will be used in for loop */ /* flag will be used in case xs > xe */

    coeffs[0] = a0;
    coeffs[1] = a1;
    coeffs[2] = a2;
    coeffs[3] = a3;
   	coeffs[4] = a4;
   	flag = 0;

   	if(xe < xs){				/* in case if xstart > xend */
    
    	temp = xe;
    	xe = xs;
    	xs = temp;
    	flag++;
    }

    num = (xe-xs) / delta;				
    sum = 0.0, temp = xs,temp2 = xs;

	for(i = 0; i < num; i++){

		temp = temp + delta;
		sum = sum + tpzd_area(temp2, fourth_degree_pol(coeffs, temp2), temp, fourth_degree_pol(coeffs, temp));
		temp2 = temp2 + delta;
	} 

	if(flag != 0)
		return -sum;
	return sum;
}

			/* (P(x) = (a0x^3 + a1x^2 + a2x^1 + a3x^0)(xs = xstart, xe = xend) */
double root3(double a0, double a1, double a2, double a3, double xs, double xe)
{
	/*-------------------------------------------------------------------   */
	/*Root is estimated with "FALSE POSITION METHOD(REGULA FALSI METHOD)".  */
	/*-------------------------------------------------------------------   */

    double coeffs[10];		/*  array of coefficents declared. */

    double pot_root,pot_root2,pot_root3,PRECISION; 	/* these declarations are explained below.   */
    int COUNTER;

    coeffs[0] = a0;
    coeffs[1] = a1;
    coeffs[2] = a2;
    coeffs[3] = a3;
    /* Conditions below checks some of the preconditions for this method, before the essential algorithm starts.*/
/* -------------------------------------------------------------------------------------------------------------------   */
	if(third_degree_pol(coeffs, xs) * third_degree_pol(coeffs, xe)  > 0){
		/* Method only works when there is one root in the given interval. */

		printf("There aren't any roots or there are roots more than one.\n");
		return 0;
	}
	else if(third_degree_pol(coeffs, xs) * third_degree_pol(coeffs, xe) == 0){
		/* Condition checks if one of the interval or both of them are the roots or not.   */

		if(third_degree_pol(coeffs, xs) == 0){

			if(third_degree_pol(coeffs, xe) == 0){
				printf("%f and %f are roots.\n",xe,xs);
				return xe;
			}
			return xe;
		}
		return xs;
	}
/* ------------------------------------------------------------------------------------------------------------------- */
	/* Conditions above checks some of the preconditions for this method, before the essential algorithm starts. */

	else{
		
		/* find_pot_root calculates the potential root. */

		pot_root = find_pot_root(xs, third_degree_pol(coeffs, xs), xe, third_degree_pol(coeffs, xe));
		
		
		pot_root2 = xe; /* pot_root, pot_root2, pot_root3 are the variables used in this algorithm.*/
		pot_root3 = xs; 
						/* xe's and xs's values are assigned to the different variables because,
						if loop cannot achieve the wanted estimation in do while loop xe's and xs's original
						values are needed. */

		/* Stopping criterion */ 
		PRECISION = 0.0000001; /* Before returning estimated root, It has to be in this precision. */

		/* Stopping criterion */
		COUNTER = 0; /* If this estimation can not achieve to the wanted precision in at most 10000 steps it will be terminated. */

		/* Main purpouse is continuously minimize the interval with find_pot_root formula. */
		do{
			if(third_degree_pol(coeffs, pot_root) * third_degree_pol(coeffs, pot_root2) < 0){
				/* Checking if there are any root between pot_root and pot_root2. */

				pot_root3 = find_pot_root(pot_root, third_degree_pol(coeffs, pot_root), pot_root2, third_degree_pol(coeffs ,pot_root2));
				/* Estimating the new potential root. */
	
				if(third_degree_pol(coeffs, pot_root3) * third_degree_pol(coeffs, pot_root2) < 0){
					/* Checking if there are any root between pot_root3 and pot_root. */
					pot_root = pot_root3;	/* There is no use of pot_root's old value, so we assign pot_root3's value to it. */
					
				}
				else{
					pot_root2 = pot_root3; /* There is no use of pot_root2's old value, so we assign pot_root3's value to it. */
				}
			}
			else if(third_degree_pol(coeffs, pot_root) * third_degree_pol(coeffs, pot_root3) < 0){
				/* Checking if there are any root between pot_root and pot_root3. */
				
				pot_root2 = find_pot_root(pot_root3, third_degree_pol(coeffs, pot_root3), pot_root, third_degree_pol(coeffs, pot_root));
				/* Estimating the new potential root. */

				if(third_degree_pol(coeffs, pot_root2) * third_degree_pol(coeffs, pot_root3) < 0){
					/* Checking if there are any root between pot_root2 and pot_root3. */
					pot_root = pot_root2; /* There is no use of pot_root's old value, so we assign pot_root2's value to it. */
				}
				else{
					pot_root3 = pot_root2; /* There is no use of pot_root3's old value, so we assign pot_root2's value to it. */
				}
			}

			
			
			/* ---------------------------CHECKING THE FIRST STOPPING CRITERIA----------------------------------- */
			if(third_degree_pol(coeffs, pot_root2) < PRECISION && third_degree_pol(coeffs, pot_root2) > -PRECISION ){
				return pot_root2;
			}
			if(third_degree_pol(coeffs, pot_root3) < PRECISION && third_degree_pol(coeffs, pot_root3) > -PRECISION){
				return pot_root3;
			}
			/* ---------------------------CHECKING THE FIRST STOPPING CRITERIA----------------------------------- */

		COUNTER++;	
		}while(COUNTER < 10000);	/* <<<--- CHECKING THE SECOND STOPPING CRITERIA */

		/* pot_root2 or pot_root3 will be definitely change after the loop and achieve the optimum precision.
		Condition checks which one it is.*/ 
		if(pot_root2 < xe)
			return pot_root2;
		return pot_root3;	
	}
}

			/* (P(x) = (a0x^4 + a1x^3 + a2x^2 + a3x^1 + a4x^0)(xs = xstart, xe = xend) */	
double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)
{

	/*-------------------------------------------------------------------   */
	/*Root is estimated with "FALSE POSITION METHOD(REGULA FALSI METHOD)".  */
	/*-------------------------------------------------------------------   */

    double coeffs[10];		/*  array of coefficents declared. */
 
    double pot_root,pot_root2,pot_root3,PRECISION; 	/* these declarations are explained below.   */
    
    int COUNTER;

    coeffs[0] = a0;
    coeffs[1] = a1;
    coeffs[2] = a2;
    coeffs[3] = a3;
   	coeffs[4] = a4;

    /* Conditions below checks some of the preconditions for this method, before the essential algorithm starts.*/
/* -------------------------------------------------------------------------------------------------------------------*/
	if(fourth_degree_pol(coeffs, xs) * fourth_degree_pol(coeffs, xe)  > 0){
		/* Method only works when there is one root in the given interval.*/

		printf("There aren't any roots or there are roots more than one.\n");
		return 0;
	}
	else if(fourth_degree_pol(coeffs, xs) * fourth_degree_pol(coeffs, xe) == 0){
		/* Condition checks if one of the interval or both of them are the roots or not.*/

		if(fourth_degree_pol(coeffs, xs) == 0){

			if(fourth_degree_pol(coeffs, xe) == 0){

				printf("%f and %f are roots.\n",xe,xs);
				return xe;
			}
			return xe;
		}
		return xs;
	}
	/*------------------------------------------------------------------------------------------------------------------- */
	/* Conditions above checks some of the preconditions for this method, before the essential algorithm starts. */

	else{
				/*find_pot_root calculates the potential root. */
		pot_root = find_pot_root(xs, fourth_degree_pol(coeffs, xs), xe, fourth_degree_pol(coeffs, xe));
		
		pot_root2 = xe; /* pot_root, pot_root2, pot_root3 are the variables used in this algorithm.*/
		pot_root3 = xs; 
						/* xe's and xs's values are assigned to the different variables because,
						if loop cannot achieve the wanted estimation in do while loop xe's and xs's original
						values are needed. */
		
		/* Stopping criterion */
		PRECISION = 0.0000001; /* Before returning estimated root, It has to be in this precision. */

		/* Stopping criterion */
		COUNTER = 0; /* If this estimation can not achieve to the wanted precision in at most 10000 steps it will be terminated. */ 

		/* Main purpouse is continuously minimize the interval with find_pot_root formula. */
		do{

			if(fourth_degree_pol(coeffs, pot_root) * fourth_degree_pol(coeffs, pot_root2) < 0){
				/* Checking if there are any root between pot_root and pot_root2. */

				pot_root3 = find_pot_root(pot_root, fourth_degree_pol(coeffs, pot_root), pot_root2, fourth_degree_pol(coeffs, pot_root2));
				/* Estimating the new potential root. */
	
				if(fourth_degree_pol(coeffs, pot_root3) * fourth_degree_pol(coeffs, pot_root2) < 0){
					/* Checking if there are any root between pot_root and pot_root3. */
					
					pot_root = pot_root3;	/* There is no use of pot_root's old value, so we assign pot_root3's value to it. */
						
				}
				else{
					pot_root2 = pot_root3;	/* There is no use of pot_root2's old value, so we assign pot_root3's value to it. */		
				}
			}
			else if(fourth_degree_pol(coeffs, pot_root) * fourth_degree_pol(coeffs, pot_root3) < 0){
				/* Checking if there are any root between pot_root and pot_root3. */
				
				pot_root2 = find_pot_root(pot_root3, fourth_degree_pol(coeffs, pot_root3), pot_root, fourth_degree_pol(coeffs, pot_root));
				
				if(fourth_degree_pol(coeffs, pot_root2) * fourth_degree_pol(coeffs, pot_root3) < 0){
					/* Checking if there are any root between pot_root2 and pot_root3. */
					
					pot_root = pot_root2;	/* There is no use of pot_root's old value, so we assign pot_root2's value to it. */
						
				}
				else{
					pot_root3 = pot_root2;	/* There is no use of pot_root3's old value, so we assign pot_root2's value to it. */
				}
			}
			/* ---------------------------CHECKING THE FIRST STOPPING CRITERIA-------------------------------------- */
			if(fourth_degree_pol(coeffs, pot_root2) < PRECISION && fourth_degree_pol(coeffs, pot_root2) > -PRECISION ){
	
				return pot_root2;
			}
			if(fourth_degree_pol(coeffs, pot_root3) < PRECISION && fourth_degree_pol(coeffs, pot_root3) > -PRECISION){
				
				return pot_root3;
			}
			/* ---------------------------CHECKING THE FIRST STOPPING CRITERIA-------------------------------------- */

			COUNTER++;
			
		}while(COUNTER < 10000);	/* <<<--- CHECKING THE SECOND STOPPING CRITERIA*/ 

		/* pot_root2 or pot_root3 will be definitely change after the loop and achieve the optimum precision.
		Condition checks which one it is.*/ 
		if(pot_root2 < xe)
			return pot_root2;

		return pot_root3;
	}
}
/* ------------------------ FUNCTIONS USED----------------------------------------------------- */

double third_degree_pol(double coeffs[], double x){ /* Function returns the third degree polynom's value. */
													/* coeffs are (a0,a1,a2,a3), x is input. */
													/* P(x) = a0x^3 + a1x^2 + a2x^1 + a3 */  
	double sum;

	/* P(x) = ((a0*x + a1)*x + a2)*x) + a3 */ /* it is written like this to avoid overflow */
	sum = ((coeffs[0]*x + coeffs[1])*x + coeffs[2])*x + coeffs[3];
	return sum;
}

double fourth_degree_pol(double coeffs[], double x){ /* Function returns the fourth degree polynom's value. */
													 /* coefficients are (a0,a1,a2,a3,a4), x is input. */
													 /* P(x) = a0x^4 + a1x^3 + a2x^2 + a3x^1 + a4 */
	double sum;

	/* P(x) = (((a0*x + a1)*x + a2)*x + a3)*x + a4 */ /* it is written like this to avoid overflow */ 
	sum = (((coeffs[0]*x + coeffs[1])*x + coeffs[2])*x + coeffs[3])*x + coeffs[4];
	return sum;
}

double find_pot_root(double xs, double ys, double xe, double ye){ /* function returns a potential root between two interval. */
																  /* xs = xstart, ys = f(xstart), xe = xend, ye = f(end) */
	double pot_root;
	/* pot_root = [xstart*f(xend) - xend*f(xstart)] / (f(xend) - f(xstart)) */
	pot_root = (xs * ye - xe * ys) / (ye - ys);
	return pot_root;
}

double tpzd_area(double xs, double ys, double xe, double ye){ /* function returns are of a trapezoid. */
															  /* xs = xstart, ys = f(xstart), xe = xend, ye = f(end) */
	double area;
	/* area = (1/2) * (xend - xstart) * (f(xstart) + f(xend)) */
	area = (0.5)*(xe - xs)*(ys + ye);
	return area;
}
/* ------------------------- FUNCTIONS USED----------------------------------------------------- */
