#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

unordered_map<char ,int> result;

string solution(vector<string> survey, vector<int> choices) {
    string answer = "";
    
    for(int i = 0; i < (int)survey.size(); i++){
        string str = survey[i];
        int point = choices[i];
        if(point == 1) result[str[0]] += 3;
        if(point == 2) result[str[0]] += 2;
        if(point == 3) result[str[0]] += 1;
        if(point == 5) result[str[1]] += 1;
        if(point == 6) result[str[1]] += 2;
        if(point == 7) result[str[1]] += 3;
        
    }
    
    for(auto e : result){
        cout << e.first << " " << e.second << "\n";
    }
    
    if(result['R'] >= result['T'])
        answer += 'R';
    else answer += 'T';
    
    if(result['C'] >= result['F'])
        answer += 'C';
    else answer += 'F';
    
    if(result['J'] >= result['M'])
        answer += 'J';
    else answer += 'M';
    
    if(result['A'] >= result['N'])
        answer += 'A';
    else answer += 'N';
    
    return answer;
}