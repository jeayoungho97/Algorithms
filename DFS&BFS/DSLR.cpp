#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int A, B;
        cin >> A >> B;

        vector<int> prev(10000, -1);
        vector<char> how(10000, 0);
        vector<bool> visited(10000, 0);

        queue<int> q;
        q.push(A);
        visited[A] = 1;

        while (!q.empty()) {
            int cur = q.front(); q.pop();
            if (cur == B) break;

            // D
            int nxt = (cur * 2) % 10000;
            if (!visited[nxt]) {
                visited[nxt] = 1;
                prev[nxt] = cur;
                how[nxt] = 'D';
                q.push(nxt);
            }

            // S
            nxt = (cur == 0 ? 9999 : cur - 1);
            if (!visited[nxt]) {
                visited[nxt] = 1;
                prev[nxt] = cur;
                how[nxt] = 'S';
                q.push(nxt);
            }

            // L
            nxt = (cur % 1000) * 10 + (cur / 1000);
            if (!visited[nxt]) {
                visited[nxt] = 1;
                prev[nxt] = cur;
                how[nxt] = 'L';
                q.push(nxt);
            }

            // R
            nxt = (cur / 10) + (cur % 10) * 1000;
            if (!visited[nxt]) {
                visited[nxt] = 1;
                prev[nxt] = cur;
                how[nxt] = 'R';
                q.push(nxt);
            }
        }

        string ans;
        for (int x = B; x != A; x = prev[x]) ans.push_back(how[x]);
        reverse(ans.begin(), ans.end());
        cout << ans << '\n';
    }


    return 0;
}