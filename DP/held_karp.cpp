#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    vector<vector<int>> w(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cin >> w[i][j];

    const int INF = 1e9;
    int FULL = 1 << n;
    vector<vector<int>> dp(FULL, vector<int>(n, INF));
    dp[1<<0][0] = 0; // 시작: 0만 방문

    for (int mask = 0; mask < FULL; ++mask) {
        for (int u = 0; u < n; ++u) if (dp[mask][u] < INF) {
            for (int v = 0; v < n; ++v) {
                if (mask & (1<<v)) continue;
                if (w[u][v] == 0) continue;
                int nmask = mask | (1<<v);
                dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + w[u][v]);
            }
        }
    }

    int ans = INF;
    for (int u = 0; u < n; ++u) if (dp[FULL-1][u] < INF && w[u][0] != 0)
        ans = min(ans, dp[FULL-1][u] + w[u][0]);
    cout << ans << '\n';
}
