#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int solution(vector<vector<int>> routes) {
    int answer = 0;
    
    vector<pair<int, int>> v;
    
    for(int i = 0; i < routes.size(); i++){
        v.push_back({routes[i][0], routes[i][1]});
    }
    
    sort(v.begin(), v.end());
    
  
    int idx = -40000;
    
    for(auto e : v){
        if(idx < e.first){
            answer++;
            idx = e.second;
        }
        else{
            if(e.second < idx)
                idx = e.second;
        }
    }
    return answer;
}