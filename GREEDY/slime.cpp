// 액체 괴물 => 가장 크기가 작은 두개를 계속 합쳐나가는게 시간이 가장 적게 걸림

#include <iostream>
#include <queue>
#include <functional>

int main() {
    int n;
    std::cin >> n;

    std::priority_queue<int, std::vector<int>, std::greater<>> pq;

    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        pq.push(temp);
    }

    int cnt = 0;

    while (pq.size() > 1) {
        int sum = 0;
        sum += pq.top();
        pq.pop();
        sum += pq.top();
        pq.pop();

        cnt += sum;
        // std::cout << "sum = " << sum << '\n';

        pq.push(sum);
    }

    std::cout << cnt << '\n';

    return 0;
}