#include<malloc.h>	
#include <stdio.h>
#include <string.h> 
#include "expression_evaluate.h"

#define MAX_STACK_SIZE  100

struct stac{
	int *data;
	int top;
};
typedef stac stack;
stack *creatstack(){
	stack *s;
	s = (stack *)malloc(sizeof(stack));
	s->data = (int *)calloc(MAX_STACK_SIZE ,sizeof(int));
	s->top = -1;
	return s;
}
void push(stack *s, int data){
	s->top++;
	s->data[s->top] = data;
}
int top(stack *s){
	return s->top;
}
int pop(stack *s){
	if (top(s) == -1) return -1;
	int k = s->data[s->top];
	s->top--;
	return k;
}

int empty(stack *s){
	if (s->top == -1) return 1;
	return 0;
}

int precedence(char op){
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}
 
int oprn(int a, int b, char op){
	switch (op){
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	}
	return 0;
}

int isdigit(char c){
	if (c >= '0' && c <= '9') return 1;
	return 0;
}
int isopr(char c){
	if (c == '+' || c == '-' || c == '/' || c == '*') return 1;
	else return 0;
}
int evaluate(char *str){
	stack *val;
	stack *op;
	int i;
	val = creatstack();
	op = creatstack();
	int len = strlen(str);
	i = 0;
	while (str[i] != '\0'){
		if (str[i] == '('){
			push(op,str[i]);
			i++;
		} 
		else if ((str[i]=='-' && (i==0 || isopr(str[i-1])==1)) || isdigit(str[i])==1){
			int data = 0;
			int flag = 1;
			if (str[i] == '-'){
				flag = -1;
				i++;
			}
			while (i < len && isdigit(str[i])==1)
			{
				data = (data * 10) + (str[i] - '0');
				i++;
			}

			push(val,data*flag);
		}
 
		else if (str[i] == ')')
		{
			while (empty(op)==0 && op->data[top(op)] != '(')
			{
				int val2 = val->data[top(val)];
				pop(val);

				int val1 = val->data[top(val)];
				pop(val);

				char opr = op->data[top(op)];

				pop(op);
				
				push(val,oprn(val1, val2, opr));
			}

			pop(op);
			i++;
		}
		else
		{
			while (empty(op)==0 && precedence(op->data[top(op)])>= precedence(str[i])){
				int val2 = val->data[top(val)];
				pop(val);

				int val1 = val->data[top(val)];
				pop(val);

				char opr = op->data[top(op)];
				pop(op);

				push(val,oprn(val1, val2, opr));
			}

			push(op,str[i]);
			i++;
		}
	}
	while (empty(op)==0){
		int val2 = val->data[top(val)];
		pop(val);

		int val1 = val->data[top(val)];
		pop(val);

		char opr = op->data[top(op)];
		pop(op);
		push(val,oprn(val1, val2, opr));
	}
 
	return val->data[top(val)];
}