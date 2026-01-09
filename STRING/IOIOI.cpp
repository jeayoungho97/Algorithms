#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int N, M, MAX, ans;
int IOI[1000001];
string S;

int main() {
    cin >> N >> M;
    cin >> S;

    bool started = false;
    char prev = 'S';
    int cnt = 0;

    for (int i = 0; i < M; ++i) {
        char ch = S[i];
        if (!started && ch =='I') {
            started = true;
            cnt = 0;
        }
        else if (started && prev == 'I') {
            if (ch == 'I') {
                MAX = max(MAX, cnt);
                IOI[cnt]++;
                cnt = 0;
            }
        }
        else if (started && prev == 'O') {
            if (ch == 'I') {
                cnt++;
            }
            if (ch == 'O') {
                MAX = max(MAX, cnt);
                IOI[cnt]++;
                started = false;
            }
        }

        prev = ch;
    }

    MAX = max(MAX, cnt);
    IOI[cnt]++;

    for (int i = N; i <= MAX; ++i) {
        ans += IOI[i] * (i -N + 1);
    }

    cout << ans << '\n';

    return 0;
}