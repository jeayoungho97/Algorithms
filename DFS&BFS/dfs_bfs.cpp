#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int n, m, v;
std::vector<std::vector<int>> adj;
std::vector<bool> visited;
std::queue<int> q;

void DFS(int here)
{
  if (visited[here])
    return;

  visited[here] = true;
  std::cout << here << ' ';

  for (int i : adj[here])
  {
    DFS(i);
  }
}

void BFS()
{
  q.push(v);
  visited[v] = true;
  while (!q.empty()) {
    int num = q.front();
    q.pop();
    std::cout << num << ' ';

    for (int i : adj[num]) {
      if (visited[i]) continue;
      visited[i] = true;
      q.push(i);  
    }
  }
}

int main()
{
  std::cin >> n >> m >> v;
  adj.resize(n + 1);
  visited.resize(n + 1);

  for (int i = 0; i < m; ++i)
  {
    int a, b;
    std::cin >> a >> b;

    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  for (auto &vect : adj) {
    std::sort(vect.begin(), vect.end());
  }

  DFS(v);
  std::cout << '\n';
  std::fill(visited.begin(), visited.end(), false);
  
  BFS();
  std::cout << '\n';

  return 0;
}