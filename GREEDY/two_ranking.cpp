#include <iostream>
#include <vector>
#include <algorithm>

const int MAX = 987654321;
std::vector<std::pair<int, int>> participants;

int main() {
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        participants.push_back({a, b});
    }

    std::sort(participants.begin(), participants.end());

    int cnt = 0, lowest = MAX;
    for (auto [a, b] : participants) {
        if (b < lowest) {
            cnt++;
            lowest = b;
        }
    }
    
    std::cout << cnt << '\n';

    return 0;
}