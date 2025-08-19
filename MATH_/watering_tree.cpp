#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int ans, n, max, x, y;
std::vector<int> arr;

int main() {    
    int t;
    std::cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        arr.clear();
        ans = 0, x = 0, y = 0, max = 0;

        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            int temp;
            std::cin >> temp;
            arr.push_back(temp);

            max = std::max(max, temp);
        }

        for (int i : arr) {
            if ((max - i) & 1) x++;
            
            y += (max - i) / 2 * 2;
        }

        int val1 = y / 2;
        int val2 = (x + y) / 3;

        int minimum = 1e9, val = 0;
        if (val1 > val2) {
            for (int i = val2 - 1; i <= val2 + 1; ++i) {
                if (i < 0 || y - 2 * i < 0) continue;
                int abs_val = std::abs(x + y - 3 * i);
                if (abs_val < minimum) {
                    minimum = abs_val;
                    val = i;
                }
            }
        }
        else {
            for (int i = val1 -1; i <= val1 + 1; ++i) {
                if (i < 0 || y - 2 * i < 0) continue;
                int abs_val = std::abs(x + y - 3 * i);
                if (abs_val < minimum) {
                    minimum = abs_val;
                    val = i;
                }
            }
        }

        int A = val;
        int B = x + y - 2 * val;
        if (A >= B) ans = 2 * A;
        else ans = 2 * B - 1;

        std::cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}