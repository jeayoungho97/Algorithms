#include <iostream>
#include <cstring>

long long dp[1004];

int go(int n) {
  if (n <= 1) return 1;

  long long &ret = dp[n];
  if (ret != -1) return ret;
  ret = go(n - 1) + go(n - 2);
  return ret % 10'007;
}

int main() {
  std::memset(dp, -1, sizeof(dp));

  int n;
  std::cin >> n;
  std::cout << go(n) << '\n';
  return 0;
}