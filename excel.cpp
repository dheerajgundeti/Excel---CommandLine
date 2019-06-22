#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include <string.h>

#include "helpers.h"
#include "process.h"
#include "expression_evaluate.h"

#define TABLE_SIZE_MAX 10

int main(){
	
	char *command;
	int counter;
	command = (char *)calloc(100, sizeof(char));
	cell **table;
	table = (cell **)calloc(TABLE_SIZE_MAX, sizeof(cell));
	for (counter = 0; counter < TABLE_SIZE_MAX; counter++)
		table[counter] = (cell *)calloc(TABLE_SIZE_MAX, sizeof(cell));
	int i, j;
	for (i = 0; i < TABLE_SIZE_MAX; i++){
		for (j = 0; j < TABLE_SIZE_MAX; j++)
			strcpy(table[i][j].s, "0");
	}
	char *noraml_file;
	noraml_file = (char *)malloc(sizeof(char));
	noraml_file[0] = 'Y';

	char *prev_file;
	prev_file = (char *)calloc(50, sizeof(char));
	strcpy(prev_file, "Default.csv");
	while (1){
		printf(">");
		gets(command);
		purify(command);
		if (strcmp(command, "exit") == 0)
			return 0;
		if (strcmp(command, "save") == 0){
			export1(prev_file, table);
		}
		else
			execute(command,table,prev_file,noraml_file);
	}
	return 0;
}



