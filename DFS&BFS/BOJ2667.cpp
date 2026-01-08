#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#define pii pair<int,int>
using namespace std;

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};

int N;
int MAP[25][25];
bool visited[25][25];
vector<int> result;

void go(int row, int col) {
    queue<pii> q;
    q.push({row, col});
    visited[row][col] = true;
    int cnt = 1;

    while (!q.empty()) {
        pii now = q.front(); q.pop();
        for (int dir = 0; dir < 4; ++dir) {
            pii next = {now.first + dy[dir], now.second + dx[dir]};
            if (next.first < 0 || next.first >= N || next.second < 0 || next.second >= N) continue;
            if (!MAP[next.first][next.second]) continue;
            if (visited[next.first][next.second]) continue;
            visited[next.first][next.second] = true;
            cnt++;
            q.push(next);
            // cout << "pushed " << next.first << ", " << next.second << '\n';
        }
    }

    result.push_back(cnt);
}

int main() {
    cin >> N;

    for (int i = 0; i < N; ++i) {
        string str;
        cin >> str;
        for (int j = 0; j < N; ++j) {
            MAP[i][j] = str[j] - '0';
        }
    }

    // for (int i = 0; i < N; ++i) {
    //     for (int j = 0; j < N; ++j) {
    //         cout << MAP[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!MAP[i][j] || visited[i][j]) continue;
            // cout << "go from " << i << ", " << j << '\n';
            go(i, j);
        }
    }

    cout << result.size() << '\n';
    sort(result.begin(), result.end());
    for (int i : result) {
        cout << i << '\n';
    }
    return 0;
}