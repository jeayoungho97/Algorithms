// #include <iostream> : 디버깅용
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <string>
// #include <unordered_map>

using namespace std;

struct NODE {
  int y, x;
  int dir;
};

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
int n;
int MAP[20][20];
vector<NODE> AVAIL[60000];

void init(int N, int mMap[20][20])
{
  for (int i = 0; i < 60000; ++i) {
    AVAIL[i].clear();
  }

  n = N;

  memcpy(MAP, mMap, sizeof(MAP));

  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < n; ++x) {
      for (int dir = 1; dir <= 2; ++dir) {
        for (int len = 2; len <= 5; ++len) {
          // 범위를 벗어나는지 확인
          int cy = y + (len - 1) * dy[dir];
          int cx = x + (len - 1) * dx[dir];
          if (cy >= n || cx >= n) break;

          // 벗어나지 않는 경우 최댓값을 찾고, 정규화한 값을 문자열로 담음
          int max_element = 0;
          for (int i = 0; i < len; ++i) {
            int ny = y + i * dy[dir];
            int nx = x + i * dx[dir];
            max_element = max(max_element, MAP[ny][nx]);
          }

          string str = "";

          for (int i = 0; i < len; ++i) {
            int ny = y + i * dy[dir];
            int nx = x + i * dx[dir];
            int temp = 1 - (MAP[ny][nx] - max_element);
            str += char(temp + '0');
          }

          // string 을 int 로 바꿔서 AVAIL 의 index 로 사용, vector 에 좌표 및 방향 push_back
          AVAIL[stoi(str)].push_back({y, x, dir});
        }
      }
    }
  }
}

int numberOfCandidate(int M, int mStructure[5])
{
  if (M == 1) {
    return n * n;
  }
  int min_element = mStructure[0];
  for (int i = 1; i < M; ++i) {
    min_element = min(min_element, mStructure[i]);
  }
  
  string str = "";
  for (int i = 0; i < M; ++i) {
    int temp = mStructure[i] - min_element + 1;
    str += char(temp + '0');
  }

  int ret = AVAIL[stoi(str)].size();

  string temp_str = str;
  reverse(str.begin(), str.end());
  if (temp_str != str) {
    ret += AVAIL[stoi(str)].size();
  }
 	return ret;
}

int go(NODE now, int M, int mStructure[5], int mSeaLevel) {
  int COPY[20][20];
  memcpy(COPY, MAP, sizeof(COPY));

  // 복사한 맵에 값을 더해줌
  for (int i = 0; i < M; ++i) {
    int ny = now.y + i * dy[now.dir];
    int nx = now.x + i * dx[now.dir];
    COPY[ny][nx] += mStructure[i];
  }
  // 플러드필
  queue<NODE> q;
  bool visited[20][20] = {0};

  // 네 모서리에 대해 확인
  for (int i = 0; i < n; ++i) {
    if (COPY[0][i] < mSeaLevel && !visited[0][i]) {
      q.push({0, i});
      visited[0][i] = true;
    }

    if (COPY[n - 1][i] < mSeaLevel && !visited[n - 1][i]) {
        q.push({n - 1, i});
        visited[n - 1][i] = true;
    }

    if (COPY[i][0] < mSeaLevel && !visited[i][0]) {
          q.push({i, 0});
          visited[i][0] = true;
    }

    if (COPY[i][n - 1] < mSeaLevel && !visited[i][n - 1]) {
          q.push({i, n - 1});
          visited[i][n - 1] = true;
    }
  }

  int cnt = 0;
  while(!q.empty()) {
    NODE here = q.front(); q.pop();
    cnt++;
    for (int dir = 0; dir < 4; ++dir) {
      int ny = here.y + dy[dir];
      int nx = here.x + dx[dir];
      if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
      if (visited[ny][nx]) continue;
      if (COPY[ny][nx] >= mSeaLevel) continue;

      visited[ny][nx] = true;
      q.push({ny, nx});
    }
  }

  return n * n - cnt;
}

int maxArea(int M, int mStructure[5], int mSeaLevel)
{
  // 1칸 짜리는 그냥 모든 경우에 대해 돌려보자
  if (M == 1) {
    int ret1 = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        ret1 = max(ret1, go({i, j}, 1, mStructure, mSeaLevel));
      }
    }
    return ret1;
  }

  int min_element = mStructure[0];
  for (int i = 1; i < M; ++i) {
    min_element = min(min_element, mStructure[i]);
  }
  
  string str = "";
  for (int i = 0; i < M; ++i) {
    int temp = mStructure[i] - min_element + 1;
    str += char(temp + '0');
  }

  
  int ret = 0;
  for (NODE now : AVAIL[stoi(str)]) {
    ret = max(ret, go(now, M, mStructure, mSeaLevel));
  }
  
  string temp_str = str;
  reverse(str.begin(), str.end());
  int revStructure[5];
  for (int i = 0; i < M; ++i) {
    revStructure[i] = mStructure[M - 1 - i];
  }

  for (NODE now : AVAIL[stoi(str)]) {
    ret = max(ret, go(now, M, revStructure, mSeaLevel));
  }
  
  if (AVAIL[stoi(str)].size() == 0 && AVAIL[stoi(temp_str)].size() == 0) {
    return -1;
  }

	return ret;
}