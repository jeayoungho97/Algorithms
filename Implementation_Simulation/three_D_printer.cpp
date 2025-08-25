#include <iostream>
#include <queue>
#include <algorithm>

long long ans;

struct NODE
{
  long long est, print;
  int order;
  bool operator<(const NODE &r) const
  {
    return est > r.est;
  }
};

struct cmp
{
  bool operator()(const NODE &l, const NODE &r) const
  {
    return l.order > r.order;
  }
};

int main()
{
  int n;
  std::cin >> n;
  std::queue<NODE> q;
  std::priority_queue<NODE> pq_est; // 출력 요청 예정 시간이 빠른 순

  for (int i = 1; i <= n; ++i)
  {
    long long est, print;
    std::cin >> est >> print;

    pq_est.push({est, print, i});
  }

  std::priority_queue<NODE, std::vector<NODE>, cmp> pq_order; // 우선수위가 빠른 순, 대기열
  pq_order.push(pq_est.top());
  pq_est.pop();
  long long finish_time = pq_order.top().est;
  
  while (!pq_est.empty() && !pq_order.empty())
  {
    NODE now = pq_order.top(); pq_order.pop();
    ans = std::max(ans, finish_time - now.est);
    finish_time += now.print;

    while (!pq_est.empty() && finish_time > pq_est.top().est) {
      pq_order.push(pq_est.top()); pq_est.pop();
    }

    if (pq_order.empty() && !pq_est.empty()) {
      // 대기열이 없는 경우 억지로 하나 끌고 와야함
      NODE here = pq_est.top();
      pq_order.push(here); pq_est.pop();
      finish_time = here.est;
    }
  }

  std::cout << ans << '\n';
  return 0;
}