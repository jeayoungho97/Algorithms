// 알베르토의 물감 대포
// 0번째 행에서 L or R 로 쏨.
// 벽에 맞으면 방향 바뀜 (좌우 벽 : 좌우방향 반대, 상하 벽 : 상하방향 반대) => 아래 벽에 맞으면 끝남
// 벽에 맞았는지는 y, x 가 경계의 숫자인지로 판단 => ex) y = N 이면 y = N - 2 로 바꾸고 dy *= -1;
// 물감을 한 칸 지날 때마다 숫자 1씩 증가 => 색칠할 때, 나보다 숫자 작은 곳은 색칠 못함

#include <iostream>

int canvas[6][6];

void draw(int pos, char LR) {
    int y = 5, x = pos, paint = 1;
    int dy = -1, dx = 1;
    if (LR == 'L') dx = -1;
    canvas[y][x] = paint++;

    while (true) {
        y += dy;
        x += dx;
        
        if (y == 5) break; 
        if (y < 0) {
            dy = 1;
            y = 1;
        }
        if (x < 0) {
            dx = 1;
            x = 1;
        }
        if (x >= 6) {
            dx = -1;
            x = 4;
        }

        if (canvas[y][x] == 0 || canvas[y][x] > paint) {
            canvas[y][x] = paint;
        }
        paint++;
    }
}

int main() {
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int pos;
        char dir;
        std::cin >> pos >> dir;

        draw(pos, dir);
    }

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (canvas[i][j] == 0) std::cout << '_';
            else std::cout << canvas[i][j];
        }
        std::cout << '\n';
    }
}