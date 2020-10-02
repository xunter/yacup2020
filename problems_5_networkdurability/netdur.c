#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

int n = 0;
int *nio;
int tempi;

int dist_to(int from, int to, int fromlast, int *tofromforbidden);
int inio(int i, int j);
int *getnio(int i, int j);

int main()
{
 if (!scanf("%d", &n)) return -1;
 //nio = (int *)calloc(n * (n - 1), sizeof(int));
 nio = (int *)calloc(n * n, sizeof(int));
 //nio = (int *)calloc(n * (int)ceil((n - 1) / 2.0), sizeof(int));

 for (int i = 0; i < n - 1; i++) {
  int from, to;
  if (!scanf("%d %d", &from, &to)) return -1;
  *getnio(from - 1, to - 1) = 1;
  //nio[inio(to - 1, from - 1)] = 1;
 }

 int maxdist = -1;
 int duri = 0;
 int durj = 0;
 for (int i = 0; i < n - 1; i++) {
  for (int j = i + 1; j < n; j++) {
   //printf("%d -> %d = %d\n", i + 1, j + 1, *getnio(i, j));
   int sumdistij = n;
   for (int k = 0; k < n; k++) {
    if (k == i || k == j) continue;
  //printf("dist %d->%d?\n", k + 1, i + 1);
    int disti = dist_to(k, i, -1, 0);
  //printf("dist %d->%d: %d\n", k + 1, i + 1, disti);

  //printf("dist %d->%d?\n", k + 1, j + 1);
    int distj = dist_to(k, j, -1, 0);
  //printf("dist %d->%d: %d\n", k + 1, j + 1, distj);

    int distijmin = disti < distj ? disti : distj;
    if (sumdistij == n || sumdistij < distijmin) sumdistij = distijmin;
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

int dist_to(int from, int to, int fromlast, int *tofromforbidden) {
 if (from == to) return 0;
 if (from > to) {
  tempi = from;
  from = to;
  to = tempi;
 }
 int dist = n;
 if (*getnio(from, to) > 0) {
  //printf("dist %d->%d: %d (known)\n", from + 1, to + 1, *getnio(from, to));
  //printf("dist %d->%d: %d (known)\n", from + 1, to + 1, *getnio(from, to));
  dist = *getnio(from, to);
 } else {
  int mindist = n - 1;
  for (int i = 0; i < n; i++) {
   if (i == fromlast || i == from || i == to || fromlast != -1 && tofromforbidden[i]) continue;
   if (*getnio(from, i) != 1) continue;
   if (fromlast == -1) {
    tofromforbidden = (int *)calloc(n, sizeof(int));
   }
   tofromforbidden[from] = 1;
   int disti = dist_to(i, to, fromlast == -1 ? from : fromlast, tofromforbidden);
   if (disti < mindist) mindist = disti;
   if (disti == 1) break;
  }
  dist = 1 + mindist;
  if (fromlast == -1) *getnio(from, to) = dist;
  //nio[inio(to, from)] = dist;
  //printf("dist %d->%d: %d\n", from + 1, to + 1, dist);
 }
 if (fromlast == -1 && tofromforbidden != 0) {
  free(tofromforbidden);
 }
 return dist;
}

int *getnio(int i, int j) {
 if (i > j) {
  tempi = i;
  i = j;
  j = tempi;
 }
 //int in = i * n + j;
 /*
 if (i >= (int)ceil((n - 1) / 2.0)) {
  int isub = n % 2 == 0 ? 1 : 2;
  in = i * (n - isub - i) + (n - 1 - j);
 }
 printf("[%d][%d]=%d = %d ceil: %d\n", i, j, in, nio[in], (int)ceil((n - 1) / 2.0));
*/
 return nio + i * n + j;
}

int inio(int i, int j) {
 if (i > j) {
  tempi = i;
  i = j;
  j = tempi;
 }
 int in = i * n + j;
 /*
 if (i >= (int)ceil((n - 1) / 2.0)) {
  int isub = n % 2 == 0 ? 1 : 2;
  in = i * (n - isub - i) + (n - 1 - j);
 }
 printf("[%d][%d]=%d = %d ceil: %d\n", i, j, in, nio[in], (int)ceil((n - 1) / 2.0));
*/
 return in;
}