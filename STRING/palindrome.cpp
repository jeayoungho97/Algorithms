#include <iostream>
#include <string>
using namespace std;

int cnt;

// 함수 호출 시에 call by reference 로 안하고 call by value 로 하면 시간초과 발생 (복사 비용 매우 큼)
int recursion(const string &s, int l, int r) {
  cnt++;
  if (l >= r) return 1;
  else if (s[l] != s[r])  return 0;
  else return recursion(s, l + 1, r - 1);
}

int isPalindrome(const string &s) {
  return recursion(s, 0, s.length() - 1);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    string str;
    cin >> str;
    cnt = 0;

    cout << isPalindrome(str) << ' ' << cnt << '\n';
  }


  return 0;
}