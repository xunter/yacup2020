#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std; 

bool is_palindrome_inplace(string &s, int start, int end);
bool is_smaller(string &pal1, string &s, int start, int end);

int main()
{
 string str_input;
 getline(cin, str_input);

 if (str_input.length() < 2 || str_input.length() > 200000) {
  cout << -1;
  return -1;
 }

 string min_palindrome = "";
 for (int i = 0; i < str_input.length() - 1; i++) {
  for (int j = i + 1; j < str_input.length(); j++) {
   int len = j - i + 1;
   if (is_palindrome_inplace(str_input, i, j)) {
    //cout << str_input.substr(i, len) << endl;
    if (min_palindrome.length() == 0 || is_smaller(min_palindrome, str_input, i, j)) {
     min_palindrome = str_input.substr(i, len);
     //cout << min_palindrome << endl;
    }
    break;
   }
  }
 } 

 
 if (min_palindrome.length() == 0) {
  cout << -1;
  return 0;
 }

 cout << min_palindrome;
 return 0;
}

bool is_smaller(string &pal1, string &s, int start, int end) {
 int n = pal1.length();
 int m = end - start + 1;
 int min_nm = n < m ? n : m;
 for (int i = 0; i < min_nm; i++) {
  if (pal1[i] != s[i + start]) {
   return pal1[i] < s[i + start];
  }
 }
 return n < m;
}

bool is_palindrome_inplace(string &s, int start, int end) {
 int len = end - start + 1;
 float tof = (len / 2.0);
 int to = floor(tof);
 for (int i = 0; i < to; i++) {
  if (s[i + start] != s[end - i]) {
   return false;
  }
 }
 return true;
}

