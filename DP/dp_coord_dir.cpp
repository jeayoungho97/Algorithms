#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 1e9;

const int num[4][4] = {
  {4,1,2,3}, {4,5,2,3}, {4,5,6,3}, {4,5,6,3}
};

int dp[11][4];

struct apple
{
  int y, x, order;

  bool operator<(const apple& right) const
  {
    return order < right.order;
  }
};

int solve()
{
  std::fill(&dp[0][0], &dp[0][0] + 11 * 4, INF);
  int n;
  std::cin >> n;

  std::vector<apple> apples;
  apples.push_back({0, 0, 0});

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      int temp;
      std::cin >> temp;

      if (temp != 0)
      {
        apples.push_back({i, j, temp});
      }
    }
  }

  std::sort(apples.begin(), apples.end());

  for (int i = 0; i < apples.size() - 1; ++i)
  {
    int quarter;
    int y = apples[i].y;
    int x = apples[i].x;
    int ny = apples[i + 1].y;
    int nx = apples[i + 1].x;

    if (ny < y) {
      if (nx > x) quarter = 0;
      else quarter = 3;
    }
    else {
      if (nx > x) quarter = 1;
      else quarter = 2;
    }

    if (i == 0) {
      int myDir = 1;
      for (int tarDir = 0; tarDir < 4; ++tarDir) {
        dp[i + 1][tarDir] = num[(quarter + 4 - myDir) % 4][(tarDir + 4 - myDir) % 4];
      }
    }
    else {
      for (int myDir = 0; myDir < 4; ++myDir) {
        for (int tarDir = 0; tarDir < 4; ++tarDir) {
          int &ret = dp[i + 1][tarDir];
          ret = std::min(ret, dp[i][myDir] + num[(quarter + 4 - myDir) % 4][(tarDir + 4 - myDir) % 4]);
        }
      }
    }
  }

  int ret = INF;
  for (int i : dp[apples.size() - 1]) {
    ret = std::min(ret, i);
  }

  return ret;
}

int main()
{
  int t;
  std::cin >> t;
  int cnt = 1;
  while (t--)
  {
    int result = solve();
    std::cout << '#' << cnt++ << ' ' << result << '\n';
  }

  return 0;
}