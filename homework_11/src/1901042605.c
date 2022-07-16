#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Movie_Budget{		/* Movie_Budget struct defined. */
	int budget,year;
	char *name;
	struct Movie_Budget *next;
}Movie_Budget;

typedef struct Movie_Name{			/* Movie_Name struct defined. */
	char *genre,*name;
	double score;
	struct Movie_Name *next;
}Movie_Name;
												
void read_n_display_movie_file(char *file_name);	/* Function makes whole operation. */

/* Helper functions for reading file part. */
int read_movies_dynamically(char *file_name,Movie_Budget **budget_head,Movie_Name **name_head);
char *get_line(FILE *M);
char *read_name_dynamically(char *line);
void delete_ch_till_comma(char *line);
double read_double(char *line);
int delete_node1(char *name,Movie_Budget **budget_head);
void delete_node2(char *name,Movie_Name **name_head);
void sorted_insert(Movie_Budget *new_node_data,Movie_Budget **budget_head);
void insert_end(Movie_Name *new_node_data,Movie_Name **name_head);

/* Helper functions for user interaction part. */
int scan_input();
void print_sorted(Movie_Budget **budget_head,Movie_Name **name_head,int num);
void ask_and_print_budget(Movie_Budget *budget_head,Movie_Name *name_head,int num);
void ask_and_print_score(Movie_Budget *budget_head,Movie_Name *name_head,int num);
void ask_and_print_year(Movie_Budget *budget_head,Movie_Name *name_head,int num);
void ask_and_print_str(Movie_Budget *budget_head,Movie_Name *name_head,int num,char *str);
Movie_Name *find_movie1(char *name,Movie_Name *name_head);
Movie_Budget *find_movie2(char *name,Movie_Budget *budget_head);
void sort_budgets(Movie_Budget **budget_head);
void sort_genres(Movie_Name **name_head);
void sort_names(Movie_Name **name_head);
void sort_scores(Movie_Name **name_head);
void sort_years(Movie_Budget **budget_head);
void print_movie(Movie_Budget *budget_head,Movie_Name *name_head,int num);
void print_movie2(Movie_Budget *budget_head,Movie_Name *name_head,int num);
void print_genres(Movie_Name *name_head);		
void print_th_years(Movie_Budget *budget_head);
void print_th_scores(Movie_Name *name_head);
void print_single_mov(Movie_Budget *budget_head,Movie_Name *name_head);
void print_avg_score(Movie_Name *name_head,int num);
void print_genre_freq(Movie_Name *name_head);
void free_lists(Movie_Budget *budget_head,Movie_Name *name_head);

int main(){
	char file_name[] = "Movies.txt";		

	read_n_display_movie_file(file_name);		/* Function only accepts file name. */

	return 0;
}/* End of main */
/* ============================================================================================ */

/*
*	Function makes whole operation of reading and manipulating. It accepts only filename as a string.
*/
void read_n_display_movie_file(char *file_name){

	int input,num_of_movies;			/* i is used as an indis. */

	Movie_Budget *budget_head = NULL;	/* 2 different head pointers declared and null assigned. */
	Movie_Name *name_head = NULL;
	
	/* Storing whole information in linked list. Function returns number of movies. */
	num_of_movies = read_movies_dynamically(file_name,&budget_head,&name_head);	

	if(num_of_movies < 0)	/* If function returns -1, abort whole operation because file does not exists. */
		printf("\nThere is no file such \"%s\" Terminating...\n\n",file_name); 

	else{
		input = 0;				/* 0 can be assigned initially. */

		while(input != 8){			/* Loop iterates till 8 is entered. */
			input = scan_input();	/* Taking input from user. */
			switch(input){			/* Selecting the proper operation according to user input. */
				
				case 1:		print_sorted(&budget_head,&name_head,num_of_movies);		break;
				case 2:		print_genres(name_head);									break;
				case 3:		print_th_years(budget_head);								break;
				case 4:		print_th_scores(name_head);									break;
				case 5:		print_single_mov(budget_head,name_head);					break;
				case 6:		print_avg_score(name_head,num_of_movies);					break;
				case 7:		print_genre_freq(name_head);								break;

				case 8:  	/* Freeing the allocated memory for preventing memory leak. */
							free_lists(budget_head,name_head);
							printf("\nYou exitted. Terminating ...\n");	break;

				default:    printf("\nTRY AGAIN\n");					break;
			}/* End of selection. */
		}
	}
}/* End of Function. */
/* =========================================================================================== ;*/

/*
*	Function reads txt file, which name is given as a parameter.
*	Function accepts 2 more parameter and they are head of 2 distinct linked lists.
*	Function returns -1 if given file name does not exists, otherwise function returns total number of movies.
*	Whole reading operation is made dynamically.
*/
int read_movies_dynamically(char *file_name,Movie_Budget **budget_head,Movie_Name **name_head){
	
	char ch;
	FILE *M;	
	int num;								/* num is used for counting movie number and it will be returned.*/
	char *line = NULL;						/* line is declared for reading each line dynamically. */
	Movie_Name *name_node = NULL;			/* temporary nodes are declared and null is assigned to them. */
	Movie_Budget *budget_node = NULL;
	
	M = fopen(file_name,"r");

	if(M == NULL)	num = -1;		/* If file does not exists return num as -1 and abort all operations. */

	else{

		num = 0;

		do{
			fscanf(M,"%c",&ch);
		}while(ch != '\n' && ch != EOF);	/* Passing the title. */

		while(fscanf(M,"%c",&ch) != EOF){		/* Loop iterates till end of file is reached. */

			name_node = (Movie_Name *)malloc(sizeof(Movie_Name));
			budget_node = (Movie_Budget *)malloc(sizeof(Movie_Budget));

			fseek(M,-1,SEEK_CUR);				/* After first character is read go 1 character left for reading properly. */

			line = get_line(M);					/* Getting line as a dynamically allocated string. */
			
			/* Checking if line has stored properly, strlen() is used because it must be at least 4 "," on the line. */
			if(line != NULL && !(strlen(line) < 4)){	

				/* If it is unknown assign -1 to budget. */		
				if(line[0] == 'u' || line[0] == 'U')	budget_node->budget = -1;
				else budget_node->budget = (int)read_double(line);		/* If it isn't unknown read int from line. */	

				delete_ch_till_comma(line);							/* Deleting all characters from start to first comma. */
				name_node->genre = read_name_dynamically(line);		/* Reading genre name from line string and assign pointer. */
				delete_ch_till_comma(line);
				budget_node->name = name_node->name = read_name_dynamically(line);	/* Reading name from line. */
				delete_ch_till_comma(line);
				name_node->score = read_double(line);			/* Reading initial double number from line. */
				delete_ch_till_comma(line);
				budget_node->year = (int)read_double(line);		/* Casting double to integer while assigning. */

				budget_node->next = NULL;
				name_node->next = NULL;

				/* All informations are stored, to lists. */

				/* This condition checks if same named movie is in the list.*/
				if(delete_node1(budget_node->name,budget_head)){ /* If it is, deletes the old version and decreases num. */
					delete_node2(budget_node->name,name_head);
					num--;
				}
				/* budget_head list must be sorted, other list can be inserted from end. */
				sorted_insert(budget_node,budget_head);		/* Inserting the nodes properly. */
				insert_end(name_node,name_head);
				num++;
			}
			
			free(line);			/* Freeing the all temporary usage. */
			free(budget_node);		
			free(name_node);			
		}/* End of iteration. */
		fclose(M);					/* If iteration ends, file can be closed. */
	}
	return num;						/* Returning the result. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function reads line from file and returns char pointer.
*/
char *get_line(FILE *M){

	int i,j,flag;
	char ch,*str_temp = NULL,*line = NULL;	/* Assigning all pointers to NULL. */

	i = 0;	flag = 0;
	
	do{

		flag = fscanf(M,"%c",&ch);						/* Reading character by character. */
		i++;
		line =(char *)calloc(i+1,sizeof(char));			/* Allocating memory as size of i. */

		for(j = 0; j < i-1; j++) line[j] = str_temp[j];	/* Assigning saved characters to line. */

		line[i-1] = ch;									/* Assigning character which is just read. */	

		free(str_temp);									/* Free allocated memory. */

		str_temp = line;								/* temporary string points new array. */

	}while(ch != '\n' && flag != EOF);	/* Loop iterates till newline or end of file is reached. */

	line[i-1] = '\0';									/* Assigning null character to last element. */

	return line;										/* Returning line pointer. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function allocates memory for name pointer, according to the line string and returns it.
*/
char *read_name_dynamically(char *line){

	char *name = NULL;	/* Assigning NULL first. */
	int i;

	for(i = 0; line[i] != ','; i++); 	/* Counting the characters before comma exist. */

	name = (char *)calloc(i+1,sizeof(char));	/* Allocating memory for name. */

	for(i = 0; line[i] != ','; i++) name[i] = line[i];	/* Assigning characters till comma exists. */

	name[i] = '\0';	/* Assigning the NULL char. */
	return name;
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function delete characters till comma exists.
*	Example: BEFORE ---> 123421,sample_line      <---->     AFTER ---> sample_line . 
*/
void delete_ch_till_comma(char *line){
	int i;
	char *temp;

	temp = calloc(strlen(line), sizeof(char));		/* Allocating memory for temp string. */
	i = 0;

	while(line[i] != ',' && line[i] != '\n') i++;		/* Counting the characters. */

	strcpy(temp,&line[i+1]);	/* Making the swap operation. */
	strcpy(line,temp);

	free(temp);					/* Freeing the memory that is allocated for temp string. */
}/* End of Function. */
/* =========================================================================================== */
double read_double(char *line){		/* Function reads first double number from string, and returns. */
	char *ptr;
	double num;

	num = strtod(line,&ptr);		/* Taking the first double number from line. */

	return num;						/* Returning number. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function deletes node according to the given name.
*	cur_ele means current element, pre_ele means previous element.
*	Function only works with Movie_Budget typed linked lists.
*	If function finds name deletes the node and returns 1, otherwise function returns 0.
*/
int delete_node1(char *name,Movie_Budget **budget_head){
	int ans;											
	Movie_Budget *cur_ele = NULL,*pre_ele = NULL;		/* Assigning null during declaration. */
	

	ans = 0;											/* 0 assigned initially. */
	cur_ele = pre_ele = *budget_head;					/* head of linked list assigned to pointers. */
	
	while(cur_ele != NULL &&
		 (strcmp(cur_ele->name,name) != 0)){	/* Loop iterates till, null or name found. */

		pre_ele = cur_ele;						/* If name cannot be found, go for next node. */
		cur_ele = cur_ele->next;	
	}/* End of iteration. */

	if(cur_ele != NULL){	/* If current element cannot be found, make the delete operation. */
		
		if(cur_ele == pre_ele)				/* If this condition checks, that means head pointer must be deleted. */
			*budget_head = cur_ele->next;
											
		else 								/* Previous element points where current elements point, address won't be lost. */	
			pre_ele->next = cur_ele->next;	
		
		ans = 1;
		free(cur_ele);						/* Free the memory allocated for node. */
	}
	return ans;								/* Return the result(1 or 0) */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function deletes node according to the given name.
*	cur_ele means current element, pre_ele means previous element.
*	Function only works with Movie_Name typed linked lists.
*/
void delete_node2(char *name,Movie_Name **name_head){
	Movie_Name *cur_ele = NULL,*pre_ele = NULL;			/* Assigning null during declaration. */
	
	cur_ele = pre_ele = *name_head;						/* head of linked list assigned to pointers. */
	
	while(cur_ele != NULL &&
		 (strcmp(cur_ele->name,name) != 0)){			/* Loop iterates till, null or name found. */
		pre_ele = cur_ele;
		cur_ele = cur_ele->next;						/* If name cannot be found, go for next node. */
	}/* End of iteration. */

	if(cur_ele != NULL){			/* If current element cannot be found, make the delete operation. */

		if(cur_ele == pre_ele)		/* If this condition checks, that means head pointer must be deleted. */
			*name_head = cur_ele->next;

		else						/* Previous element points where current elements point, address won't be lost. */
			pre_ele->next = cur_ele->next;
			
		free(cur_ele->name);		/* Free the memory allocated for node including name and genre pointers. */
		free(cur_ele->genre);
		free(cur_ele);
	}	
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function makes sorted insertion to budget_head with new_node_data.
*	
*/
void sorted_insert(Movie_Budget *new_node_data,Movie_Budget **budget_head){
	int flag;
	Movie_Budget *new_node,*cur_ele,*next_ele;
	
	new_node = (Movie_Budget *)malloc(sizeof(Movie_Budget));	/* Allocating memory for new node. */
	new_node->next = NULL;										/* Assigning all data to new node. */
	new_node->name = new_node_data->name;
	new_node->year = new_node_data->year;
	new_node->budget = new_node_data->budget;

	flag = 0;


	if(*budget_head == NULL ||
	  (*budget_head)->year < new_node->year){	/* If head is null or new node's year is greater insert new node as head. */

		new_node->next = *budget_head;
		*budget_head = new_node;
	}

	else if((*budget_head)->year == new_node->year &&
			(*budget_head)->budget < new_node->budget){	/* If years are equal and new node's budget is greater insert head. */

		new_node->next = *budget_head;
		*budget_head = new_node;
	}

	else{

		cur_ele = *budget_head;
		next_ele = cur_ele->next;
		
		while(cur_ele != NULL && 
			 next_ele != NULL && !flag){			/* Loop iterates till proper place for node is found. */
			
			if(next_ele->year < new_node->year)		/* If year is less, insert here. */
				flag = 1;	

			else if(next_ele->year == new_node->year){	/* If years are equal check budget. */
				if(next_ele->budget < new_node->budget)
					flag = 1;
			}

			if(!flag){								/* If flag does not check continue. */
				cur_ele = next_ele;
				next_ele = cur_ele->next;
			}		
		}/* End of iteration. */

		new_node->next = next_ele;
		cur_ele->next = new_node;
	}
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function only accepts Movie_Name data type
*	Function makes insertion at the end with new_node_data
*/
void insert_end(Movie_Name *new_node_data,Movie_Name **name_head){
	Movie_Name *temp_node = NULL,*new_node = NULL;

	new_node = (Movie_Name *)malloc(sizeof(Movie_Name));	/* Allocating memory for new node. */
	new_node->next = NULL;									/* Assigning all data to new node. */
	new_node->name = new_node_data->name;
	new_node->genre = new_node_data->genre;
	new_node->score = new_node_data->score;
	
	if(*name_head == NULL){						/* If head is null make insertion at head. */
		new_node->next = *name_head;
		*name_head = new_node;
	}
	else{

		temp_node = *name_head;
		while(temp_node->next != NULL) temp_node = temp_node->next;		/* Loop iterates till end of list is found. */

		temp_node->next = new_node;
	}	
}/* End of Function. */
/* =========================================================================================== */
int scan_input(){	/* Function prints options, takes input from user, and returns it. */
	char ch;
	int input;

	printf("\n1. List of the Sorted Data\n2. List of the Genres\n3. List of the Movie Through the Years\n");
	printf("4. List of the Movie Through the Scores\n5. All Informations of a Single Movie\n6. Average of the IMDB Scores\n");
	printf("7. Frequence of the Genres\n8. Exit\n");
	printf("\nPlease Select an operation: ");
	
	scanf("%d", &input);
	ch = getchar();			/* Taking the newline character. */

	return input;
}/* End of Function. */
/* =========================================================================================== */

/* 
*	Function takes input from user calls the proper function for sorting.
*/
void print_sorted(Movie_Budget **budget_head,Movie_Name **name_head,int num){	
	int input,flag;
	flag = 0;

	do{
		printf("\n1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year\n");
		printf("\nPlease Select an operation: ");
		scanf("%d",&input);
		switch(input){	/* Selecting the proper operation. */
			case 1: sort_budgets(budget_head);	
					ask_and_print_budget(*budget_head,*name_head,num);			flag = 0;	break;
			case 2: sort_genres(name_head);
					ask_and_print_str(*budget_head,*name_head,num,"genre");		flag = 0;	break;
			case 3: sort_names(name_head);
					ask_and_print_str(*budget_head,*name_head,num,"name");		flag = 0;	break;
			case 4: sort_scores(name_head);
					ask_and_print_score(*budget_head,*name_head,num);			flag = 0;	break;
			case 5: sort_years(budget_head);
					ask_and_print_year(*budget_head,*name_head,num);			flag = 0;	break;
			default: printf("\nTRY AGAIN\n");									flag = 1;	break;
		}/* End of Selection. */
	}while(flag != 0);				/* Loop iterates till flag is equal to 0. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function sorts budgets as ascending order.
*	Function accepts only Movie_Budget type input.
*	temp_head and temp_head2 used for searching in the list
*	min variable holds minimum budget value.	
*/
void sort_budgets(Movie_Budget **budget_head){
	Movie_Budget *temp_head = NULL,*temp_head2 = NULL,*min = NULL;
	int flag;
	int number;							/* flag,number,*str temporarily used for swap operation. */
	char *str;

	min = temp_head = *budget_head;		/* Head of list is assigned to min and temp_head. */

	while(temp_head != NULL){			/* Loop iterates till end of list is reached. */
					
		flag = 0;
		temp_head2 = temp_head->next;	/* temp_head2 points the next element of linked list. */
		min = temp_head;		
	
		while(temp_head2 != NULL){		/* Loop iterates till starting from temp_head1 to end of list is completely checked. */ 

			if(temp_head2->budget < min->budget){	/* If lesser budget is found assign it to minimum. */
				flag = 1;
				min = temp_head2;
			}
			temp_head2 = temp_head2->next;		/* Point next node. */
		}/* End of iteration. */
		if(flag == 1){							/* If flag is 1, this means swap operation must be made. */

			str = temp_head->name;
			temp_head->name = min->name;
			min->name = str;

			number = temp_head->budget;
			temp_head->budget = min->budget;
			min->budget = number;

			number = temp_head->year;
			temp_head->year = min->year;
			min->year = number;
		}
		temp_head = temp_head->next;			/* Point next node. */
	}/* End of iteration. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function sorts genres as ascending alphabetical order.
*	Function accepts only Movie_Name type input.
*	temp_head and temp_head2 used for searching in the list
*	min variable holds minimum genre data.
*/
void sort_genres(Movie_Name **name_head){
	Movie_Name *temp_head = NULL,*temp_head2 = NULL,*min = NULL;
	int flag;
	double number;					/* flag,number,*str temporarily used for swap operation. */
	char *str;

	min = temp_head = *name_head;	/* Head of list is assigned to min and name_head. */
	
	while(temp_head != NULL){		/* Loop iterates till end of list is reached. */
		
		
		flag = 0;
		temp_head2 = temp_head->next;	/* temp_head2 points the next element of linked list. */
		min = temp_head;		

		while(temp_head2 != NULL){		/* Loop iterates till starting from temp_head1 to end of list is completely checked. */

			if(strcmp(temp_head2->genre,min->genre) < 0){	/* If strcmp returns negative, then assign data to minimum. */
				flag = 1;
				min = temp_head2;
			}
			temp_head2 = temp_head2->next;	/* Point next node. */
		}/* End of iteration. */
		if(flag == 1){						/* If flag is 1, this means swap operation must be made. */

			str = temp_head->name;
			temp_head->name = min->name;
			min->name = str;

			number = temp_head->score;
			temp_head->score = min->score;
			min->score = number;

			str = temp_head->genre;
			temp_head->genre = min->genre;
			min->genre = str;
		}
		temp_head = temp_head->next;		/* Point next node. */
	}/* End of iteration. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function sorts names as ascending alphabetical order.
*	Function accepts only Movie_Name type input.
*	temp_head and temp_head2 used for searching in the list
*	min variable holds minimum name data.
*/
void sort_names(Movie_Name **name_head){
	Movie_Name *temp_head = NULL,*temp_head2 = NULL,*min = NULL;
	int flag;
	double number;					/* flag,number,*str temporarily used for swap operation. */
	char *str;

	min = temp_head = *name_head;	/* Head of list is assigned to min and name_head. */
	
	while(temp_head != NULL){		/* Loop iterates till end of list is reached. */
		
		
		flag = 0;
		temp_head2 = temp_head->next;	/* temp_head2 points the next element of linked list. */
		min = temp_head;		

		while(temp_head2 != NULL){		/* Loop iterates till starting from temp_head1 to end of list is completely checked. */

			if(strcmp(temp_head2->name,min->name) < 0){	/* If strcmp returns negative, then assign data to minimum. */
				flag = 1;
				min = temp_head2;
			}
			temp_head2 = temp_head2->next;		/* Point next node. */
		}/* End of iteration. */
		if(flag == 1){							/* If flag is 1, this means swap operation must be made. */

			str = temp_head->name;
			temp_head->name = min->name;
			min->name = str;

			number = temp_head->score;
			temp_head->score = min->score;
			min->score = number;

			str = temp_head->genre;
			temp_head->genre = min->genre;
			min->genre = str;
		}
		temp_head = temp_head->next;			/* Point next node. */
	}/*End of iteration. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function sorts scores as ascending order.
*	Function accepts only Movie_Budget type input.
*	temp_head and temp_head2 used for searching in the list
*	min variable holds minimum score value.	
*/
void sort_scores(Movie_Name **name_head){
	Movie_Name *temp_head = NULL,*temp_head2 = NULL,*min = NULL;
	int flag;
	double number;					/* flag,number,*str temporarily used for swap operation. */
	char *str;

	min = temp_head = *name_head;	/* Head of list is assigned to min and temp_head. */
	
	while(temp_head != NULL){		/* Loop iterates till end of list is reached. */
		
		
		flag = 0;
		temp_head2 = temp_head->next;	/* temp_head2 points the next element of linked list. */
		min = temp_head;		

		while(temp_head2 != NULL){		/* Loop iterates till starting from temp_head1 to end of list is completely checked. */

			if(temp_head2->score < min->score){		/* If lesser budget is found assign it to minimum. */
				flag = 1;
				min = temp_head2;
			}
			temp_head2 = temp_head2->next;			/* Point next node. */
		}/* End of iteration. */
		if(flag == 1){								/* If flag is 1, this means swap operation must be made. */

			str = temp_head->name;					
			temp_head->name = min->name;
			min->name = str;

			number = temp_head->score;
			temp_head->score = min->score;
			min->score = number;

			str = temp_head->genre;
			temp_head->genre = min->genre;
			min->genre = str;
		}
		temp_head = temp_head->next;				/* Point next node. */
	}/*End of iteration. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function years scores as ascending order.
*	Function accepts only Movie_Budget type input.
*	temp_head and temp_head2 used for searching in the list
*	min variable holds minimum year value.	
*/
void sort_years(Movie_Budget **budget_head){
	Movie_Budget *temp_head = NULL,*temp_head2 = NULL,*min = NULL;
	int flag;
	int number;							/* flag,number,*str temporarily used for swap operation. */
	char *str;

	min = temp_head = *budget_head;		/* Head of list is assigned to min and temp_head. */
	
	while(temp_head != NULL){			/* Loop iterates till end of list is reached. */
			
		flag = 0;
		temp_head2 = temp_head->next;	/* temp_head2 points the next element of linked list. */
		min = temp_head;

		while(temp_head2 != NULL){		/* Loop iterates till starting from temp_head1 to end of list is completely checked. */

			if(temp_head2->year < min->year){	/* If lesser budget is found assign it to minimum. */
				flag = 1;
				min = temp_head2;
			}
			temp_head2 = temp_head2->next;	/* Point next node. */
		}/*End of iteration. */
		if(flag == 1){						/* If flag is 1, this means swap operation must be made. */

			str = temp_head->name;
			temp_head->name = min->name;
			min->name = str;

			number = temp_head->budget;
			temp_head->budget = min->budget;
			min->budget = number;

			number = temp_head->year;
			temp_head->year = min->year;
			min->year = number;
		}
		temp_head = temp_head->next;		/* Point next node. */
	}/*End of iteration. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function asks which operation will be made to user after sorting budgets in ascending order.
*	unknown counter is used for counting unknown budgets.
*	For example if the budgets in the lists are: (-1,-1,-1,2,5,7,9)  2 will be first number user can see.
*/
void ask_and_print_budget(Movie_Budget *budget_head,Movie_Name *name_head,int num){
	int input,flag,value_start,value_end,i,unknown_counter;

	Movie_Budget *temp_head = NULL,*max = NULL,*min = NULL;		/* min and max will be store minimum maximum values. */
	Movie_Name *temp_name = NULL;

	max = min = temp_head = budget_head;
	unknown_counter = 0;
	if(temp_head->budget == -1) unknown_counter++;				/* counting unknown budgets. */

	while(temp_head != NULL){			/* finding maximum and minimum values also counting unknown budgets. */

		if(temp_head->budget == -1) unknown_counter++;
		if(max->budget < temp_head->budget) max = temp_head;
		if(min->budget > temp_head->budget || min->budget == -1) min = temp_head;

		temp_head = temp_head->next;
	}

	flag = 0;

	do{
		printf("\n1. Single Selection\n2. Multiple Selection\n");
		printf("\nPlease Select an operation: ");
		scanf("%d", &input);						/* Taking the input from user. */

		switch(input){	/* Selecting the operation according to input. */

			case 1:		printf("\nEnter value(Start counting from 1): ");
						scanf("%d", &i);

						if(i > num-unknown_counter || i < 1){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}

						else{
							printf("\n%d. Movie\n\n",i);
							print_movie(budget_head,name_head,i+unknown_counter);	/* Printing the result. */
							flag = 0;	break;
						}

			case 2:		printf("\nEnter start value(Borders will be included): ");
						scanf("%d", &value_start);

						if(value_start > max->budget || value_start < 0){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}

						printf("\nEnter end value(Borders will be included): ");
						scanf("%d", &value_end);

						if(value_end < min->budget || value_end < value_start){
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}

						printf("\n\nMovies between %d and %d, sorted by the budget.\n\n",value_start,value_end);
						temp_head = budget_head;
						
						while(temp_head != NULL){	/* Loop iterates till end of list is reached. */

							/* Printing the values between value_start end value_end. */

							if(temp_head->budget >= value_start && temp_head->budget <= value_end){

								if(temp_head->budget == -1) printf("%-20s","Unknown");
								else printf("%-20d",temp_head->budget);		

								temp_name = find_movie1(temp_head->name,name_head);
								printf("%-15s%-50s",temp_name->genre,temp_head->name);
								printf(" %-5.1f%-5d\n",temp_name->score,temp_head->year);	
							}					
							temp_head = temp_head->next;	/* Look for next node. */
						}/* End of iteration. */

						flag = 0;	break;

			default: 	printf("\nTRY AGAIN\n"); 	  flag = 1; 	   break;
		}
	}while(flag != 0);	/* Loop iterates till flag equals to 0. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function asks which operation will be made to user after sorting scores in ascending order.
*	min and max variables are used for determining the maximum and minimum borders.
*/
void ask_and_print_score(Movie_Budget *budget_head,Movie_Name *name_head,int num){
	int input,flag,i;
	double value_start,value_end;

	Movie_Name *temp_head = NULL,*max = NULL,*min = NULL;
	Movie_Budget *temp_budget = NULL;

	max = min = temp_head = name_head;
	
	while(temp_head != NULL){	/* This loop finds maximum and minimum values.*/

		if(max->score < temp_head->score) max = temp_head;
		if(min->score > temp_head->score) min = temp_head;

		temp_head = temp_head->next;
	}

	flag = 0;

	do{
		printf("\n1. Single Selection\n2. Multiple Selection\n");
		printf("\nPlease Select an operation: ");
		scanf("%d", &input);						/* Taking the input from user. */

		switch(input){	/* Selecting the operation according to input. */

			case 1:		printf("\nEnter value(Start counting from 1): ");
						scanf("%d", &i);
						if(i > num || i < 1){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}
						else{
							printf("\n%d. Movie\n\n",i);
							print_movie2(budget_head,name_head,i);	/* Printing the result. */
							flag = 0;	break;
						}

			case 2:		printf("\nEnter start value(Borders will be included): ");
						scanf("%lf", &value_start);
						if(value_start > max->score || value_start < 0){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}
						printf("\nEnter end value(Borders will be included): ");
						scanf("%lf", &value_end);
						if(value_end < min->score || value_end < value_start){
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}
						printf("\n\nMovies between %.1f and %.1f, sorted by the score.\n\n",value_start,value_end);
						temp_head = name_head;
						
						while(temp_head != NULL){	/* Loop iterates till end of list is reached. */

							/* If current node's score is between value_start end value_end print all data properly. */

							if(temp_head->score >= value_start && temp_head->score <= value_end){

								temp_budget = find_movie2(temp_head->name,budget_head);
								if(temp_budget->budget == -1) printf("%-20s","Unknown");
								else printf("%-20d",temp_budget->budget);
								printf("%-15s%-50s",temp_head->genre,temp_head->name);
								printf(" %-5.1f%-5d\n",temp_head->score,temp_budget->year);	
							}					
							temp_head = temp_head->next;
						}
						flag = 0;	break;

			default: 	printf("\nTRY AGAIN\n"); 	  flag = 1; 	   break;
		}
	}while(flag != 0);		/* Loop iterates till flag equals to 0. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function asks to the user for operations onl list which is 
*	sorted in ascending order, and display data according to user's choice.
*/
void ask_and_print_year(Movie_Budget *budget_head,Movie_Name *name_head,int num){
	int input,flag,value_start,value_end,i;

	Movie_Budget *temp_head = NULL,*max = NULL,*min = NULL;
	Movie_Name *temp_name = NULL;

	max = min = temp_head = budget_head;
	
	while(temp_head != NULL){	/* Loop finds minimum and maximum data. */

		if(max->year < temp_head->year) max = temp_head;
		if(min->year > temp_head->year) min = temp_head;

		temp_head = temp_head->next;
	}

	flag = 0;

	do{
		printf("\n1. Single Selection\n2. Multiple Selection\n");
		printf("\nPlease Select an operation: ");
		scanf("%d", &input);						/* Taking the input from user. */

		switch(input){	/* Selecting the operation according to input. */

			case 1:		printf("\nEnter value(Start counting from 1): ");
						scanf("%d", &i);

						if(i > num || i < 1){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}

						else{
							printf("\n%d. Movie\n\n",i);
							print_movie(budget_head,name_head,i);		/* Printing the result. */
							flag = 0;	break;
						}

			case 2:		printf("\nEnter start value(Borders will be included): ");
						scanf("%d", &value_start);

						if(value_start > max->year || value_start < 0){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}

						printf("\nEnter end value(Borders will be included): ");
						scanf("%d", &value_end);

						if(value_end < min->year || value_end < value_start){
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}

						printf("\n\nMovies between %d and %d, sorted by the year.\n\n",value_start,value_end);
						temp_head = budget_head;
						
						while(temp_head != NULL){	/* Loop iterates till end of the list is reached. */

							/* If current node's year is between value_start and value_end print all data properly. */	
							if(temp_head->year >= value_start && temp_head->year <= value_end){

								if(temp_head->budget == -1) printf("%-20s","Unknown");
								else printf("%-20d",temp_head->budget);

								temp_name = find_movie1(temp_head->name,name_head);
								printf("%-15s%-50s",temp_name->genre,temp_head->name);
								printf(" %-5.1f%-5d\n",temp_name->score,temp_head->year);	
							}					
							temp_head = temp_head->next;
						}
						flag = 0;	break;

			default: 	printf("\nTRY AGAIN\n"); 	  flag = 1; 	   break;
		}
	}while(flag != 0);		/* Loop iterates till flag is equal to 0. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function interacts with user for sorted list which is sorted in ascending order according to given string.
*	str can be string or genre. Menu can be change according to input.
*/
void ask_and_print_str(Movie_Budget *budget_head,Movie_Name *name_head,int num,char *str){
	int input,flag,i,j;

	Movie_Name *temp_head = NULL;

	flag = 0;
	do{
		printf("\n1. Single Selection\n2. Multiple Selection\n");
		printf("\nPlease Select an operation: ");
		scanf("%d", &input);						/* Taking the input from user. */

		switch(input){	/* Selecting the operation according to input. */

			case 1:		printf("\nEnter value(Start counting from 1): ");
						scanf("%d", &i);
						if(i > num || i < 1){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}

						else{
							printf("\n%d. Movie\n\n",i);
							print_movie2(budget_head,name_head,i);	/* Printing the ith element of list. */
							flag = 0;	break;
						}

			case 2:		printf("\nEnter start value(Borders will be included): ");
						scanf("%d", &i);

						if(i > num || i < 1){						/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}

						printf("\nEnter end value(Borders will be included): ");
						scanf("%d", &j);

						if((j > num || j < 1) || (i > j)){
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}
						printf("\n\nMovies between %d and %d, sorted by the %s.\n\n",i,j,str);
						temp_head = name_head;
						
						while(temp_head != NULL && i <= j){		/* Loop iterates till end of list or j is reached. */

							print_movie2(budget_head,name_head,i);	/* printing the ith element of list. */			
							temp_head = temp_head->next;
							i++;
						}
						flag = 0;	break;

			default: 	printf("\nTRY AGAIN\n"); 	  flag = 1; 	   break;
		}
	}while(flag != 0);		/* Loop iterates till flag is equal to 0. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function prints single movie and its information properly.
*	This function searches Movie_budget typed list.
*	Movie_name typed list is searched after num is reached. Name of movie is used as a key. 
*	num determines which movie will be printed.
*/
void print_movie(Movie_Budget *budget_head,Movie_Name *name_head,int num){	
	Movie_Name *temp_name = NULL;
	Movie_Budget *temp_head = NULL;

	temp_head = budget_head;

	while(temp_head != NULL && num-1 > 0){	/* Iterate till num or end of list is reached. */

		temp_head = temp_head->next;
		num--;
	}
		
	if(temp_head != NULL){
		if(temp_head->budget == -1) printf("%-20s","Unknown");	/* Printing the first movie information. */
		else printf("%-20d",temp_head->budget);
				
		temp_name = find_movie1(temp_head->name,name_head);		/* Looking for other list with name information. */

		printf("%-15s%-50s",temp_name->genre,temp_head->name);	/* Printing the rest of data. */
		printf(" %-5.1f%-5d\n",temp_name->score,temp_head->year);
	}
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function prints single movie and its information properly.
*	This function searches Movie_name typed list.
*	Movie_budget typed list is searched after num is reached. Name of movie is used as a key. 
*	num determines which movie will be printed.
*/
void print_movie2(Movie_Budget *budget_head,Movie_Name *name_head,int num){	
	Movie_Budget *temp_budget = NULL;
	Movie_Name *temp_head = NULL;

	temp_head = name_head;

	while(temp_head != NULL && num-1 > 0){	/* Iterate till num or end of list is reached. */

		temp_head = temp_head->next;
		num--;
	}
		
	if(temp_head != NULL){

		temp_budget = find_movie2(temp_head->name,budget_head);		/* Looking for other list with name information. */
		if(temp_budget->budget == -1) printf("%-20s","Unknown");	/* Printing the movie data after finding movie. */
		else printf("%-20d",temp_budget->budget);
		printf("%-15s%-50s",temp_head->genre,temp_head->name);		
		printf(" %-5.1f%-5d\n",temp_head->score,temp_budget->year);
	}
		
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function finds the movie with name information.
*	Searching is done in Movie_Name typed list.
*	After finding node, returns it.
*/
Movie_Name *find_movie1(char *name,Movie_Name *name_head){
	Movie_Name *temp = NULL;

	temp = name_head;	

	while(temp != NULL){							/* Loop iterates till end of list is reached. */

		if(strcmp(temp->name,name) == 0)	break;
		temp = temp->next;
	}

	return temp;									/* Returning the founded node. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function finds the movie with name information.
*	Searching is done in Movie_Budget typed list.
*	After finding node, returns it.
*/
Movie_Budget *find_movie2(char *name,Movie_Budget *budget_head){
	Movie_Budget *temp = NULL;

	temp = budget_head;

	while(temp != NULL){							/* Loop iterates till end of list is reached. */

		if(strcmp(temp->name,name) == 0)	break;
		temp = temp->next;
	}
	return temp;									/* Returning the founded node. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function prints all genres in given linked list.
*	Purpouse is catching differences, if difference is caught make printing.
*/
void print_genres(Movie_Name *name_head){
	Movie_Name *cur_name = NULL,*pre_name = NULL;

	sort_genres(&name_head);			/* Before printing genres sort them. */
	cur_name = pre_name = name_head;	

	printf("\n%s\n",cur_name->genre);	/* Print initial genre. */
	cur_name = pre_name->next;

	while(cur_name != NULL && pre_name != NULL){	/* Loop iterates till end of list is reached. */
		
		if(strcmp(cur_name->genre,pre_name->genre) != 0)	/* If difference is caught print current one. */
			printf("%s\n",cur_name->genre);

		pre_name = pre_name->next;
		cur_name = cur_name->next;
	}/* End of iteration. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function prints through to the years.
*	While printing given borders are included.
*/
void print_th_years(Movie_Budget *budget_head){
	int op,flag,year;
	Movie_Budget *temp_head = NULL,*max = NULL,*min = NULL;

	max = min = temp_head = budget_head;
	
	while(temp_head != NULL){	/* Loop searches the maximum and minimum year value. */

		if(max->year < temp_head->year) max = temp_head;
		if(min->year > temp_head->year) min = temp_head;

		temp_head = temp_head->next;
	}

	flag = 1;

	do{
		printf("\nEnter a Year: ");				/* Taking the inputs from user. */
		scanf("%d",&year);

		if(year < 0) op = -1;					/* Year cannot be negative. */

		else{
			printf("Until (0) or Since (1) (%d will be included) %d: ",year,year);
			scanf("%d",&op);
		}
		
		switch(op){		/* Selecting the proper operation according to the input. */

			case 0:		
						if(min->year > year){	/* Minimum year cannot be bigger than given year. */
							printf("\nTRY AGAIN\n");	flag = 0;	    break;
						}
						else{

							temp_head = budget_head;
							printf("\n");
							
							while(temp_head != NULL){	/* Print all movies which has lesser or equal year than given year. */
								if(temp_head->year <= year) 	printf("%s\n",temp_head->name);
								temp_head = temp_head->next;
							}						
							printf("\n");				flag = 1;		break;					
						}
		
			case 1:		
						if(max->year < year){	/* Maximum year cannot be lesser than given year. */
							printf("\nTRY AGAIN\n");					flag = 0;		break;
						}

						else{

							temp_head = budget_head;
							printf("\n");

							while(temp_head != NULL){	/* Print all movies which has greater or equal year than given year. */
								if(temp_head->year >= year) 	printf("%s\n",temp_head->name);
								temp_head = temp_head->next;
							}							
							printf("\n");				flag = 1;		break;					
						}
		
			default:	printf("\nTRY AGAIN\n");		flag = 0;		break;	
		}/* End of selection. */
	}while(flag != 1);					/* Loop iterates till flag is equal to 1. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function prints through to the years.
*	While printing given borders are included.
*/
void print_th_scores(Movie_Name *name_head){
	int op,flag;
	double score;
	Movie_Name *temp_head = NULL,*max = NULL,*min = NULL;

	max = min = temp_head = name_head;
	
	while(temp_head != NULL){			/* Finding maximum and minimum scores. */				
		if(max->score < temp_head->score) max = temp_head;
		if(min->score > temp_head->score) min = temp_head;

		temp_head = temp_head->next;
	}

	flag = 1;

	do{
		printf("\nEnter a score: ");				/* Taking the inputs from user. */
		scanf("%lf",&score);
		if(score < 0 || score > 10) op = -1;
		else{
			printf("Less (0) or Greater (1) (%.1f will be included) %.1f: ",score,score);
			scanf("%d",&op);
		}
		
		switch(op){		/* Selecting the proper operation according to the input. */

			case 0:		
						if(min->score > score){		/* Checking validity. */
							printf("\nTRY AGAIN\n");	flag = 0;	    break;
						}
						else{
							temp_head = name_head;
							printf("\n");
							
							while(temp_head != NULL){	/* Print movies which has lesser or equal score. */
								if(temp_head->score <= score) 	printf("%s\n",temp_head->name);
								temp_head = temp_head->next;
							}						
							printf("\n");				flag = 1;		break;					
						}
		
			case 1:		
						if(max->score < score){		 /* Checking validity. */
							printf("\nTRY AGAIN\n");					flag = 0;		break;
						}
						else{

							temp_head = name_head;
							printf("\n");

							while(temp_head != NULL){	  /* Print movies which has greater or equal score. */
								if(temp_head->score >= score) 	printf("%s\n",temp_head->name);
								temp_head = temp_head->next;
							}							
							printf("\n");				flag = 1;		break;					
						}
		
			default:	printf("\nTRY AGAIN\n");		flag = 0;		break;	
		}/* End of selection. */
	}while(flag != 1);
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function prints single movie's all information.
*	Function asks user for movie name and make process according to that name.
*/
void print_single_mov(Movie_Budget *budget_head,Movie_Name *name_head){
	char ch;
	int i,j,flag;
	Movie_Name *temp_name = NULL;
	Movie_Budget *temp_head = NULL;
	char *input_name = NULL,*temp_str = NULL;
	

	flag = 0;

	do{
		printf("\nPlease enter the name of the movie: ");
		i = 0;
		ch = '-';
		while(ch != '\n'){		/* This loops take the string from the user and allocates memory properly. */

			scanf("%c",&ch);
			i++;

			input_name = calloc(i,sizeof(char));	/* Allocate a new memory for essential string. */

			for(j = 0; j < i-1; j++) input_name[j] = temp_str[j];	/* Assigning characters which was saved in temp_str. */

			input_name[i-1] = ch;	/* Assigning the new character. */
			free(temp_str);			/* Free the temp_str's memory. */

			temp_str = input_name;	/* temp_str should point the same place with input_name for saving information. */
		}/* End of iteration. */

		if(i != 0)	input_name[i-1] = '\0';		/* Assigning the null char for making it string. */
			
		temp_head = budget_head;

		while(temp_head != NULL){	/* This loop finds movie according to given name. */

			if(strcmp(input_name,temp_head->name) == 0){	/* If name is found, then node is found. */
				free(input_name);
				flag = 0;
				break;
			}
			temp_head = temp_head->next;
		}

		if(temp_head != NULL){				/* Printing the founded movie. */

			printf("\n\n%-8s","Budget: ");
			if(temp_head->budget == -1) printf("%s\n","Unknown");
			else printf("%d\n",temp_head->budget);
			
			temp_name = find_movie1(temp_head->name,name_head);

			printf("%-8s%s\n%-8s%s\n","Genre: ",temp_name->genre,"Name: ",temp_head->name);
			printf("%-8s%.1f\n%-8s%d\n\n","Score: ",temp_name->score,"Year: ",temp_head->year);
			flag = 0;
		}
		else{
			printf("\nMovie cannot be found. TRY AGAIN\n");		/* If movie cannot be found ask user again. */
			flag = 1;
		}
	}while(flag != 0);			/* Loop iterates till flag is equal to 0. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function calculates and prints the average score.
*/
void print_avg_score(Movie_Name *name_head,int num){
	double sum;
	Movie_Name *temp_head = NULL;
	
	temp_head = name_head;
	sum = 0;

	while(temp_head != NULL){			/* Loop calculates the sum of scores. */
		sum += temp_head->score;
		temp_head = temp_head->next;
	}
	sum = sum / (double)num;			/* Calculating the average. */

	printf("\nAverage: %f\n\n",sum);	/* Printing the average. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function calculates and prints each genre's frequency.
*	While calculating main purpose is finding differences.
*/
void print_genre_freq(Movie_Name *name_head){
	int counter;
	Movie_Name *cur_name = NULL,*pre_name = NULL;

	sort_genres(&name_head);	/* Sorting movies according to genre. */

	cur_name = pre_name = name_head;
	counter = 1;

	printf("\n%-15s ",cur_name->genre);		/* Printing the first genre. */
	cur_name = pre_name->next;

	while(cur_name != NULL && pre_name != NULL){	/* Loop iterates till end of list is reached. */

		if(strcmp(cur_name->genre,pre_name->genre) != 0){	/* If difference is found print current genre and frequency. */
			printf("%d\n%-15s ",counter,cur_name->genre);
			counter = 1;
		}
		else counter++;

		pre_name = pre_name->next;
		cur_name = cur_name->next;
	}
	printf("%d\n\n",counter);			/* Printing the last genre's frequency. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function free's given lists for preventing memory leak.
*/
void free_lists(Movie_Budget *budget_head,Movie_Name *name_head){
	Movie_Name *temp_name = NULL;
	Movie_Budget *temp_budget = NULL;

	while(budget_head != NULL && name_head != NULL){
		
		temp_name = name_head;
		temp_budget = budget_head;

		name_head = name_head->next;
		budget_head = budget_head->next;

		free(temp_budget->name);			/* First free dynamically allocated strings. */
		free(temp_name->genre);

		free(temp_name);					/* Then free each node. */
		free(temp_budget);
	}
}/* End of Function. */
/* =========================================================================================== */