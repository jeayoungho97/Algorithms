#include <iostream>
#include <vector>
using namespace std;

struct NODE {
    int y, x, cost, dir;
};

struct MAP {
    int cost = 0, maxCost = 0, dir = 0, firstMet; 
};

vector<NODE> micros; // 군집의 정보를 담음 -> 실제 이동하는 군집
vector<bool> alive; // 살아있는 군집 정보 저장용

const int dy[] = {0, -1, 1, 0, 0}; // X 상 하 좌 우
const int dx[] = {0, 0, 0, -1, 1};
int n, m, k;

int main() {
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc) {
        micros.clear();
        alive.clear();

        cin >> n >> m >> k;
        for (int i = 0; i < k; ++i) {
            int y, x, cost, dir;
            cin >> y >> x >> cost >> dir;
            micros.push_back({y, x, cost, dir});
            alive.push_back(true);
        }

        int time = 0;
        while (time < m) {
            MAP map[101][101];

            // 이동 -> 계산
            for (int i = 0; i < k; ++i) {
                if (!alive[i]) continue; // 죽은 군집 제외
                NODE& now = micros[i];

                now.y += dy[now.dir];
                now.x += dx[now.dir];

                // 경계선에 닿은 경우
                if (now.y == 0 && now.dir == 1) {
                    now.cost /= 2;
                    now.dir = 2;
                }
                else if (now.y == n - 1 && now.dir == 2) {
                    now.cost /= 2;
                    now.dir = 1;
                }
                else if (now.x == 0 && now.dir == 3) {
                    now.cost /= 2;
                    now.dir = 4;
                }
                else if (now.x == n - 1 && now.dir == 4) {
                    now.cost /= 2;
                    now.dir = 3;
                }

                // 부딪혀서 죽었다면 죽었다고 처리
                if (now.cost <= 0) {
                    alive[i] = false;
                    continue;
                }

                // 가는 길에 누가 이미 왔었다면 뒤에 오는 애들은 그냥 죽었다고 처리.
                if (map[now.y][now.x].maxCost == 0) map[now.y][now.x].firstMet = i;
                else alive[i] = false;

                // 가는 길에 있든 없든 코스트 더하면 됨
                map[now.y][now.x].cost += now.cost;

                // 가려는 위치에 이미 와있는 군집이 있다면 갱신하고 방향 바꾸면 끝.
                if (map[now.y][now.x].maxCost < now.cost) {
                    map[now.y][now.x].maxCost = now.cost;
                    map[now.y][now.x].dir = now.dir;
                }

                micros[map[now.y][now.x].firstMet].cost = map[now.y][now.x].cost;
                micros[map[now.y][now.x].firstMet].dir = map[now.y][now.x].dir;
            }

            time++;
        }

        int ans = 0;
        for (int i = 0; i < k; ++i) {
            if (!alive[i]) continue;
            ans += micros[i].cost;
        }

        cout << '#' << tc << ' ' << ans << '\n';
    }



    return 0;
}