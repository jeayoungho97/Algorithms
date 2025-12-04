// BOJ 11478 서로 다른 부분 문자열의 개수
#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
    string str;
    cin >> str;

    set<string> s;
    
    for (int i = 0; i < str.length(); ++i) {
        for (int j = i; j < str.length(); ++j) {
            string sub = str.substr(i, j - i + 1);
            s.insert(sub);
        }
    }

    cout << s.size() << '\n';

    return 0;
}