// check commit name check again check last time
#include <iostream>

int parent[1001];
bool circuit[1001][1001];

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

bool unionSet(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[b] = a;
    else {
        return false;
    }
    return true;
}

void initParent(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

void getCircuit(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> circuit[i][j];
        }
    }
}

bool readCircuit(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (circuit[i][j]) {
                if (!unionSet(i, j)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;

    initParent(n);
    getCircuit(n);
    if (readCircuit(n)) {
        std::cout << "WARNING\n";
    }
    else std::cout << "STABLE\n";


    return 0;
}