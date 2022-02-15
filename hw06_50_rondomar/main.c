#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void){
	int **matrix1;
	int **matrix2;
	//int **matrix3;
	int row1 = 0;
	int col1 = 0;
	int row2 = 0;
	int col2 = 0;
	//int matrix1_size = 0;
	//int matrix2_size = 0;
	
	/* matrix 1 */
	
	if (!(scanf("%d %d", &row1, &col1))){
		fprintf(stderr, "Error: Chybny vstup!\n");
		return 100;
	}
	else{
		/* scan first matrix */
		//matrix1_size = row1*col1;
		matrix1 = (int **)malloc(row1 * sizeof(int*));
		for(int i = 0; i < row1; ++i){
			matrix1[i] = (int *)malloc(col1 * sizeof(int));
		}
		for(int i = 0; i < row1; ++i){
			for(int u = 0; u < col1; ++u){
				if(!(scanf("%d", &matrix1[i][u]))){
					fprintf(stderr, "Error: Chybny vstup!\n");
					for(int i = 0; i < row1; ++i){
						free(matrix1[i]);
					}
					free(matrix1);
					return 100;
				}
			}
		}
	}
		
		/* scan operation */
		char operator;
		while(isspace(scanf("%c", &operator))){
			continue;
		}
		if(!(scanf("%c", &operator))){
				fprintf(stderr, "Error: Chybny vstup!\n");
				for(int i = 0; i < row1; ++i){
					free(matrix1[i]);
				}
				free(matrix1);
				return 100;
		}
		else if(operator != '+' && operator != '-' && operator != '*'){
			fprintf(stderr, "Error: Chybny vstup!\n");
			for(int i = 0; i < row1; ++i){
				free(matrix1[i]);
			}
			free(matrix1);
			return 100;
		}
	
	/* matrix 2 */
	if (!(scanf("%d %d", &row2, &col2))){
		fprintf(stderr, "Error: Chybny vstup!\n");
		for(int i = 0; i < row1; ++i){
			free(matrix1[i]);
		}
		free(matrix1);
		return 100;
	}
	else{
		/* scan second matrix */
		//matrix2_size = row2*col2;
		matrix2 = (int **)malloc(row2 * sizeof(int*));
		for(int i = 0; i < row2; ++i){
			matrix2[i] = (int *)malloc(col2 * sizeof(int));
		}
		for(int i = 0; i < row2; ++i){
			for(int u = 0; u < col2; ++u){
				if(!(scanf("%d", &matrix2[i][u]))){
					fprintf(stderr, "Error: Chybny vstup!\n");
					for(int i = 0; i < row1; ++i){
						free(matrix1[i]);
					}
					free(matrix1);
					for(int i = 0; i < row2; ++i){
						free(matrix2[i]);
					}
					free(matrix2);
					return 100;
				}
			}
		}
	}
		
	/* Do the operation */
	if(operator == '+'){
		if(row1 != row2 || col1 != col2){
			fprintf(stderr, "Error: Chybny vstup!\n");
			for(int i = 0; i < row1; ++i){
				free(matrix1[i]);
			}
			free(matrix1);
			for(int i = 0; i < row2; ++i){
				free(matrix2[i]);
			}
			free(matrix2);
			return 100;
		}
		else{
			printf("%d %d\n", row1, col1);
			for(int i = 0; i < row1; ++i){
				for(int u = 0; u < col1; ++u){
					printf("%d", (matrix1[i][u]) + (matrix2[i][u]));
					if(u < col1 -1){
						printf(" ");
					}
				}
				printf("\n");
			}
		}
	}
	else if(operator == '-'){
		if(row1 != row2 || col1 != col2){
			fprintf(stderr, "Error: Chybny vstup!\n");
			for(int i = 0; i < row1; ++i){
				free(matrix1[i]);
			}
			free(matrix1);
			for(int i = 0; i < row2; ++i){
				free(matrix2[i]);
			}
			free(matrix2);
			return 100;
		}
		else{
			printf("%d %d\n", row1, col1);
			for(int i = 0; i < row1; ++i){
				for(int u = 0; u < col1; ++u){
					printf("%d", (matrix1[i][u]) - (matrix2[i][u]));
					if(u != col1 - 1){
						printf(" ");
					}
				}
				printf("\n");
			}
		}
	}
	else if(operator == '*'){
		if(col1 != row2){
			fprintf(stderr, "Error: Chybny vstup!\n");
			for(int i = 0; i < row1; ++i){
				free(matrix1[i]);
			}
			free(matrix1);
			for(int i = 0; i < row2; ++i){
				free(matrix2[i]);
			}
			free(matrix2);
			return 100;		
		}
		else{
			printf("%d %d\n", row1, col2);
			for(int i = 0; i < row1; ++i){
				for(int u = 0; u < col2; ++u){
					int temp_result = 0;
					int result = 0;
					for(int o = 0; o < col1; ++o){
						temp_result = matrix1[i][o] * matrix2[o][u];
						result += temp_result;
					}
					printf("%d", result);
					if(u != col2 - 1){
						printf(" ");
					}
				}
				printf("\n");
			}
		}
	}
	else{
		fprintf(stderr, "Error: Chybny vstup!\n");
		for(int i = 0; i < row1; ++i){
			free(matrix1[i]);
		}
		free(matrix1);
		for(int i = 0; i < row2; ++i){
			free(matrix2[i]);
		}
		free(matrix2);
		return 100;
	}

	for(int i = 0; i < row1; ++i){
		free(matrix1[i]);
	}
	free(matrix1);
	for(int i = 0; i < row2; ++i){
		free(matrix2[i]);
	}
	free(matrix2);
	
	return 0;
}
