#ifndef STIVE_H
#define STIVE_H
#include <iostream>
#include <cstring>
struct nodstiva {
	char info[100];
	int operand;
	nodstiva* urm;
};

struct stiva {
	nodstiva* varf;
	int nrElemente;
};
bool stivaesteVida(stiva S);
void initializeazastiva(stiva& S);
void popstiva(stiva& S);
void pushstiva(stiva& S, char element[100]);
void afiseazastiva(stiva S);
#endif
