// 지역구 나누기
// 완전 탐색, bitmasking

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int ans, n;
int map[9][9];
int voter[9];
vector<int> groupA, groupB;

void init()
{
	ans = 1e9;
}

void dfs(int here, int bitmask, bool isA, int &visited) {
	visited |= (1 << here);

	for (int i = 0; i < n; ++i) {
		if (visited & (1 << i)) continue;
		if (!map[here][i]) continue;
		bool alsoA = (bitmask & (1 << i));
		if (isA != alsoA) continue;

		dfs(i, bitmask, alsoA, visited);
	}
}

bool valid(int bitmask)
{
	groupA.clear();
	groupB.clear();

	for (int i = 0; i < n; ++i) {
		if (bitmask & (1 << i)) groupA.push_back(i);
		else groupB.push_back(i);
	}

	int visited = 0;
	if (!groupA.empty()) dfs(groupA[0], bitmask, 1, visited);
	if (!groupB.empty()) dfs(groupB[0], bitmask, 0, visited);
	if (visited != (1 << n) - 1) return false;

	return true;
}

void solve(int bitmask)
{
	if (!valid(bitmask))
		return;

	int sumA = 0, sumB = 0;
	for (int i = 0; i < n; ++i)
	{
		if (bitmask & (1 << i))
			sumA += voter[i];
		else
			sumB += voter[i];
	}

	ans = min(ans, abs(sumA - sumB));
}

int main()
{
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; ++tc)
	{
		init();

		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cin >> map[i][j];
			}
		}

		for (int i = 0; i < n; ++i)
			cin >> voter[i];

		for (int i = (1 << (n - 1)); i < (1 << n); ++i)
		{ // 중복을 피하기 위해 n - 1 마을은 1 로 고정.
			solve(i);
		}

		cout << '#' << tc << ' ' << ans << '\n';
	}

	return 0;
}