#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct antonym_t{			/* Linked list for antonyms. */

	char *antonym;
	struct antonym_t *next_ant;
}antonym_t;

typedef struct synonym_t{			/* Linked list for synonyms. */

	char *synonym;
	struct synonym_t *next_syn;
}synonym_t;

typedef struct word_t{				/* Linked list for each word, and each node includes antonyms and synonyms. */

	char *word;
	antonym_t *antonyms;
	synonym_t *synonyms;
	int prob_syn;
	int prob_ant;
	struct word_t *next;
}word_t;

typedef struct record_t{			/* Node for each user's record. */
	char word_str[46];
	int ant_prob;
	int syn_prob;
}record_t;

typedef struct user_t{				/* Linked list for usernames. */
	
	char username[46];
	struct user_t *next_u;
}user_t;

void english_learn_func(char *file_name1,char *file_name2);			/* Main function which includes all operation. */

word_t *store_words(char *file_name1,char *file_name2,int *num);	/* Helper functions for storing the words. */
char *delete_ch_till_space(char *line);
void insert_antonyms(antonym_t **antonym_head,char *line);
void insert_end(word_t **word_head,word_t *new_node_data);
void insert_synonyms(synonym_t **synonym_head,char *line);
int find_insert(word_t **word_head,word_t *new_node_data);

char *select_user(char *usernames_file);							/* Helper functions for user interaction part. */
char *add_user(char *usernames_file);
void update_records(word_t **head_word,int *correct_ans,int *incorrect_ans,char *user_file);
void ask_user_word(word_t **head_word,int *correct_ans,int* incorrect_ans,int num);
void find_max_prob(word_t *head_word,int *max_syn,int *max_ant);
void update_user_file(char *user_file,int *correct_ans,int *incorrect_ans,word_t *head_word);
void add_ant_syn(word_t **head_word);
void insert_user(user_t **user_head,user_t *new_node_data);
void insert_antonym_end(antonym_t **antonym_head,char *word);
void insert_synonym_end(synonym_t **synonym_head,char *word);
void update_files(char *file_name1,char *file_name2,word_t *word_head);
void free_list(word_t *word_head);

int main(){
	char *file_name1 = "antonyms.txt";				/* File names are assigned. */
	char *file_name2 = "synonyms.txt";

	english_learn_func(file_name1,file_name2);

	return 0;
}/* End of main */
/* ====================================================================================================== */

/* 
*	This function reads all data from txt files and stores them into linked list.
*	After that arranges the files which are binary for each user.
*	All these arrangements made according to the user inputs.
*/
void english_learn_func(char *file_name1,char *file_name2){

	int input,flag,num,correct_ans,incorrect_ans;		/* num is for holding the total number of words. */
	char ch;

	char *user_file = NULL;
	word_t *head_word = NULL;

	char *usernames_file = "usernames.worddat";
	srand(time(NULL));

	num = 0;												
	head_word = store_words(file_name1,file_name2,&num);	/* Read all words from files and store it in linked list. */

	input = 0;
	flag = 0;		

	while(flag != -1){					/* Loop iterates till flag equals to -1. */

		printf("\n1. Select user\n");
		printf("2. Add new user\n");
		printf("3. Exit\n\n");
		printf("Choose(1,2,3): ");

		scanf("%d",&input);				/* Taking operation input from the user. */
		ch = getchar();					/* Taking the '\n' character. */
	
		switch(input){
			case 1: user_file = select_user(usernames_file);	/* Function returns the proper name for user file. */
					
					if(user_file != NULL)	flag = 1;
					else flag = 0;
					break;
									
			case 2: user_file = add_user(usernames_file);					flag = 1;	break;	/* Function creates user file. */
			
			case 3: printf("You exitted. Terminating ...\n");
					update_files(file_name1,file_name2,head_word);
					free_list(head_word);									flag = -1;	break;
			
			default: printf("Invalid input!\n\n");							flag = 0;	break;
		}/* End of selection. */

		if(flag == 1){
			correct_ans = 0; 		incorrect_ans = 0;
														/* Arranging probabilities according to user's record. */
			update_records(&head_word,&correct_ans,&incorrect_ans,user_file);	
			flag = 0;
			
			while(flag != -1 && flag != -2){	/* If flag equals -2, user goes to upper menu, if flag equals -1 program ends. */
				
				printf("\n\n===== USER RECORD ====\n\n");
				if(correct_ans == 0 && incorrect_ans == 0){
					printf("User did not solve any questions yet.");
				}
				else
					printf("Correct answers = %d\nIncorrect answers = %d",correct_ans,incorrect_ans);
				
				printf("\n\n===== USER RECORD ====\n\n");
				printf("\n1. Generate Question\n2. Add antonym or synonym to user selected word\n3. Change the user\n4. Exit\n");
				printf("Choose(1,2,3,4): ");
				scanf("%d",&input);
				ch = getchar();

				switch(input){

					case 1:		ask_user_word(&head_word,&correct_ans,&incorrect_ans,num);	flag = 0;		break;
					case 2:		add_ant_syn(&head_word);									flag = 0;		break;
					case 3:		printf("Going to upper menu.\n\n");							flag = -2;		break;
					case 4:		printf("You exitted. Terminating ...\n");					flag = -1;
								update_files(file_name1,file_name2,head_word);
								update_user_file(user_file,&correct_ans,&incorrect_ans,head_word);
								free_list(head_word);														break;
					default:	printf("Invalid input!\n\n");				flag = 0;						break;
				}/* End of selection. */
			}
			if(input != 4)									/* This condition prevents segmentation fault. */
					update_user_file(user_file,&correct_ans,&incorrect_ans,head_word);	
		}
	}
}/* End of Function. */
/* ====================================================================================================== */

/*
*	Function stores each word in a linked list and each node of this linked list includes 2 different lists
*  which include antonyms and synonyms for that word.
*/
word_t *store_words(char *file_name1,char *file_name2,int *num){
	int i;
	char ch;
	char *line_buffer = NULL;
	FILE *A,*S;
	word_t *word_head = NULL;
	word_t *new_node = NULL;

	/* ----------------------------- Reading the first file ------------------------------ */

	A = fopen(file_name1,"r");
	
	if(A == NULL){
		printf("\nThere is no file such \"%s\". Terminating...\n\n",file_name1); 
		exit(1);
	}
	
	S = fopen(file_name2,"r"); /* This condition is for testing other file before storing. */
	
	if(S == NULL){
		printf("\nThere is no file such \"%s\". Terminating...\n\n",file_name2); 
		exit(1);
	}
	fclose(S);					/* Storing synonyms does not started, so file can be closed now. */

	line_buffer =(char *)calloc(1025,sizeof(char));	/* Allocating memory for each line. */

	i = 0;						/* i is for counting total number of words. */

	while(fgets(line_buffer,1020,A) != NULL){
		
		if(strlen(line_buffer) > 4){							/* length of line cannot be less than 4. */

			new_node = (word_t *)malloc(sizeof(word_t));		/* Allocating memory for new node and antonyms. */
			
			new_node->word = delete_ch_till_space(line_buffer);	/* Function deletes all characters till space. */
			delete_ch_till_space(line_buffer);					/* Deleting the '<>'' part. */ 

			new_node->next = NULL;								/* Assigning null and necessary values before inserting. */
			new_node->synonyms = NULL;
			new_node->prob_ant = 100;
			new_node->prob_syn = 100;

			insert_antonyms(&new_node->antonyms,line_buffer);	/* Inserting the antonyms to interior linked list. */	
			insert_end(&word_head,new_node);					/* Inserting the main linked list. */
			i++;
			free(new_node);
		}
			
		free(line_buffer);
		line_buffer =(char *)calloc(1025,sizeof(char));
	}/* End of iteration. */

	free(line_buffer);
	fclose(A);
	
	/* ----------------------------- Reading the second file ------------------------------ */
	
	line_buffer =(char *)calloc(1025,sizeof(char));				
	S = fopen(file_name2,"r");
	
	while(fgets(line_buffer,1020,S) != NULL){	/* This part is same as reading first file except find_insert() function. */

		if(strlen(line_buffer) > 4){

			new_node = (word_t *)malloc(sizeof(word_t));
			
			new_node->word = delete_ch_till_space(line_buffer);
			delete_ch_till_space(line_buffer);

			new_node->next = NULL;
			new_node->antonyms = NULL;
			new_node->prob_ant = 100;
			new_node->prob_syn = 100;

			insert_synonyms(&new_node->synonyms,line_buffer);	

			if(find_insert(&word_head,new_node)) i--;  /* Insert informations if word is already read, otherwise add node to end. */

			i++;
			free(new_node);
		}
			
		free(line_buffer);
		line_buffer =(char *)calloc(1025,sizeof(char));
	}
	free(line_buffer);
	fclose(S);

	*num = i;											/* Returning the number of words counted. */
	return word_head;									/* Returning the head of that linked list. */
}/* End of Function. */
/* ====================================================================================================== */

/* 
*	Function deletes all characters till space,carriage return,newline or end of file.
*	Function returns the string that deleted.
*	Ex: if line is "yield <> stand survive", line will be "<> stand survive", and "yield" will be returned.
*	If there are no strings to return function returns NULL.
*/
char *delete_ch_till_space(char *line){	
	int i;
	char *temp = NULL,*str = NULL;

	temp = calloc(strlen(line), sizeof(char));		/* Allocating memory for temp string. */
	i = 0;

	while(line[i] != ' ' && line[i] != '\r' && line[i] != '\n' && i < (int)strlen(line)) i++;		/* Counting the characters. */
	if(i > 0){

		if(line[i-1] != '<' && line[i-1] != '>' && line[i-1] != '='){

			str = (char *)calloc(i+1,sizeof(char));
			
			i = 0;

			while(line[i] != ' ' && line[i] != '\r' && line[i] != '\n' && i < (int)strlen(line)){
				str[i] = line[i];
				i++;
			}
			str[i] = '\0';
		}

		if(line[i] != '\0'){
			
			strcpy(temp,&line[i+1]);	/* Making the swap operation. */
			strcpy(line,temp);	
		}

		else
			line[0] = '\0';	
	}

	free(temp);					/* Freeing the memory that is allocated for temp string. */
	
	return str;
}/* End of Function. */
/* ====================================================================================================== */

/*
*	Function is a recursive function which inserts node to end of a linked list.
*/
void insert_antonyms(antonym_t **antonym_head,char *line){
	char *str = NULL;

	str = delete_ch_till_space(line);	/* If there is no word in given line function returns NULL. */
	
	if(str != NULL){	/* Call function till str equals NULL. */

		*antonym_head = (antonym_t *)malloc(sizeof(antonym_t));
		(*antonym_head)->antonym = str;	
		insert_antonyms(&(*antonym_head)->next_ant,line); 		/* Call function for the next elemnt of antonym list. */
	}
	else
		*antonym_head = NULL;	/* Last element points NULL. */
}/* End of Function. */
/* ====================================================================================================== */
void insert_end(word_t **word_head,word_t *new_node_data){	/* Function inserts new word to the end of the linked list. */

	word_t *temp_node = NULL,*new_node = NULL;

	new_node = (word_t *)malloc(sizeof(word_t));			/* Allocating memory for new node. */
	new_node->next = NULL;									/* Assigning all data to new node. */
	new_node->word = new_node_data->word;
	new_node->antonyms = new_node_data->antonyms;
	new_node->synonyms = new_node_data->synonyms;
	new_node->prob_ant = new_node_data->prob_ant;
	new_node->prob_syn = new_node_data->prob_syn;

	if(*word_head == NULL){						/* If head is null make insertion at head. */
		new_node->next = *word_head;
		*word_head = new_node;
	}
	else{

		temp_node = *word_head;
		while(temp_node->next != NULL) temp_node = temp_node->next;		/* Loop iterates till end of list is found. */

		temp_node->next = new_node;
	}	
}/* End of Function. */
/* ====================================================================================================== */

/*
*	Function is a recursive function which inserts node to end of a linked list.
*/
void insert_synonyms(synonym_t **synonym_head,char *line){
	char *str = NULL;

	str = delete_ch_till_space(line);	/* If there is no word in given line function returns NULL. */

	if(str != NULL){	/* Call function till str equals NULL. */

		*synonym_head = (synonym_t *)malloc(sizeof(synonym_t));
		(*synonym_head)->synonym = str;
		insert_synonyms(&(*synonym_head)->next_syn,line); 		/* Call function for the next elemnt of synonym list. */
	}
	else
		*synonym_head = NULL;			/* Last element points NULL. */
}/* End of Function. */
/* ====================================================================================================== */

/*
*	If function finds the same word in linked list inserts new datas to that list, if word cannot be found, Function
*  inserts end.
*	Function returns the information of word is founded or not.
*/
int find_insert(word_t **word_head,word_t *new_node_data){

	int flag;
	word_t *temp_node = NULL,*new_node = NULL;

	new_node = (word_t *)malloc(sizeof(word_t));			/* Allocating memory for new node. */
	new_node->next = NULL;									/* Assigning all data to new node. */
	new_node->word = new_node_data->word;
	new_node->antonyms = new_node_data->antonyms;
	new_node->synonyms = new_node_data->synonyms;
	new_node->prob_ant = new_node_data->prob_ant;
	new_node->prob_syn = new_node_data->prob_syn;

	flag = 0;
	if(*word_head == NULL){									/* If head is null make insertion at head. */
		new_node->next = *word_head;
		*word_head = new_node;
	}
	else{
		
		temp_node = *word_head;
		while(temp_node->next != NULL){

			if(strcmp(temp_node->word,new_node->word) == 0){	/* If word is found, exit from loop. */
				free(new_node->word);
				free(new_node);
				flag = 1;
				break;
			}
			temp_node = temp_node->next;
		}
		if(flag)												/* If word is found add synonym list. */
			temp_node->synonyms = new_node_data->synonyms;	
																
		else 													/* If word cannot be found, add end of the list. */
			temp_node->next = new_node;
	}
	return flag;
}/* End of Function. */
/* ====================================================================================================== */

/*
*	Function displays all user and asks for the username.
*	Function returns the string which is the name of the file for each user.
*/
char *select_user(char *usernames_file){

	FILE *A;
	int i,num,input,flag;
	char ch;
	user_t *user_head = NULL,*temp_node = NULL;
	char *ret_name = NULL;

	A = fopen(usernames_file,"rb");

	if(A == NULL)	printf("There aren't any user, please add user.\n");

	else{
		i = 0;
		temp_node = (user_t *)malloc(sizeof(user_t));		/* Creating a linked list for holding usernames. */
		temp_node->next_u = NULL;

		while(fread(temp_node,sizeof(user_t),1,A) != 0){	/* Reading binary file for storing usernames. */
			
			insert_user(&user_head,temp_node);

			free(temp_node);
			temp_node = (user_t *)malloc(sizeof(user_t));
			temp_node->next_u = NULL;

			i++;
		}
		free(temp_node);
		num = i;

		fclose(A);											/* Closing file. */

		flag = 0;
	
		while(flag != 1){									/* User interaction part. */

			temp_node = user_head;
			
			i = 0;
			while(temp_node != NULL && i < num){			/* Printing each user. */
				printf("%d. %s\n",i+1,temp_node->username);
				temp_node = temp_node->next_u;
				i++;
			}

			printf("\nChoose(number): ");
			scanf("%d",&input);
			ch = getchar();

			if(input < 1 || input > num){					/* If input is invalid warn user. */

				printf("Invalid input is entered! Max is: %d, min is: 1\n\n",num);	flag = 0;
			}
			else{											/* If input is valid, create the filename. */

				temp_node = user_head;
				i = 0;

				while(temp_node != NULL && i < input-1){
					temp_node = temp_node->next_u;
					i++;
				}
				if(temp_node != NULL){
					ret_name = (char *)calloc(46,sizeof(char));
					sprintf(ret_name,"%s%s",temp_node->username,".worddat");	/* Concatinate strings. */
				}

				for(i = 0; user_head != NULL; i++){		/* Free the allocated memory. */

					temp_node = user_head;
					user_head = user_head->next_u;
					free(temp_node);
				}
				flag = 1;
			}
		} 	
	}

	return ret_name;						/* Return the filename. */
}/* End of Function. */
/* ====================================================================================================== */
void insert_user(user_t **user_head,user_t *new_node_data){	/* Function inserts username to the linked list. */

	user_t *new_node = NULL,*temp_node = NULL;

	new_node = (user_t *)malloc(sizeof(user_t));

	strcpy(new_node->username,new_node_data->username);

	new_node->next_u = NULL;

	if(*user_head == NULL){									/* If head is NULL new head is new entry. */
		new_node->next_u = *user_head;
		*user_head = new_node;
		
	}
	else{

		temp_node = *user_head;
		while(temp_node->next_u != NULL)	temp_node = temp_node->next_u;
		temp_node->next_u = new_node;
	}	
}/* End of Function. */
/* ====================================================================================================== */
char *add_user(char *usernames_file){			/* Adding new user to usernames file. */

	FILE *A;
	user_t *user_node = NULL;
	char *ret_name = NULL;

	user_node = (user_t *)malloc(sizeof(user_t));
	user_node->next_u = NULL;

	ret_name = (char *)calloc(46,sizeof(char));

	A = fopen(usernames_file,"ab");				/* Append username to file for user's name. */

	if(A != NULL){
		printf("Please enter the user name: ");
		scanf("%[^\n]%*c",user_node->username);
		fwrite(user_node,sizeof(user_t),1,A);
		fclose(A);
	}
	
	sprintf(ret_name,"%s%s",user_node->username,".worddat");	/* Creating the file for user. */
	free(user_node);

	return ret_name;			/* Return the user file. */
}/* End of Function. */
/* ====================================================================================================== */

/*
*	Function simply asks user question according to users previous answers.
*	Determination of questions are done with calculating probabilites according to user's answer.
*	These probabilities are inside the each node of word linked list.
*	Probability calculation is like increasing or decrasing each node's ratio, after that generating number
*  between 1 and maximum and choose questions according to the ratios which are prob_syn and prob_ant.
*/
void ask_user_word(word_t **head_word,int *correct_ans,int* incorrect_ans,int num){
	int random,quest,i,flag,input,max_ant,max_syn,rand_ant,rand_syn;
	char ch,input_word[46];
	word_t *temp_node = NULL;
	antonym_t *temp_ant = NULL;
	synonym_t *temp_syn = NULL;

	max_ant = 100;							/* max_ant and max_syn are for generating number properly. */
	max_syn = 100;

	flag = 0;

	while(flag == 0){

		find_max_prob(*head_word,&max_syn,&max_ant);			/* Finding the maximum propabilities. */

		random = rand() % num; 									/* Generating number for propability calculations. */
		quest = rand() % 2;										/* Generate question. */
		rand_ant = rand() % max_ant + 1;
		rand_syn = rand() % max_syn + 1;

		temp_node = *head_word;

		i = 0;

		while(temp_node != NULL && i < random){			/* Select a word randomly. */
			temp_node = temp_node->next;
			i++;
		}
	
		if(quest){									/* If question is for antonyms go into this condition. */

			if(temp_node->antonyms != NULL){		/* Checking if there are antonyms. */

				if(rand_ant <= temp_node->prob_ant){	/* If generated ratio is less or equal to founded one ask question. */
					printf("\nWhat is the antoynm of %s?\n",temp_node->word);
					
					if(temp_node->prob_ant > 50)
						temp_node->prob_ant = temp_node->prob_ant - 30;		/* Decrease ration because word is already asked.*/

					flag = 1;
				}
				else
					flag = 0;		
			}
			else
				quest = 0;
			
		}
		if(!quest){								/* If synonym is asked go into this condition. */

			if(temp_node->synonyms != NULL){	/* Checking if there are synonyms. */

				if(rand_syn <= temp_node->prob_syn){	/* If generated ratio is less or equal to founded one ask question. */

					printf("\nWhat is the synoynm of %s?\n",temp_node->word);
					
					if(temp_node->prob_syn > 50)
						temp_node->prob_syn = temp_node->prob_syn - 30;		/* Decrease ration because word is already asked.*/
					
					flag = 2;
				}
				else
					flag = 0;
			}
			else
				flag = 0;
		}

	}
								/* ---- USER INTERACTION PART ---- */

	printf("Answer: ");
	scanf("%[^\n]%*c",input_word);

	if(flag == 1){				/* Operations if antonym is asked. */

		temp_ant = temp_node->antonyms;

		if(temp_node->prob_syn < 500 && temp_node->synonyms != NULL)	/* If there are synonyms increase the chance. */
					temp_node->prob_syn *= 2;

		while(temp_ant != NULL){
			if(strcmp(input_word,temp_ant->antonym) == 0){		/* If answer is right decrease the probability. */
				printf("Correct answer!\n");
				(*correct_ans)++;

				if(temp_node->prob_ant > 2)
					temp_node->prob_ant /= 2;
				

				break;
			}
			temp_ant = temp_ant->next_ant;
		}
		if(temp_ant == NULL){									/* If answer is wrong, increase the probability. */


			if(temp_node->prob_ant < 500)	
				temp_node->prob_ant *= 2;

			printf("Answer is incorrect. Do you want to add this as an antonym?\n\n1. Yes\n2. No\nChoose: ");
			(*incorrect_ans)++;

			scanf("%d",&input);
			ch = getchar();

			if(input == 1)										/* Condition is for if user wants to add answer as an antonym. */
				insert_antonym_end(&temp_node->antonyms,input_word);
		}
	}

	else if(flag == 2){						/* Operations if synonym is asked. */

		temp_syn = temp_node->synonyms;

		if(temp_node->prob_ant < 500 && temp_node->antonyms != NULL)	/* If there are synonyms increase the chance. */
					temp_node->prob_ant *= 2;

		while(temp_syn != NULL){
			if(strcmp(input_word,temp_syn->synonym) == 0){				/* If answer is right decrease the probability. */
				printf("Correct answer!\n");
				(*correct_ans)++;
				if(temp_node->prob_syn > 2 ){
					temp_node->prob_syn /= 2;
				}

				break;
			}
			temp_syn = temp_syn->next_syn;
		}
		if(temp_syn == NULL){										/* If answer is wrong, increase the probability. */

			if(temp_node->prob_syn < 500)
				temp_node->prob_syn *= 2;

			printf("Answer is incorrect. Do you want to add this as an synonym?\n1. Yes\n2. No\nChoose: ");
			scanf("%d",&input);
			ch = getchar();
			(*incorrect_ans)++;
			if(input == 1)									/* Condition is for if user wants to add answer as an synonym. */
				insert_synonym_end(&temp_node->synonyms,input_word);		
		}
	}
}/* End of Function. */
/* ====================================================================================================== */
void add_ant_syn(word_t **head_word){	/* Function is for adding antonym or synonym to a user selected word. */

	int input;
	char ch,input_word[46];
	word_t *temp_node = NULL;
	antonym_t *temp_ant = NULL;
	synonym_t *temp_syn = NULL;
												/* Asking the word to user. */
	printf("Please enter the word you want to add antonym or synonym.\nWord: ");
	scanf("%[^\n]%*c",input_word);

	temp_node = *head_word;

	if(*head_word == NULL)
		printf("List is empty! Please fill the txt files.\n");

	while(temp_node != NULL){							/* Search file for inputted word. */

		if(strcmp(temp_node->word,input_word) == 0){				/* If word is found go for other operations. */
			printf("1. Add antonym\n2. Add synonym\nChoose: ");
			scanf("%d",&input);
			ch = getchar();

			switch(input){
				case 1: printf("Please enter an antonym for %s.\nAntonym: ",input_word);
						scanf("%[^\n]%*c",input_word);
						temp_ant = temp_node->antonyms;
						while(temp_ant != NULL){				/* Checking if user entered already existing antonym. */

							if(strcmp(temp_ant->antonym,input_word) == 0){
								printf("This antonym is already exists.\n\n");
								break;
							}
							temp_ant = temp_ant->next_ant;
						}
						if(temp_ant == NULL)
							insert_antonym_end(&temp_node->antonyms,input_word);
						
						break;
				case 2:	printf("Please enter a synonym for %s.\nSynonym: ",input_word);
						scanf("%[^\n]%*c",input_word);
						temp_syn = temp_node->synonyms;
						while(temp_syn != NULL){
																/* Checking if user entered already existing antonym. */
							if(strcmp(temp_syn->synonym,input_word) == 0){
								printf("This synonym is already exists.\n\n");
								break;
							}
							temp_syn = temp_syn->next_syn;
						}
						if(temp_syn == NULL)
							insert_synonym_end(&temp_node->synonyms,input_word);

						break;

				default: printf("Invalid input!\n\n");	break;
			}/* End of selection. */
			break;
		}
		temp_node = temp_node->next;
	}
	if(temp_node == NULL)	printf("Word cannot be found.\n\n");
}/* End of Function. */
/* ====================================================================================================== */
void update_files(char *file_name1,char *file_name2,word_t *head_word){	/* Function updates all files after operations done.*/
	FILE *A,*S;
	word_t *temp = NULL;
	antonym_t *temp_ant = NULL;
	synonym_t *temp_syn = NULL;

	A = fopen(file_name1,"w");
	S = fopen(file_name2,"w");

	temp = head_word;

	while(temp != NULL){				/* Printing datas as same as before. */
		
		if(temp->antonyms != NULL){
			fprintf(A,"%s ",temp->word);
			temp_ant = temp->antonyms;
			fprintf(A,"<>");
			while(temp_ant != NULL){
				fprintf(A," %s",temp_ant->antonym);
				temp_ant = temp_ant->next_ant;
			}
			fprintf(A,"\n");
		}
		if(temp->synonyms != NULL){
			fprintf(S,"%s ",temp->word);
			temp_syn = temp->synonyms;
			fprintf(S,"=");
			while(temp_syn != NULL){
				fprintf(S," %s", temp_syn->synonym);
				temp_syn = temp_syn->next_syn;
			}
			fprintf(S,"\n");	
		}
		temp = temp->next;
	}
	fclose(A);
	fclose(S);
}/* End of Function. */
/* ====================================================================================================== */
void free_list(word_t *word_head){			/* Function frees all of the allocated memory for linked list. */
	word_t *temp_node = NULL;
	antonym_t *temp_ant = NULL;
	synonym_t *temp_syn = NULL;

	while(word_head != NULL){
		temp_node = word_head;
		
		while(word_head->antonyms != NULL){
			temp_ant = word_head->antonyms;
			word_head->antonyms = word_head->antonyms->next_ant;
			free(temp_ant->antonym);
			free(temp_ant);
		}
		while(word_head->synonyms != NULL){
			temp_syn = word_head->synonyms;
			word_head->synonyms = word_head->synonyms->next_syn;
			free(temp_syn->synonym);
			free(temp_syn);
		}
		free(temp_node->word);
		word_head = word_head->next;
		free(temp_node);
	}
}/* End of Function. */
/* ====================================================================================================== */
void insert_antonym_end(antonym_t **antonym_head,char *word){	/* Function makes an insertion at the end for antonyms. */
	antonym_t *new_node = NULL,*temp_node = NULL;

	new_node = (antonym_t *)malloc(sizeof(antonym_t));
	new_node->next_ant = NULL;
	new_node->antonym = (char *)calloc(strlen(word)+1,sizeof(char));
	strcpy(new_node->antonym,word);

	temp_node = *antonym_head;

	if(*antonym_head == NULL){									/* If head is null insert at head. */
		new_node->next_ant = *antonym_head;
		*antonym_head = new_node;
	}
	else{
		while(temp_node->next_ant != NULL)	temp_node = temp_node->next_ant;
		
		temp_node->next_ant = new_node;
	}
}/* End of Function. */
/* ====================================================================================================== */
void insert_synonym_end(synonym_t **synonym_head,char *word){	/* Function makes an insertion at the end for synonyms. */

	synonym_t *new_node = NULL,*temp_node = NULL;

	new_node = (synonym_t *)malloc(sizeof(synonym_t));
	new_node->next_syn = NULL;
	new_node->synonym = (char *)calloc(strlen(word)+1,sizeof(char));
	strcpy(new_node->synonym,word);

	temp_node = *synonym_head;

	if(*synonym_head == NULL){									/* If head is null insert at head. */
		new_node->next_syn = *synonym_head;
		*synonym_head = new_node;
	}
	else{
		while(temp_node->next_syn != NULL)	temp_node = temp_node->next_syn;
		
		temp_node->next_syn = new_node;
	}
}/* End of Function. */
/* ====================================================================================================== */

/*
*	Function calculates the maximum ratios and returns them as a parameter. 
*/
void find_max_prob(word_t *head_word,int *max_syn,int *max_ant){
	word_t *temp_node = NULL;

	*max_ant = 100;
	*max_syn = 100;

	temp_node = head_word;					/* Initial values can be assigned. */
	*max_ant = temp_node->prob_ant; 
	*max_syn = temp_node->prob_syn;

	while(temp_node != NULL){
		if(temp_node->prob_ant > *max_ant)
			*max_ant = temp_node->prob_ant;

		if(temp_node->prob_syn > *max_syn)
			*max_syn = temp_node->prob_syn;

		temp_node = temp_node->next;			/* Going to the next node. */
	}
}/* End of Function. */
/* ====================================================================================================== */

/*
*	Function updates user's performance to binary file.
*	Probabilites are saved in that file for asking questions afterwards properly.
*/
void update_user_file(char *user_file,int *correct_ans,int *incorrect_ans,word_t *head_word){

	FILE *A;
	record_t *user_record = NULL;

	A = fopen(user_file,"wb");
	if(A == NULL){
		printf("An error occured!\n");
		exit(1);
	}

	fwrite(correct_ans,sizeof(int),1,A);
	fwrite(incorrect_ans,sizeof(int),1,A);

	while(head_word != NULL){

		user_record = (record_t *)malloc(sizeof(record_t));		/* Copying the datas to user struct and writing them to file. */
		strcpy(user_record->word_str,head_word->word);
		user_record->syn_prob = head_word->prob_syn;			
		user_record->ant_prob = head_word->prob_ant;
		head_word = head_word->next;
		fwrite(user_record,sizeof(record_t),1,A);
		free(user_record);
	}
	fclose(A);
}/* End of Function. */
/* ====================================================================================================== */

/*
*	Function stores all ratios from binary files to linked list.
*/
void update_records(word_t **head_word,int *correct_ans,int *incorrect_ans,char *user_file){
	FILE *A;
	word_t *temp_node = NULL;
	record_t *user_record = NULL;
	
	A = fopen(user_file,"rb");

	if(A != NULL){						/* Read all datas first user_record after that assign them to each node. */

		fread(correct_ans,sizeof(int),1,A);
		fread(incorrect_ans,sizeof(int),1,A);

		user_record = (record_t *)malloc(sizeof(record_t));
		temp_node = *head_word;

		while(fread(user_record,sizeof(record_t),1,A) != 0){

			while(temp_node != NULL){
				if(strcmp(user_record->word_str,temp_node->word) == 0){
					temp_node->prob_ant = user_record->ant_prob;
					temp_node->prob_syn = user_record->syn_prob;
				}
				temp_node = temp_node->next;
			}
			free(user_record);
			user_record = (record_t *)malloc(sizeof(record_t));
			temp_node = *head_word;
		}
		free(user_record);
		fclose(A);
	}
	else{
		temp_node = *head_word;

		while(temp_node != NULL){
			temp_node->prob_syn = 100;
			temp_node->prob_ant = 100;
			temp_node = temp_node->next;
		}
	}
}/* End of Function. */
/* ====================================================================================================== */