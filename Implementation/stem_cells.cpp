#include <iostream>
#include <queue>
#include <cstring>

// 기본 pq 용
struct NODE {
    int y, x, hp, go_time, dead_time;
    bool operator<(const NODE & right) const {
        // 번식 시간이 가까운게 top
        return go_time > right.go_time;
    }
};

// 임시 pq 용
struct Cmp {
    bool operator()(const NODE& a, const NODE& b) {
        // y, x 는 작은게 top
        // hp 는 큰게 top
        if (a.hp != b.hp) return a.hp < b.hp;
        if (a.y != b.y) return a.y > b.y;
        return a.x > b.x;
    }
};

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
const int coord_shift = 400;

int n, m, k;
int ans;
bool visited[1000][1000];
std::priority_queue<NODE> pq;

void init() {
    ans = 0;
    std::memset(visited, 0, sizeof(visited));
    while (!pq.empty()) {
        pq.pop();
    }
}

void input() {
    std::cin >> n >> m >> k;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int temp;
            std::cin >> temp;
            if (temp == 0) continue;
            pq.push({i, j, temp, temp + 1, temp * 2});
            visited[i + coord_shift][j + coord_shift] = 1;
            if (temp * 2 > k) ans++;
        }
    }
}

void solve() {
    int time = 0;
    while (time != k + 1) {
        std::priority_queue<NODE, std::vector<NODE>, Cmp> temp_pq;
        while (!pq.empty() && pq.top().go_time == time) {
            NODE here = pq.top();
            pq.pop();

            for (int i = 0; i < 4; ++i) {
                int ny = here.y + dy[i];
                int nx = here.x + dx[i];
                if (visited[ny + coord_shift][nx + coord_shift]) continue;
                temp_pq.push({ny, nx, here.hp, time + here.hp + 1, time + here.hp * 2});
            }
        }
        
        bool chosen[1000][1000] = {0};
        while (!temp_pq.empty()) {
            NODE here = temp_pq.top();
            temp_pq.pop();
            int Y = here.y + coord_shift, X = here.x + coord_shift;
            if (chosen[Y][X]) continue;
            chosen[Y][X] = 1;
            visited[Y][X] = 1;
            if (here.dead_time > k) ans++;
            pq.push(here);
        }

        time++;
    }
    
    
}

int main() {
    int T;
    std::cin >> T;

    for (int tc = 1; tc <= T; ++tc) {
        init();

        input();

        solve();

        std::cout << '#' << tc << ' ' << ans << '\n';
    }


    return 0;
}