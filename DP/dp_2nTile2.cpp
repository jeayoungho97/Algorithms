#include <iostream>
#include <cstring>

int dp[1004];

int go(int n) {
  if (n <= 1) return 1;

  int &ret = dp[n];
  if (ret != -1) return ret;
  ret = go(n - 1) % 10007 + (2 * go(n - 2)) % 10007;
  return ret % 10'007;
}

int main() {
  std::memset(dp, -1, sizeof(dp));

  int n;
  std::cin >> n;
  std::cout << go(n) << '\n';
  return 0;
}

//BOJ 11727