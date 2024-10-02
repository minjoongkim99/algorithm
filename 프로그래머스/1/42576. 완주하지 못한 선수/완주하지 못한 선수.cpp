#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map<string, int> m;
    for(auto str : participant)
        m[str]++;
    for(auto str : completion){
        m[str]--;
    }
    for(auto e : m){
        if(e.second == 1){
            answer = e.first;
            break;
        }
    }
    return answer;
}