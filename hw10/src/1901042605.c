#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{					/* Movie typed struct defined. */
	double budget;
	int genre;
	char *name;
	double score;
	int year;
}Movie;

void read_n_display_movie_file(char *file_name);			/* Function which includes whole operation. */

															 
Movie *read_movies_dynamically(int *num,char *file_name);	/* Helper functions for reading data from txt file. */
char *get_line(FILE *M);
double read_double(char *line);
void delete_ch_till_comma(char *line);
void read_genre_dynamically(char *line,int *genre);
char *read_name_dynamically(char *line);

int scan_input();											/* Helper functions for user interaction, and data manipulation. */

void print_movie(Movie *movies,int indis);		/* Helper functions for sorting operations. */
void print_sorted(Movie *movies,int num);
void sort_budgets(Movie *movies,int num);
void sort_genres(Movie *movies,int num);
void sort_names(Movie *movies,int num);
void sort_scores(Movie *movies,int num);
void sort_years(Movie *movies,int num);
void ask_and_print(Movie *movies,int num,char *str);
int find_minindex_budget(Movie *movies,int num);
int find_minindex_genres(Movie *movies,int num);
int find_minindex_names(Movie *movies,int num);
int find_minindex_scores(Movie *movies,int num);
int find_minindex_years(Movie *movies,int num);

void print_genres();							/* Helper functions for other operations. */
void print_th_years(Movie *movies,int num);
void print_th_scores(Movie *movies,int num);
void print_single_mov(Movie *movies,int num);
void print_avg_score(Movie *movies,int num);
void print_genre_freq(Movie *movies,int num);
int find_maxindex_scores(Movie *movies,int num);
int find_maxindex_years(Movie *movies,int num);

					/* Global variables declared. */
char **genre_p;		/* genre_p is a pointer to dynamically allocated string array. */
int size_genre;		/* size_genre is number of string on that array. */

int main(){
	char file_name[] = "Movies.txt";		

	read_n_display_movie_file(file_name);		/* Function only accepts file name. */

	return 0;
}/* End of main */
/* ============================================================================================ */

/*
*	Function makes whole operation of reading and manipulating. 
*/
void read_n_display_movie_file(char *file_name){

	int input,num_of_movies,i;		/* i is used as an indis. */
	Movie *movies_p = NULL;			/* movies_p is struct array for storing movie informations. */

	genre_p = NULL;					/* NULL and 0 are assigned to the global variables. */
	size_genre = 0;			

	movies_p = read_movies_dynamically(&num_of_movies,file_name);	/* Function returns Movie type pointer. */

	if(num_of_movies < 0)	/* Function returns -1 if file does not exist. */
		printf("\nThere is no file such \"%s\" Terminating...\n\n",file_name);

	else{
		input = 0;				/* 0 can be assigned initially. */

		while(input != 8){		/* Loop iterates till 8 is entered. */

			input = scan_input();	/* Taking input from user. */

			switch(input){	/* Selecting the proper operation according to user input. */
				
				case 1:		print_sorted(movies_p,num_of_movies);		break;
				case 2:		print_genres();								break;
				case 3:		print_th_years(movies_p,num_of_movies);		break;
				case 4:		print_th_scores(movies_p,num_of_movies);	break;
				case 5:		print_single_mov(movies_p,num_of_movies);	break;
				case 6:		print_avg_score(movies_p,num_of_movies);	break;
				case 7:		print_genre_freq(movies_p,num_of_movies);	break;

				case 8:  	/* Freeing the allocated memory for preventing memory leak. */
							for(i = 0; i < num_of_movies; i++) free(movies_p[i].name);
							free(movies_p);
							for(i = 0; i < size_genre;i++) free(genre_p[i]);
							free(genre_p);
							printf("\nYou exitted. Terminating ...\n");	break;

				default:    printf("\nTRY AGAIN\n");					break;
			}/* End of selection. */
		}/* End of iteration. */
	}
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function reads txt file, which name is given as a parameter. 
*	It returns Movie typed struct pointer, and num variable as a number of element in that struct array.
*	Whole reading operation is made dynamically.
*/
Movie *read_movies_dynamically(int *num,char *file_name){
	
	char ch;
	FILE *M;
	int i,j;								/* i is used for counting lines, j is used as local variable for iterations. */
	char *line = NULL,*temp_line = NULL;	/* line and temp_line are used for storing lines. */
	Movie *movies = NULL;					/* movies struct will be returned. */
	Movie *movies_temp = NULL;				/* movies_temp is used for saving information, while array size increasing. */

	M = fopen(file_name,"r");

	if(M == NULL)	*num = -1;				/* If file does not exists return num as -1. */

	else{

		do{
			fscanf(M,"%c",&ch);
		}while(ch != '\n' && ch != EOF);	/* Passing the title. */

		i = 0;

		while(fscanf(M,"%c",&ch) != EOF){	/* Loop iterates till end of file is reached. */

			fseek(M,-1,SEEK_CUR);			/* After first character is read go 1 character left for reading properly. */

			line = get_line(M);				/* Getting line as a dynamically allocated string. */

			movies = calloc(i+1,sizeof(Movie));	/* Allocating memory for Movie struct array. */

			for(j = 0; j < i; j++)			/* After increasing array size, taking saved data from movies_temp. */
				movies[j] = movies_temp[j];		

			/*---------------------------------- Assigning budget ----------------------------------  */	
			
			/* If it is unknown assign -1 to budget. */					
			if(line[0] == 'u' || line[0] == 'U')	(movies+i)->budget = -1;

			else (movies+i)->budget = read_double(line);		/* If it isn't unknown read double from line. */

			/*--------------------------------   Budget assigned   ---------------------------------- */
			
			/*--------------------------------   Assigning genre   ---------------------------------- */

			temp_line = calloc(strlen(line)+1,sizeof(char));	/* Allocate memory for temp_line string. */
			delete_ch_till_comma(line);							/* Deleting all characters from start to first comma. */

			for(j = 0; line[j] != ',' && line[j] != '\0';j++)	/* Reading genre till comma exist. */
				temp_line[j] = line[j];

			temp_line[j] = '\0';		/* NULL character is assigned. */

			read_genre_dynamically(temp_line,&movies[i].genre);	/* Assigning genre. */

			/*---------------------------------  Genre assigned   ----------------------------------- */

			/*--------------------------- Assigning Name, Score, and Year --------------------------- */

			delete_ch_till_comma(line);
			movies[i].name = read_name_dynamically(line);		/* Function returns char pointer which points string. */
			delete_ch_till_comma(line);
			(movies+i)->score = read_double(line);				/* Reading initial double number from line. */
			delete_ch_till_comma(line);
			(movies+i)->year = (int)read_double(line);			/* Casting double to integer while assigning. */

			/*-------------------------- Name, Score, and Year are assigned. -------------------------- */

			for(j = 0; j < i; j++){			/* Checking if that movie which has same name exists. */

				if(!strcmp(movies[j].name,movies[i].name)){	/* If it exist overwrite. */
					free(movies[j].name);
					movies[j] = movies[i];
					i--;
					break;
				}
			}/* End of iteration. */

			free(movies_temp);		/* Free all memory that is not useful anymore. */
			free(temp_line);
			free(line);

			movies_temp = movies;	/* movies_temp should point to essential array for next line. */
			i++;
		}
		fclose(M);					/* If iteration ends file can be closed. */
		*num = i;					/* i can be returned as total number of movies. */
	}
	return movies;					/* Returning the struct pointer. */
}/* End of Function. */
/* =========================================================================================== */
	/* =========== Helper functions for storing movie data from txt dynamically. =========== */

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
		line = calloc(i+1,sizeof(char));				/* Allocating memory as size of i. */

		for(j = 0; j < i-1; j++) line[j] = str_temp[j];	/* Assigning saved characters to line. */

		line[i-1] = ch;		/* Assigning character which is just read. */	

		free(str_temp);		/* Free allocated memory. */

		str_temp = line;	/* temporary string points new array. */

	}while(ch != '\n' && flag != EOF);	/* Loop iterates till newline or end of file is reached. */

	line[i-1] = '\0';	/* Assigning null character to last element. */

	return line;		/* Returning line pointer. */
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
*	Function delete characters till comma exists.
*	Example: BEFORE ---> 123421,sample_line      <---->     AFTER ---> sample_line . 
*/
void delete_ch_till_comma(char *line){
	int i;
	char *temp;

	temp = calloc(strlen(line)+1, sizeof(char));		/* Allocating memory for temp string. */
	i = 0;

	while(line[i] != ',' && line[i] != '\n') i++;		/* Counting the characters. */

	strcpy(temp,&line[i+1]);	/* Making the swap operation. */
	strcpy(line,temp);

	free(temp);					/* Freeing the memory that is allocated for temp string. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function assigns genre to string array dynamically.
*	String array pointer is global variable.
*   Function returns proper genre code for movie struct.
*/
void read_genre_dynamically(char *line,int *genre){

	int i;
	char **genre_temp = NULL;			/* Temporary string array declared, and NULL is assigned. */

	for(i = 0; i < size_genre; i++){	/* Checking if genre exist. */
		if(!strcmp(line,genre_p[i])){

			*genre = i;					/* Assign the proper genre code. */
			return;						/* If genre exists assign genre code, and return. */
		}
	}/* End of iteration. */

	*genre = size_genre;				/* If genre does not exist assign size as code. */
	size_genre++;						/* Increase the size. */
	
	genre_temp = calloc(size_genre,sizeof(char *));		/* Allocate memory for temporary string array. */

	for(i = 0; i < size_genre-1;i++)					/* Allocate memory for each string on that array. */
		genre_temp[i] = calloc(strlen(genre_p[i])+1,sizeof(char));

	genre_temp[size_genre-1] = calloc(strlen(line)+1,sizeof(char));		/* Allocate memory for new string. */

	for(i = 0; i < size_genre-1; i++) strcpy(genre_temp[i],genre_p[i]);	/* Assign strings from genre_p */

	strcpy(genre_temp[size_genre-1],line);	/* Assign new string. */

	for(i = 0;i<size_genre-1;i++)	free(genre_p[i]);	/* Free the memory allocated for genre_p */
	free(genre_p);

	genre_p = calloc(size_genre,sizeof(char *));		/* Allocate new memory for genre_p. */
	
	for(i = 0; i < size_genre; i++){					/* Assign strings and new string to string array. */
		genre_p[i] = calloc(strlen(genre_temp[i])+1,sizeof(char));
		strcpy(genre_p[i],genre_temp[i]);
	}

	for(i = 0; i < size_genre;i++) free(genre_temp[i]);	/* Free the memory for temporary array elements. */

	free(genre_temp);		/* Free the allocated memory for genre_temp. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function allocates memory for name pointer, according to the line string and returns it.
*/
char *read_name_dynamically(char *line){

	char *name = NULL;	/* Assigning NULL first. */
	int i;

	for(i = 0; line[i] != ','; i++); 	/* Counting the characters before comma exist. */

	name = calloc(i+1,sizeof(char));	/* Allocating memory for name. */

	for(i = 0; line[i] != ','; i++) name[i] = line[i];	/* Assigning characters till comma exists. */

	name[i] = '\0';	/* Assigning the NULL char. */
	return name;
}/* End of Function. */
/* =========================================================================================== */
	/* =========== Helper functions for interacting with the user and manipulating the data. =========== */

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
void print_movie(Movie *movies,int indis){	/* Function prints each movie and its information properly. */

	if(movies[indis-1].budget == -1) printf("%-20s","Unknown");
	else printf("%-20ld",(long int)movies[indis-1].budget);
	printf("%-15s",genre_p[movies[indis-1].genre]);
	printf("%-50s",movies[indis-1].name);
	printf(" %-5.1f%-5d\n",movies[indis-1].score,movies[indis-1].year);
}/* End of Function. */
/* =========================================================================================== */
void print_sorted(Movie *movies,int num){	/* Function takes input from user calls the proper function for sorting. */
	int input,flag;
	flag = 0;

	do{
		printf("\n1. Budget\n2. Genre\n3. Name\n4. Score\n5. Year\n");
		printf("\nPlease Select an operation: ");
		scanf("%d",&input);
		switch(input){	/* Selecting the proper operation. */
			case 1: sort_budgets(movies,num);	flag = 0;	break;
			case 2: sort_genres(movies,num);	flag = 0;	break;
			case 3: sort_names(movies,num);		flag = 0;	break;
			case 4: sort_scores(movies,num);	flag = 0;	break;
			case 5: sort_years(movies,num);		flag = 0;	break;
			default: printf("\nTRY AGAIN\n");	flag = 1;	break;
		}/* End of Selection. */
	}while(flag != 0);
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function sorts element of struct array, according to budget values.
*	User will not see unknown budget movies. Lowest budget movie will be the initial.  
*/	
void sort_budgets(Movie *movies,int num){	
	int i,min,unknown_counter;					/* unknown_counter counts total number of unknown budget movies. */
	Movie temp_mov;								/* temp_mov is used for swapping. */

	unknown_counter = 0;

	for(i = 0; i < num; i++){
		min = find_minindex_budget(&movies[i],num - i);		/* Finding the minimum index except current index. */
		if(movies[i+min].budget == -1) unknown_counter++;	/* If unknown found, increase the counter. */
		temp_mov = movies[i];					/* Making the swap operation. */
		movies[i] = movies[i+min];
		movies[i+min] = temp_mov;
	}/* End of iteration. */

	ask_and_print(&movies[unknown_counter],num-unknown_counter,"budget");	/* Interacting and printing. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function finds the minimum element's index of an array according to budgets, and returns it.
*/
int find_minindex_budget(Movie *movies,int num){	
	int i,min_index;
	double min;

	min = movies[0].budget;					/* Initial element can be minimum */
	min_index = 0;

	for(i = 1; i < num; i++){				/* Iteration finds minimum index. */
		if(movies[i].budget < min){
			min = movies[i].budget;
			min_index = i;
		}
	}
	return min_index;						/* Return minimum index. */
}/* End of Function. */
/* =========================================================================================== */
void sort_genres(Movie *movies,int num){		/* Function sorts genre according to alphabetical order. */
	int i,min;
	Movie temp_mov;

	for(i = 0; i < num; i++){
		min = find_minindex_genres(&movies[i],num - i);		/* Finding and returning the minimum index. */
		temp_mov = movies[i];								/* Making the swap operation. */
		movies[i] = movies[i+min];
		movies[i+min] = temp_mov;
	}

	ask_and_print(movies,num,"genre");		/* Interacting the user and printing the result. */
}/* End of Function. */
/* =========================================================================================== */
int find_minindex_genres(Movie *movies,int num){	/* Function finds minimum index value of struct array according to genres. */
	int i,min_index;
	
	min_index = 0;

	for(i = 1; i < num; i++){
										/* If first parameter is less strcmp will return negative value. */
		if(strcmp(genre_p[movies[i].genre],genre_p[movies[min_index].genre]) < 0){
			min_index = i;
		}
	}

	return min_index;					/* Return minimum index. */
}/* End of Function. */
/* =========================================================================================== */
void sort_names(Movie *movies,int num){		/* Function sorts name according to their alphabetical order. */
	int i,min;
	Movie temp_mov;

	for(i = 0; i < num; i++){
		min = find_minindex_names(&movies[i],num - i);	/* Finding and returning the minimum index. */
		temp_mov = movies[i];							/* Making the swap operation. */
		movies[i] = movies[i+min];
		movies[i+min] = temp_mov;
	}
	ask_and_print(movies,num,"names");					/* Interacting the user and printing the result. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function finds minimum element of an array and returns its index according to scores.
*/
int find_minindex_names(Movie *movies,int num){
	int i,min_index;

	min_index = 0;

	for(i = 1; i < num; i++){	/* strcmp() will return negative value if first parameter is smaller than second. */
		if(strcmp(movies[i].name,movies[min_index].name) < 0)	min_index = i;
	}
		
	return min_index;		/* Returning the minimum index. */
}/* End of Function. */
/* =========================================================================================== */
void sort_scores(Movie *movies,int num){	/* Function sorts struct array according to scores. */
	int i,min;
	Movie temp_mov;			/* Temporary struct is used for swap operations. */

	for(i = 0; i < num; i++){
		min = find_minindex_scores(&movies[i],num - i);	/* Finding and returning the minimum index. */
		temp_mov = movies[i];							/* Making the swap operation. */
		movies[i] = movies[i+min];
		movies[i+min] = temp_mov;
	}
	
	ask_and_print(movies,num,"scores");					/* Interacting the user and printing the result. */
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function finds minimum element of an array and returns its index according to scores.
*/
int find_minindex_scores(Movie *movies,int num){
	int i,min_index;
	double min;

	min = movies[0].score;			/* Initial element can be minimum. */
	min_index = 0;

	for(i = 1; i < num; i++){		/* Minimum element's index will be found in this iteration. */
		if(movies[i].score < min){
			min = movies[i].score;
			min_index = i;
		}
	}
	return min_index;				/* Returning the found index. */
}/* End of Function. */
/* =========================================================================================== */
void sort_years(Movie *movies,int num){	/* Function sorts struct array according to year informations. */
	int i,min;
	Movie temp_mov;						/* Temporary struct declared for swap operation. */	
	
	for(i = 0; i < (num); i++){
		min = find_minindex_years(&movies[i],num - i);	/* Finding the minimum index and returning it. */
		temp_mov = movies[i];
		movies[i] = movies[i+min];
		movies[i+min] = temp_mov;
	}
	
	ask_and_print(movies,num,"years");	/* Interacting the user and printing the result. */
}/* End of Function. */
/* =========================================================================================== */
int find_minindex_years(Movie *movies,int num){
	int i,min_index,min;


	min = movies[0].year;
	min_index = 0;

	for(i = 1; i < num; i++){
		if(movies[i].year < min){
			min = movies[i].year;
			min_index = i;
		}
	}
	return min_index;
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function interacts with user and prints the result according to user interaction. 
*/
void ask_and_print(Movie *movies,int num,char *str){
	int input,i,j,flag;

	flag = 0;

	do{
		printf("\n1. Single Selection\n2. Multiple Selection\n");
		printf("\nPlease Select an operation: ");
		scanf("%d", &input);						/* Taking the input from user. */

		switch(input){	/* Selecting the operation according to input. */

			case 1:		printf("\nEnter value: ");
						scanf("%d", &i);
						if(i > num || i < 1){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}
						else{
							printf("\n%d. Movie\n\n",i);
							print_movie(movies,i);			/* Printing the result. */
							flag = 0;	break;
						}

			case 2:		printf("\nEnter start value: ");
						scanf("%d", &i);
						if(i > num || i < 1){	/* Checking the input. */
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}
						printf("\nEnter end value: ");
						scanf("%d", &j);
						if((j > num || j < 1) || (i > j)){
							printf("\nINVALID INPUT!\n\n"); flag = 1; break;
						}
						printf("\n\nMovies between %d and %d, sorted by the %s.\n\n",i,j,str);
						while(i <= j){

							print_movie(movies,i);		/* Printing the result. */
							i++;
						}
						flag = 0;	break;

			default: 	printf("\nTRY AGAIN\n"); 	  flag = 1; 	   break;
		}
	}while(flag != 0);
}/* End of Function. */
/* =========================================================================================== */
void print_genres(){	/* Function prints genres stored. */
	int i;
	printf("\n");

	for(i = 0; i < size_genre; i++)		printf("%s\n",genre_p[i]);
}/* End of Function. */
/* =========================================================================================== */
void print_th_years(Movie *movies,int num){	/* Function prints according through the years. */
	int op,i,flag,year,indis;
	flag = 1;
												/* While printing the result, function includes borders. */
	do{
		printf("\nEnter a Year: ");				/* Taking the inputs from user. */
		scanf("%d",&year);
		printf("Until (0) or Since (1) %d: ",year);
		scanf("%d",&op);

		switch(op){		/* Selecting the proper operation according to the input. */

			case 0:		indis = find_minindex_years(movies,num);	/* If user chooses until, find minimum. */

						if(movies[indis].year > year){
							printf("\nTRY AGAIN\n");	flag = 0;	    break;
						}
						else{
							printf("\n");
							for(i = 0; i < num;i++){
								if(movies[i].year <= year) 	printf("%s\n",movies[i].name);
							}
							printf("\n");				flag = 1;		break;					
						}
		
			case 1:		indis = find_maxindex_years(movies,num);	  /* If user chooses since, find maximum. */

						if(movies[indis].year < year){
							printf("\nTRY AGAIN\n");
														flag = 0;		break;
						}
						else{
							printf("\n");
							for(i = 0; i < num; i++){
								if(movies[i].year >= year) 	printf("%s\n",movies[i].name);
							}
							printf("\n");				flag = 1;		break;					
						}
		
			default:	printf("\nTRY AGAIN\n");		flag = 0;		break;	
		}/* End of selection. */
	}while(flag != 1);
}/* End of Function. */
/* =========================================================================================== */

/*
*	Function finds the maximum element's index of given array according to year, and returns it. 
*/
int find_maxindex_years(Movie *movies,int num){	
	int i,max_index,max;

	max = movies[0].year;		/* Initial element can be maximum. */
	max_index = 0;

	for(i = 1; i < num; i++){
		if(movies[i].year > max){
			max = movies[i].year;
			max_index = i;
		}
	}
	return max_index;			/* Returning the index. */
}/* End of Function. */
/* =========================================================================================== */
void print_th_scores(Movie *movies,int num){/* Function prints according through the scores. */
	int op,i,flag,indis;
	double score_input;

	flag = 1;
											/* While printing the result, function includes borders. */
	do{
		printf("\nEnter a score: ");		/* Taking the inputs from user. */
		scanf("%lf",&score_input);
		printf("Less (0) or Greater (1) %.1f: ",score_input);
		scanf("%d",&op);

		switch(op){							/* Selecting the operation according the inputs. */
			case 0:
					indis = find_minindex_scores(movies,num);

					if(movies[indis].score > score_input){
						printf("\nTRY AGAIN\n");
												flag = 0;				break;
					}
					else{
						printf("\n");
						for(i = 0; i < num;i++){							
							if(movies[i].score <= score_input) printf("%s\n",movies[i].name);			
						}
						printf("\n");
												flag = 1;				break;
					}		
		case 1:
					indis = find_maxindex_scores(movies,num);

					if(movies[indis].score < score_input){
						printf("\nTRY AGAIN\n");
												flag = 0;				break;
					}
					else{
						printf("\n");
						for(i = 0; i < num; i++){
							if(movies[i].score >= score_input) printf("%s\n",movies[i].name);	
						}
						printf("\n");
												flag = 1;				break;
					}
		default:	printf("\nTRY AGAIN\n");	flag = 0;				break;
		}/* End of selection. */		
	}while(flag != 1);
}/* End of Function. */
/* =========================================================================================== */
/*
*	Function finds the maximum element's index of given array according to scores, and returns it. 
*/
int find_maxindex_scores(Movie *movies,int num){
	int i,max_index;
	double max;

	max = movies[0].score;		/* Initial element can be maximum. */
	max_index = 0;

	for(i = 1; i < num; i++){
		if(movies[i].score > max){
			max = movies[i].score;
			max_index = i;
		}
	}
	return max_index;			/* Returning the index. */
}/* End of Function. */
/* =========================================================================================== */
/*
*	Function takes name of movie from user and searches it, prints the all information.
*	Strings are allocated on the heap dynamically.
*/
void print_single_mov(Movie *movies,int num){
	char ch;
	char *input_name = NULL,*temp_str = NULL;
	int i,j,flag;

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

		if(i != 0)	input_name[i-1] = '\0';		/* Assigning the null char to char array. */
			

		for(j = 0; j < num; j++){				/* Searching the name in array. */
			if(!strcmp(input_name,movies[j].name)){
				free(input_name);
				flag = 0;
				break;
			}
		}
		if(j != num){						/* If j is not equal to num that means name is found, print the info. */
			printf("\n\n%-8s","Budget: ");
			if(movies[j].budget == -1) printf("%s\n","Unknown");
			else printf("%ld\n",(long int)movies[j].budget);
			printf("%-8s%s\n%-8s%s\n","Genre: ",genre_p[movies[j].genre],"Name: ",movies[j].name);
			printf("%-8s%.1f\n%-8s%d\n\n","Score: ",movies[j].score,"Year: ",movies[j].year);
			flag = 0;
		}
		else{
			printf("\nMovie cannot be found. TRY AGAIN\n");
			flag = 1;
		}
	}while(flag != 0);
}/* End of Function. */
/* =========================================================================================== */
void print_avg_score(Movie *movies,int num){	/* Function calculates and prints the average score. */
	int i;
	double sum;
	sum = 0;

	for(i = 0; i < num; i++)	sum += movies[i].score;

	sum /= (double)num;

	printf("\nAverage: %f\n",sum);
}/* End of Function. */
/* =========================================================================================== */
void print_genre_freq(Movie *movies,int num){	/* Function calculates and prints the total number of each genre. */

	int counter,i,j;
	counter = 0;
	printf("\n\n");
	for(i = 0; i < size_genre; i++){
		for(j = 0; j < num; j++){
			if(movies[j].genre == i) counter++;
		}
		printf("%-15s %d\n",genre_p[i],counter);
		counter = 0;
	}
}/* End of Function. */
/* =========================================================================================== */