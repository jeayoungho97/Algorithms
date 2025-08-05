// 오목
// 왼쪽에서부터 완탐하면서 돌이 나오면 -> \ | / 의 네 가지 방향으로 탐색 (visited 잘 체크)
// 걸리는게 있다면 그 방향으로 가면서 돌의 개수를 셈
// 돌이 5개가 되고 끝난다면 돌의 색깔과 시작점을 반환

// 만약 돌이 6개 이상이라면 안됨. visited 를 처리할 때 돌의 좌표와 방향까지 함께.

#include <iostream>

const int dy[] = {0, 1, 1, 1};
const int dx[] = {1, 1, 0, -1};

int map[19][19];
bool visited[19][19][4];

int main()
{
  for (int i = 0; i < 19; ++i)
  {
    for (int j = 0; j < 19; ++j)
    {
      std::cin >> map[i][j];
    }
  }

  for (int y = 0; y < 19; ++y)
  {
    for (int x = 0; x < 19; ++x)
    {
      if (map[y][x] != 0)
      {
        int color = map[y][x];
        for (int dir = 0; dir < 4; ++dir)
        {
          int cnt = 1;
          if (visited[y][x][dir])
            continue;
          visited[y][x][dir] = true;
          int ny = y;
          int nx = x;
          while (true)
          {
            ny += dy[dir];
            nx += dx[dir];
            if (ny < 0 || ny >= 19 || nx < 0 || nx >= 19 || visited[ny][nx][dir] || map[ny][nx] != color) break;
            visited[ny][nx][dir] = true;
            cnt++;
          }

          if (cnt == 5)
            {
              std::cout << color << '\n';
              if (dir == 3) {
                std::cout << ny - dy[dir] + 1 << ' ' << nx - dx[dir] + 1 << '\n';
              }
              else {
                std::cout << y + 1 << ' ' << x + 1 << '\n';
              }
              return 0;
            }
        }
      }
    }
  }

  std::cout << 0 << '\n';
  return 0;
}