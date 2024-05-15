#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
using namespace std;
vector<int> v;
int solution(int k, vector<int> t) {
    // k 한 상자에 담으려는 귤의 개수.
    // answer : 서로 다른 종류의 수.
    int answer = 0;
    unordered_map <int, int> m;
    sort(t.begin(), t.end());
    for(auto e : t){
        m[e]++;
    }
    
    priority_queue<int> pq;
    for(auto e: m){
        pq.push(e.second);
    }
    
    while(!pq.empty()){
        if(k <= 0) break;
        //cout << k << " and " << pq.top() << "\n";
        k -= pq.top();
        answer++;
        pq.pop();
    }
    return answer;
}