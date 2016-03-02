#include "../headers/KillerSudoku.h"
#include <stdio.h>
#include <math.h>

void printHorizLine(int gridLength);

void printSudoku(KSData* ksData) {
	int b = ksData->boxLength;
	int g = ksData->gridLength;

	printHorizLine(g);

	for (int row = 0; row < g; row++) {
		printf("|");

		for (int col = 0; col < g; col++) {
			printf("%d", ksData->grid[col][row]->value);
			printf("%c", ((col+1) % b == 0 ? '|' : ' '));
		}
		printf("\n");

		if ((row+1) % b == 0)
			printHorizLine(g);
	}
}

void printHorizLine(int gridLength) {
	for(int i = 0;
			i < 2 * gridLength + 1;
			i++) {
		printf("—");
	}
	printf("\n");
}
