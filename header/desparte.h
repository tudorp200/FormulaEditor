#ifndef DESPARTE_H
#define DESPARTE_H
#include <iostream>
#include <cstring>
#include "stive.h"
#include "cozi.h"
extern char mat[100][100];
extern int la;
extern char text[251];
void altmodificareecuatii(char s[251], char c[2]);
void modificareecuatii(char s[251], char c);
void partionare();
int verificare();
void infixat();
int despartire();
#endif
