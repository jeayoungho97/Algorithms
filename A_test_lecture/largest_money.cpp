#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string s;  // 원본 문자열
string answer; // 정답 저장용
int times; // 교환횟수
int ans;
bool found_ans;

void init() {
    ans = 0;
    found_ans = false;
}

void input() {
    cin >> s >> times;

    // 입력받은 문자열 중에서 생성할 수 있는 최댓값을 미리 저장해둔다 -> 기저조건이 됨.
    answer = s;
    sort(answer.begin(), answer.end(), greater<>());
}

void dfs(string str, int cnt) {
    if (found_ans) return;
    // 1. 기저조건
    if (cnt == times) {
        ans = max(ans, stoi(str));
        return;
    }

    if (str == answer) {
        if ((times - cnt) % 2 == 0) {
            // 짝수번 남았으므로 정답은 최댓값 그대로
            ans = stoi(answer);
        }

        if ((times - cnt) % 2 == 1) {
            // 홀수번 남았으므로 또 15번 한 번 돌려봄
            for (int i = 0; i < str.size(); ++i) {
                for (int j = i + 1; j < str.size(); ++j) {
                    swap(str[i], str[j]);
                    ans = max(ans, stoi(str));
                    swap(str[i], str[j]);
                }
            }  
        }

        // 홀수 번 남았을 때 ans 가 된다면.. 짝수 번 남았을 때 또 ans 가 될 순 없나? 흠...
        found_ans = true;
        return;
    }

    // 2. 재귀조건
    for (int i = 0; i < str.size(); ++i) {
        for (int j = i + 1; j < str.size(); ++j) {
            if (found_ans) return;
            swap(str[i], str[j]);
            dfs(str, cnt + 1);
            swap(str[i], str[j]);
        }
    }
}

void solve() {
    dfs(s, 0); // 교환된 문자열, 몇번째 교환인지
}

int main() {
    // 작은 수, 작은 교환 횟수는 그냥 완전 탐색으로 가능
    // 큰 수, 큰 교환 횟수는 5~6번이면 모든 교환 가능 -> 이후엔 교환 횟수 - 최댓값을 만들기 위한 교환 횟수가 짝수가 되면 best 짝수가 안나오면 1, 2 자리수만 변경
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        init();
        input();
        solve();

        cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}