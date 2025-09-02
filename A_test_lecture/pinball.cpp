#include <iostream>
#include <vector>
using namespace std;

struct NODE {
    int y, x;
};

vector<NODE> wormhole[11];

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
int ans;
int n;
int MAP[101][101];

const int block[6][4] = {
    {0, 1, 2, 3}, // dummy block
    {2, 3, 1, 0},
    {1, 3, 0, 2},
    {3, 2, 0, 1},
    {2, 0, 3, 1},
    {2, 3, 0, 1}
};

void init() {
    ans = -21e8;
    for (int i = 0; i < 11; ++i) {
        wormhole[i].clear();
    }
}

void input() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> MAP[i][j];
            if (MAP[i][j] >= 6) {
                // 웜홀 따로 관리
                wormhole[MAP[i][j]].push_back({i, j});
            }
        }
    }

}

int go(int y, int x, int dir) {
    int ny = y;
    int nx = x;
    int nd = dir;
    int flag = 0; // 출발 여부
    int cnt = 0; // 몇 번 부딪히는지
    
    while (true) {
        // 1. 시작 위치로 되돌아 오는 경우
        if (ny == y && nx == x && flag == 1) {
            break;
        }

        // 움직이기
        ny += dy[nd];
        nx += dx[nd];
        flag = 1;
        
        // 벽에 부딪히는 경우
        if (ny < 0 || nx < 0 || ny >= n || nx >= n) {
            ny -= dy[nd];
            nx -= dx[nd];

            nd = (nd + 2) % 4;

            cnt++;
        }

        // 블랙홀에 빠지는 경우
        if (MAP[ny][nx] == -1) {
            break;
        }

        // 웜홀에 빠지는 경우
        if (MAP[ny][nx] >= 6 && MAP[ny][nx] <= 10) {
            int wormholenum = MAP[ny][nx];
            if (ny == wormhole[wormholenum][0].y && nx == wormhole[wormholenum][0].x) {
                ny = wormhole[wormholenum][1].y;
                nx = wormhole[wormholenum][1].x;
            }
            else {
                ny = wormhole[wormholenum][0].y;
                nx = wormhole[wormholenum][0].x;
            }
        }

        // 블럭에 부딪히는 경우
        if (MAP[ny][nx] >= 1 && MAP[ny][nx] <= 5) {
            nd = block[MAP[ny][nx]][nd];
            cnt++;
        }
    }

    return cnt;
}

void solve() {
    // 모든 빈 공간에서 4방향으로 출발해본다.
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (MAP[i][j] != 0) continue;

            for (int dir = 0; dir < 4; ++dir) {
                int ret = go(i, j, dir);
                if (ret > ans) ans = ret;
            }
        }
    }


}

int main() {
    //Simulation -> 하지만 시간의 흐름으로 하지 않음
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        init();
        input();
        solve();

        cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}