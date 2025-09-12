#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

struct NODE {
    int idx;
    long long height;
};

int N;
long long ans = 0;

int main() {
    cin >> N;

    stack<NODE> stk;
    stk.push({0, 0});
    for (int i = 1; i <= N; ++i) {
        long long h;
        cin >> h;

        while(!stk.empty()) {
            NODE now = stk.top();
            if (now.height > h) {
                stk.pop();
                ans = max(ans, now.height * ((i - 1) - stk.top().idx));
            }
            else break;
        }

        stk.push({i, h});
    }

    while(!stk.empty()) {
        NODE now = stk.top(); stk.pop();
        if (now.idx == 0) break;
        ans = max(ans, now.height * (N - stk.top().idx));
    }

    cout << ans << '\n';

    return 0;
}