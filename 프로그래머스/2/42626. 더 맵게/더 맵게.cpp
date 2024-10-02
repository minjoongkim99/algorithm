#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<>> pq;
    for(int val : scoville){
        pq.push(val);
    }
    
    while(pq.size() > 1){
        int x = pq.top();
        if(x >= K) break;
        pq.pop();
    
        int y = pq.top();
        //cout << x << " and " << y << "\n";
        pq.pop();
        pq.push(x + y * 2);
        answer++;
        if(pq.size() < 2) break;
    }
    
    if(pq.top() < K)
        answer = -1;
    return answer;
}