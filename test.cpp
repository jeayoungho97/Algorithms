#include <iostream>
#include <vector>
#include <algorithm>
#define min(a,b) (a>b?b:a)
#define max(a,b) (a>b?a:b)
using namespace std;

struct pos {
    int ind, x1, x2;
    bool operator<(const pos& r) {
        if (x1 == r.x1) {
            return x2 < r.x2;
        }
        return x1 < r.x1;
    }
};

vector<pos> v;
int v_ind[100001];


int main() {
    int n, q, x1, x2, y, i, ind;
    cin >> n >> q;
    for (i = 1; i <= n; i++) {
        cin >> x1 >> x2 >> y;
        v.push_back({ i, x1, x2});
        v_ind[i] = i - 1;
    }
    sort(v.begin(), v.end());
    for (i = 1; i < v.size(); i++) {
        if (v[i].x1 <= v[i - 1].x2 && v[i].x2 >= v[i - 1].x1) {
            v[i].x1 = min(v[i - 1].x1, v[i].x1);
            v[i].x2 = max(v[i - 1].x2, v[i].x2);
            v_ind[v[i].ind] = v_ind[v[i - 1].ind];
        }
    }
    for (i = 0; i < q; i++) {
        cin >> x1 >> x2;
        if (v_ind[x1] == v_ind[x2]) {
            cout << 1 << '\n';
        }
        else {
            cout << 0 << '\n';
        }
    }
    return 0;
}