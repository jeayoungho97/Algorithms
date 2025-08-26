#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int n, k, ans;
int map[9][9];
bool visited[9][9];

void dfs(int y, int x, int length, bool hasCut) {
	ans = max(ans, length);

	int here = map[y][x];
	for (int i = 0; i < 4; ++i) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
		if (visited[ny][nx]) continue;

		int next = map[ny][nx];

		if (next >= here) {
			if (!hasCut && next < here + k) {
				visited[ny][nx] = 1;
				int temp = map[ny][nx];
				map[ny][nx] = map[y][x] - 1;
				dfs(ny, nx, length + 1, true);
				map[ny][nx] = temp;
				visited[ny][nx] = 0;
			}
		}
		else {
			visited[ny][nx] = 1;
			dfs(ny, nx, length + 1, hasCut);
			visited[ny][nx] = 0;
		}
	}
}

int main() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; ++tc) {
		memset(visited, 0, sizeof(visited));
		ans = 0;
		cin >> n >> k;

		int max_val = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> map[i][j];
				if (map[i][j] > max_val) max_val = map[i][j];
			}
		}

		vector<pair<int, int>> maxIdx;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (map[i][j] == max_val) maxIdx.push_back({i, j});
			}
		}

		for (auto [y,x] : maxIdx) {
			visited[y][x] = 1;
			dfs(y, x, 1, 0);
			visited[y][x] = 0;
		}

		cout << '#' << tc << ' ' << ans << '\n';
	}


	return 0;
}