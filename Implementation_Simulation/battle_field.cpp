#include <iostream>
#include <string>
using namespace std;

// 포탄 발사시 벽에 충돌 / 맵 탈출 시 소멸
// 벽돌벽은 평지가 되고 강철벽은 '아무 일도 없었다.'
struct TANK
{
    int y, x, dir;
};

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
int ans;
int h, w, n;
string input;
char map[21][21];
TANK tank;

void shoot()
{
    int ny = tank.y;
    int nx = tank.x;
    while (true)
    {
        ny += dy[tank.dir];
        nx += dx[tank.dir];

        if (ny < 0 || nx < 0 || ny >= h || nx >= w)
            break;

        if (map[ny][nx] == '*')
        {
            map[ny][nx] = '.';
            break;
        }
        else if (map[ny][nx] == '#')
            break;
    }
}

void MOVE(int dir)
{
    tank.dir = dir;
    int ny = tank.y + dy[dir];
    int nx = tank.x + dx[dir];
    if (ny < 0 || nx < 0 || ny >= h || nx >= w)
        return;
    if (map[ny][nx] == '.')
        tank.y = ny, tank.x = nx;
}

int main()
{
    int t;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc)
    {
        // init

        // input
        cin >> h >> w;
        for (int i = 0; i < h; ++i)
        {
            string temp;
            cin >> temp;
            for (int j = 0; j < w; ++j)
            {
                map[i][j] = temp[j];
                if (map[i][j] == '^')
                {
                    tank = {i, j, 0};
                    map[i][j] = '.';
                }
                else if (map[i][j] == '>')
                {
                    tank = {i, j, 1};
                    map[i][j] = '.';
                }
                else if (map[i][j] == 'v')
                {
                    tank = {i, j, 2};
                    map[i][j] = '.';
                }
                else if (map[i][j] == '<')
                {
                    tank = {i, j, 3};
                    map[i][j] = '.';
                }
            }
        }

        cin >> n;
        cin >> input;

        // solve
        for (int i = 0; i < n; ++i)
        {
            char now = input[i];
            switch (now)
            {
            case 'S':
                shoot();
                break;

            case 'U':
                MOVE(0);
                break;

            case 'R':
                MOVE(1);
                break;

            case 'D':
                MOVE(2);
                break;

            case 'L':
                MOVE(3);
                break;
            }
        }

        char &ch = map[tank.y][tank.x];
        switch (tank.dir)
        {
        case 0:
            ch = '^';
            break;
        case 1:
            ch = '>';
            break;
        case 2:
            ch = 'v';
            break;
        case 3:
            ch = '<';
            break;
        }

        cout << '#' << tc << ' ';
        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                cout << map[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}