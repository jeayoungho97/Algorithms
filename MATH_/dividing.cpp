#include <iostream>
#include <algorithm>
using namespace std;

int N, MAX;
int number[100001]; // 각 플레이어의 숫자
bool have[1000001]; // 해당 숫자가 존재하는지
int ans[1000001];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> number[i];
    have[number[i]] = true;
    MAX = max(MAX, number[i]);
  }

  for (int i = 1; i <= MAX; ++i) {
    if (!have[i]) continue;

    int cnt = 1;
    int num = 0;
    while (true) {
      cnt++;
      num = i * cnt;
      if (num > MAX) break;
      if (!have[num]) continue;
      ans[i]++;
      ans[num]--;
    }
  }

  for (int i = 0; i < N; ++i) {
    cout << ans[number[i]] << ' ';
  }
  cout << '\n';

  return 0;
}