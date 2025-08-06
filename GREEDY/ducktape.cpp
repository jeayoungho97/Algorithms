#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, l;
    std::cin >> n >> l;

    std::vector<int> positions;
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        positions.push_back(temp);
    }

    std::sort(positions.begin(), positions.end());

    int cnt = 0, end = -1;
    for (int i = 0; i < positions.size(); ++i) {
        if (positions[i] > end) {
            cnt++;
            end = positions[i] + l - 1;
        }
    }

    std::cout << cnt << '\n';

    return 0;
}