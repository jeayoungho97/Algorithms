#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, int>> shape[4]; // shape[n] = n번 90도 회전한 좌표의 모음
char map[10][10];
int cnt, until = 3;

std::pair<int, int> rotate(int y, int x, int cnt) {
    switch(cnt) {
        case 0 :
        return {y, x};
        case 1 :
        return {x, 3 - y};
        case 2 : 
        return {3 - y, 3 - x};
        case 3 :
        return {3 - x, y};
    }
    return {0, 0};
}

void getShape() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            char input;
            std::cin >> input;
            if (input == '$') {
                for (int k = 0; k < 4; ++k) {
                    auto [y, x] = rotate(i, j, k);
                    shape[k].push_back({y, x});
                }
            }
        }
    }
}

void rotShape() {
    for (int i = 0; i < 4; ++i) {
        std::sort(shape[i].begin(), shape[i].end());
        int left = 4, top = 4;
        for (auto [y, x] : shape[i]) {
            if (y < top) top = y;
            if (x < left) left = x;
        }

        if (left > 0 || top > 0) {
            for (auto& [y,x] : shape[i]) {
                y -= top;
                x -= left;
            }
        }

        // Debugging
        //
        // std::cout << "shape" << i << "\n";
        // for (auto [y, x] : shape[i]) {
        //     std::cout << "y = " << y << ", x = " << x << '\n';
        // }
        // std::cout << "================================\n";
    }
}

void checkShape() {
    for (int i = 1; i < 4; ++i) {
        bool isOG = false;
        for (int j = 0; j < shape[0].size(); ++j) {
            if (shape[i][j] != shape[0][j]) isOG = true;
        }

        if (!isOG) {
            until = i - 1;
            return;
        }
    }
}

void getMap() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cin >> map[i][j];
        }
    }
}

void go(int wshape, int y, int x) {
    auto [i, j] = shape[wshape][0];
    int dy = y - i;
    int dx = x - j;

    for (auto [cy,cx] : shape[wshape]) {
        int ny = cy + dy;
        int nx = cx + dx;
        if (ny < 0 || ny >= 10 || nx < 0 || nx >= 10 || map[ny][nx] != '_') return;
    }

    cnt++;
}

void checkMap() {
    for (int wshape = 0; wshape <= until; ++wshape) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (map[i][j] == '_') {
                    go(wshape, i, j);
                }
            }
        }
    }
}

int main() {
    getShape();
    rotShape();
    checkShape();
    
    getMap();
    checkMap();
    
    std::cout << cnt << '\n';
    return 0;
}