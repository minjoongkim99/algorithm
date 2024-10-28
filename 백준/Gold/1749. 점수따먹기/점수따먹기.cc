#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int arr[203][203];
int prefix_sum[203][203];
int n, m;

int ans = -100000000;
int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);  cin.tie(nullptr);

    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> arr[i][j];
            prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1] + arr[i][j];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = i; k <= n; k++){
                for(int l = j; l <= m; l++){
                    int val = prefix_sum[k][l] - prefix_sum[i - 1][l] - prefix_sum[k][j - 1] + prefix_sum[i - 1][j - 1];
                    if(val > ans)
                        ans = val;
                    else continue;
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}