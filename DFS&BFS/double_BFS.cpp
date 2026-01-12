#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct Pair{
    int y, x;
};
int N, ans1, ans2;
char MAP[101][101];
bool visited[101][101];

void go(int row, int col) {
    char color = MAP[row][col];
    queue<Pair> q;
    q.push({row, col});
    while (!q.empty()) {
        Pair now = q.front(); q.pop();
        int cy = now.y;
        int cx = now.x;

        for (int dir = 0; dir < 4; ++dir) {
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if (visited[ny][nx] || MAP[ny][nx] != color) continue;

            visited[ny][nx] = 1;
            q.push({ny, nx});
        }
    }
}

void go2(int row, int col) {
    char color = MAP[row][col];
    bool isBlue = (color == 'B');

    queue<Pair> q;
    q.push({row, col});
    while (!q.empty()) {
        Pair now = q.front(); q.pop();
        int cy = now.y;
        int cx = now.x;

        for (int dir = 0; dir < 4; ++dir) {
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if (visited[ny][nx]) continue;
            if (isBlue && MAP[ny][nx] != color) continue;
            if (!isBlue && MAP[ny][nx] == 'B') continue;

            visited[ny][nx] = 1;
            q.push({ny, nx});
        }
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> MAP[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!visited[i][j]) {
                visited[i][j] = 1;
                ans1++;
                go(i, j);
            }
        }
    }

    fill(&visited[0][0], &visited[0][0] + 101 * 101, 0);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!visited[i][j]) {
                visited[i][j] = 1;
                ans2++;
                go2(i, j);
            }
        }
    }

    cout << ans1 << ' ' << ans2 << '\n';
    return 0;
}