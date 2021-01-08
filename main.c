#include <stdio.h>
#include "sudoku.h"

int main(int argc, char *argv[])
{
    sudoku su;

    if (argc < 2) {
        printf("Usage: sudos <sudoku-file>\n");
        return 1;
    }

    load_sudoku(argv[1], &su);
    print_sudoku(&su);

    solve_sudoku(&su, 1);

    return 0;
}
