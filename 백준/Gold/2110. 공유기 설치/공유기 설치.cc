#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n, c;
int arr[200003];
int st, en;

bool para_search(int mid){
    int idx = 0, cnt = 0;

    while(idx != n){
        idx = lower_bound(arr + idx, arr + n, arr[idx] + mid) - arr;
        cnt++;
    }
    return cnt >= c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);    cout.tie(nullptr);

    cin >> n >> c;

    for(int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);

    st = 1;
    en = *max_element(arr, arr + n);

    while(st < en){
        int mid = (st + en + 1) / 2;

        if(para_search(mid)){
            st = mid;
        }
        else en = mid - 1;
    }

    cout << st << '\n';
}