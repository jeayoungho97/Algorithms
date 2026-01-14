#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int val;   
    string path;
};

int A, B;
int visited[10001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        fill(visited, visited + 10001, 1e9);
        queue<Node> q;
        cin >> A >> B;
        visited[A] = 1;
        visited[B] = 0; 
        q.push({A, ""});

        while (!q.empty()) {
            Node now = q.front(); q.pop();
            int cval = now.val;
            string cpath = now.path;
            
            int next;
            int nextvisited = visited[cval] + 1;
            string nextpath;

            // 두 배
            next = (cval * 2) % 10'000;
            nextpath = cpath + "D";


            if (!visited[next] || visited[next] > nextvisited) {
                visited[next] = nextvisited;
                q.push({next, nextpath});
            }

            if (visited[B]) {
                cout << nextpath << '\n';
                break;
            }

            // -1
            next = (cval + 9999) % 10'000;
            nextpath = cpath + "S";
            if (!visited[next] || visited[next] > nextvisited) {
                visited[next] = nextvisited;
                q.push({next, nextpath});
            }

            if (visited[B]) {
                cout << nextpath << '\n';
                break;
            }

            // 왼쪽
            next = (cval * 10) % 10'000 + (cval / 1000);
            nextpath = cpath + "L";
            if (!visited[next] || visited[next] > nextvisited) {
                visited[next] = nextvisited;
                q.push({next, nextpath});
            }

            if (visited[B]) {
                cout << nextpath << '\n';
                break;
            }

            // 오른쪽
            next = (cval / 10) + (cval % 10) * 1000;
            nextpath = cpath + "R";
            if (!visited[next] || visited[next] > nextvisited) {
                visited[next] = nextvisited;
                q.push({next, nextpath});
            }

            if (visited[B]) {
                cout << nextpath << '\n';
                break;
            }
        }
    }

    return 0;
}