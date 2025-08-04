#include <iostream>
#include <vector>

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    std::vector<int> temp;
    int i = left, j = mid + 1;
    // i : left 의 시작
    // j : right 의 시작

    // arr[i] 와 arr[j] 를 비교하면서 더 작은걸 temp 에 추가, 작은 쪽의 index + 1
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]); // 정렬 조건 ( <= )
        else temp.push_back(arr[j++]);
    }

    // 아직 남아있는 값이 있다면 전부 temp 에 추가
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    // temp 의 값을 arr 에 복사
    for (int k = 0; k < temp.size(); ++k) {
        arr[left + k] = temp[k];
    }
}

void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;

    // mergeSort : 좌우 반반으로 나눠서 각각을 정렬한 후 합치는 것
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main()
{
    std::vector<int> arr = {5, 2, 4, 6, 1, 3};
    mergeSort(arr, 0, arr.size() - 1);
    for (int i : arr)
        std::cout << i << ' ';
    std::cout << '\n';
    return 0;
}