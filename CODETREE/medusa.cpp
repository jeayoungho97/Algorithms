#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
#define pii pair<int,int>
using namespace std;

struct NODE {
  int soldiers;
  bool medusa; // 메두사의 시선이 닿는 곳 => false 로 초기화
  bool immune; // 앞의 전사가 가려줘서 메두사의 시선으로부터 안전한 곳 => false 로 초기화
  bool notRoad;
};

// 초기화 X
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};
int N, M;
int sy, sx, er, ec;
int visited[51][51]; // 경로 만들 때만 사용
bool finished = false;
bool noAnswer = false; // 집에서 공원까지 갈 수 없는 경우
queue<int> path; // 이동방향을 담은 경로 (상 하 좌 우)

// 초기화 O
int soldiers_moved; // 이동한 병사의 수
int soldiers_rocked; // 돌이 된 병사의 수
int soldiers_attacked; // 공격한 병사의 수
int soldier_dist[51][51]; // bfs 로 만든 메두사로부터 병사까지의 거리
NODE MAP[51][51];

void printMAP() {

  cout << "Medusa\n";
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (i == sy && j == sx) {
        cout << '*' << ' ';
      }
      else cout << 0 << ' ';
    }
    cout << '\n';
  }

  cout << "Soldiers\n";
    for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << MAP[i][j].soldiers << ' ';
    }
    cout << '\n';
  }
}


// 확인 완료
void findPath() {
  queue<pii> q;
  q.push({er, ec});
  visited[er][ec] = 1;

  while (!q.empty()) {
    pii now = q.front(); q.pop();

    for (int dir = 0; dir < 4; ++dir) {
      int ny = now.first + dy[dir];
      int nx = now.second + dx[dir];
      if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
      if (visited[ny][nx]) continue;
      if (MAP[ny][nx].notRoad) continue;
      visited[ny][nx] = visited[now.first][now.second] + 1;
      q.push({ny, nx});
    }
  }

  if (visited[sy][sx] == 0) {
    noAnswer = true;
    return;
  }

  int cy = sy, cx = sx;
  while (true) {
    if (cy == er && cx == ec) break;

    for (int dir = 0; dir < 4; ++dir) {
      int ny = cy + dy[dir];
      int nx = cx + dx[dir];
      if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
      if (visited[ny][nx] == visited[cy][cx] - 1) {
        path.push(dir);
        cy = ny, cx = nx;
        break;
      }
    }
  }
}


// 초기화
void init() {
  for (int i = 0; i < 51; ++i) {
    for (int j = 0; j < 51; ++j) {
      MAP[i][j].medusa = false;
      MAP[i][j].immune = false;
    }
  }
  soldiers_moved = 0;
  soldiers_rocked = 0;
  soldiers_attacked = 0;
}


// 메두사 이동
void medusaMove() {
  int dir = path.front(); path.pop();
  sy += dy[dir];
  sx += dx[dir];

  // 메두사에게 전사들 공격받고 사라짐
  MAP[sy][sx].soldiers = 0;

  // 끝까지 이동 완료
  if (path.empty()) finished = true;
}


// 대각선 찾기
int find(int y, int x, int dir) {
  if (x == sx || y == sy) return 0; // 0 -> 보는 방향 대로 일직선으로 
  if (x > sx && y < sy) return 1; // 오른쪽 위
  if (x > sx && y > sy) return 2; // 오른쪽 아래
  if (x < sx && y > sy) return 3; // 왼쪽 아래
  if (x < sx && y < sy) return 4; // 왼쪽 위
}

// 병사를 이용해 뒤쪽 가리기
void COVER(int y, int x, int dir) {
  int CASE = find(y, x, dir);
  int ny = y;
  int nx = x;
  int mul = 1;

  if (CASE == 0) {
    while (true) {
      ny += dy[dir];
      nx += dx[dir];
      if (ny < 0 || nx < 0 || ny >= N || nx >= N) break;
      MAP[ny][nx].immune = true;
    }
  }

  if (CASE == 1) {

    if (dir == 0) {
      // 위 + 오른위
      while (true) {
        ny += dy[dir];
        if (ny < 0) break;

        for (int adder = 0; adder <= mul; ++adder) {
          if (x + adder >= N) break;
          MAP[ny][x + adder].immune = true;
        }

        mul++;
      }
     }

    if (dir == 3) {
      // 오 + 오른위
      while (true) {
        nx += dx[dir];
        if (nx >= N) break;

        for (int adder = 0; adder <= mul; ++adder) {
          if (y - adder < 0) break;
          MAP[y - adder][nx].immune = true;
        }

        mul++;
      }
    }
  }

  if (CASE == 2) {
    if (dir == 1) {
      // 아래 + 오른아래
      while (true) {
        ny += dy[dir];
        if (ny >= N) break;

        for (int adder = 0; adder <= mul; ++adder) {
          if (x + adder >= N) break;
          MAP[ny][x + adder].immune = true;
        }

        mul++;
      }
    }

    if (dir == 3) {
      // 오 + 오른아래
      while (true) {
        nx += dx[dir];
        if (nx >= N) break;

        for (int adder = 0; adder <= mul; ++adder) {
          if (y + adder >= N) break;
          MAP[y + adder][nx].immune = true;
        }

        mul++;
      }
    }
  }

  if (CASE == 3) {

    if (dir == 1) {
      // 아래 + 왼아래
      while (true) {
        ny += dy[dir];
        if (ny >= N) break;

        for (int adder = 0; adder <= mul; ++adder) {
          if (x - adder < 0) break;
          MAP[ny][x - adder].immune = true;
        }

        mul++;
      }
    }

    if (dir == 2) {
      // 왼 + 왼아래
      while (true) {
        nx += dx[dir];
        if (nx < 0) break;

        for (int adder = 0; adder <= mul; ++adder) {
          if (y + adder >= N) break;
          MAP[y + adder][nx].immune = true;
        }

        mul++;
      }
    }
  }

  if (CASE == 4) {

    if (dir == 0) {
      // 위 + 왼쪽위
      while (true) {
        ny += dy[dir];
        if (ny < 0) break;

        for (int adder = 0; adder <= mul; ++adder) {
          if (x - adder < 0) break;
          MAP[ny][x - adder].immune = true;
        }

        mul++;
      }
    }

    if (dir == 2) {
      // 왼 + 왼쪽위
      while (true) {
        nx += dx[dir];
        if (nx < 0) break;

        for (int adder = 0; adder <= mul; ++adder) {
          if (y - adder < 0) break;
          MAP[y - adder][nx].immune = true;
        }

        mul++;
      }
    }
  }
}

int lookUD(int dir) {
    // 상 하
    init();
    int temp_soldier = 0;

    for (int mul = 1; ; ++mul) {
      int ny = sy + mul * dy[dir];
      if (ny < 0 || ny >= N) break;

      for (int nx = sx - mul; nx <= sx + mul; ++nx) {
        if (nx < 0) continue;
        if (nx >= N) break;
        if (MAP[ny][nx].immune) continue;

        MAP[ny][nx].medusa = true;
        if (MAP[ny][nx].soldiers) {
          temp_soldier += MAP[ny][nx].soldiers;
          COVER(ny, nx, dir);
        }
      }
    }

    return temp_soldier;
}

int lookLR(int dir) {
    // 좌 우
    init();
    int temp_soldier = 0;

    for (int mul = 1; ; ++mul) {
      int nx = sx + mul * dx[dir];
      if (nx < 0 || nx >= N) break;

      for (int ny = sy - mul; ny <= sy + mul; ++ny) {
        if (ny < 0) continue;
        if (ny >= N) break;
        if (MAP[ny][nx].immune) continue;

        MAP[ny][nx].medusa = true;
        if (MAP[ny][nx].soldiers) {
          temp_soldier += MAP[ny][nx].soldiers;
          COVER(ny, nx, dir);
        }
      }
    }

    return temp_soldier;
}


// 메두사 시선 처리
void medusaLook() {
  // 4 방향에 대해 조사 => 각 방향 볼때마다 MAP[i][j].medusa, immune 초기화 시켜줘야함
  int num_soldier = 0;
  int dir_to_look = -1;

  for (int dir = 0; dir < 4; ++dir) {
    int temp_soldier;
    if (dir < 2) {
      temp_soldier = lookUD(dir);
    }
    else if (dir < 4) {
      temp_soldier = lookLR(dir);
    }

    if (num_soldier < temp_soldier) {
      num_soldier = temp_soldier;
      dir_to_look = dir;
    }
  }

  if (dir_to_look < 2) {
    lookUD(dir_to_look);
  }
  else {
    lookLR(dir_to_look);
  }

  soldiers_rocked = num_soldier;
  // cout << num_soldier << " rocked\n";
  // printMAP();
}

void findSoldierPath() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      soldier_dist[i][j] = abs(i - sy) + abs(j - sx);
    }
  }
}

// 전사 이동
void soldierMove() {
  NODE tempMAP[51][51];
  // cout << "Before soldier move : tempMAP\n";
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (MAP[i][j].medusa) tempMAP[i][j] = MAP[i][j];
      else {
        NODE original = MAP[i][j];
        original.soldiers = 0;
        tempMAP[i][j] = original;
      }

      // cout << tempMAP[i][j].soldiers << ' ';
    }
    // cout << '\n';
  }

  findSoldierPath();

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (MAP[i][j].medusa) continue;
      if (MAP[i][j].soldiers == 0) continue;

      int moving_soldiers = MAP[i][j].soldiers;
      int ni = -1, nj = -1;
      bool attacked = false;

      // 첫번째 이동
      for (int dir = 0; dir < 4; ++dir) {
        int ny = i + dy[dir];
        int nx = j + dx[dir];
        if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
        if (MAP[ny][nx].medusa) continue;
        if (soldier_dist[ny][nx] >= soldier_dist[i][j]) continue;

        soldiers_moved += moving_soldiers;

        if (ny == sy && nx == sx) {
          soldiers_attacked += moving_soldiers;
          attacked = true;
          break;
        }
        else {
          ni = ny;
          nj = nx;
          break;
        }
      }

      if (attacked) continue;
      if (ni == -1 && nj == -1) {
        tempMAP[i][j].soldiers += moving_soldiers;
        continue;
      }
    
      // 두번째 이동
      int nni = -1;
      int nnj = -1;
      for (int dir = 0; dir < 4; ++dir) {
        int temp_dir = dir + 2;
        temp_dir %= 4;

        int ny = ni + dy[temp_dir];
        int nx = nj + dx[temp_dir];
        if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
        if (MAP[ny][nx].medusa) continue;
        if (soldier_dist[ny][nx] >= soldier_dist[ni][nj]) continue;
        soldiers_moved += moving_soldiers;
        nni = ny, nnj = nx;

        if (ny == sy && nx == sx) {
          soldiers_attacked += moving_soldiers;
          break;
        }
        else {
          // cout << "ny : " << ny << " nx : " << nx << '\n';
          // cout << tempMAP[ny][nx].soldiers << '\n';
          tempMAP[ny][nx].soldiers += moving_soldiers;
          // cout << tempMAP[ny][nx].soldiers << '\n';
          break;
        }
      }

      if (nni == -1 && nnj == -1) {
        tempMAP[ni][nj].soldiers += moving_soldiers;
      }
    }
  }

  // cout << "after soldier move : tempMAP\n";
  // for (int i = 0; i < N; ++i) {
  //   for (int j = 0; j < N; ++j) {
  //     cout << tempMAP[i][j].soldiers << ' ';
  //   }
  //   cout << '\n';
  // }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      MAP[i][j] = tempMAP[i][j];
    }
  }
}

void print() {
  cout << soldiers_moved << ' ' << soldiers_rocked << ' ' << soldiers_attacked << '\n';
}

int main() {
  cin >> N >> M;
  cin >> sy >> sx >> er >> ec;
  for (int i = 0; i < M; ++i) {
    int row, col;
    cin >> row >> col;
    MAP[row][col].soldiers++;
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> MAP[i][j].notRoad;
    }
  }

  findPath(); // 메두사 이동경로 결정

  if (noAnswer) {
    cout << -1 << '\n';
    return 0;
  }

  while (true) {
    init(); // 전역변수 무조건 초기화

    medusaMove(); // 메두사 이동
    if (finished) {
      cout << 0 << '\n';
      break;
    }

    medusaLook(); // 메두사 시선 결정 및 병사 얼리기
    // cout << "before soldier move\n";
    // printMAP();

    soldierMove(); // 병사 이동 및 공격

    // cout << "after soldier move\n";
    // printMAP();
    // cout << '\n';

    print(); // 모든 전사가 이동한 거리의 합, 메두사로 인해 돌이 된 전사의 수, 메두사를 공격한 전사의 수

  }

  return 0;
}