#include <iostream>

int dp[11];

int main() {
  dp[1] = 1;
  dp[2] = 2;
  dp[3] = 4;

  for (int i = 4; i <= 10; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
  }

  int t;
  std::cin >> t;

  while (t--) {
    int n;
    std::cin >> n;
    std::cout << dp[n] << '\n';
  }
  

  return 0;
}