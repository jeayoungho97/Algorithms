#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

struct NODE {
    int num, cost;
    bool operator<(const NODE& r) const {
        return cost > r.cost;
    }
};

int n, m, u, v;
std::vector<NODE> adj[801];
int dist[801][3];

void dijkstra(int start, int node) {
    std::priority_queue<NODE> pq;
    std::fill(dist, dist + 801 * 3, 1e9);
    dist[start][node] = 0;
    pq.push({start, 0});
    while (!pq.empty()) {
        NODE now = pq.top(); pq.pop();
        if (dist[now.num][node] < now.cost) continue;
        dist[now.num][node] = now.cost;
        for (NODE next : adj[now.num]) {
            int nextcost = now.cost + next.cost;
            if (dist[next.num][node] <= nextcost) continue;
            pq.push({next.num, nextcost});
        }
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        adj[from].push_back({to, cost});
        adj[to].push_back({from, cost});
    }
    std::cin >> u >> v;

    dijkstra(1, 0);
    dijkstra(u, 1);
    dijkstra(v, 2);


    return 0;
}