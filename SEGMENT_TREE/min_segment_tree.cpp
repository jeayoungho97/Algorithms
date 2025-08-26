#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1e9
using namespace std;

int n, m;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;

	int size = 1;
	while (size < n) {
		size *= 2;
	}
	size *= 2;

	vector<int> segTree(size, MAX);
	for (int i = size / 2; i < size / 2 + n; ++i) {
		cin >> segTree[i];
	}

	for (int i = size - 1; i >= 2; i -= 2) {
		segTree[i / 2] = min(segTree[i], segTree[i - 1]);
	}

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		int start_idx = size / 2 + a - 1;
		int end_idx = size / 2 + b - 1;

		int ret = MAX;
		while (start_idx <= end_idx) {
			if (start_idx & 1) ret = min(ret, segTree[start_idx]);
			if (!(end_idx & 1)) ret = min(ret, segTree[end_idx]);

			start_idx = (start_idx + 1) / 2;
			end_idx = (end_idx - 1) / 2;
		}

		cout << ret << '\n';
	}

	return 0;
}