#include <iostream>
#include <queue>
using namespace std;

// 접수창구 수 N, 정비창구 수 M, 고객수 K
int N, M, K;
// 이용한 접수 창구, 정비 창구 번호
int A, B;

// 접수 창구별 작업 시간
int ai[10];
// 접수 창구별 작업 시간
int bj[10];
// 고객이 입장한 방문시간
int tk[1001];

struct NODE{
    int aNum;
    int bNum;
    int arrive_time;
};
NODE man[1001]; // k의 범위

// 접수 창구로 가기 위한 대기열 -> 접수 창구 (or 정비 창구)에는 온 순서대로 배정
queue<int> aQueue;
int aEndTime[11];
int aPerson[11];

queue<int> bQueue;
int bEndTime[11];
int bPerson[11];

void init(){
    // 사용된 자료구조 전부 초기화

    // 큐 비우기
    while(!aQueue.empty()) aQueue.pop();
    while(!bQueue.empty()) bQueue.pop();

    // 창구 상태 초기화
    for(int i=1;i<=N;i++){
        aEndTime[i] = -1;
        aPerson[i]  = 0;
    }
    for(int i=1;i<=M;i++){
        bEndTime[i] = -1;
        bPerson[i]  = 0;
    }

    // 고객 정보 초기화
    for(int i=1;i<=K;i++){
        man[i].aNum = 0;
        man[i].bNum = 0;
        // arrive_time은 입력에서 채움
    }
}

void solve(){
    // 시간 변수 t
    int t = 0;
    // 시뮬레이션 종료용 변수
    int out = 0;

    // 시뮬을 돌리는 코드 -> 고객 정보를 담은 구조체에 어떤 창구를 갔는지 기록하기
    while(1){
        for(int i = 1; i<= K; i++){
            if(man[i].arrive_time == t) aQueue.push(i);
        }

        for(int i = 1; i<=N; i++){
            if(aEndTime[i] == t){
                aEndTime[i] = -1;
                bQueue.push(aPerson[i]);
            }
        }

        for(int i = 1; i<=N; i++){
            // 접수창구로 가기 위한 고객이 없다면, 넣을 필요가 없음
            if(aQueue.empty()) break;

            // 비어있는 창구가 있다면, 새로운 고객이 접수
            if(aEndTime[i] == -1){
                // 작업 끝나는 시간 : 현재 시간 + 해당 창구에서 작업에 소요되는 시간
                aEndTime[i] = t + ai[i];

                // 대기열 1번 고객 뽑음
                int num = aQueue.front();
                aQueue.pop(); // 찾기+제거하기까지 한 세트
                aPerson[i] = num;
                // 대기열 1번 고객의 접수 창구 번호 기록
                man[num].aNum = i;
            }
        }

        for(int i=1;i<=M;i++){
            if(bEndTime[i] == t){
                bEndTime[i] = -1;
                int finished = bPerson[i];
                bPerson[i] = 0;
                if(finished != 0){
                    out++; 
                }
            }
        }

        for(int i=1;i<=M;i++){
            if(bEndTime[i] == -1 && !bQueue.empty()){
                int num = bQueue.front(); bQueue.pop();
                bPerson[i]  = num;
                man[num].bNum = i;
                bEndTime[i]  = t + bj[i]; 
            }
        }

        if(out == K) break;
        t++;
    }
}


int main(){
    int T;
    cin >> T;

    for(int tc = 1; tc<=T; tc++){
        // init
        // 배열, 구조체, vector, queue 등과 같은 자료구조 초기화 필수
        init();

        // input
        cin >> N >> M >> K >> A >> B ;

        for(int i = 1; i<=N; i++) cin >> ai[i];
        for(int i = 1; i<=M; i++) cin >> bj[i];
        for(int i = 1; i<=K; i++) cin >> man[i].arrive_time;

        // simulate
        solve();

        // result
        int result = 0;
        for(int i = 1; i<=K; i++){
            if(man[i].aNum == A and man[i].bNum == B){
                // 고객번호를 누적해서 출력
                result += i;
            }
        }
        if(result > 0) cout << "#" << tc << " " << result << '\n';
        else cout << "#" << tc << ' ' << -1 << '\n';
    }
    return 0;
}
