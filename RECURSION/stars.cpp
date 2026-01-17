#include <iostream>
using namespace std;

int go(int row, int col, int size) {
  int unit = size / 3;
  if (size == 1) return 1;
  if (row / unit == 1 && col / unit == 1) return 0;
  else return go(row % unit, col % unit, unit);
}

int main() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (go(i, j, N)) cout << '*';
      else cout << ' ';
    }
    cout << '\n';
  }
  return 0;
}