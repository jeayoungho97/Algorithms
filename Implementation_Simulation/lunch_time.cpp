#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct cmp{
	bool operator()(pair<int,int>& l, pair<int,int>& r) const {
		return l.first > r.first;
	}
};

int n, ans;
int map[11][11];
vector<pair<int, int>> people;
vector<pair<pair<int, int>, int>> stair; // pair : coords, int : time

void go(int bitmask) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> arrTime; // arrTime + which stair

	// 사람마다 계단까지 걸리는 시간을 arrTime 에 담음 (걸리는 시간이 작은 순)
	for (int i = 0; i < people.size(); ++i) {
		auto [py, px] = people[i];
		bool which_stair = (bitmask & (1 << i));
		pair<int, int> stair_coord = stair[which_stair].first;

		int estTime = abs(py - stair_coord.first) + abs(px - stair_coord.second);
		arrTime.push({estTime, which_stair});
	} 

	queue<int> stair_go[2]; // 계단 내려가기 시작한 시간, 최대 3명
	queue<int> stair_wait[2]; // 현재 계단에서 기다리고 있는 사람들, 내려갈 수 있는 최소 시간 (도착 시간 + 1)

	int time = 0, cnt = 0;
	while (true) {
		// 계단 내려가는 사람들이 현재 시간에 빠져나갈지 결정
		for (int i = 0; i < 2; ++i) {
			while (!stair_go[i].empty()) {
				int exitTime = stair_go[i].front() + stair[i].second;
				if (exitTime == time) {
					stair_go[i].pop();
					cnt++;
				}
				else break;
			}
		}

		if (cnt == people.size()) break;

		// 계단 내려갈 수 있는 사람 있다면 일단 대기줄에 넣음
		while (!arrTime.empty()) {
			auto now = arrTime.top(); 
			if (now.first == time) {
				stair_wait[now.second].push(now.first + 1);
				arrTime.pop();
			}
			else break;
		}

		// 대기줄에서 계단에 내려갈 수 있다면 보내주기
		for (int i = 0; i < 2; ++i) {
			while (!stair_wait[i].empty()) {
				int goTime = stair_wait[i].front();
				if (stair_go[i].size() < 3 && goTime <= time) {
					stair_go[i].push(time);
					stair_wait[i].pop();
				}
				else break;
			}
		}

		time++;
	}

	// Debugging
	// if (time < ans) {
	// 	cout << time << '\n';
	// 	for (int i = 0; i < people.size(); ++i) {
	// 		bool temp = (bitmask & (1 << i));
	// 		cout << (int)temp << ' ';
	// 	}
	// 	cout << '\n';
	// }


	ans = min(ans, time);
}

int main() {
	// 사람을 비트마스킹해서 0번 계단 갈 사람, 1번 계단 갈 사람으로 나눔	
	int t;
	cin >> t;
	
	for (int tc = 1; tc <= t; ++tc) {
		// init
		ans = 1e9;
		people.clear();
		stair.clear();

		// input
		cin >> n;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cin >> map[i][j];
				if (map[i][j] == 1) people.push_back({i, j});
				if (map[i][j] > 1) stair.push_back({{i, j}, map[i][j]});
			}
		}

		// solve for each case

		// IMPORTANT : MISTAKE
		// n = size of map
		// bitmask => num of people 만큼 해야함!!!!!!!!!!!
		for (int bitmask = 0; bitmask < (1 << people.size()); ++bitmask) {
			go(bitmask);
		}

		cout << '#' << tc << ' ' << ans << '\n';
	}


	return 0;
}