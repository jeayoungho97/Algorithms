#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

// 유니온 파인드
// 좌표를 (0,0) => 1, (0,1) => 2, 0,2 => 3 ... 식으로 만들어야함

struct NODE {
  int y, x; // 우선순위 비교하기 위해서
  int food = 0; // 신봉하는 음식 (비트마스킹)
  int power; // 신앙심
  int ganjul;
  bool operator<(const NODE& r) const {
    if (power != r.power) return power < r.power;
    if (y != r.y) return y > r.y;
    return x > r.x;
  }
};

struct NODE_LEADER {
  int y, x; // 우선순위 비교하기 위해서
  int food = 0; // 신봉하는 음식 (비트마스킹)
  int power; // 신앙심
  int ganjul;
  bool operator<(const NODE_LEADER& r) const {
    if (ganjul != r.ganjul) return ganjul < r.ganjul;
    if (y != r.y)      return y > r.y;          
    return x > r.x;                                   
  }
};

struct PAIR {
  int y, x;
};

// 상 하 좌 우
const int dy[] = {-1, 1, 0, 0};
const int dx[] = {0, 0, -1, 1};



int N, T;
NODE person[51][51];
priority_queue<NODE> group[2501]; // 유니온파인드해서 parent 값을 idx 로 받아야함
priority_queue<NODE_LEADER> leaders;

int parent[2501];
bool visited[51][51];

int find(int x) {
  if (parent[x] == 0) return x;
  return parent[x] = find(parent[x]);
}

void UNION(int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b) return;
  parent[b] = a;
}

void init() {
  memset(parent, 0, sizeof(parent));
  memset(visited, false, sizeof(visited));
  for (int i = 0; i < 2501; ++i) {
    if (group[i].empty()) continue;
    while(!group[i].empty()) {
      group[i].pop();
    }
  }
}

void morning() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      person[i][j].power++;
    }
  }
}

void BFS(int i, int j) {
  queue<PAIR> q;
  q.push({i, j});
  visited[i][j] = true;
  person[i][j].power--;

  group[find(i * N + j + 1)].push(person[i][j]);

  while (!q.empty()) {
    PAIR now = q.front(); q.pop();

    for (int dir = 0; dir < 4; ++dir) {
      int ny = now.y + dy[dir];
      int nx = now.x + dx[dir];
      if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
      if (visited[ny][nx]) continue;

      if (person[now.y][now.x].food == person[ny][nx].food) {
        visited[ny][nx] = true;
        UNION(now.y * N + now.x + 1, ny * N + nx + 1);
        person[ny][nx].power--;
        group[find(ny * N + nx + 1)].push(person[ny][nx]);

        q.push({ny, nx});
      }
    }
  }
}

// BFS 도 해야겠다
void lunch() {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (visited[i][j]) continue;
      BFS(i, j);
    }
  }

  for (int i = 1; i < 2501; ++i) {
    if (group[i].empty()) continue;

    // 리더의 신앙심 -> 1, 간절함 -> B - 1
    NODE now = group[i].top();

    person[now.y][now.x].power += group[i].size();

    if (group[i].size() == 1) continue;
    person[now.y][now.x].ganjul = person[now.y][now.x].power - 1;
    now = person[now.y][now.x];

    // 전파 순서도 미리 정함
    NODE_LEADER leader = {now.y, now.x, now.food, now.power, now.ganjul};

    leaders.push(leader);
  }
}

void dinner() {
  bool junpa[51][51] = {0};

  while (!leaders.empty()) {
    NODE_LEADER now = leaders.top(); leaders.pop();
    cout << "food : " << now.food << " coord : " << now.y << ' ' << now.x << " ganjul : " << now.ganjul << " power : " << now.power << '\n';
    if (junpa[now.y][now.x]) continue;
    // 전파 시작
    person[now.y][now.x].power = 1;
    int dir = (now.ganjul + 1) % 4;
    int ny = now.y;
    int nx = now.x;

    cout << "dir :" << dir << '\n';

    while (true) {
      ny += dy[dir];
      nx += dx[dir];

      if (ny < 0 || nx < 0 || ny >= N || nx >= N) break;

      NODE& next = person[ny][nx];

      if (next.food == now.food) continue;

      if (now.ganjul > next.power) {
        // 강한 전파
        junpa[ny][nx] = true;
        next.food = now.food;
        now.ganjul -= next.power + 1;
        next.power++;
      }
      else {
        // 약한 전파
        junpa[ny][nx] = true;
        next.food ^= now.food;
        next.power += now.ganjul;
        now.ganjul = 0;
      }

      if (now.ganjul == 0) break;
    }

    cout << "====" << now.food << "====\n";
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cout << person[i][j].food << ' ';
      }
      cout << '\n';
    }
    cout << "====" << now.power << "====\n";
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        cout << person[i][j].power << ' ';
      }
      cout << '\n';
    }
    

  }

  int ret[8] = {0};
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      ret[person[i][j].food] += person[i][j].power;
    }
  }

  cout << ret[7] << ' ' << ret[3] << ' ' << ret[5] << ' ' << ret[6] << ' ' << ret[4] << ' ' << ret[2] << ' ' << ret[1] << '\n';
}

int main() {
  cin >> N >> T;
  for (int i = 0 ; i < N; ++i) {
    string str;
    cin >> str;
    for (int j = 0; j < N; ++j) {
      if (str[j] == 'T') {
        person[i][j].food ^= (1 << 0);
      }
      else if (str[j] == 'C') {
        person[i][j].food ^= (1 << 1);
      }
      else if (str[j] == 'M') {
        person[i][j].food ^= (1 << 2);
      }

      person[i][j].y = i;
      person[i][j].x = j;
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> person[i][j].power;
    }
  }

  while (T--) {
    init();

    morning();

    lunch();

    dinner();
  }

  return 0;
}


//   for (int i = 0; i < N; ++i) {
//     for (int j = 0; j < N; ++j) {
//
//     }
//   }



///////////////////드디어 알아냈다!!!!!!////////// 전파할 때 신앙심을 1로 바꿔야하고, 전파 당했으면 당한 리더는 전파하면 안 됨....