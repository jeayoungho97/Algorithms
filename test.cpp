#include <iostream>
#include <vector>
#include <algorithm>

struct atom {
    int x, y, dir, energy;
};

struct node {
    int p1, p2;
    double time;

    bool operator<(node right){
        return time < right.time;
    }
};

int atom_cnt, ans;
std::vector<atom> atoms;
double bang_time[1001][1001]; // 두 원자가 부딪히는 시간 : 소수까지 표현

int Quad(int x, int y) {
    if (x > 0 && y > 0) return 1;
    if (x < 0 && y > 0) return 2;
    if (x < 0 && y < 0) return 3;
    if (x > 0 && y < 0) return 4;
    if (x == 0) return 5;
    if (y == 0) return 6;
}

void check(int a, int b) {
    int dx = atoms[b].x - atoms[a].x;
    int dy = atoms[b].y - atoms[a].y;
    int dir1 = atoms[a].dir;
    int dir2 = atoms[b].dir;

    if (std::abs(dx) == std::abs(dy)) {
        double val = std::abs(dx);
        int quad = Quad(dx, dy);
        // SUPER HARD CODING
        switch(dir1) {
            case 0 :
            if (quad == 1 && dir2 == 2) bang_time[a][b] = std::min(bang_time[a][b], val);
            if (quad == 2 && dir2 == 3) bang_time[a][b] = std::min(bang_time[a][b], val);
            break;

            case 1 :
            if (quad == 3 && dir2 == 3) bang_time[a][b] = std::min(bang_time[a][b], val);
            if (quad == 4 && dir2 == 2) bang_time[a][b] = std::min(bang_time[a][b], val);
            break;

            case 2 :
            if (quad == 2 && dir2 == 1) bang_time[a][b] = std::min(bang_time[a][b], val);
            if (quad == 3 && dir2 == 0) bang_time[a][b] = std::min(bang_time[a][b], val);
            break;

            case 3 : 
            if (quad == 4 && dir2 == 0) bang_time[a][b] = std::min(bang_time[a][b], val);
            if (quad == 1 && dir2 == 1) bang_time[a][b] = std::min(bang_time[a][b], val);
            break;
        }
    }
    else if (dx == 0 || dy == 0) {
        int quad = Quad(dx, dy);
        if (dir1 == 0){
            double val = std::abs(dy) / 2.0;
            if (quad == 5 && dir2 == 1) bang_time[a][b] = std::min(bang_time[a][b], val);
        } 
        if (dir1 == 1){
            double val = std::abs(dy) / 2.0;
            if (quad == 5 && dir2 == 0) bang_time[a][b] = std::min(bang_time[a][b], val);
        }
        if (dir1 == 2){
            double val = std::abs(dx) / 2.0;
            if (quad == 6 && dir2 == 3) bang_time[a][b] = std::min(bang_time[a][b], val);
        }
        if (dir1 == 3){
            double val = std::abs(dx) / 2.0;
            if (quad == 6 && dir2 == 2) bang_time[a][b] = std::min(bang_time[a][b], val);
        }
    }
}

int main() {
    int t;
    std::cin >> t;
    
    for (int tc = 1; tc <= t; ++tc) {
        // 초기화
        std::fill(&bang_time[0][0], &bang_time[0][0] + 1001 * 1001, 1e9);
        atoms.clear();
        ans = 0;

        // 입력
        std::cin >> atom_cnt;
        atoms.resize(atom_cnt);

        for (int i = 0; i < atom_cnt; ++i) {
            int x, y, dir, energy;
            std::cin >> x >> y >> dir >> energy;

            atoms[i] = {x,y,dir,energy};
        }

        for (int i = 0; i < atom_cnt; ++i) {
            for (int j = i + 1; j < atom_cnt; ++j) {
                check(i, j);
            }
        }

        std::vector<bool> dead(atom_cnt);
        std::vector<node> bangbangbang;

        // 시간 빠른 순서대로 충돌시켜버림
        for (int i = 0; i < atom_cnt; ++i) {
            for (int j = i + 1; j < atom_cnt; ++j) {
                if (bang_time[i][j] != 0) bangbangbang.push_back({i, j, bang_time[i][j]});
            }
        }

        std::sort(bangbangbang.begin(), bangbangbang.end());

        double cur_time = -1;
        std::vector<int> to_die;
        bool visited[1001];
        // 죽일놈들 중복 제거하고 to_die 에 담아서 시간 바뀌면 한번에 죽여버림!
        for (node nd : bangbangbang) {
            if (nd.time != cur_time) {
                std::fill(visited, visited + 1001, 0);
                cur_time = nd.time;
                for (int i : to_die) {
                    dead[i] = 1;
                    ans += atoms[i].energy;
                }
                to_die.clear();
            }

            if (nd.time == 1e9 || dead[nd.p1] || dead[nd.p2]) continue;

            if (!visited[nd.p1]) {
                visited[nd.p1] = 1;
                to_die.push_back(nd.p1);
            }
            if (!visited[nd.p2]) {
                visited[nd.p2] = 1;
                to_die.push_back(nd.p2);
            }
        }

        for (int i : to_die) {
            ans += atoms[i].energy;
        }

        std::cout << '#' << tc << ' ' << ans << '\n';
    }


    return 0;
}