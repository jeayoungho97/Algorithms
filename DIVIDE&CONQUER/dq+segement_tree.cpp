#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;

vector<pair<ll, int>> minSeg; // {minVal, minIdx}
const ll llMAX = 1e18;
const int intMAX = 1e9;
int n, Size;

ll findMax(int left, int right) {
  // 최솟값 찾기
  if (left == right) return minSeg[left].first;

  int start_idx = left;
  int end_idx = right;

  pair<ll, int> min = {llMAX, intMAX};
  while (start_idx <= end_idx) {
    if ((start_idx & 1)) min = std::min(min, minSeg[start_idx]);
    if ((end_idx & 1) == 0) min = std::min(min, minSeg[end_idx]);

    start_idx = (start_idx + 1) / 2;
    end_idx = (end_idx - 1)/ 2;
  }
  int mid = min.second;
  ll ret;
  if (mid == left) {
    ret = std::max(min.first * (right - left + 1), findMax(mid + 1, right));
  }
  else if (mid == right) {
    ret = std::max(min.first * (right - left + 1), findMax(left, mid - 1));
  }
  else {
    ret = std::max(findMax(left, mid - 1), findMax(mid + 1, right));
    ret = std::max(ret, min.first * (right - left + 1));
  }

  return ret;
}

int main() {
  while (true) {
    // init()
    minSeg.clear();

    // input
    cin >> n;
    if (n == 0) break;

    Size = 1;
    while (Size < n) {
      Size *= 2;
    }
    Size *= 2;
    // 최솟값을 담는 세그먼트 트리
    minSeg.resize(Size, {llMAX, 0});
    for (int i = Size / 2; i < Size / 2 + n; ++i) {
      ll temp;
      cin >> temp;
      minSeg[i] = {temp, i};
    }
    for (int i = Size - 1; i >= 2; i -= 2) minSeg[i / 2] = std::min(minSeg[i], minSeg[i - 1]);

    // 분할정복
    cout <<  findMax(Size / 2, Size / 2 + n - 1) << '\n';
  }


  return 0;
}