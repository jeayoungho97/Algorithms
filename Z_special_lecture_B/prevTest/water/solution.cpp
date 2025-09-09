#define MAX_WIDTH 500
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n;                                                        // tc별 어항의 개수
int IDs[21], lengths[21][MAX_WIDTH], upShapes[21][MAX_WIDTH]; // 각 어항의 ID, 각 열의 높이, 각 열의 위쪽 결합번호
int width, height;                                            // 모든 어항의 너비, 높이 (모두 같음)
int versions[21][501];                                        // 각 어항의 각각의 열 idx 의 버전

struct NODE
{
  int ID_idx, idx; // 어항의 ID_idx (ID 로 가는 idx), 그 안에서의 idx
  int version;     // => addStructure 로 변경되면 version 이 1 증가함 => checkStructures 에서 확인할 때 버전이 같아야 유효한 것
  // ID = 5, idx = 3 에 구조물이 추가되면 ID = 5, idx = 1, 2, 3, 4, 5 의 버전을 늘려서 DAT 에 추가해 넣어야함. (앞 뒤로 2칸씩)
  // => 근데 앞 뒤로 가는 게 범위를 벗어나면 넣지 않아도 됨. (0 미안인지, width 초과인지를 확인!)

  bool operator<(const NODE &r) const
  {
    if (ID_idx == r.ID_idx)
      return idx < r.idx;
    return IDs[ID_idx] < IDs[r.ID_idx];
  }
};

struct Result
{
  int ID;
  int height;
  int used;
};

vector<NODE> DAT[334];   // 000 ~ 333 까지 가능
vector<int> waterok[21]; // 어항 별, 높이별 빈칸

void init(int N, int mWidth, int mHeight, int mIDs[], int mLengths[][MAX_WIDTH], int mUpShapes[][MAX_WIDTH])
{
  memset(versions, 0, sizeof(versions));

  n = N, width = mWidth, height = mHeight;

  // DAT 의 각각의 벡터를 모두 초기화
  for (int i = 0; i < 334; ++i)
  {
    DAT[i].clear();
  }

  // 각 어항의 ID 를 복사함
  for (int id = 0; id < n; ++id)
  {
    IDs[id] = mIDs[id];
  }

  // 어항의 각 열의 높이도 복사해옴
  for (int id = 0; id < n; ++id)
  {
    for (int idx = 0; idx < width; ++idx)
    {
      lengths[id][idx] = mLengths[id][idx];
      upShapes[id][idx] = mUpShapes[id][idx];
    }
  }

  // DAT 를 초기화 => {IDs[id], idx}
  for (int id = 0; id < n; ++id)
  {
    int num;
    for (int idx = 0; idx < width - 2; ++idx)
    {
      num = upShapes[id][idx] * 100 + upShapes[id][idx + 1] * 10 + upShapes[id][idx + 2];

      DAT[num].push_back({id, idx, 0});
    }
  }

  // 각 어항에 대해 높이별 빈칸을 초기화 후 계산
  for (int id = 0; id < n; ++id) {
    waterok[id].resize(height + 1, 0);

    for (int h = 1; h <= height; ++h) {
      int cnt = width;
      for (int idx = 0; idx < width; ++idx) {
        if (lengths[id][idx] >= h) cnt--;
      }

      waterok[id][h] = cnt;
    }
  }
}

int checkStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{
  int num = mDownShapes[0] * 100 + mDownShapes[1] * 10 + mDownShapes[2];

  int cnt = 0;

  for (NODE now : DAT[num])
  {
    // 버전 확인
    if (now.version != versions[now.ID_idx][now.idx])
      continue;

    bool unavailable = false;
    int nextLength[3]; // 기둥들을 더한 뒤의 높이
    for (int i = 0; i < 3; ++i)
    {
      int cur_idx = now.idx + i;

      nextLength[i] = lengths[now.ID_idx][cur_idx] + mLengths[i];
      // 어항 넘어가는지 확인
      if (nextLength[i] > height)
      {
        // cout << "overflowed!\n";
        unavailable = true;
      }
    }

    for (int i = 0; i < 2; ++i)
    {
      // 기둥끼리 겹치는지 확인
      int cur_idx = now.idx + i;

      int top = nextLength[i];
      int bottom = lengths[now.ID_idx][cur_idx] + 1;
      int next_top = nextLength[i + 1];
      int next_bottom = lengths[now.ID_idx][cur_idx + 1] + 1;

      if (top < next_bottom || bottom > next_top)
      {
        unavailable = true;
      }
    }

    if (unavailable)
      continue;

    cnt++;
  }

  return cnt;
}

int addStructures(int mLengths[], int mUpShapes[], int mDownShapes[])
{

  int ret = 0;

  int num = mDownShapes[0] * 100 + mDownShapes[1] * 10 + mDownShapes[2];

  // 가능한 NODE 의 벡터를 정렬해서 ID 가 작은 순, 같은 ID 라면 idx 가 작은 순으로 정렬!
  sort(DAT[num].begin(), DAT[num].end());

  for (NODE now : DAT[num])
  {
    // 버전 확인
    if (now.version != versions[now.ID_idx][now.idx])
    {
      continue;
    }

    bool unavailable = false;
    int nextLength[3]; // 기둥들을 더한 뒤의 높이
    for (int i = 0; i < 3; ++i)
    {
      int cur_idx = now.idx + i;

      nextLength[i] = lengths[now.ID_idx][cur_idx] + mLengths[i];
      // 어항 넘어가는지 확인
      if (nextLength[i] > height)
      {
        unavailable = true;
      }
    }
    for (int i = 0; i < 2; ++i)
    {
      // 기둥끼리 겹치는지 확인
      int cur_idx = now.idx + i;

      int top = nextLength[i];
      int bottom = lengths[now.ID_idx][cur_idx] + 1;
      int next_top = nextLength[i + 1];
      int next_bottom = lengths[now.ID_idx][cur_idx + 1] + 1;

      if (top < next_bottom || bottom > next_top)
      {
        unavailable = true;
      }
    }

    if (unavailable)
      continue;

    for (int i = 0; i < 3; ++i)
    {
      // waterok 먼저 최신화
      for (int j = 1; j <= mLengths[i]; ++j)
      {
        waterok[now.ID_idx][lengths[now.ID_idx][now.idx + i] + j]--;
      }

      // 실제로 기둥들을 더함
      lengths[now.ID_idx][now.idx + i] += mLengths[i];

      // 위쪽 결합 번호도 갱신
      upShapes[now.ID_idx][now.idx + i] = mUpShapes[i];
    }

    // 양쪽으로 2만큼 벌려서 DAT 갱신
    for (int cur_idx = now.idx - 2; cur_idx <= now.idx + 2; ++cur_idx)
    {
      if (cur_idx < 0 || cur_idx + 2 >= width)
        continue;

      int cur_num = upShapes[now.ID_idx][cur_idx] * 100 + upShapes[now.ID_idx][cur_idx + 1] * 10 + upShapes[now.ID_idx][cur_idx + 2];

      // 버전 + 1
      versions[now.ID_idx][cur_idx]++;

      // 갱신된 버전으로 DAT 에 푸쉬백
      DAT[cur_num].push_back({now.ID_idx, cur_idx, versions[now.ID_idx][cur_idx]});
    }

    ret = IDs[now.ID_idx] * 1000 + now.idx + 1;

    break;
  }

  return ret;
}

Result pourIn(int mWater)
{
  Result ret;
  ret.ID = 1e9;
  ret.height = ret.used = 0;

  // waterok 계산
  for (int id = 0; id < n; ++id) {
    int sum = 0, h = 1;
    while (true) {
      if (sum + waterok[id][h] > mWater || h > height) {
        break;
      }

      sum += waterok[id][h];
      h++;
    }
    h--;

    // sum : 현재 사용한 물의 양
    // h : 현재 높이
    if (sum == 0) continue;

    // 아이디, 높이, 사용량
    Result current = {IDs[id], h, sum};

    if (h > ret.height) {
      ret = current;
    }
    else if (h == ret.height) {
      if (sum > ret.used) {
        ret = current;
      }
      else if (sum == ret.used) {
        if (IDs[id] < ret.ID) {
          ret = current;
        }
      }
    }
  }

  if (ret.height == 0) {
    ret.ID = 0;
  }
  return ret;
}
