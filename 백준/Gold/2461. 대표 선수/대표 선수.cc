#include <iostream>

#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int arr[1002][1002];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);    cout.tie(nullptr);
    cin >> n >> m;
    vector<int> v(n, 0);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> arr[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        sort(arr[i], arr[i] + m);
    }

    int ans = 2000000000;
    while (true) {
        int idx1, idx2;
        
        int mx = -1, mn = 2000000000;
        for (int i = 0; i < n; i++) {
            if (mn > arr[i][v[i]]) {
                mn = arr[i][v[i]];
                idx1 = i;
            }
            if (mx < arr[i][v[i]]) {
                mx = arr[i][v[i]];
                idx2 = i;
            }
            
        }

        ans = min(ans, mx - mn);
        v[idx1]++;

        if (v[idx1] >= m)
            break;
    }

    cout << ans;
}