#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

int arr[30002];
int n, d, k, c;
int ret = 0;
int main(){

    cin >> n >> d >> k >> c;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    map<int,int> m;

    for(int i = 0; i < k; i++){
        m[arr[i]]++;
    }


    int st = 0; int en = k - 1;
    while(st < n){
        
        en = (en + 1) % n;
        m[arr[en]]++;

        m[arr[st]]--;
        if(m[arr[st]] == 0){
            m.erase(arr[st]);
        }
        st++;

        m[c]++;      
        
        if(m.size() > ret){
            ret = m.size();
        }
        
        m[c]--;
        if(m[c] == 0)
            m.erase(c);

    }

    cout << ret;
    return 0;
}
