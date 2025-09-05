#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_N 20
#define MAX_WIDTH 500

struct Result {
    int ID;
    int height;
    int used;
};

extern void init(int N, int mWidth, int mHeight, int mIDs[], int mLengths[][MAX_WIDTH], int mUpShapes[][MAX_WIDTH]);
extern int checkStructures(int mLengths[3], int mUpShapes[3], int mDownShapes[3]);
extern int addStructures(int mLengths[3], int mUpShapes[3], int mDownShapes[3]);
extern Result pourIn(int mWater);

#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_CHECK 3
#define CMD_POUR 4

static int mIDs[MAX_N];
static int mLengths_tanks[MAX_N][MAX_WIDTH];
static int mUpShapes_tanks[MAX_N][MAX_WIDTH];

int checkr, checkw;


static bool run()
{   
    checkr = 0, checkw = 0;


    int query_num;
    scanf("%d", &query_num);

    int ans;
    bool ok = false;

    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int N, mWidth, mHeight;
            scanf("%d %d %d", &N, &mWidth, &mHeight);
            for (int i = 0; i < N; i++)
            {
                scanf("%d", &mIDs[i]);
            }
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < mWidth; j++)
                    scanf("%d", &mLengths_tanks[i][j]);
            }
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < mWidth; j++)
                    scanf("%d", &mUpShapes_tanks[i][j]);
            }
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
                printf("right ans : %d wrong ans : %d\n", ans, ret);
                checkw++;
            }
            else checkr++;
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
                ok = false;
            }
        }
        else if (query == CMD_POUR)
        {
            int mWater;
            scanf("%d", &mWater);
            Result ret = pourIn(mWater);

            int ans_height = 0;
            int ans_used = 0;
            scanf("%d", &ans);
            if (ans != 0) {
                scanf("%d %d", &ans_height, &ans_used);
            }
            if (ans != 0 && (ans != ret.ID || ans_height != ret.height || ans_used != ret.used))
            {
                ok = false;
            }
            else if (ans == 0 && ret.ID != 0)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    setbuf(stdout, NULL);
     freopen("sample_input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= 1; tc++)
    {
        int score = run() ? MARK : 0;
        printf("check right : %d wrong : %d\n", checkr, checkw);
        printf("#%d %d\n", tc, score);
    }
    return 0;
}