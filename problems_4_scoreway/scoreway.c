#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define true 1
#define false 0
#define null 0

int main()
{ 
 int n = 0;
 int m = 0;
 scanf("%d %d", &n, &m);

 if (n == 0 || m == 0) {
  printf("0\n");
  return 0;
 }

 int n_nums[10000];
 int m_nums[10000];

 for (int i = 0; i < n; i++) scanf("%d", &n_nums[i]);
 for (int i = 0; i < m; i++) scanf("%d", &m_nums[i]);

 int maxn = 0;
 int maxni = 0;
 int maxm = 0;
 int maxmj = 0; 
 for (int j = 0; j < m; j++) {
  if (maxm < m_nums[j]) {
   maxm = m_nums[j];
   maxmj = j;
  }
 }
 for (int i = 0; i < n; i++) {
  int nnum = n_nums[i];
  if (maxn < nnum) {
   maxn = nnum;
   maxni = i;
  }
 }

 int ni = 0;
 int mj = 0;
 unsigned long sumn = 0;
 unsigned long summ = 0;
 for (; ni < maxni; ni++) {
  sumn += n_nums[ni];
  summ += m_nums[0];
 }
 for (mj = 0; mj < m; mj++) {
  sumn += n_nums[maxni];
  summ += m_nums[mj];

  int gapi = -1;
  if (mj < m - 1 && m_nums[mj] == maxm) {
   for (int i = n - 1; i > ni; i--) {
    if (n_nums[i] == maxn) {
     gapi = i;
     break;
    }
   }
   if (gapi != -1) {
    for (ni++; ni <= gapi; ni++) {
     sumn += n_nums[ni];
     summ += m_nums[mj];
    }
    ni--;
   }
  }
 }
 for (ni++ + mj--; ni < n; ni++) {
  sumn += n_nums[ni];
  summ += m_nums[mj];
 }

 if (summ >= pow(10, 9)) {
  int kops = summ % 1000000000;
  int cels = summ - kops;
  cels = cels / (int)pow(10, 9);
  sumn += cels;
  summ = kops;
 }
 if (sumn > 0) {
  printf("%ld", sumn);
  int zcount = 9;
  for (int i = zcount; i >= 0; i--) {
   if (summ <= (pow(10, i - 1) - 1)) printf("0");
  }
 }
 if (summ > 0 || sumn == 0) {
  printf("%ld", summ);
 }
 printf("\n");
 return 0;
}


