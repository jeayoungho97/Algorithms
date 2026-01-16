#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> ret;
vector<bool> truth;
vector<int> par;
int N, M;

int find(int x) {
    if (par[x] == -1) return x;
    return par[x] = find(par[x]);
}

void Union(int a, int b) {
    a = find(a), b = find(b);

    if (a != b) {
        par[b] = a;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    par.resize(N + 1, -1);

    int true_num;
    cin >> true_num;

    truth.resize(N + 1, false);

    for (int i = 0 ; i < true_num; ++i) {
        int person;
        cin >> person;
        truth[person] = true;
    }

    for (int i = 0; i < M; ++i) {
        int party_num;
        cin >> party_num;

        vector<int> v(party_num);
        cin >> v[0];

        for (int j = 1; j < party_num; ++j) {
            int person;
            cin >> person;
            v[j] = person;

            Union(v[0], v[j]);
        }

        ret.push_back(v);
    }

    for (int i = 1; i <= N; ++i) {
        find(i);
    }

    for (int i = 1; i <= N; ++i) {
        if (truth[i]) truth[find(i)] = true;
    }

    int ans = 0;
    for (vector<int> &v : ret) {
        bool isTrue = false;
        for (int &person : v) {
            if (par[person] == -1) {
                if (!truth[person]) isTrue = true;
            }
            else if (!truth[par[person]]) isTrue = true;
        }

        if (isTrue) ans++;
    }

    cout << ans << '\n';

    return 0;
}