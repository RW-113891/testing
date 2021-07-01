#include<stdio.h>
#include<stdlib.h>
#include"inputmatrix.h"

#define MAX_VAL 99999.9

int simplex_core(double *Xvector, int *X_sub, double *minimize, int *flag);

int main(void)
{
  int i;
  int j;
/*subscript of matrix.*/

  double Xvector[COLUMN+SLACK];
  int X_sub[SLACK];
  /* basic solution vector */

  int flag;
  /* end flag */

  double minimize= EPS;
  /* value of objective function */

  /* input initial Xvector */
  for(j=0;j<=COLUMN-1;j++)
  {
      Xvector[j] = EPS;
  }
  for(j=COLUMN;j<=COLUMN+SLACK-1;j++)
  {
      Xvector[j] = Bvector[j-COLUMN];
      X_sub[j-COLUMN] = j;
  }

  flag=0;
  i=0;
  while(flag == 0)
  {
      i++;
      simplex_core(Xvector,X_sub,&minimize,&flag);
      if(i==100) break; /* infinite roop break */
  }

  for(j=0;j<=COLUMN-1;j++)
  {
      printf("x_%d = %f\n",j,Xvector[j]);
  }
  printf("z = %f\n",-minimize);
  /* return value */

  return 0;
}

int simplex_core(double *Xvector, int *X_sub, double *minimize, int *flag)
{
    int i;
    int j;
    /*subscript of matrix.*/

    double mini_n;
    int mini_i;
    int mini_j;
    double mini_m;
    /* minimize subscript number */

    double pibot_v;
    double pibot_c;
    /* pibot term */

    int flag_u;
    /*unbound flag*/

     for(j=0;j<=COLUMN+SLACK-1;j++)
     {
         if(Amatrix[ROW][j] > -EPS)
         {
             *flag = 1;
         } else {
             *flag = 0;
             break;
         }
     }

    if(*flag == 1)
    {
        printf("simplex method is ended.\n");
        return 0;
    }
/* all cost coefficients is >=0, end of function */
    mini_n = MAX_VAL;
    mini_j = COLUMN+SLACK;
    for(j=0;j<=COLUMN+SLACK-1;j++)
    {
        if(Amatrix[ROW][j] < mini_n)
        {
            mini_n = Amatrix[ROW][j];
            mini_j = j;
        }
    }

    /* If coefficident matrix <= 0, solution is unbound...*/
    flag_u = 0;
    for(i=0;i<=ROW-1;i++)
    {
       if(Amatrix[i][mini_j] < EPS)
       {
          flag_u = 1;
       } else {
          flag_u = 0;
          break;
       }
    }

    if(flag_u ==1 )
    {
       printf("This solution is unbound...");
       return 1;
    }

    /* Step of pibot subscription */
    mini_m = MAX_VAL;
    mini_i = ROW+1;
    for(i=0;i<=ROW-1;i++)
    {
        if(Amatrix[i][mini_j] > -EPS)
        {
            if(Bvector[i]/Amatrix[i][mini_j] < mini_m)
            {
                mini_m = Bvector[i] / Amatrix[i][mini_j];
                mini_i = i;
            }
        }
    }

    /* pibot operation*/
    /* step 1 */
    pibot_v = Amatrix[mini_i][mini_j];
    for(j=0;j<=COLUMN+SLACK-1;j++)
    {
        Amatrix[mini_i][j] = Amatrix[mini_i][j] / pibot_v;
    }
    Bvector[mini_i] = Bvector[mini_i] / pibot_v;

    /* step 2 */
    for(i=0;i<=ROW;i++)
    {
        if(mini_i != i)
        {
            pibot_c = Amatrix[i][mini_j] / Amatrix[mini_i][mini_j];
            for(j=0;j<=COLUMN+SLACK-1;j++)
            {
                Amatrix[i][j] = Amatrix[i][j] - pibot_c * Amatrix[mini_i][j];
            }
            if(i<=ROW-1)
            {
                Bvector[i] -= Bvector[mini_i] * pibot_c;
            }
        }
    }
    *minimize -= Bvector[mini_i] * pibot_c;

    /* step 3 */
    X_sub[mini_i] = mini_j;
    for(j=0;j<=COLUMN+SLACK-1;j++)
    {
        for(i=0;i<=SLACK-1;i++)
        {
            if(X_sub[i] == j)
            {
                Xvector[j] = Bvector[i];
                break;
            } else {
                Xvector[j] = EPS;
            }
        }
    }



    /* debug
    for(i=0;i<=ROW;i++)
    {
        for(j=0;j<=COLUMN+SLACK-1;j++)
        {
            printf("A[%d][%d]=%f\n",i,j,Amatrix[i][j]);
        }
        if(i<=ROW-1)
        {
            printf("B[%d]=%f\n",i,Bvector[i]);
        }
    }
    for(i=0;i<=ROW-1;i++)
    {
            printf("X_sub[%d]=%d\n",i,X_sub[i]);
    }
    printf("--------\n");
    */
}

