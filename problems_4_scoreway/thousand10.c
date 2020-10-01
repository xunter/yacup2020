#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0
#define null 0

int main()
{ 
 srand(time(NULL));
 int n = 0;
 int m = 0;
 scanf("%d %d", &n, &m);

 FILE *f = fopen("input_thousand10.txt", "w");

 fprintf(f, "%d %d\n", n, m);

 for (int i = 0; i < n; i++) {
  int num = rand() % 10;
  fprintf(f, "%d", num);
  if (i != n - 1) {
   fprintf(f, " ");
  }
 }
 fprintf(f, "\n");

 for (int i = 0; i < m; i++) {
  int num = rand() % 10;
  fprintf(f, "%d", num);
  if (i != m - 1) {
   fprintf(f, " ");
  }
 }
 fprintf(f, "\n");

 fclose(f);

 return 0;
}


