#include <string>
#include <vector>

using namespace std;

int ret;
int visited[10];

void backtracking(int cnt, int power, vector<vector<int>> &dungeons){
    if(power < 0)   return;
    
    if(cnt > ret){
        ret = cnt;
    }
    
    for(int i = 0; i < dungeons.size(); i++){
        
        if(visited[i])  continue;
        if(dungeons[i][0] > power)  continue;
        
        visited[i] = 1;
        backtracking(cnt + 1, power - dungeons[i][1], dungeons);
        visited[i] = 0;
    }
}

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    
    backtracking(0, k, dungeons);
    
    answer = ret;
    return answer;
}