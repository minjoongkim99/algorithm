#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int arr[1002];
int dp[1002];
int pre[1002];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);    cout.tie(nullptr);

    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        dp[i] = 1;
        pre[i] = i;
    }

    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(arr[i] > arr[j]){
                if(dp[j] + 1 > dp[i]){
                    dp[i] = dp[j] + 1;
                    pre[i] = j;
                }
            }
            else continue;
        }
    }

    int idx = -1;
    int mx = 0;
    for(int i = 0; i < n; i++){
        if(dp[i] > mx){
            mx = dp[i];
            idx = i;
        }
    }

    vector<int> v;
    v.push_back(arr[idx]);
    while(true){
        if(pre[idx] == idx) break;
        v.push_back(arr[pre[idx]]);
        idx = pre[idx];
    }

    reverse(v.begin(), v.end());

    cout << mx << '\n';
    for(auto e : v){
        cout << e << ' ';
    }
    cout << '\n';
    return 0;
}