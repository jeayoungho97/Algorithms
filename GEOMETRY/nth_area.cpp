#include <iostream>
#include <vector>
#include <cmath>

#define ll long long

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<ll, ll>> coords(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> coords[i].first >> coords[i].second;
    }

    ll sum1 = 0, sum2 = 0;

    for (int i = 0; i < n - 1; ++i) {
        sum1 += coords[i].first * coords[i + 1].second;
        sum2 += coords[i].second * coords[i + 1].first;
    }
    sum1 += coords[n - 1].first * coords[0].second;
    sum2 += coords[n - 1].second * coords[0].first;

    double result = (double)(std::abs(sum1 - sum2)) / 2;
    
    printf("%.1lf\n", result);
    
    return 0;
}