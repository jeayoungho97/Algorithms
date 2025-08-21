#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct NODE {
    int num, cost;
    bool operator<(const NODE& right) const {
        return cost > right.cost;
    }
};

int n, t;
std::vector<NODE> adj[20001];
int dist[20001];

void dijkstra(int start) {
    std::fill(dist, dist + 20001, 1e9);
    std::priority_queue<NODE> pq;
    pq.push({start, 0});
    dist[start] = 0;

    while (!pq.empty()) {
        NODE now = pq.top(); pq.pop();
        if (dist[now.num] < now.cost) continue;
        dist[now.num] = now.cost;

        for (NODE next : adj[now.num]) {
            int nextcost = now.cost + next.cost;
            if (dist[next.num] <= nextcost) continue;
            pq.push({next.num, nextcost});
        }
    }
}

int main() {
    std::cin >> n >> t;
    for (int i = 0; i < t; ++i) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        adj[from].push_back({to, cost});
    }
    dijkstra(0);

    if (dist[n - 1] == 1e9) std::cout << "impossible\n";
    else std::cout << dist[n - 1] << '\n';

    return 0;
}