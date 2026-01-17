#include <iostream>
#include <algorithm>
using namespace std;

int board[2][100'001];
int dp[2][100'001];
int col;

int go(int y, int x) {
    if (x >= col) return 0;

    int& ret = dp[y][x];
    if (ret != -1) return ret;

    ret = board[y][x];
    ret += max(go((y + 1) % 2, x + 1), go((y + 1) % 2, x + 2));

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int ans = 0;
        fill(&dp[0][0], &dp[0][0] + 2 * 100'001, -1);

        cin >> col;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < col; ++j) {
                cin >> board[i][j];
            }
        }

        ans = max(go(0, 0), go(1, 0));
        cout << ans << '\n';
    }


    return 0;
}