#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FAIL      1
#define WIN       2
#define CLOSED    -1
#define BOMB      -2


void fill_field(int **field, int n, int m, int k);
void print_field_full(int **field, int n, int m);
int all_checked(int **field, int n, int m);
void print_field(int **field, int n, int m);
int count_near_bombs(int **field, int x, int y, int n, int m);
int check_coord(int **field, int x, int y, int n, int m);

int main(int argc, char const *argv[])
{
   int n, m, k;
   int x, y, result;

   printf("MINESWEEPER GAME!\n");
   printf("Clear a field containing hidden 'bombs' without detonating any of them.\n"
          "If chosen coordinates contain a bomb, the player loses the game. \n"
          "If no bomb is revealed, a digit displayed \n"
          "indicates how many adjacent squares contain bombs.\n");
   printf("The player wins when all squares without bombs are opened.\n\n");

   if (argc != 4)
   {
      fprintf(stderr, "Usage: %s n m k, where (n,m) is a field size and k is a number of bombs\n", argv[0]);
      return -1;
   }

   n = atoi(argv[1]);
   m = atoi(argv[2]);
   k = atoi(argv[3]);

   if ((n < 0) || (m < 0))
   {
      printf("n and m must be positive numbers!\n");
      return -1;
   }

   if ((k < 0) || (k > n * m))
   {
      printf("Wrong number of bombs!\n");
      return -1;
   }

  // ALLOCATE MEMORY FOR A 2D ARRAY field WITH SIZE (n, m)
  int **field;
  field = (int**)malloc(n*sizeof(int*));
  for(int i = 0; i<n;i++){
     field[i] = (int*)malloc(m*sizeof(int));
  }


   fill_field(field, n, m, k);
   print_field(field, n, m);

   while (1)
   {
      printf("\nEnter coordinates: ");
      scanf("%d %d", &x, &y);
      if ((x < 0) || (y < 0) || (x >= n) || (y >= m))
      {
         printf("Wrong coordinates!");
         continue;
      }

      result = check_coord(field, x, y, n, m);

      if (result == FAIL)
      {
         print_field_full(field, n, m);
         printf("****************\n");
         printf("   YOU LOST!\n");
         printf("****************\n");
         break;
      }
      else if (result == WIN)
      {
         print_field_full(field, n, m);
         printf("****************\n");
         printf("   YOU WON!\n");
         printf("****************\n");
         break;
      }
      else
      {
         print_field(field, n, m);
      }
   }

   // FREE MEMORY ALLLOCATED FOR A 2D ARRAY field WITH SIZE (n, m)
   for (int i = 0;i<n;i++){
      free(field[i]);
   }
   free(field);
   return 0;
}

/* HELP FUNCTIONS */


/*
 * >=0 - opened location
 * -2 - bomb
 * -1 - closed location (not checked yet)
 */
void fill_field(int **field, int n, int m, int k)
{
   srand(time(0));

   //x = rand() % n; // random number between 0 and n-1

   int i, j, xb, yb, counter = 0;
   for (i = 0; i < n; ++i)
   {
      for (j = 0; j < m; ++j)
      {
         field[i][j] = CLOSED;
      }
   }

   // set bombs
   while (counter < k)
   {
      xb = rand() % n;
      yb = rand() % m;
      if (field[xb][yb] == BOMB)
      {
         continue;          // there is already a bomb
      }
      field[xb][yb] = BOMB; // new bomb
      counter++;
   }
}


void print_field_full(int **field, int n, int m)
{
   int i, j;

   printf("\t");
   for (j = 0; j < m; ++j)
   {
      printf("%d ", j);
   }
   printf("\n");

   for (i = 0; i < n; ++i)
   {
      printf("%d\t", i);
      for (j = 0; j < m; ++j)
      {
         if (field[i][j] == BOMB)
         {
            printf("%s ", "*");
         }
         else if (field[i][j] == CLOSED)
         {
            printf("%s ", ".");
         }
         else
         {
            printf("%d ", field[i][j]);
         }
      }
      printf("\n");
   }
}


void print_field(int **field, int n, int m)
{
   int i, j;

   printf("\t");
   for (j = 0; j < m; ++j)
   {
      printf("%d ", j);
   }
   printf("\n");

   for (i = 0; i < n; ++i)
   {
      printf("%d\t", i);
      for (j = 0; j < m; ++j)
      {
         if (field[i][j] >= 0)
         {
            printf("%d ", field[i][j]);
         }
         else
         {
            printf("%s ", ".");
         }
      }
      printf("\n");
   }
}


int all_checked(int **field, int n, int m)
{
   int i, j;

   for (i = 0; i < n; ++i)
   {
      for (j = 0; j < m; ++j)
      {
         if (field[i][j] == CLOSED)
         {
            return 0;
         }
      }
   }

   return 1;
}


int count_near_bombs(int **field, int x, int y, int n, int m)
{
   int counter = 0;

   if ((x > 0) && (y > 0) && (field[x - 1][y - 1] == BOMB))
   {
      counter++;
   }
   if ((x > 0) && (field[x - 1][y] == BOMB))
   {
      counter++;
   }
   if ((x > 0) && (y < m - 1) && (field[x - 1][y + 1] == BOMB))
   {
      counter++;
   }
   if ((y < m - 1) && (field[x][y + 1] == BOMB))
   {
      counter++;
   }
   if ((x < n - 1) && (y < m - 1) && (field[x + 1][y + 1] == BOMB))
   {
      counter++;
   }
   if ((x < n - 1) && (field[x + 1][y] == BOMB))
   {
      counter++;
   }
   if ((x < n - 1) && (y > 0) && (field[x + 1][y - 1] == BOMB))
   {
      counter++;
   }
   if ((y > 0) && (field[x][y - 1] == BOMB))
   {
      counter++;
   }

   return counter;
}


int check_coord(int **field, int x, int y, int n, int m)
{
   if (field[x][y] == BOMB)
   {
      return FAIL;                  // it is a bomb
   }

   int numbombs = count_near_bombs(field, x, y, n, m);
   field[x][y] = numbombs;

   if (all_checked(field, n, m) == 1)
   {
      return WIN;                    // YOU WIN!
   }
   return 0;
}
