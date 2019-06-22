#ifndef _UTILITY_H
#define _UTILITY_H

#include "helpers.h"

int get_x(char *s);
int get_y(char *s);
char *get_dat(char *s);
char *get_exp_file(char *s);
int modify(cell **table, int x, int y);
char *replace_withdata(cell **table, char *s, int **flags, int *flag);
void change(cell **table, int *ind, char *ans, char *sd, int **flags, int *flag);
int check(char *s);
char *get_expression(char *s);

#endif