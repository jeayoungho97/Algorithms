#include <iostream>
#include <vector>

struct ABC
{
  int num;
  char ch;

  bool operator<(ABC right)
  {
    if (num != right.num)
    {
      return num < right.num;
    }
    else
    {
      return ch < right.ch;
    }
  }
};

int main()
{
  int n;
  std::cin >> n;

  std::vector<ABC> arr(n);

  for (int i = 0; i < n; ++i)
  {
    std::cin >> arr[i].num >> arr[i].ch;
  }

  for (int i = 0; i < n; ++i)
  {
    if (i > 0)
    {
      ABC temp = arr[i];
      int idx = -1;
      for (int j = 0; j < i; ++j)
      {
        if (arr[i] < arr[j])
        {
          idx = j;
          break;
        }
      }
      if (idx == -1) idx = i; // 이 조건을 안 넣어서... 기존 자리를 고수해야할 경우가 체크가 안됨.

      for (int j = i - 1; j >= idx; --j)
      {
        arr[j + 1] = arr[j];
      }
      arr[idx] = temp;
    }
  }

  for (ABC a : arr)
  {
    std::cout << a.num << ' ' << a.ch << '\n';
  }
  return 0;
}