#include <stdio.h>							// Autor: Szymon Hejmanowski
void odejmij_jeden(int** a);				// Grupa: 2
void to_abs(int tab[], int n);				// Data: 01.12.2022
void przestaw_abs(int tab[], int n);		// Termin: 01.12.2022
int main()									// Lab4
{
	int tab[6] = {10, -5, -6, 3, -3, 4};
	int n = 6;
	
	for (int i = 0; i < n; i++) {
		przestaw_abs(tab, n);
	}

	for (int i = 0; i < n; i++) {
		printf("%d ", tab[i]);
	}
	printf("\n");


	printf("Wartosc minimalna: %d\n", tab[0]);
	printf("Wartosc maksymalna: %d\n", tab[n - 1]);

	if (n % 2 == 0) {
		float mediana = (tab[n / 2] + tab[(n / 2) - 1]);
		mediana /= 2;
		printf("Mediana: %f\n", mediana);
	}
	else {
		printf("Mediana: %d\n", tab[n / 2]);
	}



	return 0;
}