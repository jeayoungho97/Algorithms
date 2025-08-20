#include <iostream>
#include <queue>
#include <vector>

/* INPUT
10 12
0 1 23
0 3 8
1 4 100
3 4 10
1 2 26
4 5 50
4 7 11
7 5 777
2 5 35
5 8 5
5 6 1
6 9 53
*/

struct EDGE {
    int num;  // 연결될 곳의 노드 번호
    int cost; // 가중치
    bool operator<(const EDGE& right) const{
        // 1. 가중치 값이 작은 것 우선
        if (cost < right.cost) return false;
        return true;
    }
};

std::vector<EDGE> adj[20];
int dist[20]; // index : 노드 번호, value : 최단 거리
int N, M;

void dijkstra(int start) {
    // 1. 사전 준비
    //   i. PQ 생성(우선순위에 따라 관리)
    std::priority_queue<EDGE> pq;

    //  ii. 정답 배열 초기화(해당 노드까지의 최단거리 저장용)
    std::fill(dist, dist + 20, 1e9);

    // 2. 시작 노드 큐에 등록
    dist[start] = 0;
    pq.push({start, 0});

    // 3 - 5 반복
    while (!pq.empty()) {
        // 3. 최상위 노드 확인 및 추출(now 확정)
        EDGE now = pq.top(); pq.pop();
        // 3-1. dist 확인
        if (dist[now.num] < now.cost) continue;
        // 3-2. dist 확정
        dist[now.num] = now.cost;

        // 4. now -> next 후보 찾기
        for (EDGE next : adj[now.num]) {
            int nextcost = now.cost + next.cost;

            // 4-1. dist 확인
            if (dist[next.num] <= nextcost) continue;

            // 4-2. next 등록 (누적값 + 가중치)
            pq.push({next.num, nextcost});
        }        
    }
}

int main() {
    std::cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        adj[from].push_back({to, cost});
        adj[to].push_back({from, cost});
    }
    dijkstra(0);

    for (int i = 0; i < N; ++i) {
        std::cout << dist[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}