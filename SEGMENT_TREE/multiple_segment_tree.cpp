#include <iostream>
#include <vector>
#define MAX 1e9
#define ll long long
#define divider (ll)1'000'000'007
using namespace std;
int n, m, k;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m >> k;
	int size = 1;
	while (size < n) {
		size *= 2;
	}
	size *= 2;

	vector<ll> segTree(size, 1);

	for (int i = 0; i < n; ++i) {
		int idx = i + size / 2;
		cin >> segTree[idx];
	}

	for (int i = size - 1; i >= 2; i -= 2) {
		segTree[i / 2] = segTree[i] * segTree[i - 1];
		segTree[i / 2] %= divider;
	}

	for (int i = 0; i < m + k; ++i) {
		int a;
		cin >> a;
		if (a == 1) {
			// UPDATE
			int b;
			ll c;
			cin >> b >> c;

			int idx = b + size / 2 - 1;
			segTree[idx] = c;

			while (idx > 1) {
				segTree[idx / 2] = segTree[idx / 2 * 2] * segTree[idx / 2 * 2 + 1];
				segTree[idx / 2] %= divider;
				idx /= 2;
			}
		}
		else if (a == 2) {
			// QUERY
			int b, c;
			cin >> b >> c;
			int start_idx = b + size / 2 - 1;
			int end_idx = c + size / 2 - 1;

			ll ret = 1;
			while (start_idx <= end_idx) {
				if (start_idx & 1) {
					ret *= segTree[start_idx];
					ret %= divider;
				}
				
				if ((end_idx & 1) == 0) {
					ret *= segTree[end_idx];
					ret %= divider;
				}

				start_idx = (start_idx + 1) / 2;
				end_idx = (end_idx - 1) / 2;
			}

			cout << ret << '\n';
		}
	}

	return 0;
}