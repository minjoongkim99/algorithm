#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int arr[302][302];
int sum[302][302];
int ans = -1000000000;
int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> arr[i][j];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
        }
    }

    for(int len = 0; len < n; len++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(i + len > n || j + len > n) continue;
                int val = sum[i + len][j + len] - sum[i + len][j - 1] - sum[i - 1][j + len] + sum[i - 1][j - 1];
                if(ans < val)
                    ans = val;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}