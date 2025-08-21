#include <iostream>
#include <vector>
#include <algorithm>

struct NODE {
    int idx, x1, x2;
    bool operator<(const NODE& right) {
        if (x1 == right.x1) return x2 < right.x2;
        return x1 < right.x1;
    }
};

std::vector<NODE> arr;
int parent[100001];

int main() {
    int n, q, x1, x2, y, i, idx;
    std::cin >> n >> q;

    for (i = 1; i <= n; ++i) {
        std::cin >> x1 >> x2 >> y;
        arr.push_back({i, x1, x2});
        parent[i] = i;
    }

    std::sort(arr.begin(), arr.end());

    for (i = 1; i < arr.size(); ++i) {
        if (arr[i].x1 <= arr[i - 1].x2 && arr[i].x2 >= arr[i - 1].x1) {
            
        }
    }

    for (i = 0; i < q; ++i) {
        std::cin >> x1 >> x2;
        if (parent[x1] == parent[x2]) {
            std::cout << 1 << '\n';
        }
        else std::cout << 0 << '\n';
    }


    return 0;
}