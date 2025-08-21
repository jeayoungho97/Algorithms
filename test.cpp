#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct NODE
{
    int y, x, cost;
    bool operator<(const NODE &r) const
    {
        return cost > r.cost;
    }
};

struct TUNNEL
{
    int ay, ax, by, bx, c;
    bool operator<(const TUNNEL &r) const
    {
        return c < r.c;
    }
};
int map[30][30], n, m;
int dist[30][30];

std::vector<TUNNEL> tunnels;

void dijkstra()
{
    std::fill(&dist[0][0], &dist[0][0] + 30 * 30, 1e9);
    std::priority_queue<NODE> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;

    while (!pq.empty())
    {
        NODE now = pq.top();
        pq.pop();
        if (dist[now.y][now.x] < now.cost)
            continue;

        for (int i = 0; i < 4; ++i)
        {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= n)
                continue;

            int temp;
            if (map[ny][nx] > map[now.y][now.x])
                temp = 2 * (map[ny][nx] - map[now.y][now.x]);
            else if (map[ny][nx] < map[now.y][now.x])
                temp = 0;
            else
                temp = 1;

            int nextcost = now.cost + temp;
            if (dist[ny][nx] <= nextcost)
                continue;
            dist[ny][nx] = nextcost;
            pq.push({ny, nx, nextcost});
        }
        for (const TUNNEL &tun : tunnels)
        {
            int temp_nxt = now.cost;
            int temp_y, temp_x;

            if (now.y == tun.ay - 1 && now.x == tun.ax - 1)
            {
                temp_y = tun.by - 1, temp_x = tun.bx - 1;
                temp_nxt += tun.c;
            }
            else if (now.y == tun.by - 1 && now.x == tun.bx - 1)
            {
                temp_y = tun.ay - 1, temp_x = tun.ax - 1;
                temp_nxt += tun.c;
            }
            else
                continue;

            if (dist[temp_y][temp_x] <= temp_nxt)
                continue;
            dist[temp_y][temp_x] = temp_nxt;
            pq.push({temp_y, temp_x, temp_nxt});
        }
    }
}

int main()
{
    int t;
    std::cin >> t;

    for (int tc = 1; tc <= t; ++tc)
    {
        std::cin >> n >> m;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                std::cin >> map[i][j];
            }
        }

        tunnels.clear();
        for (int i = 0; i < m; ++i)
        {
            int ay, ax, by, bx, c;
            std::cin >> ay >> ax >> by >> bx >> c;
            tunnels.push_back({ay, ax, by, bx, c});
        }
        std::sort(tunnels.begin(), tunnels.end());

        dijkstra();

        int ans = dist[n - 1][n - 1];
        std::cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}
