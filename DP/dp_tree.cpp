#include <iostream>
#include <algorithm>

int n, arr[501][501], dp[501][501];

void go() {
    for (int here = 1; here < n; ++here) {
        for (int i = 0; i <= here; ++i) {
            int diag_left = (i > 0) ? dp[here - 1][i - 1] : 0;
            int diag_right = (i < here) ? dp[here - 1][i] : 0;
    
            int& ret = dp[here][i];
            ret = arr[here][i] + std::max(diag_left, diag_right);
        }
    }
}

int main() {
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0 ; j <= i; ++j) {
            std::cin >> arr[i][j];
        }
    }

    dp[0][0] = arr[0][0];
    go();

    int result = 0;
    for (int i = 0; i < n; ++i) {
        result = std::max(result, dp[n - 1][i]);
    }

    std::cout << result << '\n';
    return 0;
}