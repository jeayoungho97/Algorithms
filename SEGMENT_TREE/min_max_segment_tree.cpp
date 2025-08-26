#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1e9
#define ll long long
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

	vector<ll> minSeg(size, MAX);
	vector<ll> maxSeg(size, 0);

	for (int i = 0; i < n; ++i) {
		int idx = size / 2 + i;
		int temp;
		cin >> temp;
		minSeg[idx] = temp;
		maxSeg[idx] = temp;
	}

	for (int i = size - 1; i >= 2; --i) {
		minSeg[i / 2] = min(minSeg[i / 2], minSeg[i]);
		maxSeg[i / 2] = max(maxSeg[i / 2], maxSeg[i]);
	}

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		int start_idx = a + size / 2 - 1;
		int end_idx = b + size / 2 - 1;

		ll minVal = MAX, maxVal = 0; 
		while (start_idx <= end_idx) {
			if (start_idx & 1) {
				minVal = min(minVal, minSeg[start_idx]);
				maxVal = max(maxVal, maxSeg[start_idx]);
			}
			if ((end_idx & 1) == 0) {
				minVal = min(minVal, minSeg[end_idx]);
				maxVal = max(maxVal, maxSeg[end_idx]);
			}

			start_idx = (start_idx + 1) / 2;
			end_idx = (end_idx - 1) / 2;
		}

		cout << minVal << ' ' << maxVal << '\n';
	}
	return 0;
}