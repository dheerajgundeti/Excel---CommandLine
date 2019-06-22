#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "helpers.h"
#include "utility.h"

#ifndef TABLE_SIZE_MAX
#define TABLE_SIZE_MAX 10
#endif

struct temp_cell{
	cell pres;
	int prev;
};
typedef struct temp_cell tcell;

void purify(char *s){
	int i=0,ind=0;
	while (s[i] == ' '){
		i++;
	}
	for (; s[i] != '\0'; i++){
		if (s[i] != ' '){
			s[ind] = s[i];
			ind++;
		}
		else if (s[i] == ' ' && s[i + 1] != ' '){
			s[ind] = s[i];
			ind++;
		}
	}
	s[ind] = '\0';
	for (i = 0; s[i] != '\0'; i++){
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
	}
}

void import1(char *file, cell **table){
	FILE *fp;
	int i = strlen(file);
	if (strstr(file, ".csv") == NULL){
		file[i] = '.';
		file[i + 1] = 'c';
		file[i + 2] = 's';
		file[i + 3] = 'v';
		file[i + 4] = '\0';
	}
	fp = fopen(file, "r");
	if (fp == NULL){
		printf("FILE NOT EXIST\n");
		return;
	}
	char *line;
	line = (char *)calloc(1000,sizeof(char));
	int j=0;
	i = 0;
	while (fscanf(fp, "%s", line)==1){
		char* token = strtok(line, ",");
		while (token != NULL) {
			char *dat; 
			dat = get_dat(token);
			int ok = atoi(dat);
			table[i][j].data = ok;
			char *temp;
			temp = (char *)calloc(50, sizeof(char));
			temp = get_exp_file(token);
			strcpy(table[i][j].s, temp);
			token = strtok(NULL, ",");
			j++;
		}
		i++;
	}
}
void export1(char *file,cell **table){
	FILE *fp;
	int i = strlen(file);
	if (strstr(file, ".csv") == NULL){
		file[i] = '.';
		file[i + 1] = 'c';
		file[i + 2] = 's';
		file[i + 3] = 'v';
		file[i + 4] = '\0';
	}
	fp = fopen(file, "w");
	if (fp == NULL){
		printf("FILE NOT EXIST\n");
		return;
	}
	int  j;
	for (i = 0; i < TABLE_SIZE_MAX; i++){
		for (j = 0; j < TABLE_SIZE_MAX-1; j++)
			fprintf(fp, "%d(%s),", table[i][j].data, table[i][j].s);
		fprintf(fp, "%d(%s)\n", table[i][TABLE_SIZE_MAX - 1].data, table[i][TABLE_SIZE_MAX - 1].s);
	}
	fclose(fp);
}
void set(char *s, cell **table){
	int x = get_x(s);
	int y = get_y(s);
	char *expression;
	expression = get_expression(s);
	strcpy(table[x][y].s, expression);
	if (check(expression) == 0) table[x][y].flag = 1;
	table[x][y].data = modify(table, x, y);
}

void print_table(cell **table, int n,char *normal_file){
	int i, j;
	for (j = 1; j < (n + 2) * 7; j++) printf("_");
	printf("\n");
	for (i = 0; i < n; i++){
		printf("|%7c", 'A' + i);
	}
	printf("|\n");
	for (i = 0; i < n; i++){
		for (j = 1; j < (n+2) * 7; j++) printf("_");
		printf("\n");
		for (j = 0; j < n; j++){
			if (normal_file[0] == 'Y')
				printf("|%7d", modify(table,i,j));
			else
				printf("|%7s", table[i][j].s);
		}
		printf("|\n");
	}
	for (j = 1; j < (n + 2) * 7; j++) printf("_");
	printf("\n");
}
void Sort(tcell arr[], int n)
{
	int i, j;
	tcell key;
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;
		while (j >= 0 && arr[j].pres.data > key.pres.data) {
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1].pres.data = key.pres.data;
		strcpy(arr[j + 1].pres.s, key.pres.s);
		arr[j + 1].pres.flag = key.pres.flag;
	}
}
void change(cell **table,int x,int y,int *dict,int flag){
	int i=0;
	while (table[x][y].s[i] != '\0'){
		if (flag == 1 && table[x][y].s[i] >= '0' && table[x][y].s[i] <= '9'){
			table[x][y].s[i] = dict[table[x][y].s[i] - '0'] + '0';
		}
		else if (flag == 0 && table[x][y].s[i] >= 'a' && table[x][y].s[i] <= 'z'){
			table[x][y].s[i] = dict[table[x][y].s[i] - 'a'] + 'a';
		}
		i++;
	}
}
void sort(char *s, cell **table){
	int i,flag,ind;
	if (check(s) == 1){
		flag = 0;
		ind = atoi(s);
	}
	else{
		flag = 1;
		ind = s[0] - 'a';
	}
	tcell *arr;
	arr = (tcell *)calloc(TABLE_SIZE_MAX, sizeof(tcell));
	for (i = 0; i < TABLE_SIZE_MAX; i++){
		arr[i].prev = i;
	}
	for (i = 0; i < TABLE_SIZE_MAX; i++){
		if (flag == 0){
			arr[i].pres.data = table[ind][i].data;
			strcpy(arr[i].pres.s,table[ind][i].s);
			arr[i].pres.flag = table[ind][i].flag;
		}
		else{
			arr[i].pres.data = table[i][ind].data;
			strcpy(arr[i].pres.s, table[i][ind].s);
			arr[i].pres.flag = table[i][ind].flag;
		}
	}
	Sort(arr, TABLE_SIZE_MAX);
	int *dict;
	dict = (int *)calloc(TABLE_SIZE_MAX, sizeof(int));
	for (i = 0; i < TABLE_SIZE_MAX; i++){
		dict[arr[i].prev] = i;
	}
	for (i = 0; i < TABLE_SIZE_MAX; i++){
		if (flag == 0){
			table[ind][i].data = arr[i].pres.data;
			table[ind][i].flag = arr[i].pres.flag;
			strcpy(table[ind][i].s, arr[i].pres.s);
			if (table[ind][i].flag == 1)
				change(table, ind, i, dict, flag);
		}
		else{
			table[i][ind].data = arr[i].pres.data;
			table[i][ind].flag = arr[i].pres.flag;
			strcpy(table[i][ind].s,arr[i].pres.s);
			if (table[i][ind].flag==1)
				change(table, i, ind, dict, flag);
		}
	}
}

void import2(char *file, cell **table){
	FILE *fp;
	int i = strlen(file);
	if (strstr(file, ".csv") == NULL){
		file[i] = '.';
		file[i + 1] = 'c';
		file[i + 2] = 's';
		file[i + 3] = 'v';
		file[i + 4] = '\0';
	}
	fp = fopen(file, "r");
	if (fp == NULL){
		printf("FILE NOT EXIST\n");
		return;
	}
	char *line;
	line = (char *)calloc(1000, sizeof(char));
	int j = 0;
	i = 0;
	while (fscanf(fp, "%s", line) == 1){
		char* token = strtok(line, ",");
		j = 0;
		while (token != NULL) {
			char *temp;
			temp = (char *)calloc(100, sizeof(char));
			temp = get_exp_file(token);
			strcpy(table[i][j].s, temp);
			token = strtok(NULL, ",");
			j++;
		}
		i++;
	}
}