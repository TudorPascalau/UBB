
#include <stdio.h>

int main()
{
	while (1)
	{
		printf("1. Urmatorul numar par\nO. Iesire\nDati comanda: ");

		int cmd;
		scanf_s("%d", &cmd);

		if (cmd == 0)
		{
			break;
		}

		else if(cmd == 1)
		{
			int nr;
			scanf_s("%d", &nr);
			printf("%d\n", nr + 2 - nr % 2);
		}

		else
		{
			printf("Comanda necunoscuta\n");
		}
	}

	return 0;
}