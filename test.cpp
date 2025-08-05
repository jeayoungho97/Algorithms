// 도형 끼우기
// 모양은 방향으로 저장하기 => ex) shape = {1,2,1} (오, 아, 오)
// 위의 예시 모양을 90도 돌리면 => shape_90 = {2,3,2} (아, 왼, 아)
// 즉 1 씩 더하고 4로 나눈 나머지
// 모양이 중복되는 경우는 두 가지 => 90도 돌려서 같으면 첫번째 shape 만 쓰면 됨.
//                            => 90도는 다르지만 180도 돌려서 같으면 첫번째, 두번째 shape 만 쓰면 됨.
// 돌려서 같은 모양인지 어떻게 알지..?

// 이건 안됨,,, 모양이 가지 없이 한붓그리기 가능한 경우에만 가능
// 모양 그 자체를 써야할듯?



#include <iostream>
#include <vector>

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

char shape[4][4], map[10][10];

int main() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cin >> shape[i][j];
        }
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cin >> map[i][j];
        }
    }

    for


    return 0;
}
