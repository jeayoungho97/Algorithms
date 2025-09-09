#include <queue>
#include <vector>
#include <map>
using namespace std;

struct NODE {
  int num, cost, power, id;
    bool operator<(const NODE& r) const {
    return cost > r.cost;
  }
};

struct STATE {
  int time, power;
};

const int MAX = 1e9;
int n;
int Charge[501];
STATE city[501];
int virusTime[501];
vector<NODE> adj[501];
unordered_map<int, bool> Alive;

void init(int N, int mCharge[], int K, int mId[], int sCity[], int eCity[], int mTime[], int mPower[]) {  
  n = N;

  Alive.clear();

  for (int i = 0; i < n; ++i) {
    adj[i].clear();
  }

  for (int i = 0; i < n; ++i) {
    Charge[i] = mCharge[i];
  }

  for (int i = 0; i < K; ++i) {
    adj[sCity[i]].push_back({eCity[i], mTime[i], mPower[i], mId[i]});
    Alive[mId[i]] = true;
  }
  return;
}

void add(int mId, int sCity, int eCity, int mTime, int mPower) {
  adj[sCity].push_back({eCity, mTime, mPower, mId});
  Alive[mId] = true;
	return;
}

void remove(int mId) {
  Alive[mId] = false;
	return;
}

int cost(int B, int sCity, int eCity, int M, int mCity[], int mTime[]) {
  // multi source dijkstra
  priority_queue<NODE> pq;
  fill(virusTime, virusTime + n, MAX);
  for (int i = 0; i < M; ++i) {
    pq.push({mCity[i], mTime[i]});
    virusTime[mCity[i]] = mTime[i];
  }

  // 전염병 먼저 모든 도시까지 도달하는 시간 계산
  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();
    if (virusTime[now.num] < now.cost) continue;

    for (NODE next : adj[now.num]) {
      int nextcost = now.cost + next.cost;
      if (virusTime[next.num] > nextcost) {
        virusTime[next.num] = nextcost;
        pq.push({next.num, nextcost});
      }
    }
  }

  STATE filler = {MAX, 0};
  fill(city, city + n, filler);

  NODE car;
  car.num = sCity;
  car.power = B;
  pq.push(car);
  city[sCity] = {0, B};

  while (!pq.empty()) {
    NODE now = pq.top(); pq.pop();
    if (city[now.num].time <= now.cost && city[now.num].power > now.power) continue;

    for (NODE next : adj[now.num]) {
      int cur_pow = now.power;  // 현 시점 차의 배터리
      int cur_charge = Charge[now.num]; // 현 도시의 시간당 충전량
      int pass_time = next.cost; // 다음 도시로 넘어가는 시간
      int pass_pow = next.power; // 다음 도시로 넘어가는 소모량
      int road_id = next.id; // 다음 도시로 가는 도로의 id

      while (cur_pow < pass_pow) {
        cur_pow += cur_charge;
        pass_time++;
      }
      if (cur_pow > B) cur_pow = B;

      while (cur_pow <= B) {
        int nextcost = now.cost + pass_time;
        int nextpow = cur_pow - pass_pow;
        if (virusTime[next.num] <= nextcost) break;
        if (city[next.num].time < nextcost && city[next.num].power > nextpow) continue;

        if (city[next.num].time > nextcost) {
          city[next.num].time = nextcost;
          city[next.num].power = nextpow;
        }

        pq.push({next.num, nextcost, nextpow});

        cur_pow += cur_charge;
        if (cur_pow > B) cur_pow = B;

        pass_time++;
      }

    }
  }

  if (city[eCity].time >= MAX) return -1;

	return city[eCity].time;
}