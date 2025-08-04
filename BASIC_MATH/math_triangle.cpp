#include <iostream>
#include <vector>

int main() {
  std::vector<long long> dp = {1, 1, 1, 2, 2};
  
  int t;
  std::cin >> t;
  while (t--) {
    int temp;
    std::cin >> temp;


    while (dp.size() < temp) {
      int size = dp.size();
      dp.push_back(dp[size - 1] + dp[size - 5]);
    }

    std::cout << dp[temp - 1] << '\n';
  }

  return 0;
}

// BOJ 9461 