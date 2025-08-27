#include <iostream>
#include <queue>

using namespace std;

int ans;
int n;

int main() {
    // Greedy
    // 작은 숫자로 정렬한 다음에 그냥 가장 가까운 모자를 우선적으로 쓰면 안되나?
    // 되네?

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        ans = 0;
        cin >> n;

        priority_queue<int, vector<int>, greater<int>> people;
        for (int i = 0; i < n; ++i) {
            int temp;
            cin >> temp;
            people.push(temp);
        }

        priority_queue<int, vector<int>, greater<int>> hats;
        for (int i = 0 ; i < n; ++i) {
            int temp;
            cin >> temp;
            hats.push(temp);
        }

        while (!people.empty() && !hats.empty()) {
            int cur_person = people.top();
            int cur_hat = hats.top();

            if (cur_hat < cur_person - 3) hats.pop();
            else if (abs(cur_hat - cur_person) <= 3) {
                ans++;
                hats.pop();
                people.pop();
            }
            else people.pop();
        }

        cout << '#' << tc << ' ' << ans << '\n';
    }


    return 0;
}