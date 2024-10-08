#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
using namespace std;

unordered_map <string ,int> visited;

int bfs(string begin, string target, vector<string> words){
    queue<string> q;
    q.push(begin);
    visited[begin] = 1;
    
    while(!q.empty()){
        string x = q.front();
        q.pop();
        
        for(string str : words){
            if(visited.find(str) != visited.end()) continue;
            int cnt = 0;
            for(int j = 0; j < str.size(); j++){
                if(x[j] != str[j])
                    cnt++;
            }
            if(cnt == 1){
                q.push(str);
                visited[str] = visited[x] + 1;
            }
            
        }
    }
    if(visited.find(target) != visited.end()) return visited[target] - 1;
}

int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    int flag = 0;
    for(string str : words){
        if(str == target) 
            flag = 1;
    }
    if(flag == 0) return 0;

    answer = bfs(begin, target, words);
    return answer;
}