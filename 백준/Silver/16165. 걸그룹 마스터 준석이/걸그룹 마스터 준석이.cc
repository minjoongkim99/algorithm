#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(){
    cin.tie(NULL);  cout.tie(NULL);
    unordered_map<string, string > team;
    unordered_map<string, vector<string>> ans;
    int n, m;
    cin >> n >> m;

    for(int i = 0; i < n; i++){
        string group;
        int num;
        cin >> group >> num;
        for(int j = 0; j < num; j++){
            string member;
            cin >> member;
            team[member] = group;
            ans[group].push_back(member);
        }
    }

    for(int i = 0; i < m; i++){
        string name;
        int type;
        cin >> name >> type;

        if(type == 0){
            sort(ans[name].begin(), ans[name].end());
            for(auto e : ans[name]){
                cout << e << "\n";
            }
        }
        else if(type == 1){
            cout << team[name] << "\n";
        }
    }

    //for(auto e: ans){
    //    for(int i = 0; i < e.second.size(); i++){
    //        cout << e.second[i] << " ";
    //        }
    //    cout << "\n";
    //}
    return 0;
}