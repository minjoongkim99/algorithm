#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;


vector<pair<string, string >> query;
map<string, string> m; // uuid name

vector<string> solution(vector<string> record) {
    vector<string> answer;

    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    for(int i = 0; i < record.size(); i++){
        string a, b, c;
        
        stringstream ss(record[i]);
     
        ss >> a >> b >> c;
       
        if(a == "Enter"){
            string ret = c + "님이 들어왔습니다.";
            m[b] = c;
            query.push_back({a, b});
        }
        else if(a == "Leave"){
            query.push_back({a, b});
        }
        else if(a == "Change"){
            m[b] = c;
        }
    }
    
    for(int i = 0; i < query.size(); i++){
        string a = query[i].first;
        string b = query[i].second;
        if(a == "Enter"){
            string ret = m[b] + "님이 들어왔습니다.";
            answer.push_back(ret);
        }
        else if(a == "Leave"){
            string ret = m[b] + "님이 나갔습니다.";
            answer.push_back(ret);
        }
    }
    return answer;
}