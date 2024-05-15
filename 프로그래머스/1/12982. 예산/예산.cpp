#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int solution(vector<int> d, int budget) {
    int answer = 0;
    sort(d.begin(), d.end());
    
    for(int i = 0 ; i < (int)d.size(); i++){
        if(budget - d[i] < 0) break;
        
        else{
            budget -= d[i];
            answer++;
        }
    }
    return answer;
}