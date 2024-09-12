#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int arr[100002];
int idx[100002];
int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);    cin.tie(nullptr);
    
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> m;
    for(int i = 0; i < m; i++)
        cin >> idx[i];
    sort(arr, arr + n);

    for(int i = 0; i < m; i++){
        int ans = binary_search(arr, arr + n, idx[i]);
        cout << ans << '\n';
    }
    return 0;
}