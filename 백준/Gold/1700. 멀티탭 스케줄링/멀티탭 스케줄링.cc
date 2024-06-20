#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int n, k;
int arr[102];
vector<int> tab;
int cnt = 0;

bool isIn(int cur){
    for(int i = 0; i < (int)tab.size(); i++){
        if(tab[i] == cur){
            return true;
        }
    }
    return false;
}

void replacementPolicy(int element, int nxt){
    int mx = -1, idx = -1;
    
    for(int i = 0; i < (int)tab.size(); i++){
        int localMax = 100000;
        
        for(int j = nxt; j <= k; j++){

            if(tab[i] == arr[j]){
                localMax = j;
                break;
            }
        }
        //cout << tab[i] << " ," << localMax << "\n";

        if(localMax > mx){
            mx = localMax;
            idx = i;
        }
    }

    tab[idx] = element;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);   cout.tie(nullptr);
    
    cin >> n >> k;
    for(int i = 1; i <= k; i++){
        cin >> arr[i];
    }

    for(int i = 1; i <= k; i++){
        if(isIn(arr[i])){
            continue;
        }
        else{
            if(tab.size() < n){
                tab.push_back(arr[i]);
            }
            else{
                //cout  << i << " 위치에서 교체정책\n";
                replacementPolicy(arr[i], i + 1);
                cnt++;
            }
        }
    }

    cout << cnt << "\n";
    return 0;
}