// 두 로봇
// 그냥 DFS 로 이어서
// 가면서 있었던 경로 중에서 가장 긴 놈을 빼면 답임

#include <iostream>
#include <vector>

int n, a, b, ans;
std::vector<std::vector<int>> adj;

void go() {
    
}

int main() {
    std::cin >> n >> a >> b;

    adj.resize(n, std::vector<int>(n, 0));

    for (int i = 0; i < n - 1; ++i) {
        int x, y, l;

        std::cin >> x >> y >> l;
        adj[x][y] = adj[y][x] = l;
    }

    go();

    return 0;
}