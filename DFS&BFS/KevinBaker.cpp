#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int ans = 1e9;
int ans_num = -1;

vector<int> adj[101];
int visited[101];

void BFS(int root) {
    queue<int> q;
    q.push(root);
    int sum = 0;

    while (!q.empty()) {
        int here = q.front(); q.pop();
        for (int there : adj[here]) {
            if (visited[there] != -1) continue;
            q.push(there);
            visited[there] = visited[here] + 1;
            sum += visited[there];
        }
    }

    if (ans > sum) {
        ans = sum;
        ans_num = root;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= N; ++i) {
        // visited 초기화
        fill(visited, visited + 101, -1);
        visited[i] = 0;
        BFS(i);
    }

    cout << ans_num << '\n';
    return 0;
}   