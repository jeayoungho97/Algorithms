// 미생물 연구
// 제한조건 : 2 <= n <= 15, 1 <= q <= 50
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

struct GROUP {
    int size; 
    // int sy, sx;   // sy, sx 는 처음에 배치됐던 좌하단 좌표
    int cy, cx; // cy, cx 는 현재 좌하단의 좌표
    int map[16][16]; // sy, sx 를 기준으로 어느 위치에 미생물이 있는지 (즉 모양을 결정)
};

int n, q;
int MAP[16][16];


int main() {
    cin >> n >> q;

    vector<GROUP> groups(q); // q 개의 미생물 군집 (0번 인덱스부터 시작)

    for (int i = 0; i < q; ++i) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        groups[q].size = (r2 - r1) * (c2 - c1);
        for (int row = 0; row < r2 - r1; ++row) {
            for (int col = 0; col < c2 - c1; ++col) {
                groups[q].map[row][col] = 1;
            }
        }

        for (int row = r1; row < r2; ++row) {
            for (int col = c1; col < c2; ++col) {
                // 기존 맵에 다른 미생물 있다면 삭제
                if (MAP[row][col]) {
                    int num_group = MAP[row][col];
                    GROUP& now = groups[num_group];

                    // cy, cx 는 해당 군집의 현재 좌하단
                    int cy = now.cy, cx = now.cx;
                    now.map[row - cy][col - cx] = 0; // 상대위치의 좌표를 꺼버림
                    // 각각의 미생물 군집 마다 넓이를 기록해두고 있다가, 삭제된 만큼 최신화해줌
                    now.size--;
                }


            }
        }
        // 둘로 갈라졌는지 확인은 1. 군집에서 살아있는 점 하나 잡고 플러드필 돌렸을 때 넓이가 최신화된 넓이랑 같은지 확인 => 다르다면 여러 구역으로 나뉘었다는 것
        // 갈라졌다면 없애면 되는데...
        // 잘린 다음에도 그 모양 그대로 맵이 최신화돼야하니까 모양을 담고 있어야함.
        // 서브맵? 대략 만개의 좌표를 담아야함 => 가능! int subMap[51][16][16];

        // 서브맵이 있다고 해도 어떻게 그걸 가지고 경계를 확인하고 맵에 기록할 것인지??
        // 그냥 완전탐색으로 모든 좌표에 대해서 확인해도 괜찮을듯
        // 
            // 1-1. 기존 군집이 둘로 나뉘진 않았는지 확인

        // 2. 맵 정리하기
            // 2-1. 군집을 크기별로 정렬, 큰 것부터 x 가 작은 순, y 가 작은 순으로 배치 (맵 벗어나지 않게, 겹치지 않게)
            //      크기가 같다면 먼저 넣은 군집을 우선으로!

        // 3. 인접한 군집 확인
            // 3-1. 인접한 것들이 있다면 면접을 곱해서 더함.
            //      그 때의 결과를 출력함.
            //      단 군집이 하나 뿐이라면 0 을 출력.
        
    }    



    return 0;
}