
#include <iostream>
#include <cstring>
#include "stive.h"
#include "cozi.h"
#include "transformare.h"
#include "backend.h"

using namespace std;

nod* radacina;
extern stiva pre;

int tipNod(char c[100])
{
	if (strcmp("sin", c) == 0 || strcmp("cos", c) == 0 || strcmp("tg", c) == 0 || strcmp("ctg", c) == 0)
		return 1;
	if (strcmp("arcsin", c) == 0 || strcmp("arccos", c) == 0 || strcmp("arctg", c) == 0 || strcmp("arcctg", c) == 0)
		return 1;
	if (strcmp("!=", c) == 0 || strcmp("<=", c) == 0 || strcmp(">=", c) == 0)
		return 2;
	if (strcmp("sqrt", c) == 0 || strcmp("ln", c) == 0 || strcmp("lg", c) == 0 || strcmp("abs", c) == 0 || strcmp("derivata", c) == 0 || strcmp("primitive", c) == 0)
		return 1;
	if (strcmp("sqrtord", c) == 0 || strcmp("log", c) == 0)
		return 2;
	if (strcmp("lim", c) == 0 || strcmp("integral", c) == 0)
		return 3;
	if (strcmp("sum", c) == 0)
		return 4;
	if (c[0] == '+' || c[0] == '-' || c[0] == '^' || c[0] == '*' || c[0] == '/' || c[0] == '=' || c[0] == '<' || c[0] == '>')
		return 2;
	if (c[0] == '_')
		return 1;
	return 0;
}
void initializaeazaRadacina(nod*& a)
{
	a = new nod;
}
void push(nod* y)
{
	char c[100];
	strcpy_s(c, sizeof(c), pre.varf->info);
	int w;
	w = tipNod(c);
	strcpy_s(y->symbol, sizeof(y->symbol), c);
	y->numar = w;
	y->prioritate = pre.varf->operand;
	for (int i = w - 1; i >= 0; i--)
	{
		nod* a = new nod;
		y->urmator[i] = a;
		if (!stivaesteVida(pre))
		{
			popstiva(pre);
			push(y->urmator[i]);
		}
	}
}
void creeazaarbore(nod* radacina)
{
	if (!stivaesteVida(pre))
	{
		push(radacina);
	}
}
void adaugaparanteze(nod* a)
{
	if (a != NULL)
	{
		if (strchr("+-*/^", a->symbol[0]) != NULL)
		{
			if (strchr("+-*/^", a->urmator[1]->symbol[0]) != NULL)
			{
				if (a->prioritate >= a->urmator[1]->prioritate)
				{
					nod* q;
					q = new nod;
					strcpy_s(q->symbol, sizeof(q->symbol), "()");
					q->numar = 1;
					q->urmator[0] = a->urmator[1];
					a->urmator[1] = q;
				}
			}
		}
		for (int i = 0; i < a->numar; i++)
			adaugaparanteze(a->urmator[i]);
	}
}
void parcurgereInPreordine(nod* a)
{
	if (a != NULL)
	{
		cout << a->symbol << ' ' << a->numar << ' ' << a->prioritate << endl;
		for (int i = 0; i < a->numar; i++)
			parcurgereInPreordine(a->urmator[i]);
	}
}
void generarearbore()
{
	if (tranzitie() == 1)
	{
		initializaeazaRadacina(radacina);
		creeazaarbore(radacina);
		adaugaparanteze(radacina);
		parcurgereInPreordine(radacina);
	}
}

