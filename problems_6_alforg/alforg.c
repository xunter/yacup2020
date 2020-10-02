#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLORBLACK -1
#define COLORWHITE 0

int *cells = 0;
int *pathcoords = 0;
int n, m, k;

int *getcell(int x, int y);

int main()
{
 if (scanf("%d %d %d", &n, &m, &k));

 if (k == 0) {
  printf("0\n");
  return 0;
 }

 cells = (int *)calloc(n * m, sizeof(int));

 for (int i = 0; i < k; i++) {
  int x, y;
  if (scanf("%d %d", &x, &y));
  *getcell(x, y) = COLORBLACK;
 }

 int rounds = 0;

 int maxpathsteps = (n + 1) + (m + 1) - 1;
 pathcoords = (int *)calloc(maxpathsteps * 2, sizeof(int));
 int nextround = 1;

 while (nextround) {
  int pathsteps = 0;
  int coordi = 0;
  int coordj = 0;
  //printf("0pathcoord[%d][%d]=(%d,%d)\n", pathi, pathj, coordi, coordj);
  //printf("(%d,%d)", coordi, coordj);
  //*(pathcoords) = 0;
  //*(pathcoords + maxpathsteps) = 0;
  pathsteps++;
  while (coordi < n || coordj < m) {
   //printf("maxpathstep: %d\n", pathsteps);
   for (int c = m; c > coordj; c--) {
    if (*getcell(coordi, c - 1) == COLORBLACK) {
     //printf("blackcell = (%d,%d)\n", coordi, c - 1);
     for (; coordj < c; coordj++) {
      *(pathcoords + pathsteps) = coordi;
      *(pathcoords + maxpathsteps + pathsteps) = coordj + 1;
      pathsteps++;

      //printf("ypathcoord[%d][%d]=(%d,%d)\n", pathi, pathj, coordi, coordj+1);
      //printf(" -> (%d,%d)", coordi, coordj+1);

     }
    }
   }

   if (coordi < n) {
    *(pathcoords + pathsteps) = ++coordi;
    *(pathcoords + maxpathsteps + pathsteps) = coordj;
    pathsteps++;

    //printf("pathsteps[%d][%d]:%d (%d,%d)\n", 0, 0, 0, pathcoords[0], pathcoords[maxpathsteps]);
    //printf("xpathcoord[%d][%d]=(%d,%d)\n", pathi, pathj, coordi, coordj);
    //printf(" -> (%d,%d)", coordi, coordj);
   }

   if (coordi == n && coordj < m) {
    *(pathcoords + pathsteps) = coordi;
    *(pathcoords + maxpathsteps + pathsteps) = ++coordj;
    pathsteps++;
    //printf(" -> (%d,%d)", coordi, coordj);
   }

  }
  //printf("\n");
  nextround = 0;

  //printf("pathsteps[%d][%d]:%d (%d,%d)\n", 0, 0, 0, pathcoords[0], pathcoords[maxpathsteps]);
  int pathcoordiprev = -1;
  for (int i = 0; i < pathsteps; i++) {
   
   int pathcoordi = *(pathcoords + i);
   int pathcoordj = *(pathcoords + i + maxpathsteps);
   //printf("pathsteps[%d][%d]:%d (%d,%d)\n", i, maxpathsteps + i, i+1, pathcoordi, pathcoordj);
   
   //printf("pathstep: %d coords: (%d,%d) cellunder: (%d,%d)\n", i+1, coordi, coordj, cellunderx, cellundery);

   if (pathcoordiprev != -1) {
    int pathcoordidiff = pathcoordi - pathcoordiprev;
    if (pathcoordidiff > 0) {
     int cellunderx = pathcoordiprev;
     int cellunderyfrom = pathcoordj - 1;
     for (int cellundery = cellunderyfrom; cellundery >= 0; cellundery--) {
      //printf("cell [%d][%d]: %d\n", cellunderx, cellundery, *getcell(cellunderx, cellundery));
      int colorwas = *getcell(cellunderx, cellundery);
      int colornew = colorwas == COLORWHITE ? COLORBLACK : COLORWHITE;
      *getcell(cellunderx, cellundery) = colornew;
       if (colornew == COLORBLACK) nextround = 1;
     }
    }
   }
   pathcoordiprev = pathcoordi;
  }
  rounds++;
  //printf("nextround: %d\n", nextround);
  //break;
 }

 printf("%d\n", rounds);
 free(pathcoords);
 free(cells);
 return 0;
}

int *getcell(int x, int y) {
 return cells + n * x + y;
}