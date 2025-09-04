#include <cstdio>   // C 표준 입출력 (standard I/O)
#include <cstring>

#define CMD_INIT 1
#define CMD_NUMBER_OF_CANDIDATE 2
#define CMD_MAX_AREA 3

extern void init(int N, int mMap[20][20]);
extern int numberOfCandidate(int M, int mStructure[5]);
extern int maxArea(int M, int mStructure[5], int mSeaLevel);


static int mMap[20][20];
static int mStructure[5];

static bool run()
{
    int numQuery;
    int N, M, mSeaLevel;
    int userAns, ans;

    bool isCorrect = false;

    if (scanf("%d", &numQuery) != 1) return false;

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        if (scanf("%d", &cmd) != 1) return false;

        switch (cmd)
        {
        case CMD_INIT:
            if (scanf("%d", &N) != 1) return false;
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    scanf("%d", &mMap[j][k]);
            init(N, mMap);
            isCorrect = true;
            break;

        case CMD_NUMBER_OF_CANDIDATE:
            if (scanf("%d", &M) != 1) return false;
            for (int j = 0; j < M; j++)
                scanf("%d", &mStructure[j]);
            userAns = numberOfCandidate(M, mStructure);
            scanf("%d", &ans);

            
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;

        case CMD_MAX_AREA:
            if (scanf("%d", &M) != 1) return false;
            for (int j = 0; j < M; j++)
                scanf("%d", &mStructure[j]);
            scanf("%d", &mSeaLevel);
            userAns = maxArea(M, mStructure, mSeaLevel);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                printf("MAX_AREA ERROR : userAns : %d realAns : %d\n", userAns, ans);
                isCorrect = false;
            }
            
            break;

        default:
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}

int main()
{
    // stdout 버퍼링을 끔 (출력 지연 방지)
    setbuf(stdout, NULL);

    int T, MARK;
    if (scanf("%d %d", &T, &MARK) != 2) return 0;

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}
