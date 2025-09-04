#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

struct NODE {
	int y, x, dir;
};

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };
vector<NODE> avail[60000]; // 각각의 구조물에 대해 가능한 경우 모음 (좌표, 방향)
int n, total;
int MAP[20][20];

void init(int N, int mMap[20][20])
{
	n = N;
	total = n * n;
	memcpy(MAP, mMap, sizeof(mMap));

	for (int i = 0; i < 60000; ++i) {
		avail[i].clear();
	}

	// 각각의 좌표에서 길이 1 ~ 5 에 대해 DAT 값 만들기
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			// 오른쪽, 아래로만 
			for (int dir = 1; dir <= 2; ++dir) {
				for (int len = 1; len <= 5; ++len) {
					// 해당 방향으로의 길이가 len 보다 작다면 break;
					int cy = i + (len - 1) * dy[dir];
					int cx = j + (len - 1) * dx[dir];
					if (cy < 0 || cx < 0 || cy >= N || cx >= N) break;

					// 방향으로 가면서 최댓값 확인하고 정규화 + 반대방향도 생각해야함
					int temp_max = 0;
					vector<int> arr;
					for (int k = 0; k < len; ++k) {
						int ny = i + k * dy[dir];
						int nx = j + k * dx[dir];
						temp_max = max(temp_max, mMap[ny][nx]);
						arr.push_back(mMap[ny][nx]);
					}

					// 정규화한 값을 string 에 담음
					string str = "";
					for (int idx = 0; idx < arr.size(); ++idx) {
						arr[idx] = 1 - (arr[idx] - temp_max);
						str += char(arr[idx] + '0');
					}

					avail[stoi(str)].push_back({ i, j, dir });

					// 반대인 경우도 생각 (다만 같다면 무시)
					string temp = str;
					reverse(str.begin(), str.end());

					if (str != temp) {
						int sy = i + (len - 1) * dy[dir];
						int sx = j + (len - 1) * dx[dir];
						int opp = (dir + 2) % 4;
						avail[stoi(str)].push_back({ sy,sx,opp });
					}
				}
			}


		}
	}
}

int numberOfCandidate(int M, int mStructure[5])
{
	string str = "";
	int temp_min = mStructure[0];
	for (int i = 1; i < M; ++i) temp_min = min(temp_min, mStructure[i]);

	for (int i = 0; i < M; ++i) {
		// init과 동일한 규칙: (temp_max - value) + 1
		int num = (mStructure[i] - temp_min) + 1;
		str += char('0' + num); // (근본 해결은 아래 권장 수정 참고)
	}
	return (int)avail[stoi(str)].size();
}


int go(NODE now, int Structure[5], int len, int SeaLevel) {
	// 원본 맵을 복사해옴
	int tempMAP[20][20];
	memcpy(tempMAP, MAP, sizeof(MAP));

	// 뚝방을 세움
	for (int i = 0; i < len; ++i) {
		int ny = now.y + i * dy[now.dir];
		int nx = now.x + i * dx[now.dir];

		tempMAP[ny][nx] += Structure[i];
	}

	// 가장자리에서만 확인하면서 플러드필 (가장자리 중에서 SeaLevel 이상인 것들은 continue)
	queue<NODE> q;
	bool visited[20][20] = { 0 };

	int cnt = 0;

	for (int i = 0; i < n; ++i) {
		if (tempMAP[0][i] < SeaLevel && !visited[0][i]) {
			q.push({ 0, i });
			visited[0][i] = 1;
		}

		if (tempMAP[i][0] < SeaLevel && !visited[i][0]) {
			q.push({ i,0 });
			visited[i][0] = 1;
		}

		if (tempMAP[n - 1][i] < SeaLevel && !visited[n - 1][i]) {
			q.push({ n - 1, i });
			visited[n - 1][i] = 1;
		}

		if (tempMAP[i][n - 1] < SeaLevel && !visited[i][n - 1]) {
			q.push({ i,n - 1 });
			visited[i][n - 1] = 1;
		}
	}

	while (!q.empty()) {
		NODE here = q.front(); q.pop();
		cnt++;

		for (int i = 0; i < 4; ++i) {
			int ny = here.y + dy[i];
			int nx = here.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (visited[ny][nx]) continue;
			if (tempMAP[ny][nx] >= SeaLevel) continue;
			q.push({ ny, nx });
			visited[ny][nx] = 1;
		}
	}


	return total - cnt;
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{
	string str = "";
	int temp_min = mStructure[0];
	for (int i = 1; i < M; ++i) temp_min = min(temp_min, mStructure[i]);

	for (int i = 0; i < M; ++i) {
		int num = (mStructure[i] - temp_min) + 1;
		str += char('0' + num);
	}

	int ret = 0;
	for (NODE now : avail[stoi(str)]) {
		ret = max(ret, go(now, mStructure, M, mSeaLevel));
	}

	reverse(str.begin(), str.end());
	int revStructure[5];
	memcpy(revStructure, mStructure, sizeof(int) * M);
	reverse(revStructure, revStructure + M);

	for (NODE now : avail[stoi(str)]) {
		ret = max(ret, go(now, revStructure, M, mSeaLevel));
	}
	return ret;
}
