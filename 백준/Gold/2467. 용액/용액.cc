#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
int arr[100005];
int val = 2000000000;
long st, en;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);

    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    for(int i = 0; i < n; i++){
        long idx = lower_bound(arr, arr + n, -arr[i]) - &arr[0];

        if(idx < n && idx != i) {
            if (abs(arr[idx] + arr[i]) < abs(val)) {
                val = abs(arr[idx] + arr[i]);
                st = idx;
                en = i;
            }
        }

        if(idx - 1 < n && idx - 1 != i && idx - 1 >= 0) {
            if (abs(arr[idx - 1] + arr[i]) < abs(val)) {
                val = abs(arr[idx - 1] + arr[i]);
                st = idx - 1;
                en = i;
            }
        }
        if(idx + 1 < n && idx + 1 != i && idx + 1 >= 0) {
            if (abs(arr[idx + 1] + arr[i]) < abs(val)) {
                val = abs(arr[idx + 1] + arr[i]);
                st = idx + 1;
                en = i;
            }
        }

    }
    
    if(arr[st] < arr[en])
        cout << arr[st] << " " << arr[en] << "\n";
    else
        cout << arr[en] << " " << arr[st] << "\n";
    return 0;
}
