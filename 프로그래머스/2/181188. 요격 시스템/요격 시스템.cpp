#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<vector<int>> T;

int solution(vector<vector<int>> targets) {
    int answer = 0;
   
    for(auto e : targets){
        T.push_back({e[1], e[0]});
    }
    sort(T.begin(), T.end());
    /*
    for(auto e : T){
        for(auto e1 : e){
            cout << e1 << ' ';
        }
        cout << '\n';
    }*/
    
    int idx = -1;
    for(auto e : T){
        if(e[1] >= idx){
            idx = e[0];
            cout << idx << "!\n";
            answer++;
        }
    }
    return answer;
}