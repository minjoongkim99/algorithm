#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

bool solution(vector<string> p) {
    bool answer = true;
    
    sort(p.begin(), p.end());
  
    for(int i = 0; i < p.size() - 1; i++){
        if(p[i] == p[i + 1].substr(0, p[i].size())){
            answer = false;
            break;
        }
            
    }
    return answer;
}