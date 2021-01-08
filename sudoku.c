#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sudoku.h"

char posnums[10] = {0};
long solution_number = 0;
int solution_depth = 0;

int validate_elements(int arr[]) {
    int i, j;

    for (i = 0; i < SUDOKU_SIZE; ++i) {
        for(j = 0; j < SUDOKU_SIZE; ++j) {
            if (i == j)
                continue;
            if (arr[i] == arr[j])
                return 1;
        }
    }

    return 0;
}

extern int valid_sudoku(sudoku *s) {
    int x, y, a, b, res, i, blocks;

    int r[SUDOKU_SIZE] = {0};
    int c[SUDOKU_SIZE] = {0};
    int block[SUDOKU_SIZE] = {0};
    blocks = 3;

    if (!s)
        return 0;

    for (x = 0; x < SUDOKU_SIZE; ++x) {

        memset(r, 0, SUDOKU_SIZE * sizeof (int));
        memset(c, 0, SUDOKU_SIZE * sizeof(int ));

        /* zkontroluj řádky a sloupce */
        for (y = 0; y < SUDOKU_SIZE; ++y) {
            if (!(s->playfield[x][y] >= '1' && s->playfield[x][y] <= '9'))
                return 1;
            r[y] = s->playfield[x][y] - '0';
            printf("y= %d x=%d \n", y, x);
            if (!(s->playfield[y][x] >= '1' && s->playfield[y][x] <= '9'))
                return 1;
            c[y] = s->playfield[y][x] - '0';
        }

        res = validate_elements(r);
        if (res == 1)
            return 0;
        res = validate_elements(c);
        if (res == 1)
            return 0;
    }

    /* zkontroluj bloky */
    for(a = 0; a < blocks; ++a) {
        for(b = 0; b < blocks; ++b) {
            /* projdi blok */
            i = 0;
            for (x = a * blocks; x < (a * blocks) + blocks; ++x) {
                for(y = b * blocks; y < (b * blocks) + blocks; ++y) {
                    block[i] = s->playfield[x][y] - '0';
                    i++;
                }
            }
            res = validate_elements(block);
            if (res == 1)
                return 0;
        }
    }

    return 1;
}

int load_sudoku(char *filename, sudoku *s)
{
    FILE *inp;
    int row, col;
    int c;

    inp = fopen(filename, "r");
    if (inp == NULL) return 0;

    /* Clear the playfield */
    for (row = 0; row < SUDOKU_SIZE; row++)
        for (col = 0; col < SUDOKU_SIZE; col++)
            s->playfield[row][col] = '-';

    row = 0;
    col = 0;

    do {
        c = fgetc(inp);

        if (c == '-' || (c >= '1' && c <= '9')) {
            s->playfield[row][col] = (char) c;
            col++;

            if (col >= SUDOKU_SIZE) {
                col = 0;
                row++;
            }
        }

    } while (c != EOF);


    fclose(inp);

    return 1;
}

void print_sudoku(sudoku *s)
{
    int i, j;

    printf("|-------+-------+-------|\n");

    for (i = 0; i < SUDOKU_SIZE; i++) {
        printf("| ");
        for (j = 0; j < SUDOKU_SIZE; j++) {
            printf("%c ", s->playfield[i][j]);
            if (!((j + 1) % 3)) printf("| ");
        }

        if (!((i + 1) % 3)) printf("\n|-------+-------+-------|\n");
        else printf("\n");
    }
}

void get_possibilities(sudoku *s, int i, int j, char *pos)
{
    memset(pos, 0, 10);
    strcpy(pos, "123456789");
}

int solve_sudoku(sudoku *s, int depth)
{
    int i, j, k;
    int found = 0;
    int valck = 0;

    printf("\x0D%d", depth);

    valck = valid_sudoku(s);
    if (!valck) return 0;

    for (i = 0; i < SUDOKU_SIZE; i++) {
        for (j = 0; j < SUDOKU_SIZE; j++)
            if (s->playfield[i][j] == '-') {
                found = 1;
                break;
            }
        if (found) break;
    }

    if (!found && valck) {
        printf("\n");
        print_sudoku(s);
        return 1;
    }

    get_possibilities(s, i, j, posnums);

    for (k = 0; k < strlen(posnums); k++) {
        s->playfield[i][j] = posnums[k];
        if (!solve_sudoku(s, depth + 1)) s->playfield[i][j] = '-';
    }

    return 0;
}

