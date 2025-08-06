#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int cnt = 0;
    int coin[4] = {500, 100, 50, 10};

    for (int i = 0; i < 4; ++i) {
        cnt += n / coin[i];
        n %= coin[i];
    }

    std::cout << cnt << '\n';
    
    return 0;
}