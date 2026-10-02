// Algorithm X
// Finds all the exact covers in matrix[][] (rows x columns).
// Stores the current solution in subset[].
// '_' characters are ignored.
// If subset[c] = '_' then column c isn't satisified yet.
// As the result, program prints the subset according to the filter[].
// Columns with '-' are ignored.

// Author: Wiktoria Ksel

#include <stdio.h>
#include <stdbool.h>
#define MAX_COLUMNS 300
#define MAX_ROWS 200

char matrix[MAX_ROWS][MAX_COLUMNS]; 	
char filter[MAX_COLUMNS]; 		// Determines which characters appear in the output.
char subset[MAX_COLUMNS];		// Stores the current solution.

// Sets the given array to underlines (no character in the subset).
void set_to_underline (char array[], int size) {
	for (int i = 0; i < size; i++)
		array[i] = '_';
}

// Reads the filter line, stores it in filter[], and returns the number of columns.
int get_filter() {
	int columns = 0;
	char c;

	while ((c = (char)getchar()) != '\n') {
		filter[columns] = c;
		columns++;
	}
	
	return columns;
}

// Reads the matrix rows.
// Returns the number of rows.
int get_matrix (int columns) {
	int rows = 0;
	char c;

	while ((c = (char)getchar()) != EOF) {
		for (int i = 0; i < columns; i++) {
			matrix[rows][i] = c;
			c = (char)getchar();
		}
		rows++;
	}
	
	return rows;
}

// Prints the current subset based on filter[].
void result (int columns) {
	for (int i = 0; i < columns; i++) {
		if (filter[i] == '+')
			printf("%c", subset[i]);
	}

	printf("\n");
}

// Checks if row r is disjoint with the current subset.
bool disjoint (int r, int columns) {
	bool dis = true;
	int j = 0;
	while (j < columns && dis) {
		if (matrix[r][j] != '_' && subset[j] != '_')
			dis = false;
		j++;
	}
	return dis;
}

// Adds characters from row r to the current subset.
void add_to_subset (int r, int columns) {
	for (int j = 0; j < columns; j++) {
		if (matrix[r][j] != '_')
			subset[j] = matrix[r][j];
	}
}

// Removes characters from row r from the current subset.
void remove_from_subset (int r, int columns) {
	for (int j = 0; j < columns; j++) {
		if (matrix[r][j] != '_')
			subset[j] = '_';
	}
}

// Core Algorithm X recursion.
// Tries to fill column c using available rows in the matrix (rows x columns).
void algorithm_x (int c, int rows, int columns) {
	if (c == columns)
		// All columns are satisfied.
		result(columns);
	else {
		if (subset[c] != '_') 
			// Column c is already satisfied.
			algorithm_x(c + 1, rows, columns);
		else {
			for (int r = 0; r < rows; r++) {
				if (matrix[r][c] != '_' && disjoint(r, columns)) {
					//Row r satisfies column c and is disjoint with subset.
					add_to_subset(r, columns);
					// Do the same thing to satisfy the next column.
					algorithm_x(c + 1, rows, columns);
					remove_from_subset(r, columns);
				}
			}
		}	
	}
}


int main() {

	int columns = get_filter();
	int rows = get_matrix(columns);

	set_to_underline(subset, columns);

	algorithm_x (0, rows, columns);

	return 0;
}


