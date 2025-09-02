#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int ans;
int n;  // 맵의 한 변의 길이
int ansMAP[301][301]; // -1 은 지뢰
bool visited[301][301];
vector<pair<int, int>> zeros;

void init() {
    ans = 0;
    memset(ansMAP, 0, sizeof(ansMAP));
    memset(visited, 0, sizeof(visited));
    zeros.clear();
}

void input() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char temp;
            cin >> temp;

            // 지뢰일경우 주변 숫자를 1씩 증가시킴 (예외 처리도 신경써서)
            if (temp == '*') {
                ansMAP[i][j] = -1;
                for (int dir = 0; dir < 8; ++dir) {
                    int ny = i + dy[dir];
                    int nx = j + dx[dir];
                    if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
                    if (ansMAP[ny][nx] == -1) continue;
                    ansMAP[ny][nx]++;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ansMAP[i][j] == 0) {
                zeros.push_back({i, j});
            }
        }
    }
}

void solve() {
    for (pair<int, int> now : zeros) {
        if (visited[now.first][now.second]) continue;
        // 아직 안 들린 0 클릭할 때마다 ans++
        ans++;
        queue<pair<int,int>> q;
        visited[now.first][now.second] = 1;
        q.push(now);

        while (!q.empty()) {
            pair<int, int> here = q.front(); q.pop();
            for (int i = 0; i < 8; ++i) {
                int ny = here.first + dy[i];
                int nx = here.second + dx[i];
                if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
                if (visited[ny][nx]) continue;

                visited[ny][nx] = 1;
                if (ansMAP[ny][nx] == 0) {
                    q.push({ny, nx});
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ansMAP[i][j] == -1 || visited[i][j]) continue;
            ans++;
        }
    }
}

int main() {
    // 0 을 클릭했을 때만 주변 8칸이 모두 켜짐
    // 다른 숫자는 안 켜짐

    // 우선 모든 칸에 대해 숫자를 만들어놓음
    // 0인 곳들만 클릭 -> 주변 8칸은 visited 처리하고, 연결된 0은 큐에 넣어서 알아서 또 터뜨림.
    // 0 모두 터뜨린 다음엔 남은 칸을 셈.

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