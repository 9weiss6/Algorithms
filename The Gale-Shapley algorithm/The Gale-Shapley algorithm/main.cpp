//алгоритм Гейла-Шепли, реализация ручного и автоматического ввода с использованием динамической памяти
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
using namespace std;

char *m, *w, *rel, n;

bool end_check(void);          //проверка наличия пар для всех
int check_m(int);                      //проверка наличия невесты у жениха
int check_w(int);                      //проверка наличия жениха у невесты
int rating_for_m(int);         //положение невесты в векторе приоритетов жениха
int rating_for_w(int);         //положение жениха в векторе приоритетов невесты
void get_n(void);                      //получение количества пар и выделение памяти
void inp(void);                        //ручной ввод
void generate(void);           //генерация приоритетов
void type_of_inp(void);        //выбор типа ввода
void print_priority(void);     //вывод таблицы приоритетов женихов и невест
void best_for_m(int);          //предложение лучшей из оставшихся невест
void best_for_w(int);          //выбор лучшего из предложений
void print_rel(void);          //печать таблицы отношений
void step(void);                       //одна итерация
void print_sol(void);          //печать оптимального решения

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
	//проверка наличия пар для всех женихов и невест
	for (int i = 0; i<n; i++)
		if ((check_m(i) == -1) || (check_w(i) == -1)) return(false);
	return(true);
}

int check_m(int k)
//нахождения номера невесты k-го жениха
{
	for (char i = 0; i<n; i++)
		if (*(rel + k*n + i) == 1) return (i);
	return(-1);
}

int check_w(int k)
//нахождение номера жениха k-той невесты
{
	for (int i = 0; i<n; i++)
		if (*(rel + k + i*n) == 1) return (i);
	return(-1);
}

int rating_for_w(int k)
//нахождение положения жениха в списке предпочтений невесты
{
	int i = 0;
	while (*(w + k*n + i) != k) i++;
	return(i);
}

int rating_for_m(int k)
{
	//нахождение положения невесты в списке предпочтений жениха
	int i = 0;
	while (*(m + k*n + i) != k) i++;
	return(i);
}
void get_n(void)
{
	//всякая нужная фигня
	n = 0;
	printf("Введите положительное количество пар: ");
	scanf_s("%hhi", &n);
	srand(time_t(0));

	while (n<1)
	{
		printf("Ошибка. Повторите ввод: ");
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
		printf("Не удалось выделить память");
		return;
	}
	for (i = 0; i<n2; i++) *(rel + i) = 0;
}

void inp(void)
{
	//ввод вручную
	get_n();
	printf("Введите приоритеты для женихов");
	for (int i = 0; i<n; i++)
	{
		printf("\n%2i-й жених:\n", i + 1);
		for (int j = 0; j<n; j++)
		{
			printf("%i) ", j + 1);
			scanf_s("%i", (m + i*n + j));
			for (int k = 0; k <= j; k++)
				while (((*(m + i*n + j) == *(m + i*n + k)) && (k != j)) || (*(m + i*n + j)<1) || (*(m + i*n + j)>n))
				{
					printf("Такое значение уже введено или некорректно, повторите ввод ");
					scanf_s("%i", (m + i*n + j));
				}
		}
	}
	printf("Введите приоритеты невест");
	for (int i = 0; i<n; i++)
	{
		printf("\n%2i-я невеста:\n", i + 1);
		for (int j = 0; j<n; j++)
		{
			printf("%i) ", j + 1);
			scanf_s("%i", (w + i*n + j));
			for (int k = 0; k <= j; k++)
				while (((*(w + i*n + j) == *(w + i*n + k)) && (k != j)) || (*(w + i*n + j)<1) || (*(w + i*n + j)>n))
				{
					printf("Такое значение уже введено или некорректно, повторите ввод ");
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
//генерация матриц предпочтений
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
	printf("Выберите тип ввода: 0 - генерация, 1 - ручной \n");
	scanf_s("%i", &i);
	while (i != 0 && i != 1)
	{
		printf("Неверное значение. Повторите ввод: 0 - генерация, 1 - ручной \n");
		scanf_s("%i", &i);
	}
	if (i == 0) generate();
	else inp();
}

void print_priority(void)
{
	//вывод этих матриц
	char i, j;
	printf("Приоритеты женихов\n");
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
			printf("%3i", 1 + *(m + (i*n + j)));
		printf("\n");
	}
	printf("\n");
	printf("Приоритеты невест\n");
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
//лучший из неопробованных вариантов для женихов
{
	int i = 0;
	while (*(rel + k*n + *(m + k*n + i)) != 0) i++;
	*(rel + k*n + *(m + k*n + i)) = 1;
}

void best_for_w(int k)
{
	//выбор лучшего варианта для невесты
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
	//вывод таблицы отношений
	char i, j;
	printf("Таблица предложений \n");
	printf("+ - согласие, # - отказ, . - предложения не было\n  ");
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
	//шаг проверки
	int i;
	for (i = 0; i<n; i++)
		if (check_m(i) == -1) best_for_m(i);
	for (i = 0; i<n; i++)
		best_for_w(i);
}

void print_sol(void)
{
	printf("Оптимальные пары: \n");
	for (char i = 0; i<n; i++)
	{
		printf("%3i+%3i   ", i + 1, check_m(i) + 1);
		if (!((1 + i) % 5)) printf("\n");
	}
	getchar();
}