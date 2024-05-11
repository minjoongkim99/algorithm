#include <string>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;
// d    l   r   u
int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, -1, 1, 0};
int N, M, X, Y, R, C, K;
string answer = ""; // output
int flag = 0;

void dfs(int x, int y, int k , string ans){
    if(flag) return;
    if(abs(R - x) + abs(C - y) > K - k)return;
    if(k == K){
        if(x == R && y == C){
            flag = 1;               //
            answer = ans;           //
        }
        return;                     //
    }
    
    for(int i = 0; i < 4; i++){
        int xx = x + dx[i];
        int yy = y + dy[i];
        if(xx < 1 || xx > N || yy < 1 || yy > M) continue;
        if(i == 0)  
            dfs(xx, yy, k + 1, ans + "d");
        else if(i == 1) 
            dfs(xx, yy, k + 1, ans + "l");
        else if(i == 2) 
            dfs(xx, yy, k + 1, ans + "r");
        else if(i == 3) 
            dfs(xx, yy, k + 1, ans + "u");
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    N = n;  M = m;  X = x;  Y = y;  R = r;  C = c; K = k;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);
    // cur : X, Y
    
    //가지치기 끝판왕.
    // if 조건 하나 더로 더 가지 칠 수 있음.
    if(((abs(x - r) + abs(y - c)) % 2) != (k % 2)) return "impossible";
    // 핵심 가지치기. 시작부터 가지친다. 에초에 안되는 것 거름..
    
    dfs(X, Y, 0, "");       // BackTracking!    알파벳순의 DFS!
    if(answer == "") answer = "impossible";
    
    return answer;
}