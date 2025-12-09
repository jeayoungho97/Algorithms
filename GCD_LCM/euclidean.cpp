// BOJ 13241 최소공배수
#include <iostream>
using namespace std;

int main() {
    long long A, B;
    cin >> A >> B;

    long long C = A;
    long long D = B;
    while (true) {
        long long R = C % D;
        if (R == 0) break;

        C = D;
        D = R;
    }

    long long a = A / D;
    long long b = B / D;

    long long L = a * b * D;

    cout << L << '\n';
    return 0;
}