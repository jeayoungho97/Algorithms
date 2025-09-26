// 다익스트라 같은데
// 시간복잡도상 가능? => 1000번의 쿼리, 25000번 연산
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

struct NODE {
  int y, x, cost;
  int jump;
  bool operator<(const NODE& r) const { return cost > r.cost; }
};

bool visited[51][51][6];
const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
int N, Q;
int dist[51][51];
char MAP[51][51];

void solve(int r1, int c1, int r2, int c2) {
  fill(&dist[0][0], &dist[0][0] + 51 * 51, 1e9);
  fill(&visited[0][0][0], &visited[0][0][0] + 51 * 51 * 6, false);
  priority_queue<NODE> pq;
  pq.push({r1, c1, 0, 1});
  dist[r1][c1] = 0;

  while (!pq.empty()) {
    NODE now = pq.top();
    pq.pop();
    if (dist[now.y][now.x] + 54 < now.cost) continue;

    for (int dir = 0; dir < 4; ++dir) {
      for (int jump = 1; jump <= 5; ++jump) {
        int nextcost = now.cost + 1;
        if (jump < now.jump) {
          // 점프력 감소
          nextcost += 1;
        } else if (jump > now.jump) {
          // 점프력 증가
          int temp = jump;
          while (temp != now.jump) {
            nextcost += temp * temp;
            temp--;
          }
        }

        int ny = now.y + jump * dy[dir];
        int nx = now.x + jump * dx[dir];
        
        NODE next = {ny, nx, nextcost, jump};
        // 천적 or 맵 탈출 => break
        if (ny < 0 || nx < 0 || ny >= N || nx >= N) {
          break;
        }
        if (MAP[ny][nx] == '#') {
          break;
        }

        // 미끄러운 돌 => continue
        if (MAP[ny][nx] == 'S') {
          continue;
        }

        // 여유를 두고 pq 받음 => 여기서 무한루프가 도는데 visited 같은걸로 확인을 해줘야할듯
        if (dist[ny][nx] + 54 < nextcost) {
          continue;
        }

        if (visited[ny][nx][jump] == true) continue;

        // dist 최솟값 갱신
        if (dist[ny][nx] > nextcost) {
          cout << "dist[" << ny << "][" << nx << "] = " << nextcost << '\n';
          dist[ny][nx] = nextcost;
        }

        visited[ny][nx][jump] = true;
        pq.push(next);
      }
    }
  }

  if (dist[r2][c2] >= 1e9)
    cout << -1 << '\n';
  else
    cout << dist[r2][c2] << '\n';

  cout << dist[3][1] << ' ' << dist[3][4] << ' ' << dist[1][4] << ' '
       << dist[1][2] << ' ' << dist[0][2] << ' ' << dist[0][0] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> MAP[i][j];
    }
  }

  cin >> Q;

  for (int i = 0; i < Q; ++i) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    solve(r1 - 1, c1 - 1, r2 - 1, c2 - 1);
  }

  return 0;
}