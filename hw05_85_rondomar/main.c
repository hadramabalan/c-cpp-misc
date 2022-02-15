#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


char shift(char Char,int a){
	char temp_Char = Char + a;
	
	if(Char >= 65 && Char <= 90){
    	if((int)temp_Char >= 122){
    		temp_Char -= 52;
    	}
    	else if((int)temp_Char < 0){
    		temp_Char += 204;
    	}
    	else if((int)temp_Char > 90){
    		temp_Char += 6;
    		if((int)temp_Char > 122){
    			temp_Char -= 58;
    		}
    	}
    }
    else{
		if((int)temp_Char < 0){
			temp_Char += 198;
			if(temp_Char > 90){
				temp_Char += 6;
			}
		}
    	else if((int)temp_Char > 122){
    		temp_Char -= 58;
    	}
    	else if((int)temp_Char > 90 && (int)temp_Char < 97){
    		temp_Char += 6;
    	}
    }
    return temp_Char;
}


int main(void){
    char c;
    char *cipher, *heard_message;
    int cipher_size = 3;
    int heard_message_size = 3;
    cipher = (char*)malloc(cipher_size);
    heard_message = (char*)malloc(heard_message_size);
    int cipher_count = 0;
    int heard_message_count = 0;
    
    
    /* scan the cipher */
    while(scanf("%c", &c)){
        if(c == '\n'){
            // printf("%d\n", cipher_size);
            break;
        }
        else if(!(isalpha(c))){
    		free(cipher);
    		free(heard_message);        
            fprintf(stderr, "Error: Chybny vstup!\n");
            return 100;
        }
        else{
            ++cipher_count;
            if(cipher_count == cipher_size){
                cipher_size *= 2;
                cipher = (char*)realloc(cipher, cipher_size);
            }
            cipher[cipher_count] = c;
        }
    }
    
    /* scan the heard_message */
        while(scanf("%c", &c)){
        if(c == '\n'){
            break;
        }
        else if(!(isalpha(c))){
            fprintf(stderr, "Error: Chybny vstup!\n");
    		free(cipher);
    		free(heard_message);
            return 100;
        }
        else{
            ++heard_message_count;
            if(heard_message_count == heard_message_size){
                heard_message_size *= 2;
                heard_message = (char*)realloc(heard_message, heard_message_size);
            }
            heard_message[heard_message_count] = c;
        }
    }
    /* Compare the messages' length */
    if(cipher_count != heard_message_count){
    	free(cipher);
    	free(heard_message);
        fprintf(stderr, "Error: Chybna delka vstupu!\n");
        return 101;
    }
    /* main part */
    else{
    	int deciphered_message_size = heard_message_size;
    	char *deciphered_message;
        deciphered_message = (char*)malloc(deciphered_message_size);
        static int temp_matches;
        int max_matches = -1;
        int best_shift = -1;
        char result = 0;
        for(int a = 0; a < 52; ++a){
        	temp_matches = 0;
		    for(int i = 1; i <= cipher_count; ++i){
		    	if(((int)cipher[i] >= 65 && (int)cipher[i] <= 90) || ((int)cipher[i] >= 97 && (int)cipher[i] <= 122)){
						result = shift(cipher[i], a);
						//printf("%c = %c ", (char)result, (char)heard_message[i]);
						
						if((char)result == (char)heard_message[i]){
							temp_matches++;
							//printf("%c", result);
						}
					}
					//printf("%d", temp_matches);
					//printf("\n");
			}//printf(" %d\n", temp_matches);
			if(temp_matches > max_matches){
				max_matches = temp_matches;
				best_shift = a;
			}
				//printf("best shift: %d ", best_shift);
			if(a == 51){
				for(int i = 1; i <= cipher_count; ++i){
					deciphered_message[i] = shift(cipher[i], best_shift);
					printf("%c", deciphered_message[i]);
					//printf("best shift= %d", best_shift);
    			}
			}
        }
    	printf("\n");
    	free(deciphered_message);
    }
    
    
    


    free(cipher);
    free(heard_message);
    return 0;
}
