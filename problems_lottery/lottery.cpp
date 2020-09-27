#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std; 

vector<string> split(const string& str, const string& delim);

int main()
{
 int luckyNums[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
 string sLuckyNums, sTiraz, sTicketNums;
 vector<int*> ticketNumsArr;

 getline(cin, sLuckyNums);
 vector<string> sLuckyNumsTokens = split(sLuckyNums, " ");
 for (int i = 0; i < 10; i++) {
  luckyNums[i] = atoi(sLuckyNumsTokens[i].c_str());
 }

 getline(cin, sTiraz);
 int tirazNum = atoi(sTiraz.c_str());

 int n = 0;
 while (n++ < tirazNum) {
  getline(cin, sTicketNums);
  vector<string> tokenNumsArr = split(sTicketNums, " ");
  int *ticketNums = new int[6];
  for (int i = 0; i < 6; i++) {
   ticketNums[i] = atoi(tokenNumsArr[i].c_str());
  }
  ticketNumsArr.push_back(ticketNums);
 }

 vector<bool> ticketLuckyStatusArr;
 for (int i = 0; i < ticketNumsArr.size(); i++) {
  ticketLuckyStatusArr.push_back(false);
  int *ticketNums = ticketNumsArr[i];
  int luckyCounter = 0;
  for (int j = 0; j < 6; j++) {
   bool luckyFound = false;
   for (int k = 0; k < 10; k++) {
     if (ticketNums[j] == luckyNums[k]) {
       luckyCounter++;
     }
     if (luckyCounter == 3) {
       luckyFound = true;
       ticketLuckyStatusArr[i] = true;
       break;
     }
   }
   if (luckyFound) {
    break;
   }
  }
  cout << (ticketLuckyStatusArr[i] ? "Lucky" : "Unlucky") << endl;
  delete ticketNums;
 }
 return 0;
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
