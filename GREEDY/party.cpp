#include <iostream>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;

    int cheap6 = 1001, cheap1 = 1001;

    for (int i = 0; i < m; ++i) {
        int cur6, cur1;
        std::cin >> cur6 >> cur1;

        cheap6 = std::min(cheap6, cur6);
        cheap1 = std::min(cheap1, cur1);
    }

    bool use1 = false;
    if (cheap6 > (cheap1 * 6))  use1 = true;

    int cost = 0;
    if (use1) {
        cost += (n * cheap1);
    }
    else {
        cost += (n / 6) * cheap6;
        cost += (n % 6) * cheap1;

        int temp = (n / 6) * cheap6;
        if (n % 6) temp += cheap6;

        cost = std::min(cost, temp);
    }

    std::cout << cost << '\n';

    return 0;
}