#include <iostream>
#include <vector>
#include <cmath>

std::vector<long long> arr;
std::pair<int, int> ans;

long long minVal = 1e18;

int main() {
  int n;
  std::cin >> n;

  for (long long i = 0; i < n; ++i) {
    long long num;
    std::cin >> num;
    arr.push_back(num);
  }

  int start = 0, end = n - 1;

  while (start < end) {
    long long temp = arr[start] + arr[end];
    if (std::abs(minVal) > std::abs(temp)) {
      ans = {arr[start], arr[end]};
      minVal = temp;
    }

    if (temp > 0) {
      end--;
    }
    else if (temp < 0) {
      start++;
    }
    else {
      break;
    }
  }

  std::cout << ans.first << ' ' << ans.second << '\n';
  return 0;
}