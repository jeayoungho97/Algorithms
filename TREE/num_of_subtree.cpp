#include <iostream>
#include <vector>
using namespace std;
int N, R, Q;

vector<vector<int>> adj;
vector<int> num;
vector<bool> visited;

int go(int now) {
  int& ret = num[now];
  visited[now] = true;
  for (int val : adj[now]) {
    if (visited[val]) continue;
    visited[val] = true;
    ret += go(val);
  }

  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> R >> Q;

  adj.resize(N + 1, {});
  num.resize(N + 1, 1);
  visited.resize(N + 1, false);

  for (int i = 0; i < N - 1; ++i) {
    int U, V;
    cin >> U >> V;

    adj[U].push_back(V);
    adj[V].push_back(U);
  }

  num[R] = go(R);

  for (int q = 0; q < Q; ++q) {
    int U;
    cin >> U;

    cout << num[U] << '\n';
  }

  return 0;
}