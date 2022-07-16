#include <stdio.h>
#include <string.h>

void fix_spelling_error(const char *file_dict, char *file_text);
void find_best_correction(const char *file_dict,char *word_text);
void correct_words(const char *file_dict,char *word);					/* Helper Function */
int compare_words(char *word,char *word_dict);							/* Helper Function */
int check_const_to_vow(char *word,char *word_dict);						/* Helper Function */
/* FUNCTIONS FOR BONUS PART */
void fix_spelling_error2(const char *file_dict, char *file_text);	
void find_best_correction2(const char *file_dict,char *word_text);
void correct_words2(const char *file_dict,char *word);					/* Helper Function */

int main(){

	char file_dict[] = "dictionary.txt";		 	/* Files names are assigned. */
	char file_text[] = "text.txt";

	fix_spelling_error(file_dict,file_text); 	 	/* Calling functions with file names. */

/* ---------- If you want to test bonus part please delete comment lines. ---------- */

/*	fix_spelling_error2(file_dict,file_text); */	/* BONUS PART */ 
	
	return 0;	
}/* End of main */
/* =============================================================================================================== */
void fix_spelling_error(const char *file_dict, char *file_text){	/* Function fixes at most 1 spelling mistake of words which are
																	in dictionary.*/

	int length;					/* length is used for input's length. */
	char word[70];				/* Char array is declared and it will be used for string input.*/
								/* ! WARNING ! If input file's words have no space between them or any word on that file has
								more than 70 characters, there will be an error. If input file meet these conditions 
								please separate words or increase the allocation of memory for word array. */
	FILE *T,*D;					/* T is for text file,  D is for Dictionary. */

	D = fopen(file_dict,"r");	/* Opening the file_dict. */
	if(D == NULL){
		printf("ERROR ! There are no files such %s\n",file_dict);
		return;					/* If file cannot be opened, return. */
	}

	fclose(D);				/* Condition is for checking the file_dict is exist or not, It will be opened in helper functions.*/
	
	T = fopen(file_text,"r+");	/* Opening the file_text for reading and writing simultaneously. */

	if(T == NULL){
		printf("ERROR ! There are no files such %s\n",file_text);
		return;					/* If file cannot be opened return. */
	}
	
	else{						/* If there is no error, then process can start. */

		while(fscanf(T,"%s",word) != EOF){		/* Loop iterates till cursor reachs the end of file. */
			
			length = (int)strlen(word);			/* Assigning the words length. */
			fseek(T,-length,SEEK_CUR);			/* After scanning each word move cursor to same place before scanning. */
			find_best_correction(file_dict,word);	/* Call function with scanned word and file_name. */ 
			fprintf(T,"%s",word);				/* Overwrite the corrected word to the file. */
			fseek(T,1,SEEK_CUR);				/* Move cursor 1 byte to the right. */
		}
		fclose(T);								/* Close file_text. */
	}
}/* End Of Function. */
/* =============================================================================================================== */
void find_best_correction(const char *file_dict,char *word_text){	/* Function corrects word from dictionary and returns it. */
																	/* It checks at most 1 difference. */
	int i,upper_indexes[10],upper_counter;		/* upper_indexes and upper_counter is created for saving the information if
												word has any upper letters. Dictionary checks only lower letters.*/
	char temp_str[70];							/* This variable is created because, there might be punctuation mark. */

	upper_counter = 0;				
	temp_str[0] = '\0';			

	for(i = 0; word_text[i] != '\0'; i++){
		/* This condition stores the information of which letter stores upper letter, and convert the upper letters to lower. */
		if(word_text[i] >= 65 && word_text[i] <= 90 && upper_counter < 10){		
			upper_indexes[upper_counter] = i;
			word_text[i] = word_text[i] + 32;
			upper_counter++;			     /* Increment the counter. */
		}
		/* This condition divides strings if there are any punctuation marks. */	
		else if((word_text[i] <= 37 && word_text[i] >= 33) || (word_text[i] <= 47 && word_text[i] >= 39) ||
				(word_text[i] >= 58 && word_text[i] <= 64) || (word_text[i] <= 96 && word_text[i] >= 91) ||
				(word_text[i] <= 126 && word_text[i] >= 123)){
			
			strcpy(temp_str,&word_text[i]);			/* Copying the word without punctuation mark to the temp string. */
			word_text[i] = '\0';	
			
			break;									/* If condition checks exit from loop. */
		}
	}/* End of loop. */

	correct_words(file_dict,word_text);				/* Corrects the word. */

	if(temp_str[0] != '\0')							/* If there are any string after punctuation mark send that string, too. */
		correct_words(file_dict,&temp_str[1]);		/* Do not send the punctuation mark. */

	else
		correct_words(file_dict,temp_str);			/* Correct the temporary word. */

	strcat(word_text,temp_str);						/* Concatinate both words. */
	
	if(upper_counter > 0){							/* If there was any upper letter assign them. */
		for(i = 0; i < upper_counter; i++){
			word_text[upper_indexes[i]] -= 32; 
		}
	}
	
}/* End Of Function. */
/* ====================================== HELPER FUNCTIONS ====================================== */
void correct_words(const char *file_dict,char *word){		/* Function checks dictionary for word's corrected version. */

	/* It can correct at most 1 letter differences. */
	/* Priority --> candidates1 > candidates2 */
	char word_dict[70],candidates1[3][70],candidates2[3][70];	/* Candidates are for in case of a tie choose correct word from
																dictionary. */
	int counter1,counter2,flag;
	FILE *D;										/* D is for dictionary. */

	counter1 = 0; counter2 = 0;	flag = 0;		

	if(word[0] != '\0' && strlen(word) != 1){			/* If word is empty or has only 1 letter don't start the process. */

		D = fopen(file_dict,"r");						/* Open file_dict for reading. */

		while(fscanf(D,"%s", word_dict) != EOF){	/* Iterate till cursor reaches the end of file. */ 
			if(strlen(word) == strlen(word_dict)){	/* Checking if length of word from dictonary is equal to word from text. */

				if(strcmp(word,word_dict) == 0){	/* If word is in the dictionary exit from loop. */
				
				 	flag = 1; 
				 	break;
				}
				else if(compare_words(word,word_dict) == 1){	/* Checking if there is one letter dictionary.*/ 

					/* If this difference is consonant to vowel than add it to the candidates array. */
					if(check_const_to_vow(word,word_dict) == 1 && counter1 <= 3){	/* Maximum candidate number is 3. */
					
						strcpy(candidates1[counter1],word_dict);		
						counter1++;									/* Increment the counter1. */
					}
					else if(counter2 <= 3){		/* If condition above does not check then assign word to other candidate array. */
					
						strcpy(candidates2[counter2],word_dict);
						counter2++;									/* Increment the counter2. */ 
					}
				}
			}
		}/* End of the iteration. */
		fclose(D);														/* Close the file. */	
	}
	
	if(flag != 1){												/* If words exact match was not found then check candidates.*/
		/* candidates1 has more priority than candidates2.*/

		if(counter1 == 1) strcpy(word,candidates1[0]);			/* If counter1 is 1 than there is only 1 word found. */			
						
		else if(counter1 > 1) strcpy(word,candidates1[1]);		/* If counter1 is bigger than 1 choose the second occurence. */
						
		else if(counter2 == 1) strcpy(word,candidates2[0]);		/* If counter2 is 1 than there is only 1 word found. */	
			
		else if(counter2 > 1) strcpy(word,candidates2[1]);		/* If counter2 is bigger than 1 choose the second occurence. */
	}
}/* End Of Function. */
/* =============================================================================================================== */
int compare_words(char *word,char *word_dict){		/* Function checks the number of different letters on two words */
	int i,counter,retval;						

	counter = 0;	retval = 0;
	
	for(i = 0; word[i] != '\0'; i++){				/* Function iterates till word string ends. */

		if(word[i] == word_dict[i]) counter++;		/* If they are equal increment counter. */			
	}
	if(counter >= i - 1) retval = 1;				/* If there are one letter difference return 1. */
	else if(counter >= i - 2) retval = 2;			/* If there are two letter difference return 2. */

	return retval;		/* Returning result. */
}/* End Of Function. */
/* =============================================================================================================== */
int check_const_to_vow(char *word,char *word_dict){	/* Function checks if letter is constonant to vowel or not. */
	int i,retval;
	retval = 0;

	for(i = 0; word[i] != '\0'; i++){		/* Function iterates till end of the word. */
		if(word[i] != word_dict[i]){
			if(word[i] != 'a' || word[i] != 'e' || word[i] != 'i' || word[i] != 'o' || word[i] != 'u'){
				if(word_dict[i] == 'a' || word_dict[i] == 'e' || word_dict[i] == 'i' || word_dict[i] == 'o' || word_dict[i] == 'u')
					retval++;				/* If it is increment retval. */
			}
		}
	}/* End of iteration. */
	return retval;
}/* End Of Function. */
/* ==================================================    BONUS PART    ================================================== */
void fix_spelling_error2(const char *file_dict, char *file_text){	/* Function fixes at most 1 spelling mistake of words which are
																	in dictionary. */
	int length;
	char word[70];				/* Char array is declared and it will be used for string input.*/
								/* ! WARNING ! If input file's words have no space between them or any word on that file has
								more than 70 characters, there will be an error. If input file meet these conditions 
								please separate words or increase the allocation of memory for word array. */			
	FILE *T,*D;					/* T is for text file, D is for Dictionary. */

	D = fopen(file_dict,"r");	/* Opening the file_dict. */
	if(D == NULL){
		printf("ERROR ! There are no files such %s\n",file_dict);
		return;					/* If file cannot be opened return. */
	}

	fclose(D);				/* Condition is for checking the file_dict is exist or not, It will be opened in helper functions. */

	T = fopen(file_text,"r+");  /* Opening the file_text for reading and writing simultaneously. */

	if(T == NULL){
		printf("ERROR ! There are no files such %s\n",file_text);
		return;					/* If file cannot be opened return. */
	}
	
	else{						/* If there is no error, then process can start. */

		while(fscanf(T,"%s",word) != EOF){	/* Loop iterates till cursor reachs the end of file. */
			
			length = (int)strlen(word);		/* Assigning the words length */
			fseek(T,-length,SEEK_CUR);		/* After scanning each word move cursor to same place before scanning. */
			find_best_correction2(file_dict,word);	/* Call function with scanned word and file_name. */ 
			fprintf(T,"%s",word);			/* Overwrite the corrected word to the file. */
			fseek(T,1,SEEK_CUR);			/* Move cursor 1 byte to the right. */
		}
		fclose(T);							/* Close file_text. */
	}
}/* End Of Function. */
/* =============================================================================================================== */	
void find_best_correction2(const char *file_dict,char *word_text){	/* Function corrects word from dictionary and returns it. */
																	/* It checks at most 1 difference. */
	int i,upper_indexes[10],upper_counter;		/* upper_indexes and upper_counter is created for saving the information if
												word has any upper letters. Dictionary checks only lower letters.*/
	char temp_str[70];							/* This variable is created because, there might be punctuation mark. */

	upper_counter = 0;
	temp_str[0] = '\0';

	for(i = 0; word_text[i] != '\0'; i++){
		/* This condition stores the information of which letter stores upper letter, and convert the upper letters to lower. */
		if(word_text[i] >= 65 && word_text[i] <= 90 && upper_counter < 10){
			upper_indexes[upper_counter] = i;
			word_text[i] = word_text[i] + 32;
			upper_counter++;					/* Increment the counter. */
		}
		/* This condition divides strings if there are any punctuation marks. */
		else if((word_text[i] <= 37 && word_text[i] >= 33) || (word_text[i] <= 47 && word_text[i] >= 39) ||
				(word_text[i] >= 58 && word_text[i] <= 64) || (word_text[i] <= 96 && word_text[i] >= 91) ||
				(word_text[i] <= 126 && word_text[i] >= 123)){

			strcpy(temp_str,&word_text[i]);
			word_text[i] = '\0';	
			break;
		}
	}/* End of the iteration. */

	correct_words2(file_dict,word_text);			/* Corrects the word. */

	if(temp_str[0] != '\0')							/* If there are any string after punctuation mark send that string, too. */
		correct_words2(file_dict,&temp_str[1]);		/* Do not send the punctuation mark. */

	else
		correct_words2(file_dict,temp_str);			/* Correct the temporary word. */

	strcat(word_text,temp_str);						/* Concatinate both words. */
	
	if(upper_counter > 0){							/* If there was any upper letter assign them. */
		for(i = 0; i < upper_counter; i++){
			word_text[upper_indexes[i]] -= 32; 
		}
	}
}/* End Of Function. */
/* ========================================== HELPER FUNCTION FOR BONUS PART ========================================== */	
void correct_words2(const char *file_dict,char *word){	/* Function checks dictionary for word's corrected version. */
	/* This function can correct at most 2 letter difference. */

	/* Candidates arrays are declared to store candidate words from dictionary. */
	/* Priority --> candidates1 > candidates2 > candidates3 > candidates4 > candidates5 */

 	char word_dict[70],candidates1[3][70],candidates2[3][70],candidates3[3][70],candidates4[3][70],candidates5[3][70];
	int counter1,counter2,counter3,counter4,counter5,flag;
	FILE *D;					/* D is dictionary. */

	counter1 = 0;	counter2 = 0;	counter3 = 0;	counter4 = 0;	counter5 = 0;	flag = 0;

	if(word[0] != '\0' && strlen(word) != 1){		/* If word is empty or has only 1 letter don't start the process. */

		D = fopen(file_dict,"r");					/* file_dict is opened for reading. */

		while(fscanf(D,"%s", word_dict) != EOF){	/* Loop iterates till cursor reaches the end of file. */

			if(strlen(word) == strlen(word_dict)){	/* Checking if lengths of words are equal. */

				if(strcmp(word,word_dict) == 0){	/* If exact same word is founded exit from loop. */
				
				 	flag = 1; 
				 	break;
				}
				else if(compare_words(word,word_dict) == 1){	/* One letter difference has more priority than two letter. */

					/* If this difference is consonant to vowel than add it to the candidates array. */
					if(check_const_to_vow(word,word_dict) == 1 && counter1 <= 3){  /* Maximum candidate number is 3. */
					
						strcpy(candidates1[counter1],word_dict);
						counter1++;
					}
					else if(counter2 <= 3){	/* If condition above does not check then assign word to candidate2. */
					
						strcpy(candidates2[counter2],word_dict);
						counter2++;
					}
				}

				else if(compare_words(word,word_dict) == 2){	/* Checking if difference is two letters. */

					/* If both differences is consonant to vowel it has more priority. */ 
					if(check_const_to_vow(word,word_dict) == 2 && counter3 <= 3){
						strcpy(candidates3[counter3],word_dict);
						counter3++;
					}
					/* Checking if consonant to vowel difference is 1. */
					else if(check_const_to_vow(word,word_dict) == 1 && counter4 <= 3){
						strcpy(candidates4[counter4],word_dict);
						counter4++;
					}

					else if(counter5 <= 3){		/* If conditions above does not check then assign word to candidate5. */
						strcpy(candidates5[counter5],word_dict);
						counter5++;
					}
				}		
			}
		}/* End of iteration. */
		fclose(D);					/* Close the file. */
	}
	
	if(flag != 1){											/* If exact word was not found. */
		/* Assigning candidate to word according to the priority order. */
		/* Priority --> candidates1 > candidates2 > candidates3 > candidates4 > candidates5 */
		/* If there is a tie, second occurence will be chosen. */

		if(counter1 == 1) strcpy(word,candidates1[0]);
				
		else if(counter1 > 1) strcpy(word,candidates1[1]);			/* If it checks second occurrence is chosen. */
			
		else if(counter2 == 1) strcpy(word,candidates2[0]);			
	
		else if(counter2 > 1) strcpy(word,candidates2[1]);			/* If it checks second occurrence is chosen. */

		else if(counter3 == 1) strcpy(word,candidates3[0]);
						
		else if(counter3 > 1) strcpy(word,candidates3[1]);			/* If it checks second occurrence is chosen. */
					
		else if(counter4 == 1) strcpy(word,candidates4[0]);
				
		else if(counter4 > 1) strcpy(word,candidates4[1]);			/* If it checks second occurrence is chosen. */

		else if(counter5 == 1) strcpy(word,candidates5[0]);
				
		else if(counter5 > 1) strcpy(word,candidates5[1]);			/* If it checks second occurrence is chosen. */
	}
}/* End Of Function. */