#include <iostream>
using namespace std;

int base[3][5] = {
    {0, 0, 1, 0, 0},
    {0, 1, 0, 1, 0},
    {1, 1, 1, 1, 1}
};

int go(int N, int y, int x) {
    if (N == 3) {
        return base[y][x];
    }

    if (y < N / 2) {
        if (N - 1 -y <= x && x <= N - 1 + y) {
            return go(N / 2, y, x - N / 2);
        }
        else {
            return 0;
        }
    }
    else {
        if (x < N - 1) {
            return go(N / 2, y - N / 2, x);
        }
        else {
            if (x == N - 1) return 0;
            else if (N - 1 < x) return go(N / 2, y - N / 2, x - N);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 2 * N - 1; ++j) {
            if (go(N, i, j)) cout << '*';
            else cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}