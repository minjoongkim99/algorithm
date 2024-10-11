#include <bits/stdc++.h>
using namespace std;

map<string, int> m;
string solution(vector<string> p, vector<string> c) {
    string answer = "";
    
    for(auto e : p){
        m[e]++;
    }
    for(auto e : c){
        m[e]--;
        if(m[e] == 0)
            m.erase(e);
    }
    
    for(auto e : m){
        answer = e.first;
        break;
    }
    return answer;
}