#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<string, int> given;
unordered_map<string, int> gave;
unordered_map<string, int> point;
 
int solution(vector<string> friends, vector<string> gifts) {
    int answer = 0;
    vector<int> ret(friends.size(), 0);
    vector<vector<int>> table(friends.size(), vector<int>(friends.size(), 0));
    
    for(int i = 0 ; i < gifts.size(); i++){
        for(int j = 0; j < gifts[i].size(); j++){
            if(gifts[i][j] == ' '){
                string a = gifts[i].substr(0, j);
                string b = gifts[i].substr(j + 1);
                //cout << a << " and " << b << "\n";
                for(int u = 0; u < friends.size(); u++){
                   for(int v = 0; v < friends.size(); v++){
                       if(friends[u] == a && friends[v] == b){
                           table[u][v]++;
                       }
                   }
                }
                gave[a]++;
                given[b]++;
            }
        }
    }
    
    for(int i = 0; i < friends.size(); i++){
        for(int j = 0; j < friends.size(); j++){
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }
    
    for(auto e : friends){
        //cout << e << "가 준 것" << gave[e] << " 받은 것: " << given[e];
        point[e] = (gave[e] - given[e]);
        //cout << " 포인트: " << point[e] << "\n";
    }
    
    for(int i = 0; i < friends.size(); i++){
        for(int j = 0 ; j < friends.size(); j++){
            if(i == j) continue;
            if(table[i][j] > table[j][i]){
                ret[i]++;
            }
            else if(table[i][j] == table[j][i]){
                if(point[friends[i]] > point[friends[j]]){
                    ret[i]++;
                }
            }
        }
    }
    
    for(auto e : ret){
        if(answer < e)
            answer = e;
    }
    return answer;
}