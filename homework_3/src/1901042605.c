#include <stdio.h>

void calculate_fibonacci_sequence();	/* Function prints fibonacci sequence according to inputs which are taken from the user. */

void decide_perfect_harmonic_number();	/* Function checks if input is harmonic number,and perfect number and prints divisors. */

void difference_max_min();				/* Function calculates and prints the difference between maximum and minimum numbers 
										according to the inputs which are taken from user. */
													
void bmi_calculation();					/* Function calculates and prints body mass index according to the inputs 
										which are taken from the user. */

void check_perfect_harmonic(int num);	/* Function is Helper function which used in decide_perfect_harmonic_number(). */

void print_fibonacci(int num);			/* Function is Helper function which used in calculate_fibonacci_sequence(). */



int main(void){

	calculate_fibonacci_sequence();		/* Prints fibonacci sequence */
	decide_perfect_harmonic_number();	/* Prints the given numbers divisiors and checks perfect and harmonic sitation */
	difference_max_min();				/* Prints the difference of maximum and minimum number */
	bmi_calculation();					/* Prints the body mass index. */

	return 0;							/* Main function returns 0 */
}

void calculate_fibonacci_sequence(){
/* Function prints fibonacci sequence according to inputs which are taken from the user. */

	char ch;						/* ch is used for checking if the user inputs number or not. */
	int num;						/* num will be sent to the function which prints fibonacci. */

	printf("Please enter term(s) number: ");	/* Asking the user to input total number of integers which will be printed. */
	

	do{ /* This loop gets input from the user till user inputs '*' character. */

		
		scanf("%d", &num);			/* Getting the number from user */
		ch = getchar();				/* If user input is an integer then ch will be '\n' character */
									/* If user input is not an integer then input stuck on the buffer and getchar() function
									gets that character */

		if(ch == '\n'){				/* Checking if user input is an integer. */

			if(num <= 0){			/* Checking if user input is negative integer or zero. */

				printf("Please enter \"positive\" term(s) number: ");	/* If it is negative or zero, then print warning. */

			}
			else{														/* If it is not, then call the function. */

				print_fibonacci(num);
				printf("Please enter term(s) number: ");
			
			}

		}
		else if(ch != '*'){						/* Warning if the user input is character except '*'. */

			printf("Please enter \"numeric\" term(s) number: ");
		
		}
		

	}while(ch != '*');							/* End the loop if user input is '*'. */
}	/* End of the function */

void decide_perfect_harmonic_number(){

	/* Function checks if input is harmonic number,and perfect number and prints result. */

	char ch;			/* ch is used for checking if the user inputs number or not. */
	int num;			/* num will be sent to the function which checks it's perfect and harmonic situation. */
						

	printf("\nPlease enter input number: ");		/* Asking user to input which number will be checked. */

	do{	/* This loop gets input from the user till user inputs '*' character. */	


		scanf("%d", &num); /* Getting the number from user */					
		ch = getchar();	   /* If user input is an integer then ch will be '\n' character */
						   /* If user input is not an integer then input stuck on the buffer and getchar() function
						   gets that character. */

		if(ch == '\n'){		/* Checking if user input is an integer. */

			if(num < 0){	/* Checking if user input is negative integer. */

				printf("\nPlease enter \"natural\" input number: ");		/* If it is, then it is not natural number. */

			}

			else{		/* If it is natural then send the number to the function. */

				check_perfect_harmonic(num);				/* Call the function which prints the divisors of
															that number and result. */
				printf("\nPlease enter input number: ");		
			
			}

		}
		else if(ch != '*'){		/* Warning if the user input is character except '*'. */

			printf("\nPlease enter \"numeric\" input number: ");
		
		}
		

	}while(ch != '*');			/* End the loop if user input is '*'. */

} /* End of the function */

void difference_max_min(){		/* Function calculates and prints the difference between maximum and minimum numbers 
								according to the inputs which are taken from user. */
	
	int i,num_of_input;			/* i is local variable used in loop. */ 
								/* num_of_input is total number of inputs that will be taken from user */ 
	float num,max,min;			/* Num is the number which user inputs */ /* max: maximum, min: minimum */

	num_of_input = 5;

	printf("\nPlease enter %d numbers: ", num_of_input);		/* Asking the user to enter the numbers. */

	scanf("%f", &num);						/* Taking the first number from user. */

	max = num;								/* Assigning the max and min numbers according to input */
	
	min = num;

	for(i = 0; i < num_of_input-1; i++){	/* Loop is executed num_of_input-1 times because, already first number is taken */

		scanf("%f", &num);
		
		if(num > max){						/* Determining the maximum number */
			max = num;
		}

		if(num < min){						/* Determining the minimum number */
			min = num;
		}
		
	}

	printf("\nMaximum number is: %.7g\n\n", max);		/* Printing the maximum and minimum number without trailing zeros */
	printf("Minimum number is: %.7g\n\n", min);
	printf("Difference between maximum and minimum is %.7g\n\n", max - min);	/* Printing the difference without trailing zeros */


}	/* End of the function */

void bmi_calculation(){	/* Function calculates and prints body mass index according to the inputs 
						which are taken from the user. */

	float weight,height,bmi;			/* weigh(kg), height(meter) */

	/* Asking and taking the values from the user */
	printf("\nPlease enter weight(kg): ");	
	scanf("%f", &weight);

	printf("\nPlease enter height(m): ");
	scanf("%f", &height);

	bmi = weight / (height*height);			/* Calculating the body mass index */
	
	/* Checking the body mass index category according the user inputs. */
	if(bmi < 16){
		printf("\nYour category: Severely Underweight\n");
	}
	else if(bmi < 18.5){
		printf("\nYour category: Underweight\n");
	}
	else if(bmi < 25.0){
		printf("\nYour category: Normal\n");
	}
	else if(bmi < 30.0){
		printf("\nYour category: Overweight\n");
	}
	else{
		printf("\nObese\n");
	}

}	/* End of the function */

/* ------------------------- HELPER FUNCTIONS ------------------------- */

void print_fibonacci(int num){

	int temp1,temp2,temp3,i;	/* i is a local variable which used in for loop */
								/* temp1,temp2,temp3 are temporary variables used for calculating fibonacci sequence. */

	temp1 = 0;					/* Assigning 0 to temp1 because if input is 2, it must print 1\n1 */
	temp2 = 1;

	printf("\nFibonacci Sequence: \n");
	printf("\n1\n");				/* If input is 1 no need to enter the loop. */

	for(i = 1; i < num; i++){	/* i is started from 1 because 1 is already printed */
			
		temp3 = temp1;			/* storing the temp1's value to temp3. */

		printf("\n%d\n", temp1+temp2);	/* printing the current number */

		temp1 = temp2;					/* temp2 will be the next temp1. */

		temp2 = temp3 + temp2;			/* Determining the next temp2 with temp1's stored value which is temp3. */

	} /* End of the loop if num is equal to i */

		printf("\n");	

}	/* End of the function */

void check_perfect_harmonic(int num){ 
	/* Function is Helper function which used in decide_perfect_harmonic_number(). */

	/* Perfect number is a positive integer which is equal to sum of it's positive divisiors except itself. */
	/* Harmonic Divisior Number (Ore Number) is a positive integer whose divisors have a harmonic mean which is an
	integer. */

	int i,sum,counter;	/* i is a local variable which used in for loop */
						/* sum is variable for calculating sum of divisiors */
						/* counter is used for counting the number of divisiors */

	/* If number is 0, then no need for loop */
	if(num == 0){
		printf("\nNatural Number Divisors: [1,2,..,+infinite)\n");
		printf("\nIs Perfect Number?: No\n");
		printf("\nIs Harmonic Divisor Number?: No\n\n");

		return;	/* End function if condition is true. */
	}

	counter = 1;	/* counter is 1 because, num doesn't count in this loop. */
	sum = 0;		/* 0 is assigned to sum because, garbage value does not wanted. */

	printf("\nNatural Number Divisors: "); 	

	for(i = 1; i < num; i++){ 	/* 1 assigned to i because 0 shouldn't be the denominator. */

		if(num % i == 0){		/* Checking whether i is the divisor or not. */

			sum = sum + i;		/* Calculating the sum of divisiors except num. */
			printf("%d,", i);	/* Printing the divisors with comma. */
			counter++;			/* Counting the number of divisiors. */

		}

	}
	printf("%d\n", num);		/* Printing the num, because it is one of the divisior. */


	printf("\nIs Perfect Number?: ");

	if(sum == num){				/* Checking if the number is perfect or not. */
		printf("Yes\n");		/* If it is, print "Yes". */
	}
	else{						
		printf("No\n");			/* If it is not, print "No". */
	}

	printf("\nIs Harmonic Divisor Number?: ");

	
	sum = sum + num;			/* num must be added to sum when calculating the harmonic divisior. */
								/* While determining if the number is harmonic divisior or not. The last situation of 
								calculation will be ((counter * num) % sum == 0) */
								
								/* For example if the number is 6, it's divisors are 1,2,3,6 harmonic sum of them is 
								(1/1)+(1/2)+(1/3)+(1/6), it can be written like [(6+3+2+1)/6],
								(number of divisors / [(6+3+2+1)/6]) must be an integer.Final state of this is
								[6*(number of divisors) / (6+3+2+1)], so that condition inside the if
								must be true if this number is harmonic divisor number.*/

	if((counter*num) % sum == 0){
		printf("Yes\n");
	}
	else{
		printf("No\n");
	}

	printf("\n");

}/* End of the function */

/* ------------------------- HELPER FUNCTIONS ------------------------- */