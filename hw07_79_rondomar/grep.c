#include <stdio.h>
#include <stdlib.h>

int fileSearch(char *filename, char* pattern);
int checkStringMatch(char *to_search, char *pattern);
//void printLine(int line_num, char* fileName, char* text);
int main(int argc, char **argv){

	if(argc < 3){
		fprintf(stderr, "Error: Number of arguments too low!\n");
		return 100;
	}
	
	char *pattern = argv[1];
	char *filename = argv[2]; 
	int errorCheck = 0;
	errorCheck = (fileSearch(filename, pattern));
	if(errorCheck == 1){
		fprintf(stderr, "Error: Couldn't open file!\n");
		return 100;
	}
	else if(errorCheck == 2){
		return 1;
	}
	return 0;
}

int fileSearch(char *filename, char* pattern){
	FILE *file = fopen(filename, "r");
	
		if(file == NULL){
			return 1;
		}
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	int any_match = 0;
	//char* line = (char*)malloc(size*sizeof(char)); 
	char *line;
	char array[size];
	line = array;
	//free(line);
	int line_num = 1;
	while(!feof(file)){                       
    	line = fgets(line, size, file);
    	if(line){                           
            if(checkStringMatch(line, pattern)){
            	printf("%s", line);
            	any_match++;
                //printLine(line_num, filename, line);
            }              
           line_num++;
        }
	} 
	if(!any_match){
		return 2;
	}
	//free(line);     
	fclose(file);
	//printf("\n");
	//free(line);
	return 0;
}


/*void printLine(int line_num, char* fileName, char* text){
            if(line_num){               
                    printf("%s", text);
            }
            else{
                    printf("%s %s", fileName, text);
            }
    }*/

int checkStringMatch(char *to_search, char *pattern){
    int i = 0, j = 0;
    while ((*(to_search + j) != '\0')&&(*(pattern + i) != '\0')) {
        if (*(pattern + i) != *(to_search + j)) {
            j++;
            i = 0;
        }
        else {
            i++;
            j++;
        }
    }
    if (*(pattern + i) == '\0')
        return 1;
    else
        return 0;
}
