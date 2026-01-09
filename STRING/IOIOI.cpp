#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int N, M, ans;
int IOI[1000001];
string S;

int main() {
    cin >> N >> M;
    cin >> S;

    for (int i = 2; i <= M; ++i) {
        if (S[i - 2] == 'I' && S[i - 1] == 'O' && S[i] == 'I') {
            IOI[i] = IOI[i - 2] + 1;
        }
        if (IOI[i] >= N) ans++;
    }

    cout << ans << '\n';

    return 0;
}