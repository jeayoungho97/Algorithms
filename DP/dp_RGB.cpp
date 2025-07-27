#include <iostream>
#include <algorithm>

const int MAX = 987654321;
int cost[1000][3], dp[1000][3];

int main() {
  int n;
  std::cin >> n;
  std::fill(&dp[0][0], &dp[0][0] + 1000 * 3, MAX);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 3; ++j) {
      std::cin >> cost[i][j];
      if (i == 0) dp[i][j] = cost[i][j];
      else if (i > 0) {
        for (int k = 0; k < 3; ++k) {
          if (k == j) continue;
          dp[i][j] = std::min(dp[i][j], cost[i][j] + dp[i - 1][k]);
        }
      }
    }
  }

  // //  Debugging : 
  // for (int i = 0; i < n; ++i) {
  //   for (int j = 0; j < 3; ++j) {
  //     std::cout << dp[i][j] << ' ';
  //   }
  //   std::cout << '\n';
  // }

  int result = *(std::min_element(dp[n - 1], dp[n - 1] + 3));
  std::cout << result << '\n';
  return 0;
}

// BOJ 1149