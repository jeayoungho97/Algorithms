#include <iostream>

int parent[1001];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unionSet(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        parent[b] = a;
    }
}

int main() {
    int n, q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    for (int i = 0; i < q; ++i) {
        int k, a, b;
        std::cin >> k >> a >> b;

        if (k) {
            unionSet(a, b);
        }
        else {
            if (find(a) == find(b)) std::cout << "YES\n";
            else std::cout << "NO\n";
        }
    }



    return 0;
}