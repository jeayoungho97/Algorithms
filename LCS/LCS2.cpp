#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

int dp[1001][1001];
string str1, str2;

int main() {
  cin >> str1 >> str2;

  int size1 = str1.size();
  int size2 = str2.size();

  for (int row = 1; row <= size2; ++row) {
    for (int col = 1; col <= size1; ++col) {
      if (str1[col - 1] == str2[row - 1]) {
        dp[row][col] = dp[row - 1][col - 1] + 1;
      }
      else {
        dp[row][col] = max(dp[row - 1][col], dp[row][col - 1]);
      }
    }
  }

  int y = size2, x = size1;
  stack<char> ans;

  while (true) {
    int now = dp[y][x];
    if (now == 0) break;
    if (dp[y - 1][x] == now - 1 && dp[y][x - 1] == now - 1) {
      ans.push(str1[x - 1]);
      y--; 
      x--;
    }
    else {
      if (dp[y - 1][x] > dp[y][x - 1]) y--;
      else x--;
    }
  }

  cout << dp[size2][size1] << '\n';

  if (dp[size2][size1] == 0) return 0;

  while (!ans.empty()) {
    cout << ans.top(); ans.pop();
  }
  cout << '\n';

  return 0;
}