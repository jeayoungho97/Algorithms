// 1. 기저 조건
//    - 1 ~ 12월 이용계획을 모두 확인
//

#include <iostream>
#define min(a,b) (a>b?b:a)

int T;

int day1;   // 1일 이용권의 요금
int month1; // 1달 이용권의 요금
int month3; // 3달 이용권의 요금
int year1;  // 1년 이용권의 요금
int ans;

int year[13]; // 1월부터 12월까지의 이용 계획
bool visited[13];
int sum;

void func(int now)
{
    // 1. 기저 조건
    if (now > 12) {
        if (sum < ans) {
            ans = sum;
        }
        return;
    }

    // 2. 재귀 기본형
    //  수영하지 않는 달
    if (year[now] == 0) func(now + 1); // 다음달로 진행

    // 1일 or 1달  
    sum += min(year[now] * day1, month1);
    func(now + 1);
    sum -= min(year[now] * day1, month1);

    // 3달
    sum += month3;
    func(now + 3);
    sum -= month3;
    

}

int main()
{
    std::cin >> T;
    for (int tc = 1; tc <= T; ++tc)
    {
        // reset
        ans = 1e9;

        // input
        std::cin >> day1 >> month1 >> month3 >> year1;
        for (int i = 1; i <= 12; ++i)
        {
            std::cin >> year[i];
        }

        // solve
        func(1);

        // 1년짜리와 비교도 필요함
        if (ans > year1) ans = year1;

        std::cout << '#' << tc << ' ' << ans << '\n';
    }

    return 0;
}