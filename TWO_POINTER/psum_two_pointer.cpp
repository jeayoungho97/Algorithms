#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100004;
int N, S, ans = MAX;
long long arr[MAX];

int main() {
  cin >> N >> S;

  for (int i = 0; i < N; ++i) {
    cin >> arr[i];
  }

  int start = 0, end = 0;
  long long sum = arr[0];

  while (true) {
    if (sum < S) {
      end++;
      if (end == N) {
        break;
      }

      sum += arr[end];
    }
    else {
      ans = min(ans, end - start + 1);

      sum -= arr[start];

      start++;

      if (start > end) {
        cout << 1 << '\n';
        return 0;
      }
    }
  }

  if (ans == MAX) cout << 0 << '\n';
  else cout << ans << '\n';

  return 0;
}