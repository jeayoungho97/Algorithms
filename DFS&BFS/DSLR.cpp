#include <iostream>
#include <cstring>
using namespace std;

static int prevv[10000];
static char how[10000];
static int vis[10000];
static int stamp = 1;

static int q[10000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int A, B;
        cin >> A >> B;

        int head = 0, tail = 0;
        q[tail++] = A;

        stamp++;
        if (stamp == INT_MAX) { // 혹시 모를 오버플로 방지(실제로는 거의 안 옴)
            memset(vis, 0, sizeof(vis));
            stamp = 1;
        }

        vis[A] = stamp;
        prevv[A] = -1;

        while (head < tail) {
            int cur = q[head++];
            if (cur == B) break;

            // D
            int nxt = (cur << 1) % 10000;
            if (vis[nxt] != stamp) {
                vis[nxt] = stamp;
                prevv[nxt] = cur;
                how[nxt] = 'D';
                q[tail++] = nxt;
            }

            // S
            nxt = (cur == 0) ? 9999 : (cur - 1);
            if (vis[nxt] != stamp) {
                vis[nxt] = stamp;
                prevv[nxt] = cur;
                how[nxt] = 'S';
                q[tail++] = nxt;
            }

            // L
            nxt = (cur % 1000) * 10 + (cur / 1000);
            if (vis[nxt] != stamp) {
                vis[nxt] = stamp;
                prevv[nxt] = cur;
                how[nxt] = 'L';
                q[tail++] = nxt;
            }

            // R
            nxt = (cur / 10) + (cur % 10) * 1000;
            if (vis[nxt] != stamp) {
                vis[nxt] = stamp;
                prevv[nxt] = cur;
                how[nxt] = 'R';
                q[tail++] = nxt;
            }
        }

        // 역추적: B -> A
        char out[10000];
        int len = 0;
        for (int x = B; x != A; x = prevv[x]) {
            out[len++] = how[x];
        }
        // 뒤집어서 출력
        for (int i = len - 1; i >= 0; --i) cout << out[i];
        cout << '\n';
    }

    return 0;
}
