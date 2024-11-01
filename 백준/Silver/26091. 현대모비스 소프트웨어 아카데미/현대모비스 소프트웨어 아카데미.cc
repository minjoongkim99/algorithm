#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, m;
vector<int> v;
int cnt = 0;
int main() {
    ios::sync_with_stdio(0);
    cout.tie(nullptr);				cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        v.push_back(x);
    }
    sort(v.begin(), v.end());
    
    int en = n - 1;
    for(int st = 0; st < n; st++){
        if(en <= st) break;

        while(en >= 0){
            if(v[st] + v[en] >= m){
                cnt++;
                en--;
                break;
            }
            else break;
        }
    }
    cout << cnt << '\n';
    return 0;
}