#include <iostream>
#include <vector>
#include <queue>

int ans;

void solve()
{
    // 접수, 정비, 고객 번호 모두 1부터 시작
    int n, m, k, a, b;
    std::cin >> n >> m >> k >> a >> b;


    // 문제 : 같은 시간에 도착하는 고객들이 있음 => 고객의 번호, 도착시간을 모두 저장
    std::vector<int> recTime(n + 1, 0), repTime(m + 1, 0);                                      // 접수, 수리 번호 별 걸리는 시간
    std::queue<std::pair<int,int>> cusTime;                                                     // {고객 번호, 정비소 도착시간}  
    std::vector<std::pair<int, int>> cusWent(k + 1);                                            // 고객(idx) : {접수번호, 수리번호}
    std::vector<std::pair<int, int>> recVisited(n + 1, {0, 0}), repVisited(m + 1, {0, 0});      // visited 값은 고객번호, 고객 받은 시간
    int finished = 0;                                                                           // 정비 끝날 때마다 finished++ => finished == k 이면 while 문 탈출

    for (int i = 1; i <= n; ++i) std::cin >> recTime[i];
    for (int i = 1; i <= m; ++i) std::cin >> repTime[i];
    for (int i = 1; i <= k; ++i) {
        int arrTime;
        std::cin >> arrTime;
        cusTime.push({i, arrTime});
    }

    int time = 0;
    std::queue<int> waitRec, waitRep;
    while (true) {

        // time 에 도착한 고객이 있으면 큐에 푸시
        while (!cusTime.empty()) {
            int cusNum = cusTime.front().first;
            int arrTime = cusTime.front().second;

            if (arrTime == time) {
                waitRec.push(cusNum);
                cusTime.pop();
            }
            else {
                break;
            }
        }

        // 접수 끝난 손님 먼저 waitRep 에 보내고
        // 접수 창구에 낮은 번호 순으로 대기하는 손님을 배정 (손님이 있는 경우)
        for (int i = 1; i <= n; ++i) {
            int& receptionNum = recVisited[i].first; // 접수 창구에 있는 고객의 번호    ==> 아오 이거 reference 처리 안했다가 두번째 if 문에서 걸러져가지고 계속 틀렸음
            int& arrivedTime = recVisited[i].second; // 접수 창구에 고객이 도착한 시간

            // 접수 끝난 경우
            if (receptionNum && time == arrivedTime + recTime[i]) {         
                waitRep.push(receptionNum); // 정비 창구 대기줄에 넣고
                recVisited[i] = {0, 0};   // 접수 창구 비워준다
            }

            // 접수 창구 비어있고 대기 고객이 있다면
            if (!receptionNum && !waitRec.empty()) {
                int customer = waitRec.front();
                cusWent[customer].first = i; // 고객이 어느 접수창구에 가는지 기록
                recVisited[i] = {customer, time}; // 접수창구에 접수
                waitRec.pop(); // 대기줄에서 지움
            }
        }

        // 정비 창구
        for (int i = 1; i <= m; ++i) {
            int& repairNum = repVisited[i].first;
            int& arrivedTime = repVisited[i].second;

            // 정비 끝난 경우
            if (repairNum && time == arrivedTime + repTime[i]) {
                repVisited[i] = {0, 0}; // 정비 창구 비워준다
                finished++;
            }

            // 정비 창구 비어있고 대기 고객 있다면
            if (!repairNum && !waitRep.empty()) {
                int customer = waitRep.front();
                cusWent[customer].second = i; // 고객이 어느 정비창구에 가는지 기록
                repVisited[i] = {customer, time}; // 정비창구에 접수
                waitRep.pop(); // 대기줄에서 지움
            }
        }


        if (finished == k) break;

        time++;
    }
    for (int i = 1; i <= k; ++i) {
        if (cusWent[i].first == a && cusWent[i].second == b) ans += i;
    }
}

int main()
{
    int t;
    std::cin >> t;

    for (int tc = 1; tc <= t; ++tc)
    {
        ans = 0;
        solve();
        if (ans == 0) ans = -1;
        
        std::cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}