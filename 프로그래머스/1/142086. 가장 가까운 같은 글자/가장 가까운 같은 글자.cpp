#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(string s) {
    vector<int> answer;
    vector<int> arr(26, -1);
    
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        int idx = (int)(c - 'a');
        
        if(arr[idx] == -1){
            answer.push_back(-1);
            arr[idx] = i;
        }
        else{
            answer.push_back(i - arr[idx]);
            arr[idx] = i;
        }
    }
    return answer;
}