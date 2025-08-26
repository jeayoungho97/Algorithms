#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>
#define MAX 1e9
using namespace std;

struct NODE {
	int y, x, cost;
	bool operator<(const NODE& r) const {
		return cost > r.cost;
	}
};

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
int n;
int map[126][126];
int dist[126][126];

void dijkstra(int y, int x) {
	fill(&dist[0][0], &dist[0][0] + 126 * 126, MAX);
	priority_queue<NODE> pq;
	pq.push({y, x, map[y][x]});
	dist[y][x] = map[y][x];

	while (!pq.empty()) {
		NODE now = pq.top(); pq.pop();
		if (dist[now.y][now.x] < now.cost) continue;

		for (int i = 0; i < 4; ++i) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;

			int nextcost = now.cost + map[ny][nx];
			if (dist[ny][nx] > nextcost) {
				dist[ny][nx] = nextcost;
				pq.push({ny, nx, nextcost});
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int tc = 1;
	while (true) {

		cin >> n;
		if (n == 0) break;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> map[i][j];
			}
		}

		dijkstra(0, 0);

		cout << "Problem " << tc << ": " << dist[n - 1][n - 1] << '\n';
		tc++;
	}


	return 0;
}