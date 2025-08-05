// 핵심 아이디어 
// -   col[n] = n 번째 열 visited 유무
// - diag1[n] = 행과 열의 합이 n 이 되는 대각선의 visited 유무
// - diag2[n] = 행 - 열이 n 이 되는 대각선의 visited 유무

#include <iostream>
int n, cnt;

bool column[15], diag1[30], diag2[30];

void solve(int row) {
  
  for (int col = 0; col < n; ++col) {
    if (column[col] || diag1[row + col] || diag2[(n - 1) + (row - col)]) continue;

    if (row == n - 1) {
      cnt++;
      continue;
    }

    column[col] = true;
    diag1[row + col] = true;
    diag2[(n - 1) + (row - col)] = true;

    solve(row + 1);

    column[col] = false;
    diag1[row + col] = false;
    diag2[(n - 1) + (row - col)] = false;
  }



}

int main() {
  std::cin >> n;

  solve(0);

  std::cout << cnt << '\n';

  return 0;
}