#include <iostream>
#include <queue>

int n;
long long sum, ans;
std::priority_queue<long long> pq;

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        long long temp;
        std::cin >> temp;
        sum += temp;
        pq.push(temp);
    }

    while (true) {
        long long cost = pq.top(); pq.pop();
        if (pq.empty()) break;
        ans += sum;
        sum -= cost;
    }

    std::cout << ans << '\n';

    return 0;
}