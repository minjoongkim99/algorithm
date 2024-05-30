#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> solution(vector<string> players, vector<string> callings) {
    
    vector<string> answer;
    unordered_map<string, int> m;
    
    for(int i = 0; i < (int)players.size(); i++){
        m[players[i]] = i;
    }
    
    for(auto e : callings){
        int cur = m[e];
        string tmp = players[cur];
        
        players[cur] = players[cur - 1];
        players[cur - 1] = tmp;
        
        m[players[cur - 1]] = cur - 1;
        m[players[cur]] = cur;
    }
    
    return players;
}