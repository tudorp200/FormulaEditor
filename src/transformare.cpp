#include <iostream>
#include <cstring>
#include "transformare.h"
#include "desparte.h"
#include "cozi.h"
#include "stive.h"
#define EROARE 10000
using namespace std;

extern  coada inf;
extern coada post;
extern stiva semn;
extern stiva pre;

void eliminacolada() // elimina acoladele pt a face tranzitia infixat-postfixat
{
	for (int i = 0; i <= la; i++)
	{
		if (mat[i][0] == '{' || mat[i][0] == '}')
		{
			for (int j = i; j < la; j++)
			{
				strcpy_s(mat[j], 100, mat[j + 1]);
			}
			la--;
			i--;
		}
	}
}

void infixat() //seteaza prioritatile mai degraba la elementele lui mat
{
	initializeazacoada(inf);
	for (int i = 0; i <= la; i++)
	{
		enqueuecoada(inf, mat[i]);
	}
	nodcoada* curent;
	curent = inf.prim;
	while (curent != NULL)
	{
		if (strcmp("sin", curent->info) == 0 || strcmp("cos", curent->info) == 0 || strcmp("tg", curent->info) == 0 || strcmp("ctg", curent->info) == 0)
		{
			curent->operand = 4;
		}
		else if (strcmp("arcsin", curent->info) == 0 || strcmp("arccos", curent->info) == 0 || strcmp("arctg", curent->info) == 0 || strcmp("arcctg", curent->info) == 0)
		{
			curent->operand = 4;
		}
		else if (strcmp("!=", curent->info) == 0 || strcmp("=>", curent->info) == 0 || strcmp("<=", curent->info) == 0)
		{
			curent->operand = 5;
		}
		else if (strcmp("sqrt", curent->info) == 0 || strcmp("ln", curent->info) == 0 || strcmp("abs", curent->info) == 0 || strcmp("derivata", curent->info) == 0 || strcmp("primitive", curent->info) == 0)
		{
			curent->operand = 4;
		}
		else if (strcmp("sqrtord", curent->info) == 0 || strcmp("log", curent->info) == 0 || strcmp("lg", curent->info) == 0 || strcmp("integral", curent->info) == 0)
		{
			curent->operand = 4;
		}
		else if (strcmp("lim", curent->info) == 0 || strcmp("sum", curent->info) == 0)
		{
			curent->operand = 4;
		}
		else if (curent->info[0] == '+' || curent->info[0] == '-')
		{
			curent->operand = 1;
		}
		else if (curent->info[0] == '*' || curent->info[0] == '/')
		{
			curent->operand = 2;
		}
		else if (curent->info[0] == '^')
		{
			curent->operand = 3;
		}
		else if (curent->info[0] == '=' || curent->info[0] == '<' || curent->info[0] == '>')
		{
			curent->operand = 5;
		}
		else if (curent->info[0] == '_')
		{
			curent->operand = 4;
		}
		else if (curent->info[0] == '(' || curent->info[0] == ')')
		{
			curent->operand = -1;
		}
		else
		{
			curent->operand = 0;
		}
		curent = curent->urm;
	}
	//afiseazacoada(inf);
}

void postfixat()
{
	initializeazacoada(post);
	initializeazastiva(semn);
	nodcoada* x;
	x = new nodcoada;
	while (!coadaesteVida(inf))
	{
		strcpy_s(x->info, sizeof(x->info), inf.prim->info);
		x->operand = inf.prim->operand;
		x->urm = inf.prim->urm;
		/*cout << "x: ";
		cout << x->info << endl;
		cout << "inf: ";
		afiseazacoada(inf);
		cout << "post: ";
		afiseazacoada(post);
		cout << "semn: ";
		afiseazastiva(semn);
		cout << endl;*/
		dequeuecoada(inf);
		if ((!coadaesteVida(inf) && x->operand == 0) || (coadaesteVida(inf) && x->operand == 0))
		{
			enqueuecoada(post, x->info);
			post.ultim->operand = x->operand;
		}
		else if (!coadaesteVida(inf))
		{
			if (x->info[0] == ')')
			{
				while (!stivaesteVida(semn) && semn.varf->info[0] != '(')
				{
					enqueuecoada(post, semn.varf->info);
					post.ultim->operand = semn.varf->operand;
					popstiva(semn);
				}
				popstiva(semn);
			}
			else
			{
				while (!stivaesteVida(semn) && x->info[0] != '(' && semn.varf->operand >= x->operand)
				{
					enqueuecoada(post, semn.varf->info);
					post.ultim->operand = semn.varf->operand;
					popstiva(semn);
				}
				pushstiva(semn, x->info);
				semn.varf->operand = x->operand;
			}
		}
	}
	while (!stivaesteVida(semn))
	{
		if (semn.varf->info[0] == '(')
			popstiva(semn);
		enqueuecoada(post, semn.varf->info);
		post.ultim->operand = semn.varf->operand;
		popstiva(semn);
	}
	//afiseazacoada(post);
}

void prefixat()
{
	nodcoada* curent;
	curent = post.prim;
	initializeazastiva(pre);
	while (curent != NULL)
	{
		pushstiva(pre, curent->info);
		pre.varf->operand = curent->operand;
		curent = curent->urm;
	}
	afiseazastiva(pre);
}
int tranzitie()
{
	cin.get(text, 251);
	partionare();
	cout << verificare() << endl;
	if (verificare() != EROARE)
	{
		eliminacolada();
		infixat();
		postfixat();
		prefixat();
		return 1;
	}
	return -1;
}
