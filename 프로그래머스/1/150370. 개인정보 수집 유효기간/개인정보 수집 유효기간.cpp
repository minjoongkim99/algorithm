#include <string>
#include <vector>
#include <iostream>
using namespace std;

int findDueDate(char c, const vector<string> terms){
    for(int i = 0; i < terms.size(); i++){
        if(c == terms[i][0]){
            string str = terms[i].substr(2);
            //cout << str << "\n";
            return stoi(str);
        }
    }
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    
    for(int idx = 0; idx < privacies.size(); idx++){
        int year = stoi(privacies[idx].substr(0, 4));
        int month = stoi(privacies[idx].substr(5, 2));
        int day = stoi(privacies[idx].substr(8, 2));
        char contract = privacies[idx].back();
        
        int plus = findDueDate(contract, terms);
        day--;
        if(day == 0){
            month--;
            day = 28;
            if(month == 0){
                year--;
                month = 12;
            }
        }
        
        int plusYear = plus / 12;
        int plusMonth = plus % 12;
        cout << plusYear << ", " << plusMonth << " : ";
        
        month += plusMonth;
        if(month > 12){
            month = month % 12;
            year++;
        }
        year += plusYear;
        
        if(year < stoi(today.substr(0, 4))){
            answer.push_back(idx + 1);
        }
        else if(year == stoi(today.substr(0, 4))){
            if(month < stoi(today.substr(5, 2))){
                answer.push_back(idx + 1);
            }
            else if(month == stoi(today.substr(5, 2))){
                if(day < stoi(today.substr(8, 2)))
                    answer.push_back(idx + 1);
            }
        }
        //cout << year << " " << month << " " << day << " " << contract << "\n";
    }
    return answer;
}