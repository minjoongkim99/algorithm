#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<string, int> um;
string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    
    for(string str : participant){
        um[str]++;
    }
    for(string str : completion){
        um[str]--;
    }
    
    for(auto e : um){
        if(e.second == 1){
            answer = e.first;
            break;
        }
    }
    
    return answer;
}