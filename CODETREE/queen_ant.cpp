#include <iostream>
#include <vector>
using namespace std;

struct NODE {
  int num;
  bool isAlive;
};

int N, alive = 0;
vector<NODE> v = {NODE{0, false}};

int check(int val) {
  int vsize = v.size();
  long long start = -1;
  int i;
  for (i = 1; i < vsize; ++i) {
    if (v[i].isAlive) {
      start = v[i].num;
      break;
    }
  }

  int cnt = 1;
  for (i + 1; i < vsize; ++i) {
    if (!v[i].isAlive) continue;

    if (v[i].num - start > val) {
      start = v[i].num;
      cnt++;
    }
  }

  return cnt;
}

long long BS(int r) {
  long long start = 0, end = 0;
  for (int i = v.size() - 1; i >= 0; --i) {
    if (v[i].isAlive) {
      end = v[i].num;
      break;
    }
  }
  long long ret = -1;

  while (start <= end) {
    long long mid = (start + end) / 2;
    // cout << "start : " << start << " end : " << end << " mid : " << mid << '\n';

    int cnt = check(mid);
    if (cnt <= r) {
      ret = mid;
      end = mid - 1;
    }
    else if (cnt > r){
      start = mid + 1;
    }
  }

  // cout << "result : " << ret << '\n';
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int Q;
  cin >> Q;

  for (int query = 0; query < Q; ++query) {
    int qnum; cin >> qnum;

    if (qnum == 100) {
      cin >> N;
      alive = N;
      for (int i = 1; i <= N; ++i) {
        
        int dist;
        cin >> dist;
        v.push_back({dist, true});
      }
    }
    
    if (qnum == 200) {
      alive++;
      int p;
      cin >> p;
      v.push_back({p, true});
    }

    if (qnum == 300) {
      alive--;
      int q;
      cin >> q;
      v[q].isAlive = false;
    }

    if (qnum == 400) {
      int r;
      cin >> r;

      if (r == alive || r == alive + 1) cout << 0 << '\n';
      else cout << BS(r) << '\n';
    }
  }

  return 0;
}
