#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int num, val;
};

int V;
vector<vector<Node>> v;
vector<int> dist;
vector<bool> visited;
queue<int> q;


Node bfs(int root) {
    fill(visited.begin(), visited.end(), false);
    Node node = {0, 0};
    dist[root] = 0;
    q.push(root);
    visited[root] = true;

    while (!q.empty()) {
        int now = q.front(); q.pop();
        // cout << "now : " << now << '\n';

        for (Node next : v[now]) {
            int to = next.num;
            int len = next.val;
            if (visited[to]) continue;

            dist[to] = dist[now] + len;
            q.push(to);
            visited[to] = true;

            if (dist[to] > node.val) {
                node.num = to;
                node.val = dist[to];
            }
        }
    }

    return node;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> V;
    v.resize(V + 1);
    dist.resize(V + 1);
    visited.resize(V + 1);

    for (int i = 0; i < V; ++i) {
        int num; cin >> num;

        int to;
        while (true) {
            cin >> to;
            if (to == -1) break;

            int val;
            cin >> val;

            v[num].push_back({to, val});
        }
    }

    Node far_node = bfs(1);
    Node far_node2 = bfs(far_node.num);

    cout << far_node2.val << '\n';

    return 0;
}