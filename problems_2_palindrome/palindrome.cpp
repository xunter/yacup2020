#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std; 

bool is_palindrome_inplace(const char *s, int start, int end);
bool is_smaller(const char *pal1, int pali, int pallen, const char *s, int start, int end);

int main()
{
 int min_i = -1;
 int min_len = -1;

 char str_input[200000];
 cin.getline(str_input, 200000);

 int str_len = cin.gcount() - 1;

 for (int k = 2; k <= str_len; k++) {
  if (k > 3) break;
  for (int i = 0; i < str_len - (k - 1); i++) {
    int j = i + k - 1;
    int len = j - i + 1;
    if (is_palindrome_inplace(str_input, i, j)) {
     if (min_i == -1 || !is_smaller(str_input, min_i, min_len, str_input, i, j)) {
      min_i = i;
      min_len = len;
     }
    }
  }
  if (min_i != -1) {
   break;
  }
 }
 
 if (min_i == -1) {
  cout << -1 << endl;
  return 0;
 }
 
 for (int i = 0; i < min_len; i++) {
  cout << str_input[i + min_i];
 }
 cout << endl;
 return 0;
}

bool is_smaller(const char *pal1, int pali, int pallen, const char *s, int start, int end) {
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

bool is_palindrome_inplace(const char *s, int start, int end) {
 int len = end - start + 1;
 int to = floor((float)(len / 2.0));
 for (int i = 0; i < to; i++) {
  if (s[i + start] != s[end - i]) {
   return false;
  }
 }
 return true;
}

