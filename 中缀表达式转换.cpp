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
void InitStack(SeqStack *S)//��ջS��ʼ��Ϊ��ջ
{
	S->top = 0;
}
int StackEmpty(SeqStack S)//�ж�ջ�Ƿ�Ϊ�գ�ջΪ�շ���1�����򷵻�0
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
int GetTop(SeqStack S,ElemType *e)//ȡջ��Ԫ�أ���ջ��Ԫ��ֵ���ظ�e��������1��ʾ�ɹ�������0��ʾʧ��
{
	if(S.top <= 0)
	{
		printf("ջ�Ѿ��գ�\n");
		return 0;
	}
	else
	{
		*e = S.stack[S.top-1];//ȡջ��Ԫ��
		return 1;
	}
}
int PushStack(SeqStack *S,ElemType e)//��ջ����
//��Ԫ��e��ջ��Ԫ�ؽ�ջ�ɹ�����1�����򷵻�0
{
	if(S->top >= STACKSIZE-1)
	{
		printf("ջ������������ջ��");
		return 0;
	}
	else
	{
		S->stack[S->top] = e;
		S->top++;
		return 1;
	}
}
int PopStack(SeqStack *S,ElemType *e)//��ջ����
{
	if(S->top <= 0)
	{
		printf("ջ�Ѿ�û��Ԫ�أ����ܳ�ջ��\n");
		return 0;
	}
	else
	{
		S->top--;
		*e = S->stack[S->top];
		return 1;
	}
}
int StackLength(SeqStack S)//����ջ����
{
	return S.top;
}
void ClearStack(SeqStack *S)//���ջ
{
	S->top = 0;
}
void TranslateExpress(char s1[],char s2[])//����׺���ʽת���ɺ�׺���ʽ
{
	SeqStack S;//����һ��ջ�����ڴ�������
	char ch;
	ElemType e;
	int i = 0,j = 0;
	InitStack(&S);
	ch = s1[i];
	i++;
	while(ch != '\0')//����ɨ����׺���ʽ�е�ÿ���ַ�
	{
		switch(ch)
		{
		case '('://�����ǰ�ַ��������ţ������ջ
			PushStack(&S,ch);
			break;
		case ')'://����������ţ���ջ�еĲ�������ջ������������s2��
			while(GetTop(S,&e) && e != '(')
			{
				PopStack(&S,&e);
				s2[j] = e;
				j++;
			}
			PopStack(&S,&e);//�������ų�ջ
			break;
		case '+':
		case '-':
			while(!StackEmpty(S) && GetTop(S,&e) && e != '(')//����������ǡ�+������-��,
				//��Ϊ�����ȼ�����ջ������������ȼ��������Ƚ�ջ���ַ���ջ�����������s2�У�
				//Ȼ�󽫵�ǰ�������ջ
			{
				PopStack(&S,&e);
				s2[j]= e;
				j++;
			}
			PushStack(&S,ch);//��ǰ�������ջ
			break;
		case '*':
		case '/':
			while(!StackEmpty(S) && GetTop(S,&e) && e == '/' || e == '*')
				//����������ǡ�*������/��,�Ƚ�ͬ���������ջ�����������s2�У�
				//Ȼ�󽫵�ǰ�������ջ
			{
				PopStack(&S,&e);
				s2[j]= e;
				j++;
			}
			PushStack(&S,ch);//��ǰ�������ջ
			break;    
		case ' '://��������ո񣬺���
			break;
		default://����������ǲ��������򽫲�����ֱ����������s2�У�
			//����������һ���ո������ָ������ַ�
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
		ch = s1[i];//������һ���ַ���׼������
		i++;
	}
	while(!StackEmpty(S))//��ջ������ʣ����������ջ����������s2��
	{
		PopStack(&S,&e);
		s2[j]= e;
		j++;
	}
	s2[j]= '\0';
	
}
/*float ComputeExpress(char a[])//�����׺���ʽ��ֵ
{
	OpStack S;//����һ��������ջ
	int i = 0,value;
	float x1,x2;
	float result;
	S.top = -1;//��ʼ��ջ
	while(a[i] != '\0')//����ɨ���׺���ʽ�е�ÿ���ַ�
	{
		if(a[i] != ' '&&a[i] >= '0'&&a[i] <= '9')//��ǰ�ַ�Ϊ�����ַ�
		{
			value = 0;
			while(a[i] != ' ')
			{
				value = 10*value+a[i]-'0';//��������ַ����ǿո�˵�������ַ�����λ��
				i++;
			}
			S.top++;
			S.data[S.top] = value;//����֮�����ֽ�ջ
		}
		else
		{
			switch(a[i])//��ջ�е����ֳ�ջ���Σ�Ȼ���õ�ǰ��������������㣬�ٽ������ջ
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
	if(S.top <= 0)//���ջ���գ��������ջ��������
	{
		result = S.data[S.top];
		S.top--;
		if(S.top == -1)
		{
			return result;
		}
		else
		{
			printf("���ʽ����");
			return 0;
		}
	}
	return 0;
}*/
int main(void)
{
	char a[MAXSIZE],b[MAXSIZE];
	float f;
	printf("������һ�����ʽ��");
	gets(a);
//	printf("��׺���ʽ�ǣ�%s\n",a);
	TranslateExpress(a,b);
	printf("��׺���ʽ�ǣ�%s\n",b);
//	f = ComputeExpress(b);
//	printf("�������ǣ�%.2f\n",f);
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




