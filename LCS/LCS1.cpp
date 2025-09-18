#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int map[1001][1001];

int main() {
  string str1, str2;
  cin >> str1 >> str2;

  int s1 = str1.size();
  int s2 = str2.size();

  for (int i = 1; i <= s2; ++i) {
    for (int j = 1; j <= s1; ++j) {
      if (str1[j - 1] == str2[i - 1]) {
        map[i][j] = 1 + map[i - 1][j - 1];
      }
      else {
        map[i][j] = max(map[i - 1][j], map[i][j - 1]);
      }
    }
  }

  // for (int i = 0; i <= s2; ++i) {
  //   for (int j = 0; j <= s1; ++j) {
  //     cout << map[i][j] << ' ';
  //   }
  //   cout << '\n';
  // }

  cout << map[s2][s1] << '\n';
  return 0;
}