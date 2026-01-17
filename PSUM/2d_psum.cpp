#include <iostream>
using namespace std;

int N, M;
int psum[1026][1026];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            long long x;
            cin >> x;
            psum[i][j] = x
                        + psum[i - 1][j]
                        + psum[i][j - 1]
                        - psum[i - 1][j - 1];
        }
    }

    while (M--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        long long ans = psum[x2][y2]
                        - psum[x1 - 1][y2]
                        - psum[x2][y1 - 1]
                        + psum[x1 - 1][y1 - 1];

        cout << ans << '\n';
    }
 
    return 0;
}