#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[10002][3];
int prv[10002][3];
int arr[10002];
int n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> arr[i];
    }

    dp[1][2] = 0;
    dp[1][1] = arr[1];

    for(int i = 2; i <= n; i++){
        dp[i][2] = dp[i - 1][1] + arr[i];

        dp[i][1] = max(dp[i - 2][0], dp[i - 2][1]);
        dp[i][1] = max(dp[i][1], dp[i - 2][2]);
        dp[i][1] = max(dp[i][1], dp[i - 1][0]);
        dp[i][1] += arr[i];

        dp[i][0] = max(dp[i - 2][0], dp[i - 2][1]);
        dp[i][0] = max(dp[i][0], dp[i - 2][2]);
        dp[i][0] = max(dp[i][0], dp[i - 1][0]);
        dp[i][0] = max(dp[i][0], dp[i - 1][1]);
        dp[i][0] = max(dp[i][0], dp[i - 1][2]);

    }

    
    int ret = 0;
    for(int i = 0; i < 3; i++){
        if(ret < dp[n][i])
            ret = dp[n][i];
    }
    cout << ret << "\n";
}