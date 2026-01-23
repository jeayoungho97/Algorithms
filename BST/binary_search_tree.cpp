#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int left, right, par, visited;
};

Node tree[1000001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int next, now = -1, root;

    cin >> root;
    tree[root].par = now;
    now = root;

    while (cin >> next) {        
        if (next < now) {
            tree[now].left = next;   
        }
        else {
            while (next > tree[now].par && tree[now].par != -1) {
                now = tree[now].par;
            }

            // 자기 자리 찾아가기
            while (true) {
                if (next > now) {
                    if (!tree[now].right) {
                        tree[now].right = next;
                        break;
                    }
                    else {
                        now = tree[now].right;
                    }
                }
                else {
                    if (!tree[now].left) {
                        tree[now].left = next;
                        break;
                    }
                    else {
                        now = tree[now].left;
                    }
                }
            }
        }
        
        tree[next].par = now;
        now = next;
    }

    now = root;

    while (now != -1) {
        if (tree[now].left && !tree[tree[now].left].visited) {
            now = tree[now].left;
        }
        else if (tree[now].right && !tree[tree[now].right].visited) {
            now = tree[now].right;
        }
        else {
            cout << now << '\n';
            tree[now].visited = true;
            now = tree[now].par;
        }
    }

    return 0;
}