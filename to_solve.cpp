#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct NODE {
  int num, cost;
};

int N, M;
vector<NODE> adj[40001];
int depth[40001]; // visited 의 역할 겸함
int dist[40001];

void bfs() {
  queue<NODE> q;
  depth[1] = 1;
  q.push({1, 0});

  while (!q.empty()) {
    NODE now = q.front(); q.pop();
    for (NODE next : adj[now.num]) {
      if (depth[next.num]) continue;

      depth[next.num] = depth[now.num] + 1;
      dist[next.num] = now.cost + next.cost;
      q.push({next.num, dist[next.num]});
    }
  }

}

int main() {
  cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int from, to, cost;
    cin >> from >> to >> cost;

    adj[from].push_back({to, cost});
    adj[to].push_back({from, cost});
  }

  // root 는 1번이라 가정
  bfs();

  cin >> M;
  for (int i = 0; i < M; ++i) {
    int A, B;
    cin >> A >> B;

    
  }

  return 0;
}