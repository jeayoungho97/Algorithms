#include <iostream>
#include <vector>

const int dy[] = {1, -1, 0, 0};
const int dx[] = {0, 0, -1, 1};

int ans;

struct NODE {
  int x, y, dir, energy, isAlive;
};

std::vector<NODE> atom(1001);

// 좌표에 원자의 개수를 담음
int map[4001][4001];
int cnt = 0;

void solve() {

  while (cnt > 0) {
    // 1. 이동
    for (int i = 0; i < atom.size(); ++i) {
      NODE & now = atom[i];
      if (now.isAlive == 0) continue;

      int ny = now.y + dy[now.dir];
      int nx = now.x + dx[now.dir];

      // 범위를 벗어난 경우
      if (ny < 0 || nx < 0 || ny >= 4001 || nx >= 4001) {
        now.isAlive = 0;
        cnt--;
        map[now.y][now.x] = 0;
        continue;
      }

      // 원자의 이동으로 해당 좌표의 원자 개수 증가
      map[ny][nx]++;
      map[now.y][now.x] = 0;

      // 원자 위치 갱신
      now.y = ny;
      now.x = nx;
    }

    // 2. 충돌 체크
    for (int i = 0; i < atom.size(); ++i) {

      NODE & now = atom[i];
      if (now.isAlive == 0) continue;

      // 충돌함?
      if (map[now.y][now.x] >= 2) {

        // 충돌한 모든 원자를 찾자.
        for (int j = 0; j < atom.size(); ++j) {
          if (atom[j].isAlive == 0) continue;

          if (now.y == atom[j].y && now.x == atom[j].x) {
            ans += atom[j].energy;
            cnt--;
            atom[j].isAlive = 0;
          }
        }

        map[now.y][now.x] = 0;
      }
    }
  }
}

int main() {
  int t;
  std::cin >> t;

  for (int tc = 1; tc <= t; ++tc) {
    ans = 0;
    cnt = 0;
    atom.clear();

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
      int x, y, dir, energy;
      std::cin >> x >> y >> dir >> energy;

      x = (x + 1000) * 2;
      y = (y + 1000) * 2;

      atom.push_back({x,y,dir,energy, 1});
      cnt++;
    }

    solve();

    std::cout << '#' << tc << ' ' << ans << '\n';
  }
}