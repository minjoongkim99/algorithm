#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int arr[1002];
int dp[1002];
int mx = -100002;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);    cout.tie(nullptr);

    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        dp[i] = arr[i];
    }

    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(arr[i] > arr[j]){
                if(dp[j] + arr[i] > dp[i]){
                    dp[i] = dp[j] + arr[i];
                }
            }
            else continue;
        }


    }

    mx = *max_element(dp, dp + n);
    cout << mx << '\n';
    return 0;
}