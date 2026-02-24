/**
Se dau trei siruri de caractere. 
Sa se afiseze cel mai lung prefix comun pentru fiecare din cele trei perechi
de cate doua siruri ce se pot forma.
**/

#include <stdio.h>
#include <string.h>

int prefixAsm(char* s1, char* s2, char* prefix);

int main()
{
	char s1[] = "Ana are mere";
	char s2[] = "Ana are pere";
	char s3[] = "Ana nu are mere";
	char prefix[101], rez[101];

	int maxLen = 0, Len = 0;

	rez[0] = '\0';
	Len = prefixAsm(s1, s2, prefix);
	if (Len > maxLen) 
	{
		maxLen = Len;
		strcpy(rez, prefix);
	}

	Len = prefixAsm(s1, s3, prefix);
	if (Len > maxLen) 
	{
		maxLen = Len;
		strcpy(rez, prefix);
	}

	Len = prefixAsm(s2, s3, prefix);
	if (Len > maxLen) 
	{
		maxLen = Len;
		strcpy(rez, prefix);
	}

	printf("Cel mai lung prefix comun, de lungime %d, este: '%s'\n", maxLen, rez);

	Len = prefixAsm(s1, s2, prefix);
	printf("s1-s2: Len=%d prefix='%s'\n", Len, prefix);
	Len = prefixAsm(s1, s3, prefix);
	printf("s1-s3: Len=%d prefix='%s'\n", Len, prefix);
	Len = prefixAsm(s2, s3, prefix);
	printf("s2-s3: Len=%d prefix='%s'\n", Len, prefix);


	return 0;
}