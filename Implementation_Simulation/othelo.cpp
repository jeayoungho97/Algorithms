// 오델로
// 돌을 놓았을 때, 4 방향으로 탐색해서 같은 색 돌이 있고, 
// 그 사이가 모두 채워져 있다면 모두 같은 색으로 맞춤.
// 탐색 시 같은 색 돌 만나면 조사 후 바로 종료.

// y, x 그대로 가되 마지막 출력시에 y 역순으로 출력

#include <iostream>

const int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

int board[8][8], n;

void check(int y, int x, int color) {
    for (int dir = 0; dir < 8; ++dir) {
        int ny = y;
        int nx = x;
        while (true) {
            ny += dy[dir];
            nx += dx[dir];
            if (ny < 0 || ny >= 8 || nx < 0 || nx >= 8 || board[ny][nx] == 0) break;

            if (board[ny][nx] == color) {
                if (dir == 0 || dir == 4) {
                    for (int i = y + dy[dir]; i != ny; i += dy[dir]) {
                        board[i][x] = color;
                    }
                }
                else if (dir == 2 || dir == 6){
                    for (int i = x + dx[dir]; i != nx; i += dx[dir]) {
                        board[y][i] = color;
                    }
                }
                else {
                    int cy = y, cx = x;
                    while (cy != ny && cx != nx) {
                        cy += dy[dir];
                        cx += dx[dir];
                        board[cy][cx] = color;
                    }
                }

                break;
            }
        }
    }
}

int main() {
    int color = 1; // color : 1(black) or -1(white)
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int y, x;
        std::cin >> x >> y;
        board[y][x] = color;
        
        check(y, x, color);
        color *= -1;
    }

    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] == 0) std::cout << '_';
            else if (board[i][j] == 1) std::cout << '@';
            else std::cout << 'O';
        }
        std::cout << '\n';
    }

    return 0;
}
