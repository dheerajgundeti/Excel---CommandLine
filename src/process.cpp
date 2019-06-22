#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include <string.h>

#include "helpers.h"
#include "utility.h"

#ifndef TABLE_SIZE_MAX
#define TABLE_SIZE_MAX 10
#endif

void execute(char *s, cell **table, char *prev_file, char *noraml_file){
	char command[100];
	char argument[101];
	strcpy(argument, "");
	char option[10];
	strcpy(option, "");
	char* token = strtok(s, " ");
	int i = 0;

	while (token != NULL) {
		if (i == 0) strcpy(command, token);
		if (i == 1) strcpy(argument, token);
		if (i == 2) strcpy(option, token);
		token = strtok(NULL, " ");
		i++;
	}
	if (strcmp(command, "get") == 0){
		int x, y;
		x = get_x(argument);
		y = get_y(argument);
		printf("%d\n", table[x][y].data);
	}
	if (strcmp(command, "set") == 0){
		set(argument, table);
	}
	if (strcmp(command, "print") == 0){
		print_table(table, TABLE_SIZE_MAX,noraml_file);
	}
	if (i==2 && strcmp(command, "import") == 0){
		strcpy(prev_file, argument);
		noraml_file[0] = 'Y';
		import1(argument,table);
	}
	if (strcmp(command, "export") == 0){
		export1(argument, table);
	}
	if (strcmp(command, "sort") == 0){
		sort(argument, table);
	}
	if (i == 3 && strcmp(command, "import") == 0){
		noraml_file[0] = 'N';
		import2(argument, table);
	}
}