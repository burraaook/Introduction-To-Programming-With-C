/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include "hw2_lib.h"
#include <math.h>

int zeller_method(int day, int month, int year); /* Finds the day of given date, according to Zeller's Congruence. */

void print_line(char border,char vertical,int num);	/* Prints line with given parameters, num is for how many time it prints */

int day_check(int day, int month, int year);		/* Checks if the given date is valid date or not */

int triangle_check(double a, double b, double c);	/* Function checks that triangle can be drawed with given values. */ 

double two_decimal_digits(double num);  /* This function converts double number to double number which has at most 2 digits 
									   after decimal with rounding before. */

int digit_counter(unsigned int num); 	/* Function counts number of digits of given number. */

int find_weekday_of_data(int day, int month, int year)
{
    int day_returned; /* Monday -> 0 , ... , Sunday -> 7. */
	


	/* Precondition below! checking the dates validity.*/
	if(day_check(day, month, year) == 1){
		printf("This is not a valid date. Please enter a valid date.\n");
		return 0;
	}
	/* Precondition above! checking the dates validity.*/


    day_returned = zeller_method(day, month, year); /* Day is calculated with Zeller's congruence */

    return day_returned; /* Function returns; 0 if it is Monday , ... , 7 if it is Sunday. */
}

int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year){

	int months[20],i,temp_year,temp_month,total_day;	/* days of each month are stored in an array */
	int month_difference,year_difference;			 	/* i used in loop */

											/* temp_year and temp_month are a temporary variables which represents
											years and months between ending and starting points. */

											/* total day is the value which will be returned */

											/* month_difference and year_difference are the difference 
											of starting and ending points. It is used in the 
											loops for control the counting process. */

	/* Precondition below! checking the dates validity.*/
	if(day_check(start_day, start_month,start_year) == 1){
		printf("This is not a valid date. Please enter a valid date.\n");
		return 0;
	}
	if(day_check(end_day, end_month, end_year) == 1){
		printf("This is not a valid date. Please enter a valid date.\n");
		return 0;
	}
	/* Precondition above! checking the dates validity.*/

	
	/* Days are assigned each month. months[0] = January, ..., months[11] = December.*/
	months[0] = 31; months[1] = 28; months[2] = 31; months[3] = 30; months[4] = 31; months[5] = 30; months[6] = 31;
	months[7] = 31; months[8] = 30; months[9] = 31; months[10] = 30; months[11] = 31;

	temp_month = start_month; /* temp_month will be used in the second loop */
	temp_year = start_year; /* In loop temp years will be increased since it is equal to year_difference */

	total_day = 0;

	
	/* Determining the differences according to start_month and end_month */
	if(start_month > end_month){

		month_difference = end_month - start_month + 12;
		year_difference = end_year - start_year - 1;

		if( ( ((end_year-1) % 4 == 0) && ((end_year-1) % 100 != 0)) || ((end_year-1) % 400 == 0) ){
			total_day = 1;
		}

	}
	else{

		month_difference = end_month - start_month;
		year_difference = end_year - start_year;

	}
	/* Determining the differences according to start_month and end_month */
	

	
	/* In the first loop days are counted with the information of total days in each year */
	for(i = 0; i < year_difference; i++,temp_year++){

		/* Checking if that year is leap year or not */
		if( ( (temp_year % 4 == 0) && (temp_year % 100 != 0)) || (temp_year % 400 == 0) ){

			if((i == 0) && (start_month > 2)){
				total_day = total_day + 365;
			}
			else{
				total_day = total_day + 366; /* If it is there is one more day in that year */
			}
			

		}

		else{
			total_day = total_day + 365; /* If it is not a leap year then there are 365 days. */
		}

	}

	


	/* In this loop, calculating the total days between start_month and end_month. */
	for(i = 0; i < month_difference; i++,temp_month++){

		/* Checking if it is a leap year's february or not. */
		if((temp_month-1) % 12 == 1){

			if(( (end_year % 4 == 0) && (end_year % 100 != 0) ) || (end_year % 400 == 0) ){

				total_day = total_day + months[(temp_month - 1) % 12] + 1;
			}
			else{

				total_day = total_day + months[(temp_month-1) % 12];
			}
		}
		/* Checking if it is a leap year's february or not. */
		
		else{

			total_day = total_day + months[(temp_month-1)%12];
		}
		
	}

	total_day = total_day + (end_day - start_day);

	return total_day;
}

double find_angle(double a, double b, double c){

	double vb,vc,angle; /* vb = median of b side */ 
						/* vc = median of c side */

	if(triangle_check(a,b,c) == 1){ /* Checking if triangle can be drawed with given lengths */

		printf("It is not possible to draw a triangle with these sides.\n");
		
		return 0;
	}

	/* Calculating medians value with Apollonius's Theorem. */

	vb = sqrt((0.5 * a * a)  + (0.5 * c * c) - (0.25 * b * b)); 
	vc = sqrt((0.5 * b * b) + (0.5 * a * a) - (0.25 * c * c));

	/* Calculating the angle with Cosine Theorem. */
	angle = acos(((vb * vb) / (1.5 * 1.5) + (vc * vc) / (1.5 * 1.5) - a * a) / ((2 * vb * vc) /(1.5 * 1.5)));

	return angle;
}

void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border){

	char vertical;				/* Variable for '|' */						
	int num_of_spaces;			/* It will be used for printing first column's value center aligned */


	/* PRECONDITION BELOW */
	if((digit_counter(r11) > 5) || (digit_counter(r21) > 5) || (digit_counter(r31) > 5)){

		printf("Please enter POSITIVE integer which has at most five digits.(for the first column)\n");
		return;
	}
	/* PRECONDITION ABOVE */


	vertical = '|';

	/* Printing the first line and corners */

	printf("%c%c%c",0xE2,0x94,0x8C);
	print_line(border,border, 58);
	printf("%c%c%c\n",0xE2,0x94,0x90);

	/* First line and corners are printed. */

	

	/* Printing the first row */
	printf("%c", vertical);

	printf("      Row 101      %c    Row ABCDGEF    %c    Row XYZ123%5c\n%c",vertical,vertical,vertical,vertical);

	print_line(border,vertical, 58);
	/*-------- First row is printed -------- */

	num_of_spaces = (19 - digit_counter(r11)) / 2; /* Calculating the space needed for printing center aligned */
	r12 = two_decimal_digits(r12);				   /* Converts the number to at most 2 decimal digit. */

		/*-------- Printing the second row -------- */


	/* Printing the second row's first column center aligned. */
	printf("%c\n%c",vertical,vertical);	

	if(digit_counter(r11) % 2 == 0){			   /* This row is being prevented from gliding by these conditions. */
		print_line(' ',' ',num_of_spaces + 1);
	}

	else{
		print_line(' ',' ',num_of_spaces);
	}
	
	printf("%u",r11);
	print_line(' ',' ',num_of_spaces);
	/* Second row's first column is printed center aligned. */

	printf("%c%-11.7g%9c%+-8d%11c\n%c",vertical,r12,vertical,r13,vertical,vertical);

	print_line(border,vertical, 58);
		
		/*-------- Second row is printed -------- */


	num_of_spaces = (19 - digit_counter(r21)) / 2;	/* Calculating the space needed for printing center aligned */
	r22 = two_decimal_digits(r22);					/* Converts the number to at most 2 decimal digit. */

		/*-------- Printing the third row -------- */

	/* Printing the third row's first column center aligned. */
	printf("%c\n%c",vertical,vertical);

	if(digit_counter(r21) % 2 == 0){				/* This row is being prevented from gliding by these conditions. */
		print_line(' ',' ',num_of_spaces + 1);
	}

	else{
		print_line(' ',' ',num_of_spaces);
	}

	printf("%u",r21);

	print_line(' ',' ',num_of_spaces);
	/* Third row's first column is printed center aligned. */

	printf("%c%-11.7g%9c%+-8d%11c\n%c",vertical,r22,vertical,r23,vertical,vertical);

	print_line(border,vertical, 58);

		/*-------- Third row is printed -------- */

	

	num_of_spaces = (19 - digit_counter(r31)) / 2;	/* Calculating the space needed for printing center aligned */
	r32 = two_decimal_digits(r32);					/* Converts the number to at most 2 decimal digit. */

	/*-------- Printing the fourth row -------- */

	/* Printing the fourth row's first column center aligned. */
	printf("%c\n%c",vertical,vertical);

	if(digit_counter(r31) % 2 == 0){					/* This row is being prevented from gliding by these conditions. */
		print_line(' ',' ',num_of_spaces + 1);
	}

	else{
		print_line(' ',' ',num_of_spaces);
	}
	printf("%u",r31);

	print_line(' ',' ',num_of_spaces);
	/* Fourth row's first column is printed center aligned. */

	printf("%c%-11.7g%9c%+-8d%11c\n",vertical,r32,vertical,r33,vertical);

		/*-------- Fourth row is printed -------- */

	/* Printing the last line and corners. */
	
		printf("%c%c%c",0xE2,0x94,0x94);
		print_line(border,border, 58);
		printf("%c%c%c\n",0xE2,0X94,0X98);
	
	/* Last line and corners are printed. */
}

/*----------------------------- FUNCTIONS USED -----------------------------*/

int day_check(int day, int month, int year){/* Function checks dates validity. */
											/* If it is not valid it returns 1. */
											/* If it is valid it returns 0. */
	int months[20];

	if((day <= 0 || day > 31) || (month <= 0 || month > 12) || (year <= 0)){	/* Checking if there are any negatif input 
																				and checking the maximum day and month.*/
		return 1;																
	}

	/* Days are assigned each month. months[0] = January, ..., months[11] = December.*/
	months[0] = 31; months[1] = 28; months[2] = 31; months[3] = 30; months[4] = 31; months[5] = 30; months[6] = 31;
	months[7] = 31; months[8] = 30; months[9] = 31; months[10] = 30; months[11] = 31;

	
	/* Checking the day inputs are valid or not */
	if( ((month == 2) && ((year % 4 == 0) && (year % 100 != 0) )) || ((month == 2) && (year % 400 == 0))){

		/* If it is leap year's february it shouldn't be bigger than 29 */
		if(day > 29){
			return 1;
		}
		else{
			return 0;
		}
	}

	else if(day > months[month - 1]){
		return 1;
	}	
	
	else{
		return 0;
	}

}

int triangle_check(double a, double b, double c){ /* Function checks that triangle can be drawed with given values. */
												  /* If it is not it returns 1. */
												  /* If it is it returns 0. */

	if(a <= 0 || b <= 0 || c <= 0){ /* Checking if there are any negative value. */

		return 1;
	}

	if((a >= (c+b)) ||  (b >= (a+c)) || (c >= (a+b))){ /* Checking the triangle rule */

		return 1;
	}

	else{

		return 0;
	}
}

int zeller_method(int day, int month, int year){ /* This algorithm is written according to Zeller's Congruence */
												 /* Function finds the day of given date. */

	int ftwo, ltwo, result;  /* ftwo is the first two numbers of the year. */
							 /* ltwo is the last two numbers of the year. */
							 /* result is the value that will be returned. */

	/* In this method, months are start with March. January and February are the last two months of the year */
							
	if(month == 1){

		month = 11;
		year = year - 1;
	}

	else if(month == 2){

		month = 12;
		year = year - 1;

	}

	else{

		month = month - 2;
	}
	/* In this method, months are start with March. January and February are the last two months of the year*/


	ltwo = year % 100;  /* Calculating the last two numbers of the year */
	
	year = year / 100;	
	
	ftwo = year;		/* Calculating the first two numbers of the year */
	
	
	/* The day is calculated with this formula */
	result = day + (((13 * month) - 1) / 5) + ltwo + (ltwo / 4) + (ftwo / 4) - 2 * ftwo - 1;


	/* result must between 6 and 0. If it is not adding or subtracting 7 till number comes that interval. */
	while(result < 0){ 	
			
		result = result + 7;
	}
	
	
	while(result > 6){
			
		result = result - 7;

	}
	/* result must between 6 and 0. If it is not adding or subtracting 7 till number comes that interval. */

	return result + 1;	/* Function returns; 0 if it is Monday , ... , 7 if it is Sunday. */

}

void print_line(char border,char vertical, int num){	/* Function is used in printing line in table */
	int i;												/* border and vertical variable are printed, num is used
														for how many columns are printed. */

	for(i = 1; i < num+1; i++){	
		
		if(i % 20 == 0){								/* every 20th column will be printed according to
														given vertical char */
			printf("%c", vertical);
		}

		else{

			printf("%c", border);
		}
	}

}

int digit_counter(unsigned int num){					/* Function counts number of digits of given number. */

	int counter;

	counter = 0;

	while(num > 0){

		num = num / 10;
		counter++;
	}

	return counter;
}

double two_decimal_digits(double num){ /* This function converts double number to double number which has at most 2 digits 
									   after decimal with rounding before. */
									   /* Examples: 2.483 -> 2.48 -- 1.999 -> 2 -- 5.915 -> 5.92 */
 	
 	int temp,flag;					   /* temp is used in type casting(double to int) and calculating */
									   /* flag will be used in case num is negative */	

	flag = 0;

	if(num < 0){					   /* Checking if num is a negative number. */

		num = num * (-1);
		flag = 1;
	}

	num = num * 1000;				   /* Saving the 3 digits after the decimal point and losing the unnecessary ones. */
	
	temp = (int)num;				   /* Casting the variable double to int and saving the value to temp. */

	if((temp % 10) < 5){
		temp = temp / 10;			   /* If the last number of temp is lesser than 5, then no need to round it up */
	}
	else{							   /* If the last number of temp is bigger or equal to 5,then after dividing by 10 
									   temp will be rounded up */
		temp = temp / 10;
		temp++;
	}

	num = (double)temp;					/* Casting temp to double and assign it to num. */

	num = num / 100;					/* Double number will not lost digit after dividing. */

	if(flag == 1){						/* Checking whether the num was negative or not. */

		return num*(-1);
	}

	else{

		return num;
	}

}
/*----------------------------- FUNCTIONS USED -----------------------------*/

