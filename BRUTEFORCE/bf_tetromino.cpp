#include <iostream>
#include <vector>
#include <algorithm>

int n, m, result;
int MAP[500][500];
bool visited[500][500];
std::vector<std::pair<int, int>> to_sum;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

void exSum(int y, int x)
{
  int sum4 = MAP[y][x];
  for (int i = 0; i < 4; ++i)
  {
    int ny = y + dy[i];
    int nx = x + dx[i];
    if (ny < 0 || ny >= n || nx < 0 || nx >= m)
      continue;
    sum4 += MAP[ny][nx];
  }

  for (int i = 0; i < 4; ++i)
  {
    int ny = y + dy[i];
    int nx = x + dx[i];
    int to_sub;
    if (ny < 0 || ny >= n || nx < 0 || nx >= m) to_sub = 0;
    else to_sub = MAP[ny][nx];

    result = std::max(result, sum4 - to_sub);
  }
}

void sum()
{
  int temp = 0;
  for (std::pair<int, int> p : to_sum)
  {
    temp += MAP[p.first][p.second];
  }
  result = std::max(result, temp);
}

void DFS(int y, int x)
{
  if (to_sum.size() == 4)
  {
    sum();
    return;
  }

  for (int i = 0; i < 4; ++i)
  {
    int ny = y + dy[i];
    int nx = x + dx[i];
    if (ny < 0 || ny >= n || nx < 0 || nx >= m)
      continue;
    if (visited[ny][nx])
      continue;

    visited[ny][nx] = 1;
    to_sum.push_back({ny, nx});
    DFS(ny, nx);
    to_sum.pop_back();
    visited[ny][nx] = 0;
  }
}

int main()
{
  std::cin >> n >> m;

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      std::cin >> MAP[i][j];
    }
  }

  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < m; ++j)
    {
      visited[i][j] = 1;
      to_sum.push_back({i, j});
      DFS(i, j);
      exSum(i, j);
      to_sum.pop_back();
      visited[i][j] = 0;
    }
  }

  std::cout << result << '\n';

  return 0;
}