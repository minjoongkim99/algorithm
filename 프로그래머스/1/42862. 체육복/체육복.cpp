#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int have[32];
int resv[32];

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    
    sort(lost.begin(), lost.end());
    sort(reserve.begin(), reserve.end());
    fill(&have[0], &have[0] + 32, 1);
    
    for(auto e : lost){
        have[e] = 0;
    }
    for(auto e: reserve){
        resv[e] = 1;
    }
    
    for(auto e : lost){
        if(resv[e] == 1){
            resv[e] = 0;
            have[e] = 1;
        }
    }
    
    for(auto e : lost){

        if(e - 1 > 0 && resv[e - 1] == 1 && have[e] == 0){
            resv[e - 1] = 0;
            have[e] = 1;
        }
        else if(e + 1 <= n && resv[e + 1] == 1 && have[e] == 0){
            resv[e + 1] = 0;
            have[e] = 1;
        }
    }
    
    for(int i = 1; i <= n; i++){
        if(have[i])
            answer++;
    }
    return answer;
}