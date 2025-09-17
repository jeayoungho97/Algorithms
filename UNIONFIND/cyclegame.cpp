#include <iostream>
#include <vector>
using namespace std;

int N, M, ans;
vector<int> parent;

int find(int x) {
  if (parent[x] == -1) return x;
  return parent[x] = find(parent[x]);
}

bool isCycle(int a, int b) {
  int ra = find(a);
  int rb = find(b);
  if (ra == rb) return true;

  parent[rb] = ra;
  return false;
}

int main() {
  // Union-Find
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N >> M;
  parent.resize(N, -1);

  for (int i = 1; i <= M; ++i) {
    int a, b;
    cin >> a >> b;
    if (!ans && isCycle(a, b)) {
      ans = i;
    }
  }

  cout << ans << '\n';

  return 0;
}