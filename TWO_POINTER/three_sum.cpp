#include <iostream>
#include <algorithm>

int arr[5000];

int two_pointer(int target, int start, int end) {
    if (target < 0) return 0;

    int sum, cnt = 0;
    while (start < end) {
        sum = arr[start] + arr[end];
        if (sum > target) {
            end--;
        }
        else if (sum < target) {
            start++;
        }
        else {
            cnt++;
            start++;
            end--;
        }
    }

    return cnt;
}

int main() {
    int n, k, cnt = 0;
    std::cin >> n >> k;

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    std::sort(arr, arr + n);

    for (int i = 0; i < n; ++i) {
        cnt += two_pointer(k - arr[i], i + 1, n - 1);
    }

    std::cout << cnt << '\n';
    return 0;
}