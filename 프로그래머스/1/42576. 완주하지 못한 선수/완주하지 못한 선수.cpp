#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

string solution(vector<string> p, vector<string> c) {
    ios_base::sync_with_stdio(false);
    
    string answer = "";
    unordered_map<string, int> m;
    
    for(int i = 0; i < p.size(); i++){
        m[p[i]]++;
    }
    
    for(int i = 0; i < c.size(); i++){
        m[c[i]]--;
    }
    
    for(auto e : m){
        if(e.second > 0){
            answer = e.first;
            break;
        }
        else continue;
    }
    
    return answer;
}