#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

struct NODE {
  int cost, customer;
};
int C, N;
NODE arr[21];
int dp[1001]; // dp 값에는 각각의 값을 갖기 위한 최소 비용을 저장

int go(int now) {
  if (now <= 0) return 0;

  int &ret = dp[now];
  if (ret != -1) return ret;


  ret = 1e9;
  for (int i = 0; i < N; ++i) {
    int next = now - arr[i].customer;
    ret = min(ret, arr[i].cost + go(next));
  }

  return ret;
}

int main() {
  cin >> C >> N;

  for (int i = 0; i < N; ++i) {
    int cost, customer;
    cin >> cost >> customer;
    arr[i] = {cost, customer};
  }  

  memset(dp, -1, sizeof(dp));

  cout << go(C) << '\n';

  return 0;
}