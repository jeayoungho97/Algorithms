#include <iostream>
#include <string>
using namespace std;

bool col[9][10] = {0};
bool row[9][10] = {0};
bool sec[9][10] = {0};
int map[9][9];


int findSector(int i, int j) {
  if (i < 3) {
    if (j < 3) {
      return 0;
    }
    else if (j < 6) {
      return 1;
    }
    else {
      return 2;
    }
  }
  else if (i < 6) {
    if (j < 3) {
      return 3;
    }
    else if (j < 6) {
      return 4;
    }
    else {
      return 5;
    }
  }
  else {
    if (j < 3) {
      return 6;
    }
    else if (j < 6) {
      return 7;
    }
    else {
      return 8;
    }
  }
}

void markNumber(int i, int j, bool mark) {
  row[i][map[i][j]] = mark;
  col[j][map[i][j]] = mark;
  sec[findSector(i, j)][map[i][j]] = mark;
}

bool go(int idx) {
  if (idx > 80) return true;
  // 조사했는데 아무것도 들어갈 수 없으면 return false;
  // 들어가도 괜찮으면 return true; => false 면 다음거 확인하고 true 면 확인 안함
  int i = idx / 9;
  int j = idx % 9;
  
  if (!map[i][j]) {
    for (int num = 1; num <= 9; ++num) {
      if (!row[i][num] && !col[j][num] && !sec[findSector(i, j)][num]) {
        map[i][j] = num;
        markNumber(i, j, true);

        if (!go(idx + 1)) {
          markNumber(i, j, false);
          map[i][j] = 0;
        }
        else {
          return true;
        }
      }
    }
    
    return false;
  }
  else {
    return go(idx + 1);
  }
}

int main() {
  // 각각의 행, 열에 1 ~ 9 숫자가 있는지 확인하는 2차원 배열 => col[3][4] = true 3열에 4라는 것이 있다
  // 9개의 구역에 대해서도 마찬가지
  // why? => 매번 조회하며 찾는 건 비용이 많이 듬
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      char temp;
      cin >> temp;
      map[i][j] = temp - '0';
      if (map[i][j]) markNumber(i, j, true);
    }
  }

  go(0);

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      cout << map[i][j]; 
    }
    cout << '\n';
  }

  return 0;
}