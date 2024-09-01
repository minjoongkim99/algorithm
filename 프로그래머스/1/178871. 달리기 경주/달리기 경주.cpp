#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

unordered_map<string, int> m;
unordered_map<int, string> im;
vector<string> solution(vector<string> players, vector<string> callings) {
    vector<string> answer;
    
    for(int i = 0; i < players.size(); i++){
        m[players[i]] = i;
        im[i] = players[i];
    }
    
    for(auto e : callings){
        int cur = m[e];
        
        string p1 = im[cur - 1];
        string p2 = e;
        
        m[p1] = cur;
        im[cur] = p1;
        
        m[p2] = cur - 1;
        im[cur - 1] = p2;
    }
    
    for(int i = 0; i < players.size(); i++){
        answer.push_back(im[i]);
    }
    return answer;
}