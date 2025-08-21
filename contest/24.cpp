#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct NODE {
    int y, x, cost;
    bool operator<(const NODE& r) const {
        return cost > r.cost;
    }
};

int map[30][30], n, m, ay, ax, by, bx, c;
int dist[30][30];

void dijkstra() {
    std::fill(&dist[0][0], &dist[0][0] + 30 * 30, 1e9);
    std::priority_queue<NODE> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;

    while (!pq.empty()) {
        NODE now = pq.top(); pq.pop();
        if (dist[now.y][now.x] < now.cost) continue;
        dist[now.y][now.x] = now.cost;

        for (int i = 0; i < 4; ++i) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
            
            int temp;
            if (map[ny][nx] > map[now.y][now.x]) temp = 2 * (map[ny][nx] - map[now.y][now.x]);
            else if (map[ny][nx] < map[now.y][now.x]) temp = 0;
            else temp = 1;
            int nextcost = now.cost + temp;

            if (ny == ay && nx == ax) {
                nextcost += c;
                ny = by, nx = bx;
            }
            else if (ny == by && nx == bx) {
                nextcost += c;
                ny = ay, nx = ax;
            }
            
            if (dist[ny][nx] <= nextcost) continue;
            pq.push({ny, nx, nextcost});
        }
    }
}

int main() {
    int t;
    std::cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        std::cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> map[i][j];
            }
        }

        std::cin >> ay >> ax >> by >> bx >> c;
        dijkstra();

        int ans = dist[n -1][n - 1];
        std::cout << '#' << tc << ' ' << ans << '\n';
    }



    return 0;
}
