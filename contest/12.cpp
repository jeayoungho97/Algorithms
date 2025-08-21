// 플로이드 워셜 같은데 모르겠다

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct NODE {
    int y, x;
    long long cost;
    bool operator<(const NODE& right) const {
        return cost > right.cost;
    }
};

int n, a, b;
long long ans;
char map[30][30];
long long dist[30][30];

void dijkstra(int y, int x) {
    std::priority_queue<NODE> pq;
    std::fill(&dist[0][0], &dist[0][0] + 30 * 30, 1e9);
    pq.push({y, x, 0});
    dist[y][x] = 0;

    while (!pq.empty()) {
        NODE now = pq.top(); pq.pop();
        if (dist[now.y][now.x] < now.cost) continue;
        dist[now.y][now.x] = now.cost;
        
        if (ans < now.cost) ans = now.cost;

        for (int i = 0; i < 4; ++i) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
            long long nextcost;
            if (map[now.y][now.x] != map[ny][nx]) nextcost = now.cost + b;
            else nextcost = now.cost + a;
            if (dist[ny][nx] <= nextcost) continue;
            pq.push({ny, nx, nextcost});
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> a >> b;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> map[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dijkstra(i, j);
        }
    }

    std::cout << ans << '\n';

    return 0;
}