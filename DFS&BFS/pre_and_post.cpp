#include <iostream>
#include <algorithm>
#include <vector>

int n, k, s;
std::vector<std::vector<int>> adj;
std::vector<bool> visited;

void preGo(int here) {
    visited[here] = true;
    std::cout << here << ' ';
    for (int i : adj[here]) {
        if (visited[i]) continue;

        preGo(i);
    }

}

void postGo(int here) {
    visited[here] = true;

    for (int i : adj[here]) {
        if (visited[i]) continue;

        postGo(i);
    }

    std::cout << here << ' ';
}

int main() {
    std::cin >> n >> k >> s;

    //resize vectors
    adj.resize(n + 1);
    visited.resize(n + 1);

    for (int i = 0; i < k; ++i) {
        int a, b;
        std::cin >> a >> b;

        adj[a].push_back(b);
    }
    
    for (int i = 1; i <= n; ++i) {
        std::sort(adj[i].begin(), adj[i].end(), std::greater<>());
    }

    // 전위 순회
    preGo(s);
    std::cout << '\n';

    // visited 초기화
    std::fill(visited.begin(), visited.end(), 0);

    // 후위 순회
    postGo(s);
    std::cout << '\n';

    return 0;
}