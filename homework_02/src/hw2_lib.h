/*
** hw2_io.h:
**
** The header file declaring library functions.
**
*/

int find_weekday_of_data(int day, int month, int year);

int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year);

double find_angle(double a, double b, double c);

void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border);


int zeller_method(int day, int month, int year); /* Finds the day of given date, according to Zeller's Congruence. */

void print_line(char border,char vertical,int num); /* Prints line with given parameters, num is for how many time it prints */

int day_check(int day, int month, int year);        /* Checks if the given date is valid date or not */

int triangle_check(double a, double b, double c);   /* Function checks that triangle can be drawed with given values. */ 

double two_decimal_digits(double num);  /* This function converts double number to double number which has at most 2 digits 
                                       after decimal with rounding before. */

int digit_counter(unsigned int num);    /* Function counts number of digits of given number. */
