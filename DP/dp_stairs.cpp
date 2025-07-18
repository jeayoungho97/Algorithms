#include <iostream>
#include <vector>

std::vector<int> dp;

int main() {
  int n;
  std::cin >> n;
  dp.resize(n + 1, 0);
  
  int prev_val = 0;
  for (int i = 1; i <= n; ++i) {
    int cur_val;
    std::cin >> cur_val;
    
    // prev2 = val[n] + dp[n - 2]
    // prev3 = val[n] + val[n - 1] + dp[n - 3]
    int prev2 = (i > 2) ? dp[i - 2] : 0;
    int prev3 = (i > 3) ? dp[i - 3] : 0;
    
    prev2 += cur_val;
    prev3 += cur_val + prev_val;

    dp[i] = std::max(prev2, prev3);
    prev_val = cur_val;
  }

  std::cout << dp[n] << '\n';

  return 0;
}

// BOJ 2579