#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

struct NODE {
	int y, x, cost;
	bool operator<(const NODE& r) const {
		return cost > r.cost;
	}
};

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int Y, X, n, ans;
int MAP[1000][1000];
int dist[1000][1000];

void dijkstra(int y, int x) {
	fill(&dist[0][0], &dist[0][0] + 1000 * 1000, 1e9);
	priority_queue<NODE> pq;
	pq.push({ y, x, MAP[y][x] });
	dist[y][x] = MAP[y][x];

	while (!pq.empty()) {
		NODE now = pq.top(); pq.pop();
		if (dist[now.y][now.x] < now.cost) continue;

		for (int i = 0; i < 4; ++i) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (MAP[ny][nx] == -1) continue;
			int nextcost = now.cost + MAP[ny][nx];
			if (dist[ny][nx] > nextcost) {
				dist[ny][nx] = nextcost;
				ans = max(ans, nextcost);
				pq.push({ ny, nx, nextcost });
			}
		}
	}
}

int main() {
	cin >> Y >> X >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> MAP[i][j];
		}
	}

	dijkstra(Y, X);

	cout << ans << '\n';
	return 0;
}