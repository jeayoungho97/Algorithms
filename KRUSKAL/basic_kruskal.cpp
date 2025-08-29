// 크루스칼은?
// 간선의 길이를 최솟값으로 정렬한 뒤
// 최단 간선부터 두 정점이 같은 집합이 아니라면 연결하는 식으로 반복
// 모든 간선이 연결됐는지를 count 한 뒤 출력.
#include <iostream>
#include <algorithm>
using namespace std;

struct NODE {
  // 두 정점과 간선의 가중치
	int x1, x2, cost;
	bool operator<(const NODE& r) const {
		return cost < r.cost;
	}
};

int v, e;
NODE edge[100001];
int parent[10001];

int find(int x) {
  // parent 가 0 이라는 것은 아직 아무런 곳에 연결되지 않았다는 것
	if (parent[x] == 0) return x;

  // parent 가 존재할 경우 경로 압축을 해가며 최상위 parent 를 찾고 그것을 반환
	return parent[x] = find(parent[x]);
}

bool UNION(int x1, int x2) {
  // 두 정점의 부모(그룹명)를 찾음
	x1 = find(x1);
	x2 = find(x2);

  // 서로 같은 그룹이면 false 반환
	if (x1 == x2) return false;

  // 다른 그룹이라면 하나의 그룹으로 합치고 true 반환
	parent[x2] = x1;
	return true;
}

int main() {
  // v : 정점, e : 간선
	cin >> v >> e;

	for (int i = 0; i < e; ++i) {
    // a 와 b 가 c 의 cost 로 연결돼있음
		int a, b, c;
		cin >> a >> b >> c;
		edge[i] = { a, b, c };
	}

  // cost 가 가장 작은게 먼저 오도록 정렬
	sort(edge, edge + e);

	int sum = 0, cnt = 0;
	for (int i = 0; i < e; ++i) {
    // 최소 간선부터 조회하는데, 두 정점이 서로 같은 집합이 아니라면 간선을 연결함
		if (UNION(edge[i].x1, edge[i].x2)) {
			sum += edge[i].cost;
			cnt++;
		}
	}

  // 모든 간선이 연결이 되었다면 정상 출력
	if (cnt == v - 1) cout << sum << '\n';
	else std::cout << -1 << '\n';

	return 0;
}