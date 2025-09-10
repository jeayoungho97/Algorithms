// 미생물 연구
// 제한조건 : 2 <= n <= 15, 1 <= q <= 50
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define MAX_SIZE 16
using namespace std;

struct GROUP {
  int size, num;  // num : group 이 생성된 시점
  // int sy, sx;   // sy, sx 는 처음에 배치됐던 좌하단 좌표
  int cy, cx;                   // cy, cx 는 현재 좌하단의 좌표
  int map[MAX_SIZE][MAX_SIZE];  // sy, sx 를 기준으로 어느 위치에 미생물이
                                // 있는지 (즉 모양을 결정) -> 값은 num 과 같음
  bool isAlive = true;
  bool operator<(const GROUP &rhs) const {
    if (size == rhs.size) return num < rhs.num;
    return size < rhs.size;
  }
};

struct NODE {
  int y, x;
};

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
int n, q;
int MAP[MAX_SIZE][MAX_SIZE];

int bfs(int y, int x, int map[MAX_SIZE][MAX_SIZE]) {
  queue<NODE> q;
  bool visited[MAX_SIZE][MAX_SIZE] = {0};
  q.push({y, x});
  visited[y][x] = true;

  int cnt = 0;
  while (!q.empty()) {
    NODE now = q.front();
    q.pop();
    cnt++;

    for (int i = 0; i < 4; ++i) {
      int ny = now.y + dy[i];
      int nx = now.x + dx[i];
      if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
      if (visited[ny][nx]) continue;
      if (!map[ny][nx]) continue;
      q.push({ny, nx});
      visited[ny][nx] = 1;
    }
  }

  return cnt;
}

int main() {
  cin >> n >> q;

  vector<GROUP> groups;  // q 개의 미생물 군집 (1번 인덱스부터 시작)
  groups.push_back({});  // dummy node 추가
  groups[0].isAlive = false;

  for (int query = 1; query <= q; ++query) {
    int ans = 0;

    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    // 새롭게 생성된 군집의 넓이와 모양을 기록
    groups.push_back({});
    groups[query].num = query;
    groups[query].size = (r2 - r1) * (c2 - c1);

    for (int row = 0; row < c2 - c1; ++row) {
      for (int col = 0; col < r2 - r1; ++col) {
        groups[query].map[row][col] = query;
      }
    }

    // DB
    cout << "\ncurrent MAP\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << MAP[i][j] << ' ';
      }
      cout << '\n';
    }

    cout << "\nGROUP to put in\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i >= c1 && i < c2 && j >= r1 && j < r2)
          cout << query << ' ';
        else
          cout << 0 << ' ';
      }
      cout << '\n';
    }
    cout << '\n';
    // DB

    // 기존 맵에 다른 미생물 있다면 삭제
    for (int row = c1; row < c2; ++row) {
      for (int col = r1; col < r2; ++col) {
        if (MAP[row][col]) {
          int num_group = MAP[row][col];
          GROUP &now = groups[num_group];
          int cy = now.cy, cx = now.cx;  // cy, cx 는 해당 군집의 현재 좌하단

          now.map[row - cy][col - cx] = 0;
          if (!--now.size) now.isAlive = false;

          // for debugging
          cout << '\n';
          for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
              cout << now.map[i][j] << ' ';
            }
            cout << '\n';
          }
          cout << '\n';

          cout << "group :" << num_group << ", cy : " << cy << ", cx : " << cx
               << '\n';
          cout << "row - cy : " << row - cy << ", col - cx : " << col - cx
               << '\n';
          MAP[row][col] = 0;
        }
      }
    }

    // DB
    cout << "MAP after erasing groups\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << MAP[i][j] << ' ';
      }
      cout << '\n';
    }
    cout << '\n';
    // DB

    // 각 군집의 map에서 살아있는 점 하나 잡고 플러드필 돌림
    // 그 때의 넓이가 최신화된 넓이랑 같은지 확인
    // => 다르다면 여러 구역으로 나뉘었다는 것
    for (GROUP &now : groups) {
      if (!now.isAlive) continue;

      cout << '\n';
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          cout << now.map[i][j] << ' ';
        }
        cout << '\n';
      }
      cout << '\n';

      // 삭제된 미생물 군집들의 map 재조정
      int sy = 20, sx = 20;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (now.map[i][j]) {
            sy = min(sy, i), sx = min(sx, j);
          }
        }
      }

      int temp_map[MAX_SIZE][MAX_SIZE];
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (now.map[i][j]) {
            now.map[i - sy][j - sx] = now.map[i][j];
            // 여기가 틀림ㅋ
            
          }
        }
      }

      bool breaker = false;
      int cnt = 0;

      for (int i = 0; i < n; ++i) {
        if (breaker) break;
        for (int j = 0; j < n; ++j) {
          if (now.map[i][j]) {
            cnt = bfs(i, j, now.map);

            // DB
            cout << "\nGROUP to do BFS\n";
            for (int i = 0; i < n; ++i) {
              for (int j = 0; j < n; ++j) {
                cout << now.map[i][j] << ' ';
              }
              cout << '\n';
            }
            cout << '\n';

            cout << now.num << "의 넓이는 : " << now.size << '\n';
            cout << "플러드필 결과는 : " << cnt << '\n';
            // DB

            breaker = true;
            break;
          }
        }
      }

      if (cnt != now.size) {
        now.isAlive = false;
      }
    }

    // 2. 맵 정리하기
    memset(MAP, 0, sizeof(MAP));

    // size 순, 들어온 순서 순으로 정렬
    priority_queue<GROUP> sorted_groups;
    for (GROUP now : groups) {
      if (!now.isAlive) continue;
      sorted_groups.push(now);
    }

    while (!sorted_groups.empty()) {
      int group_num = sorted_groups.top().num;
      sorted_groups.pop();
      GROUP &now = groups[group_num];

      // 모든 좌표를 돌면서 군집이 들어갈 수 있는지 확인
      bool found = false;
      for (int j = 0; j < n; ++j) {
        if (found) break;
        for (int i = 0; i < n; ++i) {
          if (MAP[i][j]) continue;

          bool good_to_go = true;
          for (int row = 0; row < n; ++row) {
            if (!good_to_go) break;
            for (int col = 0; col < n; ++col) {
              int ny = i + row;
              int nx = j + col;
              if ((ny < 0 || nx < 0 || ny >= n || nx >= n || MAP[ny][nx]) &&
                  now.map[row][col]) {
                good_to_go = false;
                break;
              }
            }
          }

          // 들어갈 수 있다면 집어넣기
          if (good_to_go) {
            now.cy = i, now.cx = j;

            // 인접한 군집 확인용 visited
            bool visited_others[51] = {0};
            visited_others[now.num] = true;

            for (int row = 0; row < n; ++row) {
              for (int col = 0; col < n; ++col) {
                int ny = i + row;
                int nx = j + col;
                if (now.map[row][col]) {
                  MAP[ny][nx] = now.num;

                  // 4방향으로 돌면서 인접한 군집이 있는지 확인
                  for (int dir = 0; dir < 4; ++dir) {
                    int oy = ny + dy[dir];
                    int ox = nx + dx[dir];
                    if (oy < 0 || ox < 0 || oy >= n || ox >= n) continue;
                    if (!MAP[oy][ox]) continue;
                    if (visited_others[MAP[oy][ox]]) continue;

                    visited_others[MAP[oy][ox]] = true;
                  }
                }
              }
            }

            // 인접한 군집끼리 계산
            for (int i = 1; i < groups.size(); ++i) {
              if (!groups[i].isAlive) continue;
              if (i == now.num) continue;
              if (!visited_others[i]) continue;

              ans += now.size * groups[i].size;
            }

            found = true;
            break;
          }
        }
      }

      if (!found) now.isAlive = false;
    }
    // DB
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        cout << MAP[i][j] << ' ';
      }
      cout << '\n';
    }
    // DB
    cout << ans << '\n';
  }

  system("pause");
  return 0;
}