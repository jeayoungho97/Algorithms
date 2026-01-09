#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int N;
bool ans[101][101];
bool adj[101][101];
bool visited[101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> adj[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        fill(visited, visited + N, false);
        queue<int> q;
        q.push(i);

        while (!q.empty()) {
            int now = q.front(); q.pop();
            for (int j = 0; j < N; ++j) {
                if (!visited[j] && adj[now][j]) {
                    visited[j] = 1;
                    q.push(j);
                    ans[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}