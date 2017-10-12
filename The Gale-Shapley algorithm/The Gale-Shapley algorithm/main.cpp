//�������� �����-�����, ���������� ������� � ��������������� ����� � �������������� ������������ ������
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
using namespace std;

char *m, *w, *rel, n;

bool end_check(void);          //�������� ������� ��� ��� ����
int check_m(int);                      //�������� ������� ������� � ������
int check_w(int);                      //�������� ������� ������ � �������
int rating_for_m(int);         //��������� ������� � ������� ����������� ������
int rating_for_w(int);         //��������� ������ � ������� ����������� �������
void get_n(void);                      //��������� ���������� ��� � ��������� ������
void inp(void);                        //������ ����
void generate(void);           //��������� �����������
void type_of_inp(void);        //����� ���� �����
void print_priority(void);     //����� ������� ����������� ������� � ������
void best_for_m(int);          //����������� ������ �� ���������� ������
void best_for_w(int);          //����� ������� �� �����������
void print_rel(void);          //������ ������� ���������
void step(void);                       //���� ��������
void print_sol(void);          //������ ������������ �������

void main(void)
{
	type_of_inp();
	print_priority();
	while (!end_check())
		step();
	print_rel();
	print_sol();
}

bool end_check(void)
{
	//�������� ������� ��� ��� ���� ������� � ������
	for (int i = 0; i<n; i++)
		if ((check_m(i) == -1) || (check_w(i) == -1)) return(false);
	return(true);
}

int check_m(int k)
//���������� ������ ������� k-�� ������
{
	for (char i = 0; i<n; i++)
		if (*(rel + k*n + i) == 1) return (i);
	return(-1);
}

int check_w(int k)
//���������� ������ ������ k-��� �������
{
	for (int i = 0; i<n; i++)
		if (*(rel + k + i*n) == 1) return (i);
	return(-1);
}

int rating_for_w(int k)
//���������� ��������� ������ � ������ ������������ �������
{
	int i = 0;
	while (*(w + k*n + i) != k) i++;
	return(i);
}

int rating_for_m(int k)
{
	//���������� ��������� ������� � ������ ������������ ������
	int i = 0;
	while (*(m + k*n + i) != k) i++;
	return(i);
}
void get_n(void)
{
	//������ ������ �����
	n = 0;
	printf("������� ������������� ���������� ���: ");
	scanf_s("%hhi", &n);
	srand(time_t(0));

	while (n<1)
	{
		printf("������. ��������� ����: ");
		scanf_s("%i", &n);
	}
	int j = 0, k = 0, i = 0, tmp;
	bool f;
	int n2 = n*n;
	m = (char*)calloc(n2, sizeof(char));
	w = (char*)calloc(n2, sizeof(char));
	rel = (char*)calloc(n2, sizeof(char));
	if (m == NULL || w == NULL || rel == NULL)
	{
		printf("�� ������� �������� ������");
		return;
	}
	for (i = 0; i<n2; i++) *(rel + i) = 0;
}

void inp(void)
{
	//���� �������
	get_n();
	printf("������� ���������� ��� �������");
	for (int i = 0; i<n; i++)
	{
		printf("\n%2i-� �����:\n", i + 1);
		for (int j = 0; j<n; j++)
		{
			printf("%i) ", j + 1);
			scanf_s("%i", (m + i*n + j));
			for (int k = 0; k <= j; k++)
				while (((*(m + i*n + j) == *(m + i*n + k)) && (k != j)) || (*(m + i*n + j)<1) || (*(m + i*n + j)>n))
				{
					printf("����� �������� ��� ������� ��� �����������, ��������� ���� ");
					scanf_s("%i", (m + i*n + j));
				}
		}
	}
	printf("������� ���������� ������");
	for (int i = 0; i<n; i++)
	{
		printf("\n%2i-� �������:\n", i + 1);
		for (int j = 0; j<n; j++)
		{
			printf("%i) ", j + 1);
			scanf_s("%i", (w + i*n + j));
			for (int k = 0; k <= j; k++)
				while (((*(w + i*n + j) == *(w + i*n + k)) && (k != j)) || (*(w + i*n + j)<1) || (*(w + i*n + j)>n))
				{
					printf("����� �������� ��� ������� ��� �����������, ��������� ���� ");
					scanf_s("%i", (w + i*n + j));
				}
		}
	}
	for (int i = 0; i<n*n + 2 * n + 1; i++)
	{
		*(m + i) = *(m + i) - 1;
		*(w + i) = *(w + i) - 1;
	}
	system("cls");
}
void generate(void)
//��������� ������ ������������
{
	int i, j, k, tmp;
	bool f;
	get_n();
	for (i = 0; i<n; i++)
	{
		*(w + i*n) = rand() % n;
		for (k = 1; k<n; k++)
		{
			f = false;
			while (!f)
			{
				tmp = rand() % n;
				j = 0;
				while ((*(w + (i*n + j)) != tmp) && (j<k)) j++;
				if (j == k)
				{
					*(w + (i*n + j)) = tmp;
					f = true;
				}
			}
		}
	}
	for (i = 0; i<n; i++)
	{
		*(m + i*n) = rand() % n;
		for (k = 1; k<n; k++)
		{
			f = false;
			while (!f)
			{
				tmp = rand() % n;
				j = 0;
				while ((*(m + (i*n + j)) != tmp) && (j<k)) j++;
				if (j == k)
				{
					*(m + (i*n + j)) = tmp;
					f = true;
				}
			}
		}
	}
}

void type_of_inp(void)
{
	setlocale(LC_CTYPE, "Russian");
	int i;
	printf("�������� ��� �����: 0 - ���������, 1 - ������ \n");
	scanf_s("%i", &i);
	while (i != 0 && i != 1)
	{
		printf("�������� ��������. ��������� ����: 0 - ���������, 1 - ������ \n");
		scanf_s("%i", &i);
	}
	if (i == 0) generate();
	else inp();
}

void print_priority(void)
{
	//����� ���� ������
	char i, j;
	printf("���������� �������\n");
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
			printf("%3i", 1 + *(m + (i*n + j)));
		printf("\n");
	}
	printf("\n");
	printf("���������� ������\n");
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
			printf("%3i", 1 + *(w + (i*n + j)));
		printf("\n");
	}
	getchar();
	getchar();
}

void best_for_m(int k)
//������ �� �������������� ��������� ��� �������
{
	int i = 0;
	while (*(rel + k*n + *(m + k*n + i)) != 0) i++;
	*(rel + k*n + *(m + k*n + i)) = 1;
}

void best_for_w(int k)
{
	//����� ������� �������� ��� �������
	char i, tmp = -1;
	for (i = 0; i<n; i++)
		if (*(rel + i*n + k))
			if (tmp == -1) tmp = i;
			else
				if (rating_for_w(i)<rating_for_w(tmp))
					*(rel + i*n + k) = -1;
				else
				{
					*(rel + tmp*n + k) = -1;
					tmp = i;
				}
}
void print_rel(void)
{
	//����� ������� ���������
	char i, j;
	printf("������� ����������� \n");
	printf("+ - ��������, # - �����, . - ����������� �� ����\n  ");
	for (i = 0; i<n; i++)
		printf("%3i", i + 1);
	for (i = 0; i<n; i++)
	{
		printf("\n%2i) ", i + 1);
		for (j = 0; j<n; j++)
			if (*(rel + i*n + j) == 1)
				printf("+  ");
			else if (*(rel + i*n + j) == -1)
				printf("#  ");
			else printf(".  ");
	}
	printf("\n");
	getchar();
}

void step(void)
{
	//��� ��������
	int i;
	for (i = 0; i<n; i++)
		if (check_m(i) == -1) best_for_m(i);
	for (i = 0; i<n; i++)
		best_for_w(i);
}

void print_sol(void)
{
	printf("����������� ����: \n");
	for (char i = 0; i<n; i++)
	{
		printf("%3i+%3i   ", i + 1, check_m(i) + 1);
		if (!((1 + i) % 5)) printf("\n");
	}
	getchar();
}