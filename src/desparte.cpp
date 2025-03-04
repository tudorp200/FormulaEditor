#include "desparte.h"
#include "cozi.h"
#include "stive.h"
#define EROARE 10000
using namespace std;
char mat[100][100];
int la;
char text[251];
void modificareecuatii(char s[251], char c) // caz = < >
{
	int poz;
	int x = strlen(text);
	for (int i = 0; i < strlen(text); i++)
		if (text[i] == c)
		{
			poz = i;
			break;
		}
	for (int i = strlen(text) - 1; i > poz; i--)
		text[i + 3] = text[i];
	text[poz + 3] = '(';
	text[x + 3] = ')';
	for (int i = poz; i >= 0; i--)
		text[i + 2] = text[i];
	text[0] = c;
	text[1] = '(';
	text[poz + 2] = ')';
	//cout << text;
	//cout << endl;
}

void altmodificareecuatii(char s[251], char c[2]) // caz <= >= !=
{
	int poz;
	int x = strlen(text);
	for (int i = 0; i < strlen(text); i++)
		if (text[i] == c[1])
		{
			poz = i;
			break;
		}
	for (int i = strlen(text) - 1; i > poz; i--)
		text[i + 3] = text[i];
	text[poz + 3] = '(';
	text[x + 3] = ')';
	for (int i = poz - 1; i >= 0; i--)
		text[i + 3] = text[i];
	text[0] = c[0];
	text[1] = c[1];
	text[2] = '(';
	text[poz + 2] = ')';
	//cout << text;
	//cout << endl;
}

void partionare() // imparte textul pe noduri intr o matrice
{
	if (strstr(text, "!=") != NULL)
	{
		char c[2];
		c[0] = '!';
		c[1] = '=';
		altmodificareecuatii(text, c);
	}
	else if (strstr(text, ">=") != NULL)
	{
		char c[2];
		c[0] = '>';
		c[1] = '=';
		altmodificareecuatii(text, c);
	}
	else if (strstr(text, "<=") != NULL)
	{
		char c[2];
		c[0] = '<';
		c[1] = '=';
		altmodificareecuatii(text, c);
	}
	else if (strchr(text, '=') != NULL)
	{
		modificareecuatii(text, '=');
	}
	else if (strchr(text, '<') != NULL)
	{
		modificareecuatii(text, '<');
	}
	else if (strchr(text, '>') != NULL)
	{
		modificareecuatii(text, '>');
	}
	for (int i = 0; i < strlen(text); i++)
	{
		if (i == 0 && strchr("<>!", text[i]) != NULL && text[i + 1] == '=')
		{
			mat[la][0] = text[i];
			mat[la][1] = text[i + 1];
			i++;
		}
		else if (i == 0 && text[i] == '-')
		{
			mat[la][0] = '_';
			la++;
		}
		else if (i == 0 && strchr("=-<>", text[i]) != NULL)
		{
			mat[la][0] = text[i];
		}
		else if (i == 0 && text[i] == '(')
		{
			mat[la][0] = text[i];
			la++;
		}
		else if (i == 1 && text[i] == '-' && text[0] == '(')
		{
			mat[la][0] = '_';
			la++;
		}
		else if (i == 1 && text[i] == '(' && text[0] == '-')
		{
			mat[la][0] = '(';
			la++;
		}
		else if (strchr("+-/*^=()_<>{}", text[i]) != NULL && strchr("+-/*^=()_<>{}", text[i + 1]) != NULL)
		{
			if (text[i] == '(' && text[i + 1] == '-')
			{
				la++;
				mat[la][0] = text[i];
				text[i + 1] = '_';
			}
			else
			{
				la++;
				mat[la][0] = text[i];
			}
		}
		else if (strchr("+-/*^=()_<>{}", text[i]) != NULL) //caz general de despartire de semn
		{
			la++;
			mat[la][0] = text[i];
			la++;
		}
		else
		{
			mat[la][strlen(mat[la])] = text[i];  // aici construieste numarul
		}
	}
	for (int i = 0; i <= la; i++)
		cout << "nod:" << ' ' << mat[i] << endl;
	cout << endl;
}

int verificareargument(int inceput, int sfarsit, int argumente) // aici verifica intre acoladele gasite (nr argumente daca se bun si normele bunului simt la sintactica)
{
	int ps = 0, pd = 0, nr = 0;
	if (mat[inceput + 1][0] != '(' || mat[sfarsit - 1][0] != ')')
	{
		cout << "nu asa se incepe dupa acolada" << endl;
		return EROARE;
	}
	for (int i = inceput + 1; i < sfarsit; i++)
	{
		if (mat[i][0] == '(' && mat[i + 1][0] == ')')
		{
			cout << "paranteza dubioasa detectata 1" << endl;
			return EROARE;
		}
		if (mat[i][0] == '(')
			pd++;
		if (mat[i][0] == ')')
			ps++;
		if (ps > pd)
		{
			cout << "utilizare paranteze incorecta" << endl;
			return EROARE;
		}
		if (strlen(mat[i]) == 1 && strlen(mat[i + 1]) == 1)
			if (strchr("+-/^*_", mat[i][0]) != NULL && strchr("+-^/*_", mat[i + 1][0]) != NULL)
			{
				cout << mat[i][0] << ' ' << mat[i + 1][0] << endl;
				cout << "semne gresite" << endl;
				return EROARE;
			}
		if (mat[i][0] == ')' && mat[i + 1][0] == '(')
		{
			nr++;
		}
	}
	if (nr != argumente)
	{
		cout << "nu argumente bune" << endl;
		return EROARE;
	}
	if (pd != ps)
	{
		cout << "nr paranteze gresite" << endl;
		return EROARE;
	}
	return 1;
}

int prescurtare(int& i, int zt) // aici daca gaseste in verificare argument (gen acolada de inceput si acolada d sfarsit) la functie crazy (nu am gasit un nume mai bun) also merge functie in functie
{
	int aux = zt;
	if (mat[i + 1][0] != '{')
		cout << "tre sa fie {" << endl;
	for (int j = i + 2; j <= la; j++)
	{
		if (mat[j + 1][0] == '{')
		{
			if (strcmp("sin", mat[j]) == 0 || strcmp("cos", mat[j]) == 0 || strcmp("tg", mat[j]) == 0 || strcmp("ctg", mat[j]) == 0 || strcmp("arcsin", mat[j]) == 0 || strcmp("arccos", mat[j]) == 0 || strcmp("arctg", mat[j]) == 0 || strcmp("arcctg", mat[j]) == 0 || strcmp("sqrt", mat[j]) == 0 || strcmp("ln", mat[j]) == 0 || strcmp("lg", mat[j]) == 0 || strcmp("abs", mat[j]) == 0 || strcmp("derivata", mat[j]) == 0 || strcmp("primitive", mat[j]) == 0)
			{
				aux = aux + prescurtare(j, 0);
			}
			else if (strcmp("sqrtord", mat[j]) == 0 || strcmp("log", mat[j]) == 0)
			{
				aux = aux + prescurtare(j, 1);
				if (aux == aux + EROARE)
				{
					return EROARE;
				}
			}
			else if (strcmp("lim", mat[j]) == 0 || strcmp("integral", mat[j]) == 0)
			{
				aux = aux + prescurtare(j, 2);
				if (aux == aux + EROARE)
				{
					return EROARE;
				}
			}
			else if (strcmp("sum", mat[j]) == 0)
			{
				aux = aux + prescurtare(j, 3);
				if (aux == aux + EROARE)
				{
					return EROARE;
				}
			}
			zt = aux;
		}
		else if (mat[j][0] == '}')
		{
			if (verificareargument(i + 1, j, zt) == EROARE)
			{
				return EROARE;
			}
			if (verificareargument(i + 1, j, zt) == 0)
			{
				cout << "nu e bine" << endl;
				return EROARE;
			}
			i = j;
			goto bun;
		}
	}
	cout << "lipseste }" << endl;
	return EROARE;
bun:;
	return aux;
}
int verificare() // aici nu cred ca mai trebuie o descriere ce face
{
	int pd = 0, pi = 0, ad = 0, ai = 0;
	int i;
	if (strchr("+/*^-", mat[0][0]) != NULL)
	{
		cout << "nu poate incepe asa o formula" << endl;
		return EROARE;
	}
	if (strchr("+/*^=-_", mat[la][0]) != NULL)
	{
		cout << "nu se poate termina asa o formula" << endl;
		return EROARE;
	}
	for (i = 0; i <= la; i++)
	{
		if (mat[i][0] == '(' && mat[i + 1][0] == ')')
		{
			cout << "paranteza dubioasa detectata 2" << endl;
			return EROARE;
		}
		if (mat[i][0] == '(')
			pd++;
		if (mat[i][0] == ')')
			pi++;
		if (pi > pd)
		{
			cout << "utilizare paranteze incorecta" << endl;
			return EROARE;
		}
		if (strcmp("sin", mat[i]) == 0 || strcmp("cos", mat[i]) == 0 || strcmp("tg", mat[i]) == 0 || strcmp("ctg", mat[i]) == 0 || strcmp("arcsin", mat[i]) == 0 || strcmp("arccos", mat[i]) == 0 || strcmp("arctg", mat[i]) == 0 || strcmp("arcctg", mat[i]) == 0 || strcmp("sqrt", mat[i]) == 0 || strcmp("ln", mat[i]) == 0 || strcmp("lg", mat[i]) == 0 || strcmp("abs", mat[i]) == 0 || strcmp("derivata", mat[i]) == 0 || strcmp("primitive", mat[i]) == 0)
		{
			int k;
			k=prescurtare(i,0);
			if (k == EROARE)
				return EROARE;
		}
		else if (strcmp("sqrtord", mat[i]) == 0 || strcmp("log", mat[i]) == 0)
		{
			int k;
			k=prescurtare(i,1);
			if (k == EROARE)
				return EROARE;
		}
		else if (strcmp("lim", mat[i]) == 0 || strcmp("integral", mat[i]) == 0)
		{
			int k;
			k=prescurtare(i,2);
			if (k == EROARE)
				return EROARE;
		}
		else if (strcmp("sum", mat[i]) == 0)
		{
			int k;
			k=prescurtare(i, 3);
			if (k == EROARE)
				return EROARE;
		}
		if (strlen(mat[i]) == 1 && strlen(mat[i + 1]) == 1)
			if (strchr("+-/^*_", mat[i][0]) != NULL && strchr("+-^/*_", mat[i + 1][0]) != NULL)
			{
				cout << mat[i][0] << ' ' << mat[i + 1][0] << endl;
				cout << "semne gresite" << endl;
				return EROARE;
			}
		if (mat[i][0] == ')' && mat[i + 1][0] == '(')
		{
			cout << "paranteza dubioasa detectata 3" << endl;
			return EROARE;
		}
	}
	if (pd != pi)
	{	
		cout << "nr paranteze gresite" << endl;
		return EROARE;
	}
	return 1;
}
