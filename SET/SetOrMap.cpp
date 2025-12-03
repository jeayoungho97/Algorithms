// BOJ 7785 회사에 있는 사람
// map version

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    map<string, bool> mp;

    for (int i = 0; i < n; ++i) {
        string str, buf;
        cin >> str >> buf;

        if (buf == "enter") {
            mp[str] = 1;
        }
        else {
            mp[str] = 0;
        }
    }

    for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
        if (it -> second) {
            cout << it->first << '\n';
        }
    }

    return 0;
}