#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define STACKSIZE 100
#define MAXSIZE 50
 
typedef char ElemType;
typedef struct
{
	ElemType stack[STACKSIZE];
	int top;
}SeqStack;
typedef struct
{
	float data[MAXSIZE];
	int top;
}OpStack;
void InitStack(SeqStack *S)//将栈S初始化为空栈
{
	S->top = 0;
}
int StackEmpty(SeqStack S)//判断栈是否为空，栈为空返回1，否则返回0
{
	if(0 == S.top)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int GetTop(SeqStack S,ElemType *e)//取栈顶元素，将栈顶元素值返回给e，并返回1表示成功，返回0表示失败
{
	if(S.top <= 0)
	{
		printf("栈已经空！\n");
		return 0;
	}
	else
	{
		*e = S.stack[S.top-1];//取栈顶元素
		return 1;
	}
}
int PushStack(SeqStack *S,ElemType e)//进栈操作
//将元素e进栈，元素进栈成功返回1，否则返回0
{
	if(S->top >= STACKSIZE-1)
	{
		printf("栈已满，不能入栈！");
		return 0;
	}
	else
	{
		S->stack[S->top] = e;
		S->top++;
		return 1;
	}
}
int PopStack(SeqStack *S,ElemType *e)//出栈操作
{
	if(S->top <= 0)
	{
		printf("栈已经没有元素，不能出栈！\n");
		return 0;
	}
	else
	{
		S->top--;
		*e = S->stack[S->top];
		return 1;
	}
}
int StackLength(SeqStack S)//返回栈长度
{
	return S.top;
}
void ClearStack(SeqStack *S)//清空栈
{
	S->top = 0;
}
void TranslateExpress(char s1[],char s2[])//把中缀表达式转换成后缀表达式
{
	SeqStack S;//定义一个栈，用于存放运算符
	char ch;
	ElemType e;
	int i = 0,j = 0;
	InitStack(&S);
	ch = s1[i];
	i++;
	while(ch != '\0')//依次扫描中缀表达式中的每个字符
	{
		switch(ch)
		{
		case '('://如果当前字符是左括号，则将其进栈
			PushStack(&S,ch);
			break;
		case ')'://如果是右括号，将栈中的操作符出栈，将其存进数组s2中
			while(GetTop(S,&e) && e != '(')
			{
				PopStack(&S,&e);
				s2[j] = e;
				j++;
			}
			PopStack(&S,&e);//将左括号出栈
			break;
		case '+':
		case '-':
			while(!StackEmpty(S) && GetTop(S,&e) && e != '(')//如果遇到的是‘+’，‘-’,
				//因为其优先级低于栈顶运算符的优先级。所以先将栈顶字符出栈，并将其存入s2中，
				//然后将当前运算符进栈
			{
				PopStack(&S,&e);
				s2[j]= e;
				j++;
			}
			PushStack(&S,ch);//当前运算符进栈
			break;
		case '*':
		case '/':
			while(!StackEmpty(S) && GetTop(S,&e) && e == '/' || e == '*')
				//如果遇到的是‘*’，‘/’,先将同级运算符出栈，并将其存入s2中，
				//然后将当前运算符进栈
			{
				PopStack(&S,&e);
				s2[j]= e;
				j++;
			}
			PushStack(&S,ch);//当前运算符进栈
			break;    
		case ' '://如果遇到空格，忽略
			break;
		default://如果遇到的是操作符，则将操作符直接送入数组s2中，
			//并在其后添加一个空格，用来分隔数字字符
			while(ch >= '0'&&ch <= '9')
			{
				s2[j] = ch;
				j++;
				ch = s1[i];
				i++;
			}
			i--;
			s2[j] = ' ';
			j++;
		}
		ch = s1[i];//读入下一个字符，准备处理
		i++;
	}
	while(!StackEmpty(S))//将栈中所有剩余的运算符出栈，送入数组s2中
	{
		PopStack(&S,&e);
		s2[j]= e;
		j++;
	}
	s2[j]= '\0';
	
}
/*float ComputeExpress(char a[])//计算后缀表达式的值
{
	OpStack S;//定义一个操作数栈
	int i = 0,value;
	float x1,x2;
	float result;
	S.top = -1;//初始化栈
	while(a[i] != '\0')//依次扫描后缀表达式中的每个字符
	{
		if(a[i] != ' '&&a[i] >= '0'&&a[i] <= '9')//当前字符为数字字符
		{
			value = 0;
			while(a[i] != ' ')
			{
				value = 10*value+a[i]-'0';//如果数字字符不是空格，说明数字字符是两位数
				i++;
			}
			S.top++;
			S.data[S.top] = value;//处理之后将数字进栈
		}
		else
		{
			switch(a[i])//将栈中的数字出栈两次，然后用当前的运算符进行运算，再将结果入栈
			{
			case '+':
				x1 = S.data[S.top];
				S.top--;
				x2 = S.data[S.top];
				S.top--;
				result = x1+x2;
				S.top++;
				S.data[S.top] = result;
				break;
			case '-':
				x1 = S.data[S.top];
				S.top--;
				x2 = S.data[S.top];
				S.top--;
				result = x2-x1;
				S.top++;
				S.data[S.top] = result;
				break;
			case '*':
				x1 = S.data[S.top];
				S.top--;
				x2 = S.data[S.top];
				S.top--;
				result = x1*x2;
				S.top++;
				S.data[S.top] = result;
				break;
			case '/':
				x1 = S.data[S.top];
				S.top--;
				x2 = S.data[S.top];
				S.top--;
				result = x2/x1;
				S.top++;
				S.data[S.top] = result;
				break;
			}
			i++;
		}
	}
	if(S.top <= 0)//如果栈不空，将结果出栈，并返回
	{
		result = S.data[S.top];
		S.top--;
		if(S.top == -1)
		{
			return result;
		}
		else
		{
			printf("表达式错误！");
			return 0;
		}
	}
	return 0;
}*/
int main(void)
{
	char a[MAXSIZE],b[MAXSIZE];
	float f;
	printf("请输入一个表达式：");
	gets(a);
//	printf("中缀表达式是：%s\n",a);
	TranslateExpress(a,b);
	printf("后缀表达式是：%s\n",b);
//	f = ComputeExpress(b);
//	printf("计算结果是：%.2f\n",f);
	return 0;
}
/*
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 50
int ji(char x)
{
	switch(x)
	{
		case '+':
		case '-':return 1;break;
		case '*':
		case '/':return 2;break;
		case '(':return 0;break;
		case '#':return -1; 
	}
}
int main()
{
	char Stack[N];
	int top=0;
	Stack[top]='#';
	char a[100];
	gets(a);
	int n;
	n=strlen(a);
	int i=0;
	while(n)
	{
		if(a[i]<='z'&&a[i]>='a')
		printf("%c",a[i]);
		else if(a[i]=='+'||a[i]=='-'||a[i]=='*'||a[i]=='/')
		{
		while(ji(a[i])<=ji(Stack[top]))
		{
		printf("%c",Stack[top]);
		top--;
	    }
	    top++;
	    Stack[top]=a[i];
	}
	    else if(a[i]=='(')
	    {
	    	top++;
	        Stack[top]=a[i];
	}
	    else if(a[i]==')')
	    	{
			while(Stack[top]!='(')
			{
	    	printf("%c",Stack[top]);
	    	top--;
			}
			top--;
		}
		n--;
		i++;
	}
	while(top!=0)
		{
		printf("%c",Stack[top]);
		top--;
	}
	
}
 */ 




