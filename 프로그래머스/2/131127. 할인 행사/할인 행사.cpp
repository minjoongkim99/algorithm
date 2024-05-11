#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

map<string, int> m;
int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    
    for(int i = 0; i < want.size(); i++){
        m[want[i]] = number[i];
    }
    


    for(int i = 0; i <= discount.size() - 10; i++){
        map<string,int> temp;
        temp = m;
        for(int j = i; j < i + 10; j++){
            if(temp.find(discount[j]) != temp.end()){
                temp[discount[j]]--;
            }
            else continue;
        }
        
        int flag = 0;
        for(auto e : temp){
            if(e.second > 0){
                flag = 1;
                break;
            }
        }
        //cout << flag << "\n";
        if(flag == 0){
            answer++;
        }
        //cout << "\n";
    } 
    return answer;
}