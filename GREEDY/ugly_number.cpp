#include <iostream>
#include <queue>
#include <algorithm>

long long ret[1501];

void go() {
  std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq;
  pq.push(1);
  int cnt = 1;

  while (cnt <= 1500) {
    long long now = pq.top(); 
    while (!pq.empty() && pq.top() == now) {
      pq.pop();
    }
    ret[cnt] = now;
    cnt++;

    pq.push(now * 2);
    pq.push(now * 3);
    pq.push(now * 5);
  }
}

int main() {
  int n;
  std::cin >> n;
  go();
  
  for (int i = 0; i < n; ++i) {
    int temp;
    std::cin >> temp;

    std::cout << ret[temp] << ' ';
  }
  std::cout << '\n';

  return 0;
}