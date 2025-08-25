#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

struct NODE
{
	int y, x;
};

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

const int pipe[8][4] = {
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{1, 0, 1, 0},
	{0, 1, 0, 1},
	{1, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 1},
	{1, 0, 0, 1}
};

int n, m, r, c, l, ans;
int map[51][51];
int visited[51][51];

void init()
{
	ans = 0;
	memset(map, 0, sizeof(map));
	memset(visited, 0, sizeof(visited));
}

void input()
{
	cin >> n >> m >> r >> c >> l;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> map[i][j];
		}
	}
}

void solve(int row, int col, int len)
{
	queue<NODE> q;

	q.push({row, col});
	visited[row][col] = 1;

	int cnt = 1;
	while (!q.empty())
	{
		NODE now = q.front(); q.pop();
		if (visited[now.y][now.x] == l) break;

		for (int i = 0; i < 4; ++i)
		{
			if (pipe[map[now.y][now.x]][i] == 0) continue;
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= m)	continue;

			int opDir = (i + 2) % 4; 
			if (pipe[map[ny][nx]][opDir] == 0) continue;
			if (visited[ny][nx]) continue;

			cnt++;
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ny, nx});
		}
	}

	ans = cnt;
}

int main()
{
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; ++tc)
	{
		init();

		input();

		solve(r, c, l);

		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}