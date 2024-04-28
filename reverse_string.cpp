#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string big_to_little(string s, int len) {
  string little;
  for (int i=len-1;i>=0;i-=2) {
    little +=s[i-1];
    little +=s[i];
  }
  return little;
}

int main() {
  string hash;
  cin>>hash;
  cout<<big_to_little(hash,64)<<endl;
  cout<<hash.size()<<endl;
  return 0;
}