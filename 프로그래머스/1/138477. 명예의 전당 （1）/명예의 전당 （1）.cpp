#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> solution(int k, vector<int> score) {
    vector<int> answer;
    
    priority_queue<int, vector<int>, greater<int>> pq;
    
    for(auto e : score){
        pq.push(e);
        
        if(pq.size() == k + 1)
            pq.pop();
        answer.push_back(pq.top());
    }
    return answer;
}