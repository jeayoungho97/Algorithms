#include <iostream>
#include <vector>
#include <cstring>

int n, ans;
int dp[1 << 10][20000];
std::vector<int> arr;

void init() {
  ans = 0;
  arr.clear();
  std::memset(dp, -1, sizeof(dp));
}

int go(int bitmask, int diff) {
  if (diff < 0) return 0;
  if (bitmask == (1 << n) - 1) return 1;

  int &ret = dp[bitmask][diff + 10000];
  if (ret != -1) return ret;

  ret = 0;
  for (int i = 0; i < n; ++i) {
    if (bitmask & (1 << i)) continue;
    ret += go(bitmask | (1 << i), diff + arr[i]);
    ret += go(bitmask | (1 << i), diff - arr[i]);
  }
  return ret;
}

int main() {
  int t;
  std::cin >> t;

  for (int tc = 1; tc <= t; ++tc) {
    init();

    std::cin >> n;
    
    for (int i = 0; i < n; ++i) {
      int temp;
      std::cin >> temp;
      arr.push_back(temp);
    }

    ans = go(0, 0);
    std::cout << '#' << tc << ' ' << ans << '\n';
  }



  return 0;
}