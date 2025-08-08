#include <iostream>
#include <vector>
#include <algorithm>

int n, cost, cheap = 1e9, visited = 1; // visited 는 비트마스킹으로 해보자. 초기상태 = 0번 노드만 방문
std::vector<std::vector<int>> adj;

void go(int here) {
    if (visited == ((1 << n) - 1)) {
        // 모두 방문 완료 했다면 here 에서 0 으로 가는 비용을 최종적으로 추가하고 cheap 최신화
        if (!adj[here][0]) return;

        cost += adj[here][0];
        cheap = std::min(cheap, cost);
        cost -= adj[here][0];
        return;
    }

    for (int i = 1; i < n; ++i) {
        if (visited & (1 << i) || !adj[here][i]) continue;

        visited |= (1 << i);

        cost += adj[here][i];
        go(i);
        cost -= adj[here][i];

        visited ^= (1 << i);
    }
}

int main() {
    std::cin >> n;
    adj.resize(n, std::vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> adj[i][j];
        }
    }

    go(0);
    std::cout << cheap << '\n';
    return 0;
}