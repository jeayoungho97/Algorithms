#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> meetings;

    for (int i = 0; i < n; ++i) {
        int start, end;
        std::cin >> start >> end;

        meetings.push_back({end, start});
    }

    std::sort(meetings.begin(), meetings.end());
    
    int end = -1, cnt = 0;
    for (int i = 0; i < meetings.size(); ++i) {
        if (meetings[i].second >= end) {
            cnt++;
            end = meetings[i].first;
        }
    }

    std::cout << cnt << '\n';
    return 0;
}