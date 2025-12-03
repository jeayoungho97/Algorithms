// BOJ 7785 회사에 있는 사람
// set version

#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    set<string> cur;

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

    // set 은 자동으로 오름차순 정렬이 됨
    // 역순으로 하기 위해 내림차순으로 순회
    for (auto it = cur.rbegin(); it != cur.rend(); ++it) {
        // set 은 iterator 의 값을 * 로 뽑아옴
        cout << *it << '\n';
    }

    return 0;
}