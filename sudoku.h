#ifndef SUDOKU_H
#define SUDOKU_H

#define SUDOKU_SIZE 9

typedef struct {
    char playfield[SUDOKU_SIZE][SUDOKU_SIZE];
} sudoku;


extern long solution_number;

int load_sudoku(char *filename, sudoku *s);
void print_sudoku(sudoku *s);
int valid_sudoku(sudoku *s);
int solve_sudoku(sudoku *s, int depth);

#endif