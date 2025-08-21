#include <iostream>
#include <queue>
#include <cmath>

// 거리가 증식 시작으로 부터 가까운 것 우선
// 행이 작은 칸 우선
// 열이 작은 우선

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, -1, 0, 1};

int n, m;
int sy, sx, k, cnt, fy = -1, fx;
int map[100][100];

struct NODE {
    int y, x, dist;
    bool operator<(const NODE& r) const {
        if (dist == r.dist && y == r.y) {
            return x > r.x;
        }
        else if (dist == r.dist && y != r.y) return y > r.y;

        return dist > r.dist;
    }
};

std::priority_queue<NODE> pq;

void BFS() {
    pq.push({sy, sx});

    while (!pq.empty()) {
        NODE now = pq.top(); pq.pop();
        if (map[now.y][now.x] == 1) continue;
        cnt++;
        // std::cout << "cnt = " << cnt << " y : " << now.y << " x : " << now.x << '\n';
        if (cnt == k) {
            fy = now.y;
            fx = now.x;
            break;
        }
        map[now.y][now.x] = 1;

        for (int i = 0; i < 4; ++i) {
            int ny = now.y + dy[i];
            int nx = now.x + dx[i];
            if (ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
            if (map[ny][nx] == 1) continue;
            int dist = std::abs(ny - sy) + std::abs(nx - sx);
            pq.push({ny, nx, dist});            
        }
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> map[i][j];
        }
    }

    std::cin >> sy >> sx >> k;

    BFS();

    if (fy == -1) std::cout << -1 << '\n';
    else std::cout << fy << ' ' << fx << '\n';

    return 0;
}