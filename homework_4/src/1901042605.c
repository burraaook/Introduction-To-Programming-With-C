#include <stdio.h>
#include <math.h>						 /* "math.h" library is only used for pow() function. */

void print_polynomial();				 /* Prints polynomial which users asks in a pretty format. */

void check_armstrong_palindrome();		 /* Prints if the input number is armstrong,palindrome,both or neither. */			

void print_sum_of_primes();				 /* Prints the sum of primes in the interval which is asked to user. */

/* HELPER FUNCTIONS */
float scan_n_round();					  /* Function gets a floating point number input from the user, rounds it and returns. */

float round_digits(float num);			  /* Function rounds given floating point numbers to a.b format and returns. */

void print_coef_x(float num, int degree); /* Function prints each coefficient and x. */

void discard();							  /* Function discards unnecessary inputs. */

int scan_nonnegative_int();				  /* Function gets an nonnegative integer input from the user and returns. */

int sum_of_primes(int num1,int num2);	  /* Function calculates the sum of prime at given interval, and returns the result. */

int prime_check(int num);				  /* Function checks if the number is prime or not, and returns the result. */

int check_palindrome(int num);			  /* Function checks if the number is palindrome or not, and returns 3 or 1. */

int check_armstrong(int num);			  /* Function checks if the number is armstrong or not, and returns 1 or 0.*/

int digit_counter(int num);				  /* Function returns total digits of given integer. */
/* HELPER FUNCTIONS */

int main(void){						/* Functions are called one by one. */	

	print_polynomial();							

	check_armstrong_palindrome();

	print_sum_of_primes();

	return 0;
}/* End of main function. */
/* ------------------------------------------------------------------------------------------ */

void print_polynomial(){		/* Function asks the user degree and coefficients. And prints polynom in pretty format. */

	int degree,flag;				/* flag is used to not printing '+' for the first coefficient. */
	float coefficient;

	printf("\nEnter your polynomial[n a^n a^n-1 ... a^0]: ");  /* Asking for inputs. */

	scanf("%d", &degree);
	flag = 0;				/* flag should be 0 because there shouldn't be + sign if the first coefficient is positive. */

	printf("\np(x)= ");
	
	while(degree >= 0){					/* This loop prints nothing if the coefficient is equal to 0. */

		coefficient = scan_n_round();	/* Asking to user and round it to wanted format. */

		if(coefficient > 0){ 		

			if(flag != 0) printf("+ ");			/* Checking if anything printed before. */
			
			print_coef_x(coefficient, degree);

			flag = 1;							/* Coefficient is not 0 so 1 can be assigned to the flag. */
		}

		else if(coefficient < 0){

			printf("- ");						/* Printing the number's sign. */
			print_coef_x(-coefficient, degree);	/* Function works with positive numbers so send the numbers positive version. */	

			flag = 1;							/* Coefficient is not 0 so 1 can be assigned to the flag. */
		}

		degree--;
	}/* End of the loop */

	discard();									/* If anything unnecessary is inputted by the user discard all of them. */

	printf("\n");

}/* End of the first function. */
/* ------------------------------------------------------------------------------------------ */

void check_armstrong_palindrome(){ /* Function prints if the number is palindrome,armstrong,both or neither. */

	int num,flag;	/* flag is used for checking 4 different possibility. */

	flag = 1;

	printf("\n\nPlease enter an integer number: ");
	num = scan_nonnegative_int();           /* Taking the proper input before sending to the functions. */

	flag = flag + check_armstrong(num);		/* This function returns 1 if the input number is armstrong number. Otherwise it
											returns 0. */

	flag = flag * check_palindrome(num);	/* This function returns 3 if the input number is armstrong number. Otherwise it
											returns 1. */ 

	switch(flag){			/* There are 4 possibilities, therefore selecting the result and printing the proper output. */

		case 2 :
			printf("\nThis number is only Armstrong number.\n");
			break;

		case 3 :
			printf("\nThis number is only Palindrome number.\n");
			break;

		case 6 :
			printf("\nThis number is both Palindrome and Armstrong number.\n");
			break;

		default :
			printf("\nThis number does not satisfy any special cases.\n");
			break;
	}/* End of switch */

	discard();				/* If anything unnecessary is inputted by the user discard all of them. */

}/* End of the second function */
/* ------------------------------------------------------------------------------------------ */

void print_sum_of_primes(){

	int num1,num2;

	printf("\n\nPlease enter first integer number: ");

	num1 = scan_nonnegative_int();				/* Taking the proper input before sending to the functions. */

	printf("\nPlease enter second integer number: ");

	num2 = scan_nonnegative_int();				/* Taking the proper input before sending to the functions. */

	printf("\nSum of prime numbers between %d and %d : %d\n\n", num1, num2, sum_of_primes(num1,num2)); /* printing the result. */

	discard();				/* If anything unnecessary is inputted by the user discard all of them. */

}/* End of the third function. */

/* ------------------------------ HELPER FUNCTIONS ------------------------------ */

float scan_n_round(){			/* Function gets a floating point number input from the user, rounds it and returns. */

	float num;

	scanf("%f", &num);
	num = round_digits(num);	/* Rounded version of input is assigned */

	return num;
}/* End of function. */
/* ------------------------------------------------------------------------------------------ */

void discard(){					/* This loop discards unnecessary inputs. */	
	
	char ch;

	do{							

		scanf("%c", &ch);
	}while(ch != '\n');

}/* End of function. */
/* ------------------------------------------------------------------------------------------ */	

float round_digits(float num){ 		   /* This function converts floating point number to floating point number
									   which has at most 1 digits after  the decimal with rounding before.*/
 	
 	int temp,flag;					   /* temp is used in type casting(float to int) and calculating */
									   /* flag will be used in case num is negative */	

	flag = 0;

	if(num < 0){					   /* Checking if num is a negative number. */

		num = num * (-1);
		flag = 1;
	}
	
	num = num * 1000;				   /* Saving the 3 digits after the decimal point. */
	
	temp = (int)num;				   /* Casting the variable float to int and saving the value to temp. */
	
	/* If the last number of temp is lesser than 51 then no need to round it up */
	if((temp % 100) < 51) temp = temp / 100;
					   
	else{							   /* If the last number of temp is bigger or equal to 51,then after dividing by 100 
									   temp will be rounded up */
		temp = temp / 100;
		temp++;
	}

	num = (float)temp;					/* Casting temp to float and assign it to num. */

	num = num / 10;						/* Floating point number will not lost digit after dividing. */

	/* Checking whether the num was negative or not. */

	if(flag == 1)
		return num*(-1);

	else
		return num;

}/* End of function. */
/* ------------------------------------------------------------------------------------------ */

void print_coef_x(float num, int degree){  /* This function prints numx^degree format */
										   /* Function works for only positive numbers. If negative coefficient is wanted to
										   be printed, it must be multiplied -1 before sending to the function. */

	if(degree > 1){

		if(num == 1.0) printf("x^%d ", degree); /* 1 shouldn't be printed. */
		
		else printf("%.1fx^%d ", num, degree);

	}

	else if(degree == 1){					/* If degree is 1, degree should not be printed. */

		if(num == 1.0) printf("x ");		

		else printf("%.1fx ", num);

	}

	else printf("%.1f ",num);              /* If degree is 0, x should not be printed. */

} /* End of function. */
/* ------------------------------------------------------------------------------------------ */

int check_palindrome(int num){		/* Function returns 3 if the given number is palindrome number. Otherwise 1 will be returned. */

	/* A number is a palindrome number, if it is equal to its reversed version. */

	int reverse_num,temp;			/* reverse_num will be compared with num after the loop. */

	if(num <= 9){					/* If number has one digit, then no need to loop. */

		if(num < 0)					/* Negative numbers are not palindrome numbers. */
			return 1;
		
		else
			return 3;
			
	}

	temp = num;						/* num's value must be saved before the loop */
	reverse_num = 0;				

	/* Reversing process starts. */
	do{

		reverse_num = reverse_num + (temp % 10);	/* Add the last digit of the number. */

		reverse_num = reverse_num * 10;		/* Multiply the number with 10 in each loop. */
		
		temp = temp / 10;					/* Losing the digits which are already used. */

	}while(temp > 9);		/* Checking if it is smaller than 9. */

	reverse_num = reverse_num + temp;

	/* Reversing process is finished. Number is reversed */
	
	

	if(num == reverse_num)			/* Checking whether it is equal to its reversed version or not. */ 
		return 3;					/* Returns 3 if it is equal. */
	
	else
		return 1;					/* Returns 1 if it is not. */

}/* End of function. */
/* ------------------------------------------------------------------------------------------ */

int check_armstrong(int num){		/* Function returns 1 if input is an armstrong number, otherwise it returns 0. */

	/* A number is an armstrong number if it is equal to the sum of its own digits raised to the power of the number of digits. */

	int sum,temp,digit,num_of_digit;	/* temp variable is used for saving the num's value */
										/* sum variable is the variable that will be checked at the end of the function. */

	if(num < 0) return 0;						/* Negative numbers are not an armstrong number. */
		
	else if(num == 0) return 1;
			
	temp = num;
	sum = 0;
	num_of_digit = digit_counter(num);	/* digit_counter() returns the total number of digits of the integer. */

	/* Starting the process that acquires a number with input number's digits. */
	do{

		digit = temp % 10;						/* Starting from the last digit. */

		sum = sum + pow(digit,num_of_digit);	/* Multiply digit num_of_digit times and add the result to sum. */ 

		temp = temp / 10;						/* Losing the digits which are already used. */

	}while(temp != 0);							/* End the loop if temp is equal to 0. */
	/* A number with input number's digits is acquired. */

	/* Checking if that acquired number is equal to num or not. */
	
	if(sum == num) return 1;			
		
	
	else
	 return 0;

}/* End of function. */
/* ------------------------------------------------------------------------------------------ */

int digit_counter(int num){					/* Function counts number of digits of given positive integer number. */

	int counter;

	counter = 0;

	while(num > 0){

		num = num / 10;
		counter++;
	}

	return counter;
}/* End of function. */
/* ------------------------------------------------------------------------------------------ */

int scan_nonnegative_int(){			/* Function gets an nonnegative integer input from the user and returns. */
	int num,status;

	status = scanf("%d", &num);
	
	if(status == 0) discard(); /* If user enters chars with space, this condition prevents to crash. */
	
	while(num < 0 || status == 0){/* If user enters negative or nonnumeric input ask for input again till proper input is entered. */

		printf("\nPlease enter a \"nonnegative integer!\": ");
		status = scanf("%d", &num);

		if(status == 0){

			discard();		/* If status is 0 discard all of the unnecessary input. */
			num = -1;		/* Assign -1 to num because proper input has not entered yet. */
		} 
		
	}

	return num;
}/* End of function */
/* ------------------------------------------------------------------------------------------ */

int sum_of_primes(int num1,int num2){	/* Function calculates the sum of prime numbers in given interval. */
										/* Interval's boundaries should not be counted. */
	int i,sum,temp;

	if(num2 < num1){   /* Checking if num2 < num1. */

		temp = num1;	/* Swapping process starts. */
		num1 = num2;	
		num2 = temp;
	
	}/* Values are swapped. */

	sum = 0;

	for(i = num1+1; i < num2; i++){	/* Starting from num1+1 because num1 and num2 shouldn't be added to the sum. */

		if(prime_check(i) == 1){	/* If number is prime 1 will be returned. */

			sum = sum + i;

		}

	}

	return sum;						/* Return the calculated sum. */
}/* End of function. */
/* ------------------------------------------------------------------------------------------ */

int prime_check(int num){			/* Function returns 1 if number is prime, otherwise 0 will be returned. */

	int i;

	for(i = 2; i < num; i++){

		if(num % i == 0)
			return 0;	
	}

	if(num < 2) return 0;
			
	else
		return 1;

}/* End of function. */
/* ------------------------------------------------------------------------------------------ */