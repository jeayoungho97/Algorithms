#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct NODE {
    int num, cost;
    bool operator<(const NODE& r) const {
        return cost > r.cost;
    }
};

int n, m, startCity, endCity;
vector<NODE> adj[1001], radj[1001];
int dist[1001];

void dijkstra(int start) {
    fill(dist, dist + 1001, 1e9);
    priority_queue<NODE> pq;
    pq.push({start, 0});
    dist[start] = 0;

    while (!pq.empty()) {
        NODE now = pq.top(); pq.pop();
        if (now.cost > dist[now.num]) continue;

        for (NODE next : adj[now.num]) {
            int nextcost = now.cost + next.cost;
            if (dist[next.num] > nextcost) {
                dist[next.num] = nextcost;
                pq.push({next.num, nextcost});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int from, to, cost;
        cin >> from >> to >> cost;

        adj[from].push_back({to, cost});
        radj[to].push_back({from, cost});
    }

    cin >> startCity >> endCity;

    dijkstra(startCity);
    cout << dist[endCity] << '\n';

    vector<int> route;
    int idx = endCity;
    while (true) {
        route.push_back(idx);
        if (idx == startCity) break;

        for (NODE next : radj[idx]) {
            if (dist[next.num] + next.cost == dist[idx]) {
                idx = next.num; 
                break;
            }
        }
    }

    cout << route.size() << '\n';
    for (int i = route.size() - 1; i >= 0; --i) cout << route[i] << ' ';
    cout << '\n';

    return 0;
}