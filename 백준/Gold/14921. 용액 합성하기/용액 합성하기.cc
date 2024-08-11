#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int a[100005];
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);

    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int ans = 1000000000;
    for(int i = 0; i < n; i++){
        auto idx = lower_bound(a, a + n, -a[i]) - &a[0];
        //cout << i << " : ";
        //cout << idx - 1 << " " << idx  << " " << idx + 1 << "\n";

        if(idx - 1 >= 0 && idx - 1 != i){
            int sum = a[i] + a[idx - 1];
            if(abs(sum) < abs(ans)){
                ans = sum;
            }
        }
        if(idx < n && idx != i){
            int sum = a[i] + a[idx];
            if(abs(sum) < abs(ans)){
                ans = sum;
            }
        }
        if(idx + 1 < n && idx + 1 != i){
            int sum = a[i] + a[idx + 1];
            if(abs(sum) < abs(ans)){
                ans = sum;
            }
        }
    }

    cout << ans << "\n";
}