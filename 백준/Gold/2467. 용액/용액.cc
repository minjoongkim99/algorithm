#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int ans = 2000000002;
int n;
int arr[100002];
int l, r;
int main() {
    ios::sync_with_stdio(0);
    cout.tie(nullptr);				cin.tie(nullptr);

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    sort(arr, arr + n);

    for(int i = 0; i < n; i++){
        int idx = lower_bound(arr, arr + n, -arr[i]) - arr;

        if(idx - 1 >= 0 && idx - 1 != i){
            if(abs(arr[i] + arr[idx - 1]) < ans) {
                ans = abs(arr[i] + arr[idx - 1]);
                l = i;
                r = idx - 1;
            }
        }
        if(idx < n && idx != i){
            if(abs(arr[i] + arr[idx]) < ans) {
                ans = abs(arr[i] + arr[idx]);
                l = i;
                r = idx;
            }
        }
        if(idx + 1 < n && idx + 1 != i){
            if(abs(arr[i] + arr[idx + 1]) < ans) {
                ans = abs(arr[i] + arr[idx + 1]);
                l = i;
                r = idx + 1;
            }
        }
    }

    if(arr[l] < arr[r])
        cout << arr[l] << ' ' << arr[r] << '\n';
    else cout << arr[r] << ' ' << arr[l] << '\n';
    return 0;
}