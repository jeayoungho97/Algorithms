#include <iostream>
#include <vector>
#include <algorithm>

const int MAX = 987654321;

int main() {
  int n;
  std::cin >> n;
  std::vector<int> dp(n + 1, MAX);
  dp[0] = 0;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; i - j * j >= 0; ++j) {
      dp[i] = std::min(dp[i], 1 + dp[i - j * j]);
    }
  }

  std::cout << dp[n] << '\n';

  return 0;
}