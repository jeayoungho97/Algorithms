#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    long long num, idx;

    bool operator<(const Node& rhs) const {
        if (num == rhs.num) return idx < rhs.idx;
        return num < rhs.num;
    }
};

bool visited[1000001];

priority_queue<Node> pq;
priority_queue<Node> rpq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        fill(visited, visited + 1000001, false);
        while (!pq.empty()) pq.pop();
        while (!rpq.empty()) rpq.pop();

        int num, cnt = 0;
        cin >> num;
        for (int i = 0; i < num; ++i) {
            char ch; long long val;
            cin >> ch >> val;

            if (ch == 'I') {
                pq.push({val, cnt});
                rpq.push({-val, cnt});
                cnt++;
            }
            else {
                if (val == 1) {
                    while (!pq.empty() && visited[pq.top().idx]) pq.pop();
                    if (!pq.empty()) {
                        visited[pq.top().idx] = true;
                        pq.pop();
                    }
                }
                
                if (val == -1) {
                    while (!rpq.empty() && visited[rpq.top().idx]) rpq.pop();
                    if (!rpq.empty()) {
                        visited[rpq.top().idx] = true;
                        rpq.pop();
                    }
                }
            }
        }
        while (!pq.empty() && visited[pq.top().idx]) pq.pop();
        while (!rpq.empty() && visited[rpq.top().idx]) rpq.pop();

        if (pq.empty() || rpq.empty()) cout << "EMPTY\n";
        else {
            cout << pq.top().num << ' ' << -(rpq.top().num) << '\n';
        }
    }


    return 0;
}