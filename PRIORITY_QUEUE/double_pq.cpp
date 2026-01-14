#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int val, idx;
};

struct MaxCmp {
    bool operator()(const Node& a, const Node& b) const {
        if (a.val != b.val) return a.val < b.val;
        return a.idx < b.idx;
    }
};

struct MinCmp {
    bool operator()(const Node& a, const Node& b) const {
        if (a.val != b.val) return a.val > b.val;
        return a.idx > b.idx;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int k;
        cin >> k;

        vector<char> visited(k + 1, 0);

        priority_queue<Node, vector<Node>, MaxCmp> maxpq;
        priority_queue<Node, vector<Node>, MinCmp> minpq;

        int idx = 0;

        auto cleanMax = [&]() {
            while (!maxpq.empty() && visited[maxpq.top().idx]) maxpq.pop();
        };
        auto cleanMin = [&]() {
            while (!minpq.empty() && visited[minpq.top().idx]) minpq.pop();
        };

        for (int i = 0; i < k; ++i) {
            char op;
            int x;
            cin >> op >> x;

            if (op == 'I') {
                maxpq.push({x, idx});
                minpq.push({x, idx});
                idx++;
            } else {
                if (x == 1) {
                    cleanMax();
                    if (!maxpq.empty()) {
                        visited[maxpq.top().idx] = 1;
                        maxpq.pop();
                    }
                } else {
                    cleanMin();
                    if (!minpq.empty()) {
                        visited[minpq.top().idx] = 1;
                        minpq.pop();
                    }
                }
            }
        }

        cleanMax();
        cleanMin();

        if (maxpq.empty() || minpq.empty()) {
            cout << "EMPTY\n";
        } else {
            cout << maxpq.top().val << ' ' << minpq.top().val << '\n';
        }
    }

    return 0;
}