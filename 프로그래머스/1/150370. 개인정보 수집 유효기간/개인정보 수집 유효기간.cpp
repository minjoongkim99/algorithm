#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;
map<string, int> m;

void typeConvert(const vector<string> &terms){
      for(int i = 0; i < terms.size(); i++){
        string type = terms[i].substr(0, 1);
        string len = terms[i].substr(2);
        m[type] = stoi(len);
    }
}
vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vector<int> answer;

    int Y = stoi(today.substr(0, 4));
    int M = stoi(today.substr(5, 2));
    int D = stoi(today.substr(8, 2));
 
    typeConvert(terms);
    
    for(int i = 0; i < privacies.size(); i++){

        int year = stoi(privacies[i].substr(0, 4));
        int month = stoi(privacies[i].substr(5, 2));
        int day = stoi(privacies[i].substr(8, 2));
        string type = privacies[i].substr(11);;
        
        int len = m[type];
        
        int n_year = year + (month + len - 1) / 12;
        int n_month = (month + len - 1) % 12 + 1;

        if(Y > n_year)
            answer.push_back(i + 1);
        else if(Y == n_year){
            if(M > n_month){
                answer.push_back(i + 1);
            }
            else if(M == n_month){
                if(D >= day)
                    answer.push_back(i + 1);
            }
        }
        
    }
    
    return answer;
}