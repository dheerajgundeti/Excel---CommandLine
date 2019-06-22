#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "helpers.h"
#include "utility.h"
#include "expression_evaluate.h"

#ifndef TABLE_SIZE_MAX
#define TABLE_SIZE_MAX 10
#endif


int get_x(char *s){
	int i;
	int x = 0;
	for (i = 0; s[i] != '\0'; i++){
		if (s[i] == '=') break;
		if (s[i] >= '0' && s[i] <= '9') x = x * 10 + s[i] - '0';
	}
	return x;
}
int get_y(char *s){
	return s[0] - 'a';
}
char *get_dat(char *s){
	char *ans;
	ans = (char *)calloc(100, sizeof(char));
	int k = 0, i = 0;
	while (s[i] != '(') {
		ans[k] = s[i];
		i++;
		k++;
	}
	ans[k] = '\0';
	return ans;
}
char *get_exp_file(char *s){
	char *ans;
	ans = (char *)calloc(100, sizeof(char));
	int k = 0, i = 0;
	while (s[i] != '(') i++;
	i++;
	while (s[i] != ')') {
		ans[k] = s[i];
		i++;
		k++;
	}
	ans[k] = '\0';
	return ans;
}

char *get_expression(char *s){
	char *ans;
	ans = (char *)calloc(100, sizeof(char));
	int k = 0, i = 0;
	while (s[i] != '=') i++;
	i++;
	while (s[i] != '\0') {
		ans[k] = s[i];
		i++;
		k++;
	}
	ans[k] = s[i];
	return ans;
}
int check(char *s){
	int i = 0;
	while (s[i] != '\0'){
		if (s[i] >= 'a' && s[i] <= 'z') return 0;
		i++;
	}
	return 1;
}
void fun(cell **table,char *temp,char *ans,int *ind,int **flags,int *flag){
	int x, y;
	if (check(temp) == 1){
		int in = 0;
		while (temp[in] != '\0'){
			ans[ind[0]] = temp[in];
			in++;
			ind[0]++;
		}
	}
	else{
		x = get_x(temp);
		y = get_y(temp);
		if (flags[x][y] == 1){
			flag[0] = 1;
			return;
		}
		flags[x][y] = 1;
		change(table, ind, ans, temp, flags, flag);
		flags[x][y] = 0;
	}
}
void change(cell **table, int *ind, char *ans, char *sd, int **flags, int *flag){
	int x, y;
	y = get_y(sd);
	x = get_x(sd);
	if (table[x][y].flag == 0){
		char buffer[20];
		_itoa(table[get_x(sd)][get_y(sd)].data, buffer, 10);
		int i = 0;
		while (buffer[i] != '\0'){
			ans[ind[0]] = buffer[i];
			ind[0]++;
			i++;
		}
		return;
	}
	int i;
	char *temp;
	temp = (char *)calloc(10, sizeof(char));
	char *s;
	int k = 0;
	s = (char *)calloc(50, sizeof(char));
	strcpy(s, table[get_x(sd)][get_y(sd)].s);
	for (i = 0; s[i] != '\0'; i++){
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')'){
			temp[k] = '\0';
			fun(table, temp, ans, ind, flags, flag);
			ans[ind[0]] = s[i];
			ind[0]++;
			k = 0;
		}
		else{
			temp[k] = s[i];
			k++;
		}
	}
	temp[k] = '\0';
	if (s[i - 1] != ')'){
		fun(table, temp, ans, ind, flags, flag);
	}
}
char *replace_withdata(cell **table, char *s, int **flags, int *flag){
	char *ans;
	ans = (char *)calloc(1000, sizeof(char));
	int *ind;
	int i, k = 0;
	ind = (int *)calloc(1, sizeof(int));
	char *temp;
	temp = (char *)calloc(10, sizeof(char));
	ind[0] = 0;
	for (i = 0; s[i] != '\0'; i++){
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')'){
			temp[k] = '\0';
			fun(table, temp, ans, ind, flags, flag);
			ans[ind[0]] = s[i];
			ind[0]++;
			k = 0;
		}
		else{
			temp[k] = s[i];
			k++;
		}
	}
	temp[k] = '\0';
	ans[ind[0]] = '\0';
	if (s[i - 1] != ')'){
		fun(table, temp, ans, ind, flags, flag);
	}
	ans[ind[0]] = '\0';
	return ans;
}

int modify(cell **table, int x, int y){
	int **flags;
	int i;
	flags = (int **)calloc(TABLE_SIZE_MAX, sizeof(int));
	int *flag;
	flag = (int *)calloc(1, sizeof(int));
	for (i = 0; i < TABLE_SIZE_MAX; i++) flags[i] = (int *)calloc(TABLE_SIZE_MAX, sizeof(int));
	char *expr = replace_withdata(table, table[x][y].s, flags, flag);
	if (flag[0] == 1){
		printf("INVALID EXPRESSION\n");
		strcpy(table[x][y].s, "0");
		return 0;
	}
	int res = evaluate(expr);
	table[x][y].data = res;
	return res;
}