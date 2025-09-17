#include <iostream>
using namespace std;

int N, M;
int arr[2001];
int isPal[2001][2001] = {0}; // 0: unvisited, 1: true, 2: false

int checkPal(int start, int end) {
  // Memoization
  int& ret = isPal[start][end];

  if (ret) return ret;

  if (arr[start] != arr[end]) {
    return ret = 2;
  }
  else {
    if (start + 1 >= end - 1) {
      return ret = 1;
    }
    return ret = checkPal(start + 1, end - 1);
  }
}

int main() {
  // 메모이제이션을 이용해서 하면 될 듯?
  // s, e => s == e 인지 확인 후 isPal[s + 1][e - 1] = true 인지 확인
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> arr[i];
  }
  cin >> M;
  for (int i = 0; i < M; ++i) {
    int s, e;
    cin >> s >> e;
    if (checkPal(s, e) == 1) cout << 1 << '\n';
    else cout << 0 << '\n';
  }

  return 0;
}