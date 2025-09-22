#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct NODE {
  int num, cost;
};

int N, M, MAX_K;
vector<NODE> adj[40001];
int dist[40001];
int depth[40001];
int up[40001][20];

void makeTree() {
  queue<int> q;
  depth[1] = 1;
  q.push(1);

  while (!q.empty()) {
    int now = q.front(); q.pop();

    for (NODE next : adj[now]) {
      if (depth[next.num]) continue;
      q.push(next.num);
      depth[next.num] = depth[now] + 1; // 자식깊이는 부모깊이 + 1
      dist[next.num] = dist[now] + next.cost; // 루트로부터의 거리 계산

      // up 계산
      up[next.num][0] = now;
      for (int i = 1; i < MAX_K; ++i) {
        up[next.num][i] = up[up[next.num][i - 1]][i - 1];
      }
    }
  }
}

int LCA(int deep, int shallow) {
  int anc_deep = deep, anc_shall = shallow;
  bool found = false;
  
  for (int k = MAX_K; k >= 0; --k) {
    anc_deep = up[deep][k];
    anc_shall = up[shallow][k];

    if (anc_deep == anc_shall) continue;
    else {
      found = true;
      break;
    }
  }


  if (found) {
    return LCA(anc_deep, anc_shall);
  }
  
  return anc_deep;
}

int calc(int a, int b) {
  // 깊이 맞춰주기
  int deep = (depth[a] > depth[b]) ? a : b;
  int shallow = (depth[a] > depth[b]) ? b : a;

  int dist_deep = dist[deep];
  int dist_shall = dist[shallow];

  if (depth[deep] != depth[shallow]) {
    int diff = depth[deep] - depth[shallow];
    for (int i = 0; i < MAX_K; ++i) {
      if (diff & (1 << i)) {
        deep = up[deep][i];
      }
    }
  }

  // 이미 같은 노드라면
  if (deep == shallow) {
    return dist_deep - dist_shall;
  }

  int lca = LCA(deep, shallow);

  return dist_deep + dist_shall - 2 * dist[lca];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;

  // N 보다 작은 2의 제곱수의 지수 구하기
  int i = 1;
  while (i < N) {
    i *= 2;
    MAX_K++;
  }


  for (int i = 0; i < N - 1; ++i) {
    int from, to, cost;
    cin >> from >> to >> cost;
    adj[from].push_back({to, cost});
    adj[to].push_back({from, cost});
  }

  makeTree();

  cin >> M;
  for (int i = 0; i < M; ++i) {
    int a, b;
    cin >> a >> b;
    cout << calc(a, b) << '\n';
  }

  return 0;
}