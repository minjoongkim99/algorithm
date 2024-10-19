#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cmath>
using namespace std;

int n;
int arr[501][501];
int dp[501][501];
int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= i; j++){
            cin >> arr[i][j];
        }
    }

    dp[0][0] = arr[0][0];

    for(int i = 1; i < n; i++){
        for(int j = 0; j <= i; j++){
            if(j == 0){
                dp[i][j] = dp[i - 1][0] + arr[i][j];
            }
            else if(j == i){
                dp[i][j] = dp[i - 1][i - 1] + arr[i][j];
            }
            else {
                dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + arr[i][j];
            }
        }
    }

    int mx = 0;
    for(int i = 0; i < n; i++){
        if(mx < dp[n - 1][i])
            mx = dp[n - 1][i];
    }
    cout << mx << '\n';
    return 0;
}