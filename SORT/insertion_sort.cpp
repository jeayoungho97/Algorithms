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

// Another Example

#include <iostream>
#include <vector>
#include <string>

struct athlete{
  std::string name;
  int point;
};

int main() {
  int n;
  std::cin >> n;
  std::vector<athlete> result;

  for (int i = 0; i < n; ++i) {
    athlete here;
    std::cin >> here.name >> here.point;

    if (!result.empty()) {
      int size = result.size();
      result.push_back(here);
      int idx = -1;

      for (int j = 0; j < size; ++j) {
        if (here.point >= result[j].point) {
          idx = j;
          
          for (int k = size - 1; k >= idx; --k) {
            result[k + 1] = result[k];
          }

          result[idx] = here;
          break;
        }
      }

      if (result.size() == 4) {
        result.pop_back();
      }
    }
    else {
      result.push_back(here);
    }

    for (athlete a : result) {
      std::cout << a.name << ' ';
    }
    std::cout << '\n';
  }



  return 0;
}