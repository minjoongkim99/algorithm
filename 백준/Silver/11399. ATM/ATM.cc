#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> v(n ,0), pSum(n, 0);
    
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    sort(v.begin(), v.end());


    
    pSum[0] = v[0];

    for(int i = 1; i < n; i++){
        pSum[i] = pSum[i - 1] + v[i];
    }

    int ret = 0;
    for(auto e : pSum){
        ret += e;
    }
    cout << ret << "\n";
}
