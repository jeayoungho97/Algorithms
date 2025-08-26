#include <iostream>
#include <vector>
#define ll long long
using namespace std;

int main() {
  int n, m, q;
  cin >> n >> m >> q;

  int size = 1;
  for (int i = 0; i < 64; ++i) {
    if (size >= n) break;
    size *= 2;
  }
  size *= 2;

  vector<ll> seg(size, 0);

  for (int i = 0; i < n; ++i) {
    int idx = size / 2 + i;
    cin >> seg[idx];
  }

  for (int i = size - 1; i >= 2; --i) {
    seg[i / 2] += seg[i];
  }

  for (int i = 0 ; i < m + q; ++i) {
    int a;
    cin >> a;
    if (a == 1) {
      int b;
      ll c;
      cin >> b >> c;
      int idx = size / 2 + b - 1;
      ll diff = c - seg[idx];

      while (idx != 0) {
        seg[idx] += diff;
        idx /= 2;
      }

      // for (ll i : seg) cout << i << ' ';
      // cout << '\n';
    }
    else if (a == 2) {
      int b, c;
      cin >> b >> c;
      int start_idx = size / 2 + b - 1;
      int end_idx = size / 2 + c - 1;
      ll sum = 0;

      while (start_idx <= end_idx) {
        if (start_idx & 1) sum += seg[start_idx];
        if (!(end_idx & 1)) sum += seg[end_idx];

        start_idx = (start_idx + 1) / 2;
        end_idx = (end_idx - 1) / 2;
      }

      cout << sum << '\n';
    }
  }

  return 0;
}