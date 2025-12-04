// BOJ 7785 회사에 있는 사람
// set version

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    unordered_set<string> cur;

    for (int i = 0; i < n; ++i) {
        string name, action;
        cin >> name >> action;

        if (action == "enter") {
            cur.insert(name);
        }
        else {
            cur.erase(name);
        }
    }

    vector<string> result(cur.begin(), cur.end());
    sort(result.begin(), result.end(), greater<string>());

    for (const auto& name : result) {
        cout << name << '\n';
    }
    return 0;
}