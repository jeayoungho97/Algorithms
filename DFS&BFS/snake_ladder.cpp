#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int num, val;
};

int N, M;
int adj[101];
Node MAP[101];

int main() {
    // queue 에 넣는다. 이 때, 몇 번의 순서로 그 칸에 도착했는지의 정보도 같이 넣는다.
    // 또 순서를 해당 칸의 최소 도착 순서와 비교한다.
    // 나중에 큐에서 뺄 때 lazy 하게 비교한다. 
    // 최종적으로 100번 칸의 최소 순서를 뽑는다.
    cin >> N >> M;
    for (int i = 0; i < N + M; ++i) {
        int from, to;
        cin >> from >> to;
        adj[from] = to;
    }

    for (int i = 0; i <= 100; ++i) {
        MAP[i].val = 1e9;
    }

    queue<Node> q;
    q.push({1, 0});

    while (!q.empty()) {
        Node now = q.front(); q.pop();
        if (now.val >= MAP[now.num].val) continue;
        MAP[now.num].val = now.val;

        int x = now.num;
        for (int i = 1; i <= 6; ++i) {
            int nx = x + i;
            int nval = now.val + 1;
            if (nx > 100) continue;
            if (adj[nx]) nx = adj[nx];
            q.push({nx, nval});
        }
    }

    cout << MAP[100].val << '\n';

    return 0;
}