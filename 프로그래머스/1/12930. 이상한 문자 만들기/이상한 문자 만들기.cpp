#include <string>
#include <vector>
#include <cctype>
#include <iostream>
using namespace std;

string solution(string s) {
    string answer = "";
    int idx = 0;
    
    vector<string> str;
    
    for(int i = 0; i < s.size(); i++){
        if(s[i] == ' '){
            str.push_back(s.substr(idx, i - idx + 1));
            idx = i + 1;
            
        }
    }
    str.push_back(s.substr(idx));
    

    
    for(int i = 0; i < str.size(); i++){
        for(int j = 0; j < str[i].size(); j++){
            if(j % 2 == 0){
                if(islower(str[i][j]))
                    str[i][j] = toupper(str[i][j]);
            }
            if(j % 2 == 1){
                if(isupper(str[i][j]))
                    str[i][j] = tolower(str[i][j]);
            }
        }
    }
    
    for(auto e : str){
        answer += e;
        //answer += ' ';
    }
    //answer.pop_back();
    return answer;
}