#include <stdio.h>

#define MAX_CUSTOMER 50				/* MAX_CUSTOMER is the maximum number which can be kept in the system same time. */

typedef struct {					/* Customer type is defined. */
	char name[30];					/* Labels: 0 -> employee, 1 -> retired, 2 -> student, 3 -> unemployed, 4 -> other */
	int age;
	int label;
}customer_t;

void banking_system();	
int scan_customer(customer_t customers[], int num);
void insert_to_seq(customer_t customers[],int index);
int find_index_loc(customer_t customers[],int limit,int index);
int find_seg_end(customer_t customers[],int index);
int find_limit(int label);
int check_limit_overflow_smaller(customer_t customers[],int index);
int check_limit_overflow_bigger(customer_t customers[],int index);
void discard_from_seq(customer_t customers[],int index);

int main(){

	banking_system();				/* Calling the function which provides banking system. */
	return 0;						/* Main function returns 0. */
}/* End of main. */
/* ======================================================================================================= */

/*
*	This function is the essential function which displays menu and does ordering, processing customers in a proper way.	
*/
void banking_system(){
	int counter,input;						/* Struct array and variables are declared. */
	customer_t customers[MAX_CUSTOMER+1];

	/* counter variable is a variable that stores the information of how many customer is at the system at that moment. */

	counter = 0;	input = 0;				/* 0 must be assigned variables. */

	printf("\n\n\n******** Banking System *********\n\n\n");	/* Title is printed. */

	while(input != 3){						/* Loop iterates till user enters 3. */

		input = scan_customer(customers,counter);	/* Taking the inputs from user. */

		if(input == 1){								/* If input is 1 then user wants to add customer. */

			insert_to_seq(customers,counter);		/* Calling the function which inserts customer to sequence. */
			counter++;								/* Increment counter for the next user. */
		}
		else if(input == 2){						/* If input is 2 then user wants to proceed. */
			discard_from_seq(customers,counter);	/* Calling the function which discards customer from sequence. */
			counter--;								/* Counter should be decremented, because total user decreased. */
		}
	}/* End of iteration. */
}/* End of function. */
/* ======================================================================================================= */

/*
*	This function takes input from user properly, and displays menu.
*	Function returns operator input.(1 -> add, 2 -> proceed, 3 -> terminate, 0 -> do nothing)
*/
int scan_customer(customer_t customers[], int num){
	int op_input,i;									/* i is used like index and op_input is for taking input. */

	printf("\nCurrent sequence: ");

	for(i = 0; i < num; i++){						/* Printing the current sequence. */
		
		if(i != num - 1)	printf("%d-", customers[i].label);
			
		else	printf("%d", customers[i].label);			
	}

	printf("\n");
	
	printf("\n1-Add customer\n\n2-Process customer\n\n3-Stop the program\n\n");	
	printf("Enter the operation(1,2,3) -> ");
	
	scanf("%d", &op_input);				/* Taking the operator input .*/

	if(op_input == 1){

		if(num >= MAX_CUSTOMER){		/* Checking if MAX_CUSTOMER is reached. */
			printf("\nSystem can keep at most %d people same time, Therefore please proceed before adding.\n",MAX_CUSTOMER);
			op_input = 0;
		}
		
		else{							/* If max number is not reached take other inputs. */

			printf("\nPlease enter the name of the customer: ");
			scanf("%s", customers[num].name);
			printf("\nPlease enter the age of the customer: ");
			scanf("%d", &customers[num].age);
			if(customers[num].age < 0){			/* Checking if age is valid. */
				printf("\nAge cannot be negative! Please enter valid age.\n");
				op_input = 0;
			}
			else{								/* If age is valid then, label can be taken. */
				printf("\nPlease enter the label of the customer: ");
				scanf("%d", &customers[num].label);

				if(customers[num].label < 0 || customers[num].label > 4){	/* Checking if label is valid. */
					printf("\nLabel must between 0 and 4(including 0 and 4)! Please enter valid label.\n");
					op_input = 0;
				}
			}
		}	
	}
	else if(op_input == 2){				/* If input is 0 user wants to process. */

			if(num == 0){				/* Checking if are there any customer to proceed. */
				printf("\nThere is not any customer in bank system sequence.\n");
				op_input = 0;
			}		
	}
	else if(op_input == 3)				/* Checking if user wants to terminate program. */
		printf("\nProgram is stopped! Exiting...\n\n");
	
	else								/* If operator input is invalid, print warning message to user. */
		printf("\nINVALID INPUT! Please enter valid input.\n\n");
	
	return op_input;					/* Returning the operator input. */
}/* End of function. */
/* ======================================================================================================= */

/*
*	This function inserts customer to the current sequence in wanted way.
*	Main point of that function is, finds the location where customer is inserted, and inserts customer to the sequence with
*  sliding array to the right.
*/
void insert_to_seq(customer_t customers[],int index){
	int i,loc,limit;								/* i is used as counter and index, loc is location where will the customer
													is inserted, limit is every label's limit on a sequence. */
	customer_t temp;		/* Temporary customer is declared for swapping. */
	loc = index;
	

	limit = find_limit(customers[index].label);	/* Calculating limit according to customer's label. */

	/* Finding the location where will be the customer inserted on struct array. */	
	loc = find_index_loc(customers,limit,index);

	/* If loc still equals to index, then check if there is overflow for smaller labels, and get new location. */
	if(loc == index && customers[index].label > 0)		
		loc = check_limit_overflow_smaller(customers,index);
		
	/* If loc still equals to index, then check if there is an overflow for bigger labels, and get new location.*/
	if(loc == index && customers[index].label < 4)		
		loc = check_limit_overflow_bigger(customers,index);

	if(loc != index && loc >= 0){				/* If function returns given index there is no need for sliding. */

		temp = customers[index];				/* Assigning temporary customer to keep the information. */

		/* This iteration slides array to the right from wanted point. */
		for(i = index; i >= loc; i--)	customers[i+1] = customers[i];	
			
		customers[loc] = temp;			/* Assigning the stored information to the location. */
	}
}/* End of function. */
/* ======================================================================================================= */

/*
*	Function selects limit value according to the label with switch case statement.
*/
int find_limit(int label){
	int limit;
	limit = 0;
	switch(label){					/* Selecting the limit according to the label. */
		case 0: limit = 5; break;
		case 1: limit = 3; break;
		case 2: limit = 3; break;
		case 3: limit = 2; break;
		case 4: limit = 2; break;
	}/* End of selection. */

	return limit;
}/* End of function. */
/* ======================================================================================================= */

/*
*	This function finds the location where the customer should be inserted.
*	It consists of 3 part according to the flag's value.
*	Function might be recursive if some possibilites occur.
* 	Function returns wanted location as an array index.
*/
int find_index_loc(customer_t customers[],int limit,int index){
	int i,j,loc,flag,seg_end;
	
	loc = index;	flag = 1;						/* flag's value's meaning is explained on their condition. */

	seg_end = find_seg_end(customers,index);			/* Finding where the segment ends. */

	for(i = 0; i < seg_end && flag == 1; i++){			/* Loop iterates till seg_end is reached or flag isn't equal to 1. */

		if(customers[i].label == customers[index].label){	/* If same label is found, then check if there is a place. */

			flag = 2;			j = 1;						/* If flag equals 2, It means label we want to insert is on the
															sequence. */

			while(j < limit){						/* This iteration searches for the place for the inserting customer to
													the right side of customer which has same label. */
				
				if(i+j == index){					/* This condition checks, if current checked customer is end of the 
													sequence. If it is, then no need for going right anymore. */

					flag = 0;	break;				/* Loop can be terminated if this condition checks. */
				}

				else if(customers[i+j].label != customers[index].label){  /* If right side of found customer's label 
																		 is not equal to the customer's which is wanted to be
																		 inserted, then there is a place to the customer. */				
					loc = i+j;	flag = 0;	break;
				}
				j++;
			}/* End of while loop. */
		}
	}/* End of iteration. */

	if(flag == 1){		/* If flag is equal to 1 that means there aren't any label on the sequence which is equal to
						label which wanted to be inserted to sequence. */

		for(i = 0; i < index; i++){	/* This loop inserts customer to the left side of the first customer which has bigger label.*/ 

			if(customers[index].label < customers[i].label){	/* If that customer is found, then location is found. */

				loc = i;	break;
			}
		}
		/* If i equals to index, that means place cannot be found for inserting. */
		if(i == index)	loc = seg_end;			
	}

	else if(flag == 2){		/* If flag equals 2 that means, there are customers which have same label, but there aren't any place
							to insert on that segment. */
		/* Calling same function from the other segment's initial place. */
		loc = find_index_loc(&customers[seg_end],limit,index - seg_end);

		loc += seg_end;		/* Add the substracted value during passing the values. */	
	}
	return loc;									/* Returning the location where should be inserted. */
}/* End of function. */
/* ======================================================================================================= */

/*
*	Loop finds where the segment ends.
*	For Example if sequence is like this -> 0-0-1-2-2-4-1 function returns 6.
*/
int find_seg_end(customer_t customers[],int index){
	int retval,i;

	retval = index;						/* If segment does not changes index will be returned. */

	for(i = 0; i < index-1; i++){		/* Loop looks for where segment changes. */

		if(customers[i].label > customers[i+1].label){	/* If this condition checks, then segment changing location is found.*/
			retval = i+1;
			break;
		}  
	}

	return retval;	/* Returns the location which is on the right side of last element of that segment. */
}/* End of function. */
/* ======================================================================================================= */

/*
*	This function returns inserting location for bigger numbers into smaller numbers.
*	This function checks if any number is overflowed its limit.
*	If there is an overflow, function returns proper location for inserting.
*	For Example : sequence is like 0-0-0-0-0-0 and 1 labeled customer wants to enter the sequence
*  function returns 5. After implementation sequence will be like 0-0-0-0-0-1-0.	  
*/
int check_limit_overflow_smaller(customer_t customers[],int index){
	int loc,limit,label,i,j,counter;
	
	loc = index;		counter = 0;		/* counter is for counting repetition time. */

											/*This loop checks each label, if it is overflowed its limit. */
	for(label = customers[index].label-1; label >= 0 && counter != -2; label--){
		
		limit = find_limit(label);				/* Calculating limit for each label. */
		
		for(i = 0; i < index; i++){				/* This loop searches in the current sequence. */

			if(customers[i].label == label){	/* If wanted label is found, check if it is overflowed. */
				
				j = 1;
				while(j <= limit){				/* If limit is reached, end loop. */

					if(i + j == index){			/* If end of sequence is reached, end loop.*/

						i = index;	break;
					}
					else if(customers[i+j].label == label)	counter++;		/* If wanted number is found, increment counter. */
						
					j++;
				}/* End of while loop. */
			}
			if(counter == limit){								/* If counter is equal to limit, it means there is an overflow. */
				loc = i+j-1; 		counter = -2; 		break;	/* Assign the location founded and exit from loops.*/
			}
			counter = 0;
		}/* End of second loop. */		
	}/* End of main iteration. */

	return loc;				/* Returning the proper location for customer. */
}/* End of function. */
/* ======================================================================================================= */

/*
*	This function returns inserting location for smaller numbers into bigger numbers.
*	This function checks if any number is overflowed its limit.
*	If there is an overflow, function returns proper location for inserting.
*	For Example : sequence is like 2-2-2-3-3-3 and 2 labeled customer wants to enter the sequence
*  function returns 5. After implementation sequence will be like 2-2-2-3-3-2-3.	  
*/
int check_limit_overflow_bigger(customer_t customers[],int index){
	int loc,limit,label,i,j,counter;
	
	loc = index;		counter = 0;					/* counter is for counting repetition time. */

														/*This loop checks each label, if it is overflowed its limit. */
	for(label = customers[index].label+1; label <= 4 && counter != -2; label++){

		limit = find_limit(label);						/* Calculating limit for each label. */

		for(i = 0; i < index; i++){						/* This loop searches in the current sequence. */
			
			if(customers[i].label == label){			/* If wanted label is found, check if it is overflowed. */
				
				j = 1;
				while(j <= limit){						/* If limit is reached, end loop. */

					if(i + j == index){					/* If end of sequence is reached, end loop. */

						i = index;		break;
					}
					else if(customers[i+j].label == label) 	counter++;	/* If wanted label is found, increment counter. */

					j++;
				}/* End of while loop. */
			}
			if(counter == limit){							/* If counter is equal to limit, it means there is an overflow. */
				loc = i+j-1;   counter = -2;		break;	/* Assign the location founded and exit from loops.*/					
			}
			counter = 0;
		}/* End of second loop. */
	}/* End of main iteration. */

	return loc;					/* Returning the proper location for customer. */
}/* End of function. */
/* ======================================================================================================= */

/*
*	Function discards inital customer from sequence, and prints proceed customer's name.
*/	
void discard_from_seq(customer_t customers[],int index){
	int i;

	printf("\nProceed customer is %s.\n",customers[0].name);		/* Name is printed. */

	for(i = 0; i < index; i++)		customers[i] = customers[i+1];	/* Sliding array to the left. */

}/* End of function. */