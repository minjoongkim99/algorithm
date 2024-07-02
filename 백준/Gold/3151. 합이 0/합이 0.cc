#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);    cin.tie(nullptr);
    
    cin >> n;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    
    sort(v.begin(), v.end());    // vector 먼저 정렬.

    long long ans = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            long long ub = upper_bound(v.begin() + j + 1, v.end(), -v[i] - v[j]) - v.begin();
            long long lb = lower_bound(v.begin() + j + 1, v.end(), -v[i] - v[j]) - v.begin();
            // ub == lb 의 의미는? ub = lb + 2의 의미는?
            // lower_bound, upper_bound 활용해서 길이 찾기?
            if(ub - lb > 0) {
                ans += ub - lb;
            }
            else continue;
        }
    }
    // i, j 로 기준 설정을 돌리는 것임. 2중 for문과 bound 이분탐색 O(n^2*logn).
    // i, j, x. x를 찾아보자!
    cout << ans;
    return 0;
}