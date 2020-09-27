#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std; 

vector<string> split(const string& str, const string& delim);


vector<string> get_substrings(string &s, int min = 2);
vector<string> filter_palindromes(vector<string> &strs);
bool is_palindrome(string &s);
bool is_palindrome_inplace(string &s, int start, int end);
bool is_smaller(string &pal1, string &s, int start, int end);
vector<string> get_palindrome_substrings(string &s, int min);
int calc_lexicographical_order(string &s);

int main()
{
 string str_input;
 getline(cin, str_input);

// vector<string> substrs = get_palindrome_substrings(str_input, 2);
 vector<string> substrs;
 vector<string> palindromes;
 substrs.insert(substrs.begin(), str_input);
// vector<string> palindromes = filter_palindromes(substrs);
 
 string min_palindrome = "";
 for (int i = 0; i < str_input.length() - 2; i++) {
  for (int j = i + 2; j < str_input.length() + 1; j++) {
   int len = j - i;
   if (is_palindrome_inplace(str_input, i, j - 1)) {
    //cout << str_input.substr(i, len) << endl;
    if (min_palindrome.length() == 0 || is_smaller(min_palindrome, str_input, i, j - 1)) {
     string str_substr = str_input.substr(i, len);
     min_palindrome = str_substr;
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

 if (palindromes.size() == 0) {
  cout << -1;
  return 0;
 }
 
 string &s_min = palindromes[0];
 int lg_order = 0;
 for (int i = 1; i < palindromes.size(); i++) {
  string s_palindrome = palindromes[i];
  int lg_cur = calc_lexicographical_order(s_palindrome);
  if (lg_order == 0 || lg_cur < lg_order) {
   lg_order = lg_cur;
   s_min = s_palindrome;
  }
 }
 cout << s_min;

 return 0;
}

bool is_smaller(string &pal1, string &s, int start, int end) {
 int n = pal1.length();
 int m = end - start + 1;
 int min_nm = n < m ? n : m;
 if (m < n) {
  return true;
 }
 for (int i = 0; i < min_nm; i++) {
  if (pal1[i] != s[i + start]) {
   return pal1[i] < s[i + start];
  }
 }
 return n < m;
}

int calc_lexicographical_order(string &s) {
 int sum = 0;
 for (int i = 0; i < s.length(); i++) {
  sum += s[i];
 }
 return sum;
}

vector<string> get_palindrome_substrings(string &s, int min) {
 vector<string> substrs;
 int curlen = s.length(); 
 while (curlen-- > min) {
  int count_substrs = s.length() - curlen + 1; 
  for (int i = 0; i < count_substrs; i++) {
   string substr = s.substr(i, curlen);
   if (is_palindrome(substr)) substrs.push_back(substr);
  }
 }
 return substrs;
}

vector<string> filter_palindromes(vector<string> &strs) {
 vector<string> filtered;
 for (int i = 0; i < strs.size(); i++) {
  string &s = strs[i];
  if (is_palindrome(s)) {
   filtered.push_back(s);
  }
 }
 return filtered;
}

bool is_palindrome(string &s) {
 string s_reverse(s);
 std::reverse(s_reverse.begin(), s_reverse.end());
 return s == s_reverse;
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

vector<string> get_substrings(string &s, int min) {
 vector<string> substrs;
 int curlen = s.length(); 
 while (curlen-- > min) {
  int count_substrs = s.length() - curlen + 1; 
  for (int i = 0; i < count_substrs; i++) {
   string substr = s.substr(i, curlen);
   substrs.push_back(substr);
  }
 }
 return substrs;
}



vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
} //https://stackoverflow.com/a/37454181/1487713
