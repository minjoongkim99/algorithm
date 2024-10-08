#include<string>
#include <iostream>
#include <stack>
using namespace std;

stack <char> ans;
bool solution(string s)
{
    bool answer = true;
    
    if(s.size() < 2) return false;
    for(char c : s){
        if(c == '(')
            ans.push('(');
        else if(c == ')'){
            if(ans.empty() || ans.top() != '('){
                answer = false;
                break;
            }
            ans.pop();
        }
    }
    if(!ans.empty()) answer = false;
    return answer;
}