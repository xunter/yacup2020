#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

int is_palindrome_inplace(const char *s, int start, int end);
int is_smaller(const char *pal1, int pali, int pallen, const char *s, int start, int end);

int main()
{
 int min_i = -1;
 int min_len = -1;

 size_t str_max_len = 200000;
 char *str_input = (char *)malloc(str_max_len * sizeof(char));
 int str_len = getline(&str_input, &str_max_len, stdin);

 for (int k = 2; k <= str_len; k++) {
  if (k > 3) break;
  for (int i = 0; i < str_len - (k - 1); i++) {
   //for (int j = i + 1; j < str_input.length(); j++) {
    int j = i + k - 1;
    int len = j - i + 1;
    if (is_palindrome_inplace(str_input, i, j)) {
     if (min_i == -1 || !is_smaller(str_input, min_i, min_len, str_input, i, j)) {
      min_i = i;
      min_len = len;
     }
    }
   //}
  }
  if (min_i != -1) {
   break;
  }
 }
 
 if (min_i == -1) {
  printf("-1\n");
  free(str_input);
  return 0;
 }
 
 for (int i = 0; i < min_len; i++) {
  printf("%c", str_input[i + min_i]);
 }
 printf("\n");
 free(str_input);
 return 0;
}

int is_smaller(const char *pal1, int pali, int pallen, const char *s, int start, int end) {
 int n = pallen;
 int m = end - start + 1;
 int min_nm = n < m ? n : m;
 for (int i = 0; i < min_nm; i++) {
  if (pal1[pali + i] != s[i + start]) {
   return pal1[pali + i] < s[i + start];
  }
 }
 return n < m;
}

int is_palindrome_inplace(const char *s, int start, int end) {
 int len = end - start + 1;
 int to = (int)floor((double)(len / 2.0));
 for (int i = 0; i < to; i++) {
  if (s[i + start] != s[end - i]) {
   return false;
  }
 }
 return true;
}

