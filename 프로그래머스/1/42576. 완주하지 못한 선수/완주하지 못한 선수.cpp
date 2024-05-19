#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> p, vector<string> c) {
    
    string answer = "";
    
    unordered_map <string, int> m;
    for(const string &s : p){
        m[s]++;
    }
    
    for(const string &s : c){
        if(m[s] > 0){
            m[s]--;
        }
        if(m[s] == 0){
            m.erase(s);
        }
    }
    
    answer = m.begin()->first;
    return answer;
}