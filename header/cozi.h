#ifndef COZI_H
#define COZI_H
#include <iostream>
#include <cstring>
struct nodcoada {
	char info[100];
	int operand;
	nodcoada* urm;
};
struct coada {
	nodcoada* prim;
	nodcoada* ultim;
	int nrElemente;
};
bool coadaesteVida(coada C);
void initializeazacoada(coada& C);
void dequeuecoada(coada& C);
void enqueuecoada(coada& C, char element[100]);
void afiseazacoada(coada C);
#endif
