#include <iostream>
#include <vector>
#include <algorithm>

const int MAX = 987654321;

const int change[8][4] = {
  {0,1,2,3},
  {4,1,2,3},
  {4,1,2,3},
  {4,5,2,3},
  {4,5,2,3},
  {4,5,6,3},
  {4,5,6,3},
  {4,5,6,3},
};

struct apple
{
  int y, x, order;
  bool operator<(apple right) {
    return order < right.order;
  }
};

void go(std::vector<apple> apples, std::vector<std::vector<int>> &val)
{
  for (int i = 0; i + 1 < apples.size(); ++i) {
    int ny = apples[i + 1].y;
    int nx = apples[i + 1].x;

    int cy = apples[i].y;
    int cx = apples[i].x;

    int area;
    if (ny < cy) {
      if (nx > cx) area = 1;
      else if (nx < cx) area = 7;
      else area = 0;
    }
    else if (ny > cy) {
      if (nx > cx) area = 3;
      else if (nx < cx) area = 5;
      else area = 4;
    }
    else {
      if (nx > cx) area = 2;
      else if (nx < cx) area = 6;
    }

    if (i == 0) {
      int dir = 1;
      area = (area + 6 * dir) % 8;
      for (int j = 0; j < 4; ++j) {
        val[i + 1][j] = change[area][(j + (4 - dir)) % 4];
      }
    }
    else {
      for (int dir = 0; dir < 4; ++dir) {
        area = (area + 6 * dir) % 8;
        for (int j = 0; j < 4; ++j) {
          val[i + 1][j] = std::min(val[i + 1][j], change[area][(j + (4 - dir)) % 4]);
        }
      }
    }

  }
}

int solve()
{
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

  std::vector<std::vector<int>> val(apples.size() + 1, std::vector<int>(4, MAX));
  // val[i][j] = i번째 점이 j 방향이 되기 위해서 필요한 최소한의 우회전의 수

  go(apples, val);

  int ret = MAX;
  for (int i : val[apples.size() - 1]) {
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
    std::cout << '#' << cnt++ << ' ' << solve() << '\n';
    ;
  }
  return 0;
}