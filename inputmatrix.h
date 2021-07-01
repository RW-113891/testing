/* simplex method. definition of coefficent matrix */

#define COLUMN 4
#define ROW 3
#define SLACK 3
#define EPS 0.00000001
/* COLUMN: a number of variable.
ROW: a number of constrains.
SLACK: a number of slack variable.
EPS: accuracy. */

double Amatrix[ROW+1][COLUMN+SLACK]={
    {2.0, 6.0, 8.0, 9.0, 1.0, EPS, EPS},
    {8.0, 6.0, 4.0, 2.0, EPS, 1.0, EPS},
    {3.0, 1.0, 3.0, 1.0, EPS, EPS, 1.0},
    {-2.0, -5.0, -1.0, -6.0, EPS, EPS, EPS}
};

double Bvector[ROW]={27.0, 45.0, 15.0};

