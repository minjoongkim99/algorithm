#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int k, l;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);
    cin >> k >> l;
    unordered_map<string ,int> m;

    for(int i = 0; i < l; i++){
        string name;
        cin >> name;
        m[name] = i;
    }

    vector<pair<int,string>> v;

    for(auto e: m){
        v.push_back({e.second, e.first});
    }

    sort(v.begin(), v.end());
   
    int len = min(k, (int)v.size());
    for(int i = 0; i < len; i++){
        cout << v[i].second << '\n';
    }

    return 0;
}