#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <iostream>
using namespace std;

vector<string> solution(vector<string> record) {
    ios_base::sync_with_stdio(false);
    
    vector<string> answer;
    unordered_map<string, string> m;
    vector<pair<string, string>> v;
    
    for(const string & s : record){
        stringstream ss(s);
        string query, uid, nickname;
        ss >> query >> uid >> nickname;
    
        if(query == "Enter"){
            m[uid] = nickname;
            v.push_back({query, uid});
        }
        else if(query == "Leave"){
            v.push_back({query, uid});
        }
        else{
            m[uid] = nickname;
        }
    }
        
    for(auto e : v){
        if(e.first == "Enter"){
            answer.push_back(m[e.second] + "님이 들어왔습니다.");   
        }
        else{
            answer.push_back(m[e.second] + "님이 나갔습니다.");
        }
    }
    return answer;
}