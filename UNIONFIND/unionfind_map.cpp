#include <iostream>
#include <map>
#include <string>

int n;
std::map<std::string, std::string> parent;

std::string find(std::string x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void Union(std::string a, std::string b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    parent[b] = a;
}

int main() {
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string a, b;
        std::cin >> a >> b;

        if (parent[a] == "") parent[a] = a;
        if (parent[b] == "") parent[b] = b;

        Union(a, b);
    }


    for (auto & pair : parent) {
        find(pair.first);
    }
    // for (auto & pair : parent) {
    //     std::cout << pair.first << " : " << pair.second << '\n';
    // }

    std::string target;
    std::cin >> target;

    for (const auto& pair : parent) {
        if (pair.second == find(target)) std::cout << pair.first << '\n';
    }


    return 0;
}