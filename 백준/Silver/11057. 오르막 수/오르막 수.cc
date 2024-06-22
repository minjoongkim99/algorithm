#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int dp[1010][10];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 0; i < 10; i++){
        dp[1][i] = 1;
    }

    for(int i = 2; i <= n; i++){

        for(int j = 0; j < 10; j++){
            for(int k = 0; k <= j; k++){
                dp[i][j] = (dp[i][j] + dp[i - 1][k]) % 10007;
            }
        }

    }

    int ret = 0;
    for(int i = 0; i < 10; i++){
        ret += dp[n][i];
        ret %= 10007;
    }
    cout << ret << "\n";
    return 0;
}
