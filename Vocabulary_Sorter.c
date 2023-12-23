#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 100
#define MAX_WORDS 1000

/// @brief This function sorts the array of strings in alphabetical order
/// @param a holds the array of strings that are given by the user
/// @param n holds the number of strings in the array given
/// @return returns nothing
void selection_sort(char a[][MAX_LEN],int n);

/// @brief This program takes in command line arguements of a input and output txt file, it checks if the user entered at least 3 arguments
/// @brief If that passes then two FILE pointers are made to read and write, it starts with reading in the second command line argument and scaning each string in the 2 dimesional array str
/// @brief After that each words is converted to uppercase and then it is sorted from the function called selection_sort
/// @brief Then a second array of strings is made to hold each unique string from the str array, then the third arguement creates a txt file to holds that words with a number next it to show how many words there are
/// @param argc holds the amount of arguments give by the user
/// @param *argv holds an array of strings for each arguement given by the user
/// @return returns 0 if the code runs properly, but returns 1 if it failed
int main(int argc, char *argv[]){
	int i = 0,j,k,uniqueStrs = 0,num = 1;
	char str[MAX_WORDS][MAX_LEN];
	char ustr[MAX_WORDS][MAX_LEN];
	if(argc > 2){
		FILE *rfp;
		FILE *wfp;
		rfp = fopen(argv[1], "r");
		if(rfp == NULL){
			printf("Error opening file.\n");
			return 1;	
		}
		while(!feof(rfp)&&!ferror(rfp)){	
			fscanf(rfp,"%s",str[i]);
			int len = strlen(str[i]);
			for(j=0;j<len;j++)
				str[i][j] = toupper(str[i][j]);	
			i++;
		}
		selection_sort(str,i);
		for(j=0;j<i;j++){
			int duplicate = 0;
			for(k=0;k<uniqueStrs;k++){
				if(strcmp(str[j],ustr[k]) == 0){
					duplicate = 1;
					break;
				}
			}
			if(duplicate == 0){
				strcpy(ustr[uniqueStrs], str[j]);
				uniqueStrs++;
			}
		}
		wfp = fopen(argv[2],"w");
		if(wfp == NULL){
			printf("Error opening file.\n");
			return 1;
		}
		int k = 1;
		while(k<uniqueStrs)	
			fprintf(wfp,"%d %s\n", num++,ustr[k++]);
	}
	else{
		printf("Missing amount of arguments.\n");
		return 1;
	}
	return 0;
}

void selection_sort(char a[][MAX_LEN], int n){
	int i, largest = 0;
	char temp[MAX_LEN];
	if (n == 1)
		return;
	for (i = 1; i < n; i++)
		if(strcmp(a[i],a[largest]) > 0)
			largest = i;
	if (largest < n - 1) {
		strcpy(temp,a[n-1]);
		strcpy(a[n-1],a[largest]);
		strcpy(a[largest],temp);
	}
	selection_sort(a, n - 1);
}
