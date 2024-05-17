#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
using namespace std;

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;
    
    unordered_map<string, unordered_set<string>> attack;
    unordered_map<string, int> cnt;
    
    for(auto s : report){
        stringstream ss(s);
        string src , dst;
        ss >> src >> dst;
        attack[dst].insert(src);
    }
    
    for(auto &[attacked, user_list] : attack){
        if(user_list.size() < k) continue;
        for(auto e: user_list){
            cnt[e]++;
        }
    }
    
    for(int i = 0; i < id_list.size(); i++){
        answer.push_back(cnt[id_list[i]]);
    }
    return answer;
}