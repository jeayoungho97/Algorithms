#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct BC {
    int y, x, c, p;
    // 좌표, 범위, 성능
};

vector<BC> bclist; // 배터리셀 리스트

const int dy[] = {0, -1, 0, 1, 0};
const int dx[] = {0, 0, 1, 0, -1};

int ans;
int M; // 이동 시간
int A; // BC의 개수
int alist[101]; // A의 이동 정보
int blist[101]; // B의 이동 정보



void init() {
    ans = 0;
    bclist.clear();
}

void input() {
    cin >> M >> A;
    for (int i = 0; i < M; ++i) cin >> alist[i];
    for (int i = 0; i < M; ++i) cin >> blist[i];

    for (int i = 0; i < A; ++i) {
        int y, x, c, p;
        cin >> x >> y >> c >> p;
        bclist.push_back({y, x, c, p});
    }
}

int check(int bcnum, int y, int x) {
    BC now = bclist[bcnum];
    int dist = abs(now.y - y) + abs(now.x - x);
    if (dist <= now.c) return now.p;
    return 0;
}

int calc(int ay, int ax, int by, int bx) {
    int maxCharge = -1;
    for (int aBC = 0; aBC < A; ++aBC) {
        for (int bBC = 0; bBC < A; ++bBC) {
            int sumCharge = 0;
            int aCharge = check(aBC, ay, ax); // 충전 범위 내에 있다면 충전량 return
            int bCharge = check(bBC, by, bx); 
            if (aBC == bBC && aCharge && bCharge) {
                //둘이 같은 배터리셀이라면
                aCharge /= 2;
                bCharge /= 2;
            }

            sumCharge = aCharge + bCharge;
            maxCharge = max(maxCharge, sumCharge);
        }
    }

    return maxCharge;
}

void solve() {
    // 각 사용자의 시작 위치에서부터 충전량을 누적해서 최댓값 구함
    int ay = 1, ax = 1, by = 10, bx = 10;

    int time = 0;
    while (time <= M) {
        // 충전하고
        ans += calc(ay, ax, by, bx);

        // 좌표 이동
        ay += dy[alist[time]];
        ax += dx[alist[time]];
        by += dy[blist[time]];
        bx += dx[blist[time]];

        // 다음 시간 탐색
        time++;
    }
}

int main() {
    int t; 
    cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        init();

        input();

        solve();

        cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}