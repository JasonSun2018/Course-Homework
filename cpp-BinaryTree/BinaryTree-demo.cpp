#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

#define MAXSIZE 30
#define FILE_PLACE "BTNode.dat" 
#define ElemType char

typedef struct Node
{
	ElemType data;
	struct Node* lchild;
	struct Node* rchild;
} BTNode;

typedef struct
{
	BTNode* data[MAXSIZE];
	int top;
} SqStack;

void CreateBTree(BTNode*& b, char* str, int& length_b);
void DestoryBTree(BTNode*& b);
int Translate(BTNode* b, ElemType St[MAXSIZE], int i);
void SaveToFile(char str[MAXSIZE]);
void ReadFromFile(char str[MAXSIZE]);
int RTransform(BTNode*& b, char St[MAXSIZE], int i);
void Transform(BTNode*& b, char St[MAXSIZE]);
void PreOrder(BTNode* b);
void InOrder(BTNode* b);
void PostOrder(BTNode* b);
void InitStack(SqStack*& s);
bool Push(SqStack*& s, BTNode* b);
bool Pop(SqStack*& s, BTNode*& b);
bool GetTop(SqStack* s, BTNode*& b);
bool StackEmpty(SqStack* s);
void DestorySt(SqStack*& s);
void DispBTree(BTNode* b);

int main(void)
{
	int i = 0, choice, length_b1 = 0, length_b2 = 0, length_b3 = 0;
	ElemType str[MAXSIZE], St[MAXSIZE], BT[MAXSIZE], ch;
	BTNode* b1, * b2, * b3;
	b1 = NULL;
	
	while (1)
	{
		printf("\n\n2019/6 ʵ��2 PART.1\n");
		printf("==========================================================\n");
		printf("1.������ʽ�洢����������B1\n");
		printf("2.�������л���ʾ���������B1���У����洢���ļ���\n");
		printf("3.���ļ��ж������У��������л��ĵݹ鷽�����������B2\n");
		printf("4.���ļ��ж������У��������л��ķǵݹ鷽�����������B3\n");
		printf("5.ʹ�÷ǵݹ鷽����������������������\n");
		printf("6.ʹ�÷ǵݹ鷽����������������������\n");
		printf("7.�����ͷŶ�����B1,B2,B3\n");
		printf("0.�˳�ʵ�����\n");
		printf("==========================================================\n");
		
		printf(">>>��ѡ����: ");
		scanf("%d", &choice);
		fflush(stdin); //��ջ����� 
		printf("\n");
		
		switch (choice)
		{
			case 1:
				if (b1 != NULL)
				{	
					i = 0;
					DestoryBTree(b1);
				}
				
				printf("���������ű�ʾ���Ķ�����: ");
				while ((ch = getchar()) != '\n')
				{
					str[i] = ch;
					i++;
				}
				str[i] = '\0';
				
				CreateBTree(b1, str, length_b1);
				printf("�ɹ�����������B1: ");
				DispBTree(b1);
				break;
			
			case 2:
				if (length_b1 == 0)
				{
					printf("δ����������B1��");
					break;
				}
				
				Translate(b1, St, 0);
				
				printf("(�������)��ʽ�洢�ṹΪ: %s\n", St);
				SaveToFile(St);
				break;
			
			case 3:
				ReadFromFile(St);
				printf("�Ѷ�ȡ������: %s\n", St);
				
				//��ʼ��b2 
				b2 = (BTNode*)malloc(sizeof(BTNode));
				b2->lchild = b2->rchild = NULL;
				
				RTransform(b2, St, 0);
				printf("�ѽ���������B2: ");
				DispBTree(b2);
				break;
			
			case 4:
				ReadFromFile(St);
				printf("�Ѷ�ȡ������: %s\n", St);
				
				//��ʼ��b3
				b3 = (BTNode*)malloc(sizeof(BTNode));
				b3->lchild = b3->rchild = NULL;
				
				Transform(b3, St);
				printf("�ѽ���������B3: ");
				DispBTree(b3);
				break;
			
			case 5:
				if (length_b1 == 0)
				{
					printf("δ����������B1��");
					break;
				}
				
				printf("�������������: ");
				InOrder(b1);
				break;
			
			case 6:
				if (length_b1 == 0)
				{
					printf("δ����������B1��");
					break;
				}
				
				printf("�������������: ");
				PostOrder(b1);
				break;
			
			case 7:
				if (b1 != NULL)
					DestoryBTree(b1);
				if (b2 != NULL)
					DestoryBTree(b2);
				if (b3 != NULL)
					DestoryBTree(b3);
					
				printf("������ B1 | B2 | B3 �ѳɹ����٣�\n");
				break;
			
			case 0:
				printf("�ɹ��˳���\n");
				return 0;
				
			default:
				printf("��������ȷ���֣�\n");
				break;
		}
	}
}

//���������� 
void CreateBTree(BTNode*& b, ElemType* str, int& length_b)
{
	BTNode *St[MAXSIZE], *p; 
	int top = -1, k, j = 0;
	ElemType ch;
	
	length_b = 0;
	b = NULL;
	ch = str[j];
	
	while(ch != '\0')
	{
		switch (ch) 
		{
			case '(': top++; St[top] = p; k = 1; break;
			case ')': top--; break;
			case ',': k = 2; break;
			default: 
				length_b++;
				p = (BTNode* )malloc(sizeof(BTNode));
				p->data = ch;
				p->lchild = p->rchild = NULL;
				
				if (b == NULL)
				{
					b = p;
				}
				
				else
				{
					switch (k)
					{
						case 1: St[top]->lchild = p; break;
						case 2: St[top]->rchild = p; break;
					}
				}
		}
		j++;
		ch = str[j];
	}
}
 
//������ʽת�������� 
int Translate(BTNode* b, ElemType St[MAXSIZE], int i)
{
	if (b == NULL)
	{
		St[i] = '#';
		i++;
		return i;
	}
	
	St[i] = b->data;
	i++;
	i = Translate(b->lchild, St, i);
	i = Translate(b->rchild, St, i);
	St[i] = '\0';
	return i;
}

//����ʽ������ת��Ϊ������ 
int RTransform(BTNode*& b, char St[MAXSIZE], int i) //�ݹ��㷨 
{
	if (St[i] == '#' || St[i] == '\0')
	{	
		b = NULL;
		i++;
		return i;
	}
	
	BTNode* p;
	p = (BTNode*)malloc(sizeof(BTNode));
	
	p->data = St[i];
	b = p;
	i++;
	i = RTransform(b->lchild, St, i);
	i = RTransform(b->rchild, St, i);
	return i;
}

void Transform(BTNode*&b, char a[MAXSIZE]) //�ǵݹ��㷨 
{
	BTNode *St[MAXSIZE], *p; 
	int top =-1;
	int k=0,j=0,tem=0; 
	char ch; 
	b = NULL;
	ch = a[j];
	
	while (ch!=0)
	{ 
		if (ch!='#')
		{   
			top++;
			St[top] = p;
			p = (BTNode*)malloc(sizeof(BTNode));
			p->data = ch;
			p->rchild = NULL;
			p->lchild = NULL;
			if(b==NULL)
			{
				b = p;
			}
	
			else
			{
				if(k==0) 
				{
					St[top]->lchild = p;	
				}
				else
				{  
					if(k==1)
					{
						St[top]->rchild = p;
						k=0;
					}
	
					if(k==2)
					{
						St[tem]->rchild = p;
						k=0;
					}
				}
			}
		}
	
		if(ch=='#')
		{
			if(k==0)
			{
				p->lchild = NULL;
				k=1;
			}
			else
			{
				p->rchild = NULL;
				tem = top;
				while(St[tem]->rchild!=NULL) tem--;
				k=2;
			}
		}
		j++;  
		ch=a[j];
	}
}

//�����ַ������ļ��� 
void SaveToFile(char str[MAXSIZE])
{
	FILE* fp;
	
	if ((fp = fopen(FILE_PLACE, "wb")) == NULL)
	{
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
	fwrite(str, strlen(str), 1, fp);
	
	fclose(fp);
	printf("����ɹ���\n");	
}

//���ļ��ж�ȡ�ַ��� 
void ReadFromFile(char str[MAXSIZE])
{
	FILE* fp;
	int len;
	
	if ((fp = fopen(FILE_PLACE, "rb")) == NULL)
	{
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
	//��ȡ�ļ����� 
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	rewind(fp); 
	
	//��ȡ�ļ��ַ������� 
	fread(str, sizeof(char), len, fp);
	str[len] = '\0';
	
	fclose(fp);
}

//���˳��洢�ṹ�Ķ����� 
void DispBTree(BTNode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			DispBTree(b->lchild);
			if (b->rchild != NULL)
				printf(",");
			DispBTree(b->rchild);
			printf(")");
		}
	}
} 

//������������� 
void PreOrder(BTNode* b)
{
	if (b != NULL)
	{
		printf("%c", b->data);
		PreOrder(b->lchild);
		PreOrder(b->rchild);
	}
}

//������������� 
void InOrder(BTNode* b) //�ǵݹ� 
{
	BTNode* p;
	SqStack* st;
	InitStack(st);
	p = b;
	
	while (!StackEmpty(st) || p != NULL)
	{	
		while (p != NULL)
		{
			Push(st, p);
			p = p->lchild;
		}
		if (!StackEmpty(st))
		{
			Pop(st, p);
			printf("%c", p->data);
			p = p->rchild;
		}
	}
	printf("\n");
	DestorySt(st);
}

//������������� 
void PostOrder(BTNode* b) //�ǵݹ� 
{
	BTNode* p, * r;
	bool flag;
	SqStack* st;
	InitStack(st);
	
	p = b;
	do
	{
		while (p != NULL)
		{
			Push(st, p);
			p = p->lchild;
		}
		
		r = NULL;
		flag = true;
		
		while (!StackEmpty(st) && flag)
		{
			GetTop(st, p);
			
			if (p->rchild == r)
			{
				printf("%c", p->data);
				Pop(st, p);
				r = p;
			}
			
			else
			{
				p = p->rchild;
				flag = false;
			}
		}
	} while (!StackEmpty(st));
	printf("\n");
	DestorySt(st);
}

//ջ�Ĳ��� 
void InitStack(SqStack*& s)
{
	s = (SqStack*)malloc(sizeof(SqStack));
	s->top = -1;
}

bool Push(SqStack*& s, BTNode* b)
{
	if (s->top == MAXSIZE-1)
		return false;
	s->top++;
	s->data[s->top] = b;
	return true;
}

bool Pop(SqStack*& s, BTNode*& b)
{
	if (s->top == -1)
		return false;
	b = s->data[s->top];
	s->top--;
	return true;
}

bool GetTop(SqStack* s, BTNode*& b)
{
	if (s->top == -1)
		return false;
	b = s->data[s->top];
	return true;
}

bool StackEmpty(SqStack* s)
{
	if (s->top == -1)
		return true;
	return false;
}

void DestorySt(SqStack*& s)
{
	free(s);
}

//���ٶ����� 
void DestoryBTree(BTNode*& b)
{
	if (b != NULL)
	{
		DestoryBTree(b->lchild);
		DestoryBTree(b->rchild);
		free(b);
	}
}
