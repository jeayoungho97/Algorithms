// 색칠 놀이
// 왼위, 오아 좌표 + 색상(정수) 주어짐
// 색칠할 때 해당 좌표의 크기보다 크면 덮어씀
// 완전 탐색 => (i,j) 에 색깔 있으면 기본 크기 1, 
// 한칸 씩 오른쪽, 아래로 늘려가면서 i + 1 행, j + 1 열에도 같은 색깔인지 확인
// 넓이 max 값 최신화

#include <iostream>
#include <algorithm>

int map[10][10], result;

int main() {
    int n, q;
    std::cin >> n >> q;

    for (int i = 0; i < q; ++i) {
        int color, y1, x1, y2, x2;
        std::cin >> color >> y1 >> x1 >> y2 >> x2;
        for (int row = std::min(y1, y2); row <= std::max(y1, y2); ++row) {
            for (int col = std::min(x1, x2); col <= std::max(x1, x2); ++col) {
                if (map[row][col] < color) map[row][col] = color;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (map[i][j] != 0) {
                int color = map[i][j];
                int ni = i + 1, nj = j + 1;
                bool flag = false;
                while (true) {
                    if (ni < 0 || nj < 0 || ni >= n || nj >= n) break;

                    for (int row = i; row <= ni; ++row) {
                        if (map[row][nj] != color) flag = true;
                    }
                    
                    for (int col = j; col <= nj; ++col) {
                        if (map[ni][col] != color) flag = true;
                    }

                    if (flag) break;
                    ni++, nj++;
                }

                int size = (ni - i) * (nj - j);
                result = std::max(result, size);
                // std::cout << "i : " << i <<" j : " << j << " size : " << size << '\n';
            }
        }
    }

    std::cout << result << '\n';
    return 0;
}