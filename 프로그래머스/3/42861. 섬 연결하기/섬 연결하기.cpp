#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
using namespace std;

int parent[102];

int getParent(int a) {
    if (parent[a] == a) return a;
    else return parent[a] = getParent(parent[a]);
}

void unionParent(int a, int b) {
    int x = getParent(a);
    int y = getParent(b);
    
    if(x == y)
        return;
    else if(x > y){
        parent[x] = y;
    }
    else{
        parent[y] = x;
    }
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    for (int i = 1; i <= n; i++)
        parent[i] = i;
        
    vector<tuple<int, int, int>> v;
    
    for (int i = 0; i < costs.size(); i++) {
        v.push_back({costs[i][2], costs[i][0], costs[i][1]});
    }
    
    sort(v.begin(), v.end());
    
    int len = 0;
    for (int i = 0; i < v.size(); i++) {
        if (len == n - 1) {
            break;
        }
        int dist, a, b;
        tie(dist, a, b) = v[i];
        if (getParent(a) != getParent(b)) {
            unionParent(a, b);
            answer += dist;
            len++;
        }
    }
    
    return answer;
}
