#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(vector<int> bandage, int health, vector<vector<int>> attacks) {
    int answer = 0;
    answer = health;
    
    int flag = 0;

    int len = attacks.size();
    int idx = 0;
    for(int i = 1; i <= attacks[len - 1][0]; i++){
        if(attacks[idx][0] == i){
            flag = 0;
            answer -= attacks[idx][1];
            idx++;
            if(answer <= 0)
                return -1;
        }
        else{
            if(answer + bandage[1] <= health){
                answer += bandage[1];
            }
            else answer = health;
            
            flag++;
            if(flag == bandage[0]){
                if(answer + bandage[2] <= health){
                    answer += bandage[2];
                }
                else answer = health;
                flag = 0;
            }
        }
    }
    
    return answer;
}