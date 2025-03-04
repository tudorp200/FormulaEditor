#include "stive.h"

using namespace std;

bool stivaesteVida(stiva S)
{
	return S.nrElemente == 0;
}

void initializeazastiva(stiva& S)
{
	S.varf = NULL; S.nrElemente = 0;
}

void popstiva(stiva& S)
{
	if (!stivaesteVida(S))
	{
		nodstiva* varf_nou;
		varf_nou = S.varf->urm;
		delete S.varf;
		S.varf = varf_nou;
		S.nrElemente--;
	}
}


void pushstiva(stiva& S, char element[100])
// adauga un element la stiva, in varf (LIFO)
{
	nodstiva* nod_nou;
	if (stivaesteVida(S))
	{
		S.nrElemente = 1;
		S.varf = new nodstiva;
		strcpy_s(S.varf->info ,sizeof(S.varf->info), element);
		S.varf->urm = NULL;
	}
	else
	{
		S.nrElemente++;
		nod_nou = new nodstiva;
		strcpy_s(nod_nou->info, sizeof(nod_nou->info) , element);
		nod_nou->urm = S.varf;
		S.varf = nod_nou;
	}
}

void afiseazastiva(stiva S)
{
	nodstiva* nod_curent;
	nod_curent = S.varf;
	while (nod_curent != NULL)
	{
		cout << nod_curent->info << ",";
		nod_curent = nod_curent->urm;
	}
	cout << endl;
}
stiva semn;
stiva pre;
