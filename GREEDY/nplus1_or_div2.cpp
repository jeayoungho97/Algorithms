#include <iostream>

int main() {
    int a, b, cnt = 0;
    std::cin >> a >> b;

    while (b != a) {
        if (b % 10 == 1) b /= 10; // 1의 자리 숫자가 1 이라면
        else if (!(b&1)) b /= 2;  // 짝수라면
        else {
            std::cout << -1 << '\n';
            return 0;
        }
        
        cnt++;
    }
    
    std::cout << cnt << '\n';

    return 0;
}