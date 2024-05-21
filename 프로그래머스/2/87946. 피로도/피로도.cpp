#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<vector<int>> d;
int visited[10];
int ret;
void dfs(int cnt, int hp){
    if(hp <= 0){
        if(ret < cnt)
            ret = cnt;
    }
    int flag = 0;
    for(int i = 0; i < d.size(); i++){
        if(hp >= d[i][0] && !visited[i]){
            flag = 1;
            visited[i] = 1;
            dfs(cnt + 1, hp - d[i][1]);
            visited[i] = 0;
        }
    }
    if(flag == 0) {
        if(cnt > ret)
            ret = cnt;
    }
    
}

int solution(int k, vector<vector<int>> dungeons) {
    int answer = -1;
    d = dungeons;
    // 최소 필요피로도, 소모 피로도
    
    dfs(0, k); // 탐험 개수. 현재 체력.
    answer = ret;
    return answer;
}