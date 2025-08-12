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
    // 만약 sum > c 인 곳까지 갔다면? 그 전 과정의 결과는 0 + 해당 값의 제곱 이 됨.
    // 또 그 전 과정의 결과는 해당 값의 제곱이 더해짐.
    // 결과적으로 here 부터 시작해서 sum > c 되기 직전까지의 값들이 다 제곱해서 더해진 것 중에서 최댓값이 dfs(i, to_sum[i]) 의 결과가 됨! WOW!
    if (sum > c) return 0;

    int ret = 0;
    for (int i = here + 1; i < to_sum.size(); ++i) {
        // 여기서 계속 최댓값 확인 및 갱신
        ret = std::max(ret, dfs(i, sum + to_sum[i]));
    }

    return ret + to_sum[here] * to_sum[here];
}

// square_sum[i][j] 를 채우는 과정
void go(int y, int x)
{
    // to_sum = {honey[y][x], honey[y][x + 1], honey[y][x + 2], ... , honey[y][x + m - 1]}; (즉 꿀이 (y,x) 부터 오른쪽으로 m 개 만큼 담김
    for (int i = x; i < x + m; ++i) {
        to_sum.push_back(honey[y][i]);
    }

    // 정렬은 사실 가지치기를 하려고 했는데.. 지금 보니까 굳이 할 필요 없는듯?
    std::sort(to_sum.begin(), to_sum.end());

    // sum 으로 square_sum 의 original 값 자체를 바꿔가고 싶음 => 그래서 & 사용
    int &sum = square_sum[y][x];
    for (int i = 0; i < to_sum.size(); ++i) {
        // i 부터 시작해서 to_sum 의 끝까지 dfs 를 돌리면서 모든 경우의 수 고려함
        sum = std::max(sum, dfs(i, to_sum[i]));
    }
}

// square_sum 배열을 채우는 함수 => go(i, j) 를 호출하면 square_sum[i][j] 가 채워짐
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