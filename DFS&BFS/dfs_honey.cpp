#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

int n, m, c, ans;
int honey[10][10];
int square_sum[10][10];
std::vector<int> to_sum;

void init()
{
    ans = 0;
    std::fill(&honey[0][0], &honey[0][0] + 10 * 10, 0);
    std::fill(&square_sum[0][0], &square_sum[0][0] + 10 * 10, 0);
}

void getInput()
{
    std::cin >> n >> m >> c;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cin >> honey[i][j];
        }
    }
}

int dfs(int here, int sum) {
    if (sum > c) return 0;

    int ret = 0;
    for (int i = here + 1; i < to_sum.size(); ++i) {
        ret = std::max(ret, dfs(i, sum + to_sum[i]));
    }

    return ret + to_sum[here] * to_sum[here];
}

void go(int y, int x)
{
    for (int i = x; i < x + m; ++i) {
        to_sum.push_back(honey[y][i]);
    }
    std::sort(to_sum.begin(), to_sum.end());

    int &sum = square_sum[y][x];
    for (int i = 0; i < to_sum.size(); ++i) {
        sum = std::max(sum, dfs(i, to_sum[i]));
    }
}

void setSquareSum()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= n - m; ++j)
        {
            to_sum.clear();
            go(i, j);
        }
    }
}

void checkSquareSum() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << square_sum[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void findMax() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!square_sum[i][j]) continue;
            int temp = square_sum[i][j];
            for (int k = i; k < n; ++k) {
                for (int l = 0; l < n; ++l) {
                    if (!square_sum[k][l]) continue;
                    if (k == i && l < j + m) continue;
                    
                    ans = std::max(ans, temp + square_sum[k][l]);
                }
            }
        }
    }
}

void solve()
{
    setSquareSum();

    // checkSquareSum();

    findMax();
}

int main()
{
    int t;
    std::cin >> t;

    for (int tc = 1; tc <= t; ++tc)
    {
        // init
        init();

        // input
        getInput();

        // solve
        solve();

        std::cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}