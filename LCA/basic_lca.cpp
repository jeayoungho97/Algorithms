// BOJ 11437
// O(depth), BFS 로 트리 만들기

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
vector<int> adj[50001];

int par[50001];
int depth[50001];
bool visited[50001];

void bfs(int start) {
  queue<int> q;
  q.push(start);
  
  while (!q.empty()) {
    int now = q.front(); q.pop();
    visited[now] = true;

    for (int next : adj[now]) {
      if (visited[next]) continue;
      q.push(next);

      par[next] = now;
      depth[next] = depth[now] + 1;
    }
  }
}

void go(int a, int b) {
  if (depth[a] < depth[b]) {
    while (depth[a] != depth[b]) {
      b = par[b];
    }    
  }
  else if (depth[a] > depth[b]) {
    while (depth[a] != depth[b]) {
      a = par[a];
    }
  }

  while (a != b) {
    a = par[a];
    b = par[b];
  }

  cout << a << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;
  for (int i = 0; i < N - 1; ++i) {
    int a, b;
    cin >> a >> b;

    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  depth[1] = 0;

  bfs(1);

  cin >> M;
  for (int i = 0; i < M; ++i) {
    int a, b;
    cin >> a >> b;

    go(a, b);
  }

  return 0;
}