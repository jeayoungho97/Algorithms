#include <iostream>
#include <algorithm>
using namespace std;

int n, p;
int dp[21][2];
int growth[2][21];
int go(int here, int fert) {
    if (here == n) return 0;

    int& ret = dp[here][fert];
    if (ret != -1) return ret;

    ret = growth[fert][here];
    int same_fert = max(go(here + 1, fert) - p, 0);
    int diff_fert = go(here + 1, fert ^ 1);
    ret += max(same_fert, diff_fert);

    return ret;
}

int main() {
    // dp 냄새가 솔솔 나는데?
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        cin >> n >> p;

        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> growth[i][j];
            }
        }

        // dp[1][0] -> 1번 화분에 0번 비료를 줬을 경우 식물 높이 합의 최댓값
        fill(&dp[0][0], &dp[0][0] + 21 * 2, -1);
        
        int ans = max(go(0, 0), go(0, 1));

        cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}