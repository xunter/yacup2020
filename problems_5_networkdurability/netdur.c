#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

int n = 0;
int *nio;

int dist_to(int from, int to);
int inio(int i, int j);

int main()
{
 scanf("%d", &n);
 nio = (int *)calloc(n * n, sizeof(int));

 for (int i = 0; i < n - 1; i++) {
  int from, to;
  scanf("%d %d", &from, &to);
  nio[inio(from - 1, to - 1)] = 1;
  nio[inio(to - 1, from - 1)] = 1;
 }

 int maxdist = -1;
 int duri = 0;
 int durj = 0;
 for (int i = 0; i < n - 1; i++) {
  for (int j = i + 1; j < n; j++) {
   int sumdistij = 0;
   for (int k = 0; k < n; k++) {
    if (k == i || k == j) continue;
  //printf("dist %d->%d?\n", k + 1, i + 1);
    int disti = dist_to(k, i);
  //printf("dist %d->%d: %d\n", k + 1, i + 1, disti);

  //printf("dist %d->%d?\n", k + 1, j + 1);
    int distj = dist_to(k, j);
  //printf("dist %d->%d: %d\n", k + 1, j + 1, distj);
    sumdistij += disti + distj;
   }
   if (maxdist == -1 || sumdistij < maxdist) {
    maxdist = sumdistij;
    duri = i;
    durj = j;
   }
  }
 }

 printf("%d %d\n", (duri + 1), (durj + 1));

 free(nio);
 return 0;
}

int dist_to(int from, int to) {
 if (from == to) return 0;
 int distknown = nio[inio(from, to)];
 if (distknown > 0 && distknown < n) {
  //printf("dist %d->%d: %d (known)\n", from + 1, to + 1, distknown);
  return nio[inio(from, to)];
 } else {
  int mindist = n - 1;
  for (int i = 0; i < n; i++) {
   if (i == from || i == to) continue;
   if (nio[inio(from, i)] != 1) continue;
   int disti = dist_to(i, to);
   if (disti < mindist) mindist = disti;
   if (disti == 1) break;
  }
  int dist = 1 + mindist;
  nio[inio(from, to)] = dist;
  nio[inio(to, from)] = dist;
  return dist;
 }
}

int inio(int i, int j) {
 int iflat = i * n + j;
 return iflat;
}