#include <iostream>
#include <vector>
#include <queue>

std::queue<std::pair<int,int>> q;
std::vector<int> adj[11];
bool visited[11];

int main() {
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int fire;
    std::cin >> fire;

    q.push({1, 0});
    visited[1] = 1;
    bool found = false;
    while (!q.empty()) {
        int here = q.front().first;
        int cnt = q.front().second;
        q.pop();
        if (here == n) {
            std::cout << cnt << '\n';
            found = 1;
            break;
        }

        for (int i : adj[here]) {
            if (visited[i] || i == fire) continue;
            visited[i] = 1;
            q.push({i, cnt + 1});
        }
    }

    if (!found) std::cout << -1 << '\n';
    return 0;
}