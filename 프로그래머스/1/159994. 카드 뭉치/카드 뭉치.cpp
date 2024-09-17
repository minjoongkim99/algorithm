#include <string>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
queue<string> b1;
queue<string> b2;

bool check(const vector<string> cards1, const vector<string> cards2){
    for(int i = 0; i < cards1.size(); i++){
        if(b1.empty()) break;
        if(cards1[i] == b1.front()){
            b1.pop();
        }
        else break;
    }
    for(int i = 0; i < cards2.size(); i++){
        if(b2.empty()) break;
        if(cards2[i] == b2.front()){
            b2.pop();
        }
        else break;
    }
    
    if(b2.empty() && b1.empty()) return true;
    else return false;
}

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) {
    string answer = "";
    
    for(int i = 0; i < goal.size(); i++){
        for(int j = 0; j < cards1.size(); j++){
            if(goal[i] == cards1[j]){
                b1.push(goal[i]);
            }
        }
        for(int j = 0; j < cards2.size(); j++){
            if(goal[i] == cards2[j]){
                b2.push(goal[i]);
            }
        }
    }

    if(check(cards1, cards2)){
        answer = "Yes";
    }
    else answer = "No";
    return answer;
}