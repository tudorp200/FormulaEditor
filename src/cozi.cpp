#include "cozi.h"

using namespace std;

bool coadaesteVida(coada C)
{
	return C.nrElemente == 0;
}

void initializeazacoada(coada& C)
{
	C.prim = NULL; C.ultim = NULL; C.nrElemente = 0;
}

void peekcoada(coada C, char element[100])
// ia informatia din primul nod al cozii, fara a-l elimina
{
	if (!coadaesteVida(C))
		strcpy_s(element,sizeof(element), C.prim->info);
}

void enqueuecoada(coada& C, char element[100])
// adauga un element la coada, dupa ultimul element (FIFO)
{
	nodcoada* nod_nou;
	if (coadaesteVida(C))
	{
		C.nrElemente = 1;
		C.prim = new nodcoada;
		strcpy_s(C.prim->info ,sizeof(C.prim->info) ,element);
		C.prim->urm = NULL;
		C.ultim = C.prim;
	}
	else
	{
		C.nrElemente++;
		nod_nou = new nodcoada;
		strcpy_s(nod_nou->info, sizeof(nod_nou->info), element);
		nod_nou->urm = NULL;
		C.ultim->urm = nod_nou;
		C.ultim = nod_nou;
	}
}

void dequeuecoada(coada& C)
// scoate primul element din coada, din capul cozii
{
	if (!coadaesteVida(C))
	{
		nodcoada* primul;
		primul = C.prim;
		C.prim = C.prim->urm;
		delete primul;
		C.nrElemente--;
	}
	else
	{
		cerr << "EROARE: coada goala. ";
	}
}

void afiseazacoada(coada C)
{
	nodcoada* nod_curent;
	nod_curent = C.prim;
	while (nod_curent != NULL)
	{
		cout << nod_curent->info[0] << ",";
		nod_curent = nod_curent->urm;
	}
	cout << endl;
}
coada inf;
coada post;
