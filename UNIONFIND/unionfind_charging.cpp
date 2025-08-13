#include <iostream>

int t, n;
int parent[100001];

// find 는 x 가 들어갈 수 있는 충전소의 가장 큰 번호를 찾아줌
// 경로압축을 통해 지나가는 경로의 충전소도 최신화
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    parent[b] = a; 
}

int main() {
    for (int i = 1; i <= 100000; ++i) {
        parent[i] = i;
    }

    std::cin >> t >> n;

    int cnt = 0;
    bool finished = false;
    for (int i = 0; i < n; ++i) {
        int car;
        std::cin >> car;
        if (finished) continue;
        
        int able = find(car);

        // 들어갈 수 있는 가장 큰 충전소가 0 이면 이제 들어갈 수 없다는 뜻
        if (able == 0) {
            finished = true;
            continue;
        }        

        cnt++;
        Union(able - 1, able);
    }

    std::cout << cnt << '\n';
    return 0;
}