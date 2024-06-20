#include <iostream>
#include <vector>

using namespace std;

int n, s;
int arr[100003];
int pSum[100003];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);

    cin >> n >> s;

    for(int i = 1; i <= n; i++){
        cin >> arr[i];
        pSum[i] = arr[i] + pSum[i - 1];
    }

    int len = 2000000000;
    int en = 0;
    for(int st = 0; st < n; st++){

        while(en <= n && pSum[en] - pSum[st] < s){
            en++;
        }

        if(en == n + 1) break;      // out of index 처리.

        //cout << st << " " << en << "\n";
        if(en - st < len && pSum[en] - pSum[st] >= s){
            len = en - st;
        }
    }
    if(len == 2000000000){
        cout << 0 << "\n";
    }
    else cout << len << "\n";
    return 0;
}