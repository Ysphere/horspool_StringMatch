/*
Name: Yuhang Xu
Prof: FangJu Wang
Date: Mar.13.2017
ID: 0926193
CIS*3490
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/timeb.h>

int horspool(int wordLen, char * word, int stringLength, char * str,int table[]);

void Ttable(int wordLen, char * word, int table[]); /*pre generate table*/

int main(int argc, char **argv) {

	FILE *fp;
	char *data = argv[1];
	char line[400];
	char bl[200];
	char *pch;
	int i = 0;
	int length = 0;
	int j;
	char input[20];
	char foo[44050][85];
	struct timeb t1,t2;
    long t;
    int letter = 0;
    int table[127];
	fp = fopen(data, "r");

    printf("Please enter your input\n");
	scanf("%s", input);
	length = strlen(input);
	
	Ttable(length,input,table);
	
	while(fgets(line, sizeof(line), fp)) { //parsing
		pch = strtok (line,"\n");
        while (pch != NULL){ 
        	for(j = 0; j<strlen(pch); j++){
        		char b = pch[j];
				int ch = (int)b;
				if(ch<0){/*Ignore all french charcter*/
					pch[j] = '-';
					
				}
        	}
        	//printf("%lu\n", strlen(pch));
        	strcpy(foo[i],pch);
        	i++;
        	
        	pch = strtok (NULL, "\n");
        }
	}
	ftime(&t1); /*starting time*/
	for(j = 0; j<i; j++){
		strcpy(bl,foo[j]);
		letter = letter + horspool(length, input, strlen(bl), bl,table);

	}
	
	ftime(&t2); /* finish time*/

	t=(t2.time-t1.time)*1000+(t2.millitm-t1.millitm);

	printf("Total found: %d time used  %ld msec\n",letter,t);
	
	return 0;
}

void Ttable(int wordLen, char * word, int table[]){

	int k;
	int j;

	for(k = 0; k <127; k++){ /*fill in the ascii table*/
		table[k] = wordLen; // default mode
	}


	for(j = 0; j<wordLen-1; j++){
		char b = word[j];
		int ch = (int)b;
			table[ch] = wordLen - 1 - j; // special shift
			
	}



}

int horspool(int wordLen, char * word, int stringLength, char * str,int table[]){

	int count = 0;
	int k;
	for(k = 0; k<stringLength; k++){
		
		if(word[wordLen-1] != str[k+ wordLen-1]){ // if the end is not equal
			char a = str[k+ wordLen-1];
			int ah = (int)a;
			k = k + table[ah]-1;
		}else { /*If the end char is the same */
			int p = 0; // count the number of equal letter
			int bb = wordLen-1;
			while(bb >=0){ /*check string*/
				if(word[bb] == str[k+ bb]){
					p++;
				}
				bb--;
			}

			if(p == wordLen){
				count++;
			}
			char a = str[k+ wordLen-1];
			int ah = (int)a;
			k = k + table[ah]-1;
		}
	}

	return count;
}