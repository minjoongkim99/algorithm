#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
int cnt[103];
int solution(vector<int> priorities, int location) {
    int answer = 0;
    priority_queue<int> pq;
    queue<int> q;
    for(int i = 0; i < priorities.size(); i++){
        pq.push(priorities[i]);
        q.push(i);
    }
    
    int t = 1;
    while(!q.empty()){
        int x = q.front();
        q.pop();
        if(pq.top() == priorities[x]){
            cnt[x] = t++;
            pq.pop();
        }
        else q.push(x);
    }
    
    return answer = cnt[location];
}