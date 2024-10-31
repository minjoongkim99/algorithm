#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[100002][3];
int dp[100002][3];
int main() {
    ios::sync_with_stdio(0);
    cout.tie(nullptr);				cin.tie(nullptr);

    int testcase = 1;
    while(true) {
        cin >> n;
        if(n == 0) break;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> arr[i][j];
                dp[i][j] = 100000000;
            }
        }

        dp[0][1] = arr[0][1];
        dp[0][2] = min(dp[0][2], dp[0][1] + arr[0][2]);

        for(int i = 1; i < n; i++){
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + arr[i][0];

            dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = min(dp[i][1], dp[i - 1][2]);
            dp[i][1] = min(dp[i][1], dp[i][0]) + arr[i][1];

            dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]);
            dp[i][2] = min(dp[i][2], dp[i][1]) + arr[i][2];

        }
        cout << testcase << ". " << dp[n - 1][1] << '\n';
        testcase++;

    }


    return 0;
}