#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
int a[5] = {1,2,3,4,5};
int b[8] = {2,1,2,3,2,4,2,5};
int c[10] = {3,3,1,1,2,2,4,4,5,5};
vector<int> a1, b1, c1;
vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    
    for(int i = 0; i < answers.size(); i++){
        
        a1.push_back(a[i % 5]);
        b1.push_back(b[i % 8]);
        c1.push_back(c[i % 10]);
    }
    
    int idx[4] = {};
 
    for(int i = 0; i < answers.size(); i++){
        if(answers[i] == a1[i])
            idx[1]++;
        if(answers[i] == b1[i])
            idx[2]++;
        if(answers[i] == c1[i])
            idx[3]++;     
    }
    
    int ret = max(max(idx[1], idx[2]), idx[3]);
    for(int i = 1; i <= 3; i++){
        if(ret == idx[i])
            answer.push_back(i);
    }
    return answer;
}