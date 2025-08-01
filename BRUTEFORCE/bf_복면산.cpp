#include <iostream>
#include <vector>
#include <string>

std::string str1, str2, str3;
std::vector<int> arr(26);
std::vector<int> used_char;
std::vector<int> list;
std::vector<bool> visited(10, false);
int table[26];
bool flag = false;

void calculate()
{
  long long num1 = 0, num2 = 0, num3 = 0;

  for (int i = 0; i < used_char.size(); ++i)
  {
    table[used_char[i]] = list[i];
  }

  for (char ch : str1) {
    num1 = num1 * 10 + table[ch - 'A'];
  }
  for (char ch : str2) {
    num2 = num2 * 10 + table[ch - 'A'];
  }
  for (char ch : str3) {
    num3 = num3 * 10 + table[ch - 'A'];
  }

  if (num1 + num2 == num3)
  {
    flag = true;
  }
}

void func()
{
  if (flag)
    return;
  if (list.size() == used_char.size())
  {
    calculate();
    return;
  }

  for (int i = 0; i < 10; ++i)
  {
    if (visited[i])
      continue;
    list.push_back(i);
    visited[i] = true;
    func();
    visited[i] = false;
    list.pop_back();
    if (flag) return;
  }
}

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> str1 >> str2 >> str3;

  for (char ch : str1)
    arr[ch - 'A'] = 1;
  for (char ch : str2)
    arr[ch - 'A'] = 1;
  for (char ch : str3)
    arr[ch - 'A'] = 1;

  // 쓰인 알파벳을 used_char 에 담음
  for (int i = 0; i < 26; ++i)
  {
    if (arr[i])
    {
      used_char.push_back(i);
    }
  }

  if (used_char.size() > 10)
  {
    std::cout << "NO\n";
    return 0;
  }

  func();

  if (flag)
    std::cout << "YES\n";
  else
    std::cout << "NO\n";

  return 0;
}