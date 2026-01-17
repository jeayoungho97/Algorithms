#include <iostream>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int k;
        cin >> k;

        multiset<int> ms;

        for (int i = 0; i < k; ++i) {
            char op;
            int x;
            cin >> op >> x;

            if (op == 'I') {
                ms.insert(x);
            }
            else {
                if (ms.empty()) continue;

                if (x == 1) {
                    auto it = prev(ms.end());
                    ms.erase(it);
                }
                else {
                    auto it = ms.begin();
                    ms.erase(it);
                }
            }
        }

        if (ms.empty()) {
            cout << "EMPTY\n";
        }
        else {
            cout << *prev(ms.end()) << ' ' << *ms.begin() << '\n';
        }

    }

    return 0;
}