// main.c
#ifdef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#include <stdio.h>
#include <stdbool.h> // C 표준 bool
#include <stdlib.h>

#define MAX_N 20
#define MAX_WIDTH 500

struct Result
{
  int ID;
  int height;
  int used;
};

/*
    외부 구현(사용자 솔루션)이 있어야 합니다.
    solution.c(또는 solution.cpp)에 아래 4개 함수를 반드시 정의하세요.
*/
extern void init(int N, int mWidth, int mHeight, int mIDs[], int mLengths[][MAX_WIDTH], int mUpShapes[][MAX_WIDTH]);
extern int checkStructures(int mLengths[3], int mUpShapes[3], int mDownShapes[3]);
extern int addStructures(int mLengths[3], int mUpShapes[3], int mDownShapes[3]);
extern struct Result pourIn(int mWater);

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_CHECK 3
#define CMD_POUR 4

static int mIDs[MAX_N];
static int mLengths_tanks[MAX_N][MAX_WIDTH];
static int mUpShapes_tanks[MAX_N][MAX_WIDTH];

int checkr, checkw, addr, addw;

static bool run(void)
{
  checkr = 0;
  checkw = 0;
  addr = 0;
  addw = 0;

  int query_num;
  if (scanf("%d", &query_num) != 1)
    return false;

  int ans;
  bool ok = false;

  for (int q = 0; q < query_num; q++)
  {
    int query;
    if (scanf("%d", &query) != 1)
      return false;

    if (query == CMD_INIT)
    {
      int N, mWidth, mHeight;
      if (scanf("%d %d %d", &N, &mWidth, &mHeight) != 3)
        return false;

      for (int i = 0; i < N; i++)
        scanf("%d", &mIDs[i]);

      for (int i = 0; i < N; i++)
        for (int j = 0; j < mWidth; j++)
          scanf("%d", &mLengths_tanks[i][j]);

      for (int i = 0; i < N; i++)
        for (int j = 0; j < mWidth; j++)
          scanf("%d", &mUpShapes_tanks[i][j]);

      init(N, mWidth, mHeight, mIDs, mLengths_tanks, mUpShapes_tanks);
      ok = true;
    }
    else if (query == CMD_CHECK)
    {
      int mLengths[3];
      int mUpShapes[3];
      int mDownShapes[3];

      for (int i = 0; i < 3; i++)
        scanf("%d", &mLengths[i]);
      for (int i = 0; i < 3; i++)
        scanf("%d", &mUpShapes[i]);
      for (int i = 0; i < 3; i++)
        scanf("%d", &mDownShapes[i]);

      int ret = checkStructures(mLengths, mUpShapes, mDownShapes);

      scanf("%d", &ans);
      if (ans != ret)
      {
        ok = false;
        // printf("\nright ans : %d wrong ans : %d\n\n", ans, ret);
        checkw++;
      }
      else
      {
        checkr++;
      }
    }
    else if (query == CMD_ADD)
    {
      int mLengths[3];
      int mUpShapes[3];
      int mDownShapes[3];

      for (int i = 0; i < 3; i++)
        scanf("%d", &mLengths[i]);
      for (int i = 0; i < 3; i++)
        scanf("%d", &mUpShapes[i]);
      for (int i = 0; i < 3; i++)
        scanf("%d", &mDownShapes[i]);

      int ret = addStructures(mLengths, mUpShapes, mDownShapes);

      scanf("%d", &ans);
      if (ans != ret)
      {
        printf("\nright ans : %d wrong ans : %d\n\n", ans, ret);
        ok = false;
        addw++;
      }
      else
      {
        addr++;
      }
    }
    else if (query == CMD_POUR)
    {
      int mWater;
      scanf("%d", &mWater);

      struct Result ret = pourIn(mWater);

      int ans_height = 0;
      int ans_used = 0;

      scanf("%d", &ans);
      if (ans != 0)
      {
        scanf("%d %d", &ans_height, &ans_used);
      }

      if (ans != 0 && (ans != ret.ID || ans_height != ret.height || ans_used != ret.used))
      {
        ok = false;
        // printf("right ans : %d %d %d, wrong ans : %d %d %d\n", ans, ans_height, ans_used, ret.ID, ret.height, ret.used);
      }
      else if (ans == 0 && ret.ID != 0)
      {
        ok = false;
        // printf("right ans : ID = 0, wrong ans : ID = %d\n", ret.ID);
      }
    }
    else
    {
      // 정의되지 않은 명령 방어
      ok = false;
    }
  }

  return ok;
}

int main(void)
{
  setbuf(stdout, NULL);

  // sample_input.txt 가 같은 폴더에 있을 때만 freopen 시도 (선택 사항)
  // macOS에서는 아래처럼 입력 리다이렉션 사용을 권장합니다:  ./app < sample_input.txt
  FILE *fp = fopen("sample_input.txt", "r");
  if (fp)
  {
    freopen("sample_input.txt", "r", stdin);
  }

  int T, MARK;
  if (scanf("%d %d", &T, &MARK) != 2)
    return 0;

  for (int tc = 1; tc <= T; tc++)
  {
    int score = run() ? MARK : 0;

    printf("#%d %d\n", tc, score);
  }
  return 0;
}
