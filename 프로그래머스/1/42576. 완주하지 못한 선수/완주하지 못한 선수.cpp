#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

string solution(vector<string> p, vector<string> c) {
    string answer = "";
    
    map<string, int> m;
    for(int i = 0; i < p.size(); i++){
        m[p[i]]++;
    }
    
    for(int i = 0; i < c.size(); i++){
        m[c[i]]--;
        if(m[c[i]] == 0){
            m.erase(m.find(c[i]));
        }
    }
    
    cout << m.begin() -> first;
    answer = m.begin() -> first;
    return answer;
}