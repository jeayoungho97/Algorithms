#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Tuple{
    int z, y, x;
};

const int dy[6] = {-1, 0, 1, 0, 0, 0};
const int dx[6] = {0, 1, 0, -1, 0, 0};
const int dz[6] = {0, 0, 0, 0, 1, -1};

int M, N, H;
int day, total, cnt; // day : 다 익는데 걸리는 시간   total : 총 토마토 개수  cnt : 익힌 토마토 개수 (총 개수와 맞으면 day 출력, 아니면 -1 출력)
int box[101][101][101]; // z, y, x
int visited[101][101][101];
queue<Tuple> q;

void debug() {
    cout << "====" << '\n';
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < M; ++k) {
                cout << box[i][j][k] << ' ';
            }
            cout << '\n';
        }
    }
}

int main() {
    cin >> M >> N >> H;
    fill(&visited[0][0][0], &visited[0][0][0] + 101 * 101 * 101, -1);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < M; ++k) {
                cin >> box[i][j][k];
                if (box[i][j][k] == 1) {
                    visited[i][j][k] = 0;
                    q.push({i, j, k});
                    cnt++;
                }
                
                if (box[i][j][k] == -1) continue;
                total++;
            }
        }
    }

    while(!q.empty()) {
        Tuple tp = q.front(); q.pop();
        int cz = tp.z;
        int cy = tp.y;
        int cx = tp.x;
        
        for (int dir = 0; dir < 6; ++dir) {
            int nz = cz + dz[dir];
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];

            if (nz < 0 || ny < 0 || nx < 0 || nz >= H || ny >= N || nx >= M) continue;
            if (visited[nz][ny][nx] != -1 || box[nz][ny][nx] != 0) continue;

            visited[nz][ny][nx] = visited[cz][cy][cx] + 1;
            day = max(day, visited[nz][ny][nx]);

            box[nz][ny][nx] = 1;
            q.push({nz, ny, nx});
            cnt++;
        }

        // debug();
    }

    if (total == cnt) cout << day << '\n';
    else cout << -1 << '\n';

    return 0;
}