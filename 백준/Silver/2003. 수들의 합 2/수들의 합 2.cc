#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
int ans = 0;
int a[10002];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);

    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> a[i];

    int st = 0, en = 0;
    int ret = 0;

    int sum = a[0];
    //if(sum == m) ret++;

    for(st = 0; st < n; st++){
        if(sum == m){
            ret++;
        }
        while(en < n && sum < m){
            en++;
            if(en == n)
                break;

            sum += a[en];
            if(sum == m){
                //cout << st << " " << en << "\n";
                ret++;
            }
        }

        sum -= a[st];
    }

    cout << ret << "\n";
    return 0;
}