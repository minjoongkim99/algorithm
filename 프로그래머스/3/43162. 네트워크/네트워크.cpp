#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;
int n;
int parent[203];

int getParent(int a){
    if(parent[a] == a) return a;
    else return parent[a] = getParent(parent[a]);
}

void unionParent(int a, int b){
    int x = getParent(a);
    int y = getParent(b);
    
    if(x != y){
        parent[y] = x;
    }
  
}

int solution(int N, vector<vector<int>> computers) {
    int answer = 0;
    n = N;
    for(int i = 0; i < n; i++)
        parent[i] = i;
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(computers[i][j]){
                unionParent(i, j);
            } 
        }
    }
    
    unordered_map<int, bool> m;
    
    for(int i = 0; i < n; i++){
        int root = getParent(i);
        if(!m[root]){
            answer++;
            m[root] = true;
        }
    }
    return answer;
}