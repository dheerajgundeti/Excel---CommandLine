#ifndef _helpers_h
#define _helpers_h

struct Cell{
	int data;
	int flag;
	char s[50];
};
typedef Cell cell;

void purify(char *s);
void print_table(cell **table, int n, char *normal_file);
void import1(char *s, cell **table);
void export1(char *s, cell **table);
void set(char *s, cell **table);
void sort(char *s, cell **table);
void import2(char *file, cell **table);


#endif