// 장기포 문제
// 포가 있던 위치를 건너뛰지 않도록 주의!

#include <iostream>
#include <cstring>
#include <queue>

struct NODE {
	int y, x;
};

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int ans, n, py, px;
int map[51][51];
bool ate[51][51];

void init() {
	ans = 0;
	memset(ate, 0, sizeof(ate));
}

void input() {
	std::cin >> n;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> map[i][j];

			if (map[i][j] == 2) {
				py = i, px = j;
				map[i][j] = 0;
			}
		}
	}
}

void dfs(int y, int x, int cnt) {
	if (cnt == 3) return;

	for (int i = 0; i < 4; ++i) {
		int cur_y = y, cur_x = x;
		bool met_jjol = false;
		while (true) {
			cur_y += dy[i];
			cur_x += dx[i];
			if (cur_y < 0 || cur_x < 0 || cur_y >= n || cur_x >= n) break;
			
			if (met_jjol) {
				// 쫄을 이미 만났던 경우
				if (map[cur_y][cur_x]) {
					// 또 쫄을 만나는 경우
					ate[cur_y][cur_x] = 1;
					map[cur_y][cur_x] = 0;
					dfs(cur_y, cur_x, cnt + 1);
					map[cur_y][cur_x] = 1;
					break;
				}
				else {
					// 쫄이 아닌 경우
					dfs(cur_y, cur_x, cnt + 1);
				}
			}
			else {
				// 쫄을 만난 적이 없는 경우
				if (map[cur_y][cur_x]) {
					// 쫄을 처음 만난 경우
					met_jjol = true;
				}
			}
		}
	}
}

int main() {	
	int t;
	std::cin >> t;

	for (int tc = 1; tc <= t; ++tc) {
		init();

		input();

		dfs(py, px, 0);

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (ate[i][j]) ans++;
			}
		}

		std::cout << '#' << tc << ' ' << ans << '\n';
	}
	return 0;
}