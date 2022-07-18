<h1>Functions</h1>

1- Fixes the spelling errors in the given text according to the dictionary test. First one changes if the word is not in the dictionary, and it has one letter difference. If there are more than one word with this situation consonant the vowel change preeceds others. There is also a function which fixes two letter difference error.  
- void fix_spelling_error(const char *file_dict, char *file_text);  
- void find_best_correction(const char *file_dict,char *word_text);  
- void correct_words(const char *file_dict,char *word);  
- int compare_words(char *word,char *word_dict);  
- int check_const_to_vow(char *word,char *word_dict);	 
- void fix_spelling_error2(const char *file_dict, char *file_text);  