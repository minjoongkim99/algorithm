#include <string>
#include <vector>
#include <iostream>
using namespace std;
int finished[103];

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    
    vector<int> answer;
    int k = progresses.size();
    int flag = 0;
    
    
    for(int i = 0 ; i < 101; i++){
        
        for(int j = 0 ; j < k; j++){
            progresses[j] += speeds[j];
            if(progresses[j] >= 100){
                finished[j] = 1;
            }
        }
        
        int cnt = 0;
        for(int j = flag; j <= k; j++){
           
            if(finished[j] == 1){
                cnt++;
            }
            
            else if(finished[j] == 0){
                if(cnt != 0){
                    answer.push_back(cnt);
                    flag = j;
                }
                break;
            }
        }
    }
    
    return answer;
}