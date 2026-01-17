#include <iostream>
using namespace std;

int GCD (int x, int y) {
    int bigger = (x > y) ? x : y;
    int smaller = (x > y) ? y : x;

    if (smaller == 0) return bigger;

    return GCD(smaller, bigger % smaller);
}

int main() {
    int x1, y1, x2, y2, x3, y3;

    cin >> x1 >> y1 >> x2 >> y2;

    x3 = x1 * y2 + x2 * y1;
    y3 = y1 * y2;

    int gcd = GCD(x3, y3);
    x3 /= gcd;
    y3 /= gcd;

    cout << x3 << ' ' << y3 << '\n';

    return 0;
}