#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int k, l;
int main(){

    cin >> k >> l;
    unordered_map<string ,int> m;

    for(int i = 0; i < l; i++){
        string name;
        cin >> name;
        if(m.find(name) != m.end()){
            m.erase(name);
            m[name] = i;
        }
        else m[name] = i;
    }

    vector<pair<int,string>> v;

    for(auto e: m){
        //cout << e.first << " " << e.second << "\n";
        v.push_back({e.second, e.first});
    }

    sort(v.begin(), v.end());
    for(auto e : v){
        //cout << e.first << " " << e.second << "\n";
    }

    int len = min(k, (int)v.size());
    for(int i = 0; i < len; i++){
        cout << v[i].second << '\n';
    }

    return 0;
}