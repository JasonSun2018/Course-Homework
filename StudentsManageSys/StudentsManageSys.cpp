#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <fstream>

#define MAX_STUDENTNO_LEN 15
#define MAX_NAME_LEN 20
#define MAX_SEX_LEN 10
#define MAX_COURSENO_LEN 10
#define MAX_COURSENAME_LEN 20
#define MAX_MAJORNAME_LEN 20
#define FILE_PLACE_S "student.dat" 
#define FILE_PLACE_C "course.dat" 
#define FILE_PLACE_G "courseGrade.dat"
#define FILE_PLACE_SG "studentGrade.dat"
#define FILE_PLACE_SGQ "studentGradeQ.dat"

typedef struct students
{
	char sno[MAX_STUDENTNO_LEN];
	char sname[MAX_NAME_LEN];
	char sex[MAX_SEX_LEN];
	char major[MAX_MAJORNAME_LEN];
	struct students* next;
} student;

typedef struct courses
{
	char cno[MAX_COURSENO_LEN];
	char cname[MAX_COURSENAME_LEN];
	int classhours;
	struct courses* next;
} course;

typedef struct grades
{
	char sno[MAX_STUDENTNO_LEN];
	char cno[MAX_COURSENO_LEN];
	int score;
	struct grades* next;
} grade;

typedef struct studentgrades
{
	char sno[MAX_STUDENTNO_LEN];
	char sname[MAX_NAME_LEN];
	char major[MAX_MAJORNAME_LEN];
	char cno[MAX_COURSENO_LEN];
	char cname[MAX_COURSENAME_LEN];
	int score;
	struct studentgrades* next;
} sgrade;

typedef struct sstacks
{
	char sno[MAX_STUDENTNO_LEN];
	char sname[MAX_NAME_LEN];
	char sex[MAX_SEX_LEN];
	char major[MAX_MAJORNAME_LEN];
	struct sstacks *next;
} sstack;

typedef struct
{
	struct studentgrades* front;
	struct studentgrades* rear;
} sgqlink;

//1
void insert_s(student*& L);
void createfile_s(void);
//2
void insert_c(course*& L);
void createfile_c(void);
//3
void insert_g(grade*& L);
void createfile_g(void);
//base
void readfile_s(student*& L);
void readfile_c(course*& L);
void readfile_g(grade*& L);
void readfile_sg(sgrade*& L);
//4
void print_s(void);
//5
void print_c(void);
//6
void print_g(void);
//7
void print_all(void);
//8
void search_cgrade(void);
//9
void search_cfail(void);
//10
void print_sstack(void);
//11
void print_allqueue(void);
//else
void gettime(void);

//������ 
int main(void) {
	int choice;

	loop:
	printf("\n=============  "); gettime(); printf("  =============");
	printf("\n=================================================\n");
	printf("1��д��ѧ����¼\n");
	printf("2��д��γ���Ϣ��¼\n");
	printf("3��д��ѧ�����Գɼ�\n");
	printf("4��ѧ���������ѧ����¼\n");
	printf("5���γ̺���������γ���Ϣ\n");
	printf("6��ѧ�źͿγ̺��������ѧ�����Գɼ�\n");
	printf("7�����Գɼ������������ѧ�����Գɼ�\n");
	printf("8�����Գɼ����������ѡ�γ�����ѧ�����Գɼ�\n");
	printf("9�����Գɼ����������ѡ�γ̲�����ѧ�����Գɼ�\n");
	printf("10�������ѧ�������ѧ����¼���������ɵ�������\n");
	printf("11�����Գɼ���������ʽ�����������ѧ�����Գɼ�\n");
	printf("0���˳�ϵͳ\n");
	printf("=================================================\n");
	printf("���������: ");
	scanf("%d", &choice);
	printf("=================================================\n");

	switch (choice) {
	case 1: createfile_s(); goto loop;
	case 2: createfile_c(); goto loop;
	case 3: createfile_g(); goto loop;
	case 4: print_s(); goto loop;
	case 5: print_c(); goto loop;
	case 6: print_g(); goto loop;
	case 7: print_all(); goto loop;
	case 8: search_cgrade(); goto loop;
	case 9: search_cfail(); goto loop;
	case 10: print_sstack(); goto loop;
	case 11: print_allqueue(); goto loop;
	case 0: printf("�ɹ��˳���\n"); exit(1);
	}

	exit(0);
}

//else
void gettime(void){
	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);
	
	printf("%d-",1900+p->tm_year);/*��ȡ��ǰ���,��1900��ʼ������Ҫ��1900*/
	printf("%d-",1+p->tm_mon);/*��ȡ��ǰ�·�,��Χ��0-11,����Ҫ��1*/
	printf("%d   ",p->tm_mday);/*��ȡ��ǰ�·�����,��Χ��1-31*/
	printf("%d:",8+p->tm_hour); /*��ȡ��ǰʱ*/
	printf("%d:",p->tm_min); /*��ȡ��ǰ��*/
	printf("%d",p->tm_sec); /*��ȡ��ǰ��*/
}

//Function 1
void createfile_s(void) {
	student* L,* head;
	char ch;	
	FILE* fp;
	insert_s(L);

	printf("�����ļ�?('Y' to save��\n");
	scanf("%s", &ch);
	if (ch != 'Y') {
		free(L);
		printf("�ɹ����أ�");
		return;
	}

	head = L;

	if ((fp = fopen(FILE_PLACE_S, "wb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
    while(fwrite(head, sizeof(student), 1, fp)){
    	head = head->next;
    }
    
	fclose(fp);
	printf("����ɹ���\n");
	return;
}

void insert_s(student*& L) {
	student* p, * s;
	L = (student*)malloc(sizeof(student));
	char ch;
	int num=0;
	
	p = L;
	loop:
	s = (student*)malloc(sizeof(student));
	printf("������ѧ����ţ� ");
	scanf("%s", s->sno);
	printf("������ѧ�������� ");
	scanf("%s", s->sname);
	printf("������ѧ���Ա� ");
	scanf("%s", s->sex);
	printf("������ѧ��רҵ�� ");
	scanf("%s", s->major);
	s->next = NULL;
	p->next = s;
	p = s;
	num++;
	
	printf("\n������ %d ��ѧ������Ϣ\n����'Y'�������ѧ����Ϣ���������ⷵ��\n", num);
	scanf("%s", &ch);
	
	while (ch == 'Y') {
		goto loop;
	}
	
	return;
}

//Function 2
void createfile_c(void) {
	course* L,* head;
	char ch;	
	FILE* fp;
	insert_c(L);

	printf("�����ļ�?('Y' to save��\n");
	scanf("%s", &ch);
	if (ch != 'Y') {
		free(L);
		printf("�ɹ����أ�");
		return;
	}

	head = L;

	if ((fp = fopen(FILE_PLACE_C, "wb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
    while(fwrite(head, sizeof(course), 1, fp)){
    	head = head->next;
    }
    
	fclose(fp);
	printf("����ɹ���\n");
	return;
}

void insert_c(course*& L) {
	course* p, * s;
	L = (course*)malloc(sizeof(course));
	char ch;
	int num=0;
	
	p = L;
	loop:
	s = (course*)malloc(sizeof(course));
	printf("������γ���ţ� ");
	scanf("%s", s->cno);
	printf("������γ����ƣ� ");
	scanf("%s", s->cname);
	printf("������γ�ѧʱ�� ");
	scanf("%d", &s->classhours);
	s->next = NULL;
	p->next = s;
	p = s;
	num++;
	
	printf("\n������ %d ���γ̵���Ϣ\n����'Y'������ӿγ���Ϣ���������ⷵ��\n", num);

	scanf("%s", &ch);
	while (ch == 'Y') {
		goto loop;
	}

	free(s);
	return;
}

//Function 3
void createfile_g(void) {
	grade* L,* head;
	char ch;	
	FILE* fp;	
	insert_g(L);

	printf("�����ļ�?('Y' to save��\n");
	scanf("%s", &ch);
	if (ch != 'Y') {
		free(L);
		printf("�ɹ����أ�");
		return;
	}

	head = L;

	if ((fp = fopen(FILE_PLACE_G, "wb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
    while(fwrite(head, sizeof(grade), 1, fp)){
    	head = head->next;
    }
    
	fclose(fp);
	printf("����ɹ���\n");
	return;
}

void insert_g(grade*& L) {
	grade* p, * s;
	L = (grade*)malloc(sizeof(grade));
	char ch;
	int num=0;
	
	p = L;
	loop:
	s = (grade*)malloc(sizeof(grade));
	printf("������ѧ����ţ� ");
	scanf("%s", s->sno);
	printf("������γ���ţ� ");
	scanf("%s", s->cno);
	printf("������ѧ�������� ");
	scanf("%d", &s->score);
	s->next = NULL;
	p->next = s;
	p = s;
	num++;
	
	printf("\n������ %d ��ѧ���ɼ���Ϣ\n����'Y'������ӳɼ���Ϣ���������ⷵ��\n", num);

	scanf("%s", &ch);
	while (ch == 'Y') {
		goto loop;
	}

	free(s);
	return;
}

//base
void readfile_s(student*& L) {
	FILE* fp;
	student *p,*pNext,*pre;
	L = (student*)malloc(sizeof(student));
	p = L;
	
	if ((fp = fopen(FILE_PLACE_S, "rb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
	while (fread(p, sizeof(student), 1, fp)) {
		pNext = (student *)malloc(sizeof(student));
		p->next = pNext;
		pre = p;
		p = pNext;
	}
	
	pre->next = NULL;
	free(pNext);
	return;
}

void readfile_c(course*& L) {
	FILE* fp;
	course *p,*pNext,*pre;
	L = (course*)malloc(sizeof(course));
	p = L;
	
	if ((fp = fopen(FILE_PLACE_C, "rb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
	while (fread(p, sizeof(course), 1, fp)) {
		pNext = (course *)malloc(sizeof(course));
		p->next = pNext;
		pre = p;
		p = pNext;
	}
	
	pre->next = NULL;
	free(pNext);
	return;
}

void readfile_g(grade*& L) {
	FILE* fp;
	grade *p,*pNext,*pre;
	L = (grade*)malloc(sizeof(grade));
	p = L;
	
	if ((fp = fopen(FILE_PLACE_G, "rb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
	while (fread(p, sizeof(grade), 1, fp)) {
		pNext = (grade *)malloc(sizeof(grade));
		p->next = pNext;
		pre = p;
		p = pNext;
	}
	
	pre->next = NULL;
	free(pNext);
	return;
}

void readfile_sg(sgrade*& L){
	FILE* fp;
	sgrade *p,*pNext,*pre;
	L = (sgrade*)malloc(sizeof(sgrade));
	p = L;
	
	if ((fp = fopen(FILE_PLACE_SG, "rb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
	while (fread(p, sizeof(sgrade), 1, fp)) {
		pNext = (sgrade *)malloc(sizeof(sgrade));
		p->next = pNext;
		pre = p;
		p = pNext;
	}
	
	pre->next = NULL;
	free(pNext);
	return;
}

//Function 4
void print_s(void) {
	student* L;
	readfile_s(L);

	student* p, * pre, * q;
	p = L->next->next;
	L->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = L;
		while (pre->next != NULL && strcmp(pre->next->sno,p->sno)<0) {
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	
	p = L;
	printf("\nsno     sname       sex       major\n");
	while ((p = p->next) != NULL) {
		printf("%-8s%-12s%-10s%-10s\n", p->sno, p->sname, p->sex, p->major);
	}
	
	return;
}

//Function 5
void print_c(void) {
	course* L;
	readfile_c(L);

	course* p, * pre, * q;
	p = L->next->next;
	L->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = L;
		while (pre->next != NULL && strcmp(pre->next->cno,p->cno)<0) {
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	
	p = L;
	printf("\ncno     cname       classhour\n");
	while ((p = p->next) != NULL) {
		printf("%-8s%-12s%-10d\n", p->cno, p->cname, p->classhours);
	}
	return;
}

//Function 6
void print_g(void) {
	grade* L;
	readfile_g(L);

	grade* p, * pre, * q;
	
	//˫�������� 
	p = L->next->next;
	L->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = L;
		while (pre->next != NULL && strcmp(pre->next->cno,p->cno) <= 0) {
			if(strcmp(pre->next->sno,p->sno) < 0 || strcmp(pre->next->cno,p->cno) < 0 ){
				pre = pre->next;
			}
			else break;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	
	//��ӡ��Ϣ 
	p = L;
	printf("\nsno     cno     score\n");
	while((p = p->next) != NULL){
		printf("%-8s%-8s%-8d\n", p->sno, p->cno, p->score);
	}
	
	return;
}

//Function 7
void print_all(void){
	student *Ls,*Lsp;
	course *Lc,*Lcp;
	grade *Lg;
	readfile_s(Ls);
	readfile_c(Lc);
	readfile_g(Lg);
	
	grade* p, * pre, * q;
	
	//���ճɼ��������� 
	p = Lg->next->next;
	Lg->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = Lg;
		while (pre->next != NULL && pre->next->score > p->score) {
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	
	sgrade *L,*Lsg,*m,*head;
	L = (sgrade*)malloc(sizeof(sgrade));
	Lsg = (sgrade*)malloc(sizeof(sgrade));
	m = L;
	
	//����ѧ���ɼ����� 
	p = Lg; 
	while((p = p->next) != NULL){
		Lsp = Ls->next;
		Lcp = Lc->next;
		
		//Ѱ�Ҷ�Ӧ���
		while (strcmp(p->sno,Lsp->sno) != 0){
			Lsp = Lsp->next;
			if (Lsp == NULL){
				printf("ѧ����Ϣ�����ڣ�\n");
				return ; 
			}
		}
		while (strcmp(p->cno,Lcp->cno) != 0){
			Lcp = Lcp->next;
			if (Lcp == NULL){
				printf("�γ���Ϣ�����ڣ�\n");
				return ; 
			}
		}
		 
		//��ֵ 
		Lsg->score = p->score;
		strcpy(Lsg->sno,p->sno);
		strcpy(Lsg->sname,Lsp->sname);
		strcpy(Lsg->major,Lsp->major);
		strcpy(Lsg->cno,p->cno);
		strcpy(Lsg->cname,Lcp->cname);
		
		//������� 
		m->next = Lsg;
		m = Lsg;
		Lsg = (sgrade*)malloc(sizeof(sgrade));
	}
	m->next = NULL;
	free(Lsg);
	
	//��ӡ��Ϣ
	m = L;
	printf("\nѧ��    ѧ������    רҵ      ���    �γ���      �ɼ�\n") ;
	while((m = m->next) != NULL){
		printf("%-8s%-12s%-10s%-8s%-12s%-8d\n",m->sno,m->sname,m->major,m->cno,m->cname,m->score);
	}
	
	//�洢���ļ��� 
	FILE* fp;
	head = L;
	
	if ((fp = fopen(FILE_PLACE_SG, "wb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
    while(fwrite(head, sizeof(sgrade), 1, fp)){
    	head = head->next;
    }
    
	fclose(fp);
	
	return;
}

//Function 8
void search_cgrade(void){
	sgrade *L,*Lcg,*p,*q,*pre;
	readfile_sg(L);
	
	char ch[MAX_COURSENO_LEN];
	printf("��������ҵĿγ���ţ� ");
	scanf("%s",ch); 
	
	//�������� 
	Lcg = (sgrade*)malloc(sizeof(sgrade));
	q = Lcg;
	p = L;
	while ((p = p->next) != NULL){
		if (strcmp(p->cno,ch) == 0){
			q->next = p;
			q = q->next;
		}
	}
	q->next = NULL;
	
	//��֤�����Ƿ�Ϊ�� 
	if (Lcg->next == NULL) {
		printf("δ�ҵ��ÿγ����ݣ�\n");
		return; 
	}
	
	//���ճɼ��������� 
	p = Lcg->next->next;
	Lcg->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = Lcg;
		while (pre->next != NULL && pre->next->score > p->score) {
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	
	//��ӡ��Ϣ 
	q = Lcg;
	printf("\nѧ��    ѧ������    רҵ      ���    �γ���      �ɼ�\n") ;
	while((q = q->next) != NULL){
		printf("%-8s%-12s%-10s%-8s%-12s%-8d\n",q->sno,q->sname,q->major,q->cno,q->cname,q->score);
	}
	
	return;
} 

//Function 9
void search_cfail(void) {
	sgrade *L,*Lcg,*p,*q,*pre;
	readfile_sg(L);
	
	char ch[MAX_COURSENO_LEN];
	printf("��������ҵĿγ���ţ� ");
	scanf("%s",ch); 
	
	//�����ɼ�С��60�ֵ����� 
	Lcg = (sgrade*)malloc(sizeof(sgrade));
	q = Lcg;
	p = L;
	while ((p = p->next) != NULL){
		if (strcmp(p->cno,ch) == 0 && p->score < 60){
			q->next = p;
			q = q->next;
		}
	}
	q->next = NULL;
	
	//��֤�����Ƿ�Ϊ�� 
	if (Lcg->next == NULL) {
		printf("δ�ҵ��ÿγ����ݻ�����ͬѧ������\n");
		return; 
	}
	
	//���ճɼ��������� 
	p = Lcg->next->next;
	Lcg->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = Lcg;
		while (pre->next != NULL && pre->next->score > p->score) {
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	
	//��ӡ��Ϣ 
	q = Lcg;
	printf("\nѧ��    ѧ������    רҵ      ���    �γ���      �ɼ�\n") ;
	while((q = q->next) != NULL){
		printf("%-8s%-12s%-10s%-8s%-12s%-8d\n",q->sno,q->sname,q->major,q->cno,q->cname,q->score);
	}
	
	return;
} 

//Function 10
void print_sstack(void) {
	student* L;
	readfile_s(L);
	
	//ѧ�������������� 
	student* p, * pre, * q;
	p = L->next->next;
	L->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = L;
		while (pre->next != NULL && strcmp(pre->next->sno,p->sno)<0) {
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	
	//����������д��ջ 
	sstack* s,* n;
	s = (sstack *)malloc(sizeof(sstack));
	s->next = NULL;
	
	p = L;
	while((p = p->next) != NULL){
		n = (sstack *)malloc(sizeof(sstack));
		
		strcpy(n->sno,p->sno);
		strcpy(n->sname,p->sname);
		strcpy(n->sex,p->sex);
		strcpy(n->major,p->major);
		
		n->next = s->next;
		s->next = n;
	}
	
	//��ջ�����������Ϣ 
	if (s->next == NULL){
		printf("û��ѧ����Ϣ��"); 
		return;
	} 
	
	n = s;
	printf("\nsno     sname       sex     major\n");
	while ((n = n->next) != NULL) {
		printf("%-8s%-12s%-8s%-12s\n", n->sno, n->sname, n->sex, n->major);
		s->next = n->next;
		n = s;
	}
	
	return;
} 

//Function 11
void print_allqueue(void) {
	student *Ls,*Lsp;
	course *Lc,*Lcp;
	grade *Lg;
	readfile_s(Ls);
	readfile_c(Lc);
	readfile_g(Lg);
	
	grade* p, * pre, * q;
	
	//���ճɼ��������� 
	p = Lg->next->next;
	Lg->next->next = NULL;
	while (p != NULL) {
		q = p->next;
		pre = Lg;
		while (pre->next != NULL && pre->next->score > p->score) {
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
		p = q;
	}
	
	//��ʼ������ָ�� 
	sgqlink *link;
	link = (sgqlink *)malloc(sizeof(sgqlink));
	link->front = link->rear = NULL;
	
	//��ʼ��Ŀ������ 
	sgrade *L;
	L = (sgrade*)malloc(sizeof(sgrade));
	
	//����ѧ���ɼ����� 
	p = Lg; 
	while((p = p->next) != NULL){
		Lsp = Ls->next;
		Lcp = Lc->next;
		
		//Ѱ�Ҷ�Ӧ���
		while (strcmp(p->sno,Lsp->sno) != 0){
			Lsp = Lsp->next;
			if (Lsp == NULL){
				printf("ѧ����Ϣ�����ڣ�\n");
				return ; 
			}
		}
		while (strcmp(p->cno,Lcp->cno) != 0){
			Lcp = Lcp->next;
			if (Lcp == NULL){
				printf("�γ���Ϣ�����ڣ�\n");
				return ; 
			}
		}
		 
		//��ֵ 
		L->score = p->score;
		strcpy(L->sno,p->sno);
		strcpy(L->sname,Lsp->sname);
		strcpy(L->major,Lsp->major);
		strcpy(L->cno,p->cno);
		strcpy(L->cname,Lcp->cname);
		
		//������� 
		if (link->front == NULL) {
			link->front = link->rear = L;
		}
		else {
			link->rear->next = L;
			link->rear = L;
		}
		L = (sgrade*)malloc(sizeof(sgrade));
	}
	link->rear->next = NULL; 
	
	//�洢���ļ��� 
	FILE* fp;
	
	if ((fp = fopen(FILE_PLACE_SGQ, "wb")) == NULL) {
		fprintf(stderr, "can't open\n");
		exit(EXIT_FAILURE);
	}
	
	L = link->front;
	
    while(fwrite(L, sizeof(sgrade), 1, fp)){
    	L = L->next;
    }
    
	fclose(fp);

	//��ӡ��Ϣ
	if (link->rear == NULL){
		printf("��ȡ��Ϣʧ�ܣ�");
		return;
	}
	
	printf("\nѧ��    ѧ������    רҵ      ���    �γ���      �ɼ�\n") ;
	if (link->front == link->rear){
		L = link->front;
		printf("%-8s%-12s%-10s%-8s%-12s%-8d\n",L->sno,L->sname,L->major,L->cno,L->cname,L->score);
		link->front = link->rear = NULL;
		return;
	}
	
	while((L = link->front) != NULL){
		link->front = link->front->next; 
		printf("%-8s%-12s%-10s%-8s%-12s%-8d\n",L->sno,L->sname,L->major,L->cno,L->cname,L->score);
	}
	
	return;
}
