#ifndef BACKEND_H
#define BACKEND_H
#include <iostream>
#include <cstring>
#include "stive.h"
#include "cozi.h"
#include "transformare.h"

struct nod
{
	int numar = -1;
	char symbol[100] = "?";
	nod* urmator[100];
	int prioritate = -1;
};
int tipNod(char c[100]);
void initializaeazaRadacina(nod*& a);
void push(nod* y);
void creeazaarbore(nod* radacina);
void adaugaparanteze(nod* a);
void parcurgereInPreordine(nod* a);
void generarearbore();

#endif
