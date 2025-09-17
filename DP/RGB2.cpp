#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 1e9;
int N, ans = MAX;
int cost[1001][3]; // 집은 1번부터 시작
int dp[1001][3][3] = {0};

int go(int now, int fColor, int nowColor) {
  if (now > N) return 0;

  int &ret = dp[now][fColor][nowColor];
  if (ret != 0) return ret;

  ret = MAX;
  for (int color = 0; color < 3; ++color) {
    if (color == nowColor) continue;
    if (now == N - 1 && color == fColor) continue;
    int next = go(now + 1, fColor, color);
    if (next > MAX) continue;
    ret = min(ret, cost[now][nowColor] + next);
  }

  return ret;
}

int main() {
  // 1번 집의 색을 하나의 인덱스로 사용해서 dp
  // dp[n][1][2] => 1번 집이 1번색, n번 집은 2번색을 골랐을 떄 n번 집에서 N번 집까지 칠하는데 드는 최소 비용
  // 즉 우리는 dp[1][0][0] dp[1][1][1] dp[1][2][2] 중에서 가장 비용이 작은 걸 고르면 됨
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j < 3; ++j) {
      cin >> cost[i][j];
    }
  }

  for (int i = 0; i < 3; ++i) {
    ans = min(ans, go(1, i, i));
  }

  cout << ans << '\n';
  return 0;
}