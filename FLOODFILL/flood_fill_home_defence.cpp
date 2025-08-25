#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct NODE {
	int y, x;
};

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };
int map[21][21];
int visited[21][21];
int numHouse[41];
int n, m, ans;

int bfs(int y, int x) {
	queue<NODE> q;
	memset(visited, 0, sizeof(visited));
	memset(numHouse, 0, sizeof(numHouse));
	int temp = 0;

	visited[y][x] = 1;
	q.push({ y, x });

	while (!q.empty()) {
		NODE now = q.front(); q.pop();
		if (map[now.y][now.x]) numHouse[visited[now.y][now.x]]++;

		for (int i = 0; i < 4; ++i) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];

			if (ny < 0 || nx < 0 || ny >= n || nx >= n || visited[ny][nx]) continue;

			visited[ny][nx] = visited[now.y][now.x] + 1;

			q.push({ ny, nx });
		}
	}

	int cnt = 0;
	for (int i = 1; i <= 40; ++i) {
		cnt += numHouse[i];
		if (cnt * m - (i * i + (i - 1) * (i - 1)) >= 0) {
			temp = cnt;
		}
	}

	return temp;
}

int main() {
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; ++tc) {
		memset(map, 0, sizeof(map));
		ans = 0;

		cin >> n >> m;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				ans = max(ans, bfs(i, j));
			}
		}

		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}